#include "Lightmap.h"
#include "ArgumentsStart.h"

//-------------------------------------------------------------------------//

string Lightmap::DirectoryLightmaps = "";

//-------------------------------------------------------------------------//

void Lightmap::Generate( vector<Plane>& Planes, vector<PointLight>& PointLights )
{
	CountCalculateLightMaps = 0;
	int CountPlanesForThread = ( int ) ceil( ( float ) Planes.size() / ArgumentsStart::NumberThreads );

	mutex Mutex;
	vector< vector<Plane*> > PlanesForThreads( ArgumentsStart::NumberThreads );
	vector<thread> Threads;

	PRINT_LOG( "- Generate Lightmaps" );

	// Разбиваем треугольники для потока
	for ( size_t i = 0, NumTread = 1; i < Planes.size(); i++ )
	{
		if ( i + 1 > NumTread*CountPlanesForThread )
			NumTread++;

		PlanesForThreads[ NumTread - 1 ].push_back( &Planes[ i ] );
	}

	// Создаем потоки для просчета освещения
	for ( int i = 0; i < ArgumentsStart::NumberThreads; i++ )
		Threads.push_back( thread( &Lightmap::Calculate, this, ref( Mutex ), i*CountPlanesForThread, ref( PlanesForThreads[ i ] ), ref( Planes ), ref( PointLights ) ) );

	// Ждем завершения всех потоков
	for ( int i = 0; i < ArgumentsStart::NumberThreads; i++ )
		Threads[ i ].join();

	PRINT_LOG( "- Lightmaps Generated" );
}

//-------------------------------------------------------------------------//

void Lightmap::SetDirectoryForLightmaps( const string& Directory )
{
	DirectoryLightmaps = Directory;
}

//-------------------------------------------------------------------------//

void Lightmap::Calculate( mutex& Mutex, int IdStartPlane, vector<Plane*>& Planes, vector<Plane>& Geometry, vector<PointLight>& PointLights )
{
	float Distance = 0, DiffuseFactor = 0, Attenuation = 0, MaxValue = 0;
	glm::vec2 UVFactor;
	glm::vec3 Newedge1, Newedge2, PositionFragment;
	Ray Ray;

	for ( size_t Id = 0, NumberPlane = IdStartPlane; Id < Planes.size(); Id++, NumberPlane++ )
	{
		Plane* Plane = Planes[ Id ];
		Triangle* Triangle = &Plane->Triangles[ 0 ];
		Plane->LightMap.Create( ( size_t ) Triangle->SizeLightmap.x, ( size_t ) Triangle->SizeLightmap.y );

		for ( float x = 0; x < Triangle->SizeLightmap.x; x++ )
			for ( float y = 0; y < Triangle->SizeLightmap.y; y++ )
			{
				UVFactor = glm::vec2( ( x + 0.5f ) / Triangle->SizeLightmap.x, ( y + 0.5f ) / Triangle->SizeLightmap.y );

				Newedge1.x = Triangle->Edge1.x * UVFactor.x;
				Newedge1.y = Triangle->Edge1.y * UVFactor.x;
				Newedge1.z = Triangle->Edge1.z * UVFactor.x;
				Newedge2.x = Triangle->Edge2.x * UVFactor.y;
				Newedge2.y = Triangle->Edge2.y * UVFactor.y;
				Newedge2.z = Triangle->Edge2.z * UVFactor.y;

				PositionFragment = Triangle->UVVector + Newedge2 + Newedge1;
				glm::vec4 Color;

				for ( size_t IdPointLights = 0; IdPointLights < PointLights.size(); IdPointLights++ )
				{
					PointLight* PointLight = &PointLights[ IdPointLights ];
					Ray.SetRay( PointLight->Position, PositionFragment );
					
					if ( !ArgumentsStart::IsDisableShadow )
					{
						bool IsIntersect = false;
						for ( size_t IdPlane = 0; IdPlane < Geometry.size() && !IsIntersect; IdPlane++ )
							if ( Geometry[ IdPlane ] != *Triangle )
								IsIntersect = Ray.IntersectTriangle( Geometry[ IdPlane ].Triangles[ 0 ] ) || Ray.IntersectTriangle( Geometry[ IdPlane ].Triangles[ 1 ] );

						if ( IsIntersect ) continue;
					}

					Distance = glm::length( Ray.Direction );
					DiffuseFactor = glm::max( glm::dot( Triangle->Normal, Ray.Normalize_Direction ), 0.0f );
					Attenuation = PointLight->CalculateAttenuation( Distance );

					Color += PointLight->Color * Attenuation * DiffuseFactor * PointLight->Intensivity;
				}

				MaxValue = glm::max( Color.x, glm::max( Color.y, Color.z ) );

				if ( MaxValue > 255.f )
				{
					float Value = 255.f / MaxValue;
					Color.x *= Value;
					Color.y *= Value;
					Color.z *= Value;
				}

				Color.w = 255.f;
				Plane->LightMap.SetPixel( ( int ) x, ( int ) y, Color );
			}

		Plane->LightMap.SaveInFile( DirectoryLightmaps + "\\lm_" + to_string( NumberPlane ) + ".png" );

		Mutex.lock();
		CountCalculateLightMaps++;
		PRINT_LOG( "Calculate Lightmaps: " << CountCalculateLightMaps << "/" << Geometry.size() );
		Mutex.unlock();
	}
}

//-------------------------------------------------------------------------//