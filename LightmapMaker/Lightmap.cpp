#include "Lightmap.h"

//-------------------------------------------------------------------------//

string Lightmap::DirectoryLightmaps = string();
int Lightmap::CountCalculateLightMaps = 0;
int Lightmap::MaxSizeLightmap = 16;
bool Lightmap::IsEnableShadows = true;

//-------------------------------------------------------------------------//

void Lightmap::Generate( vector<Plane>& Planes, vector<PointLight>& PointLights )
{
	CountCalculateLightMaps = 0;
	int CountPlanesForThread = ceil( ( float ) Planes.size() / NUM_THREADS );

	mutex Mutex;
	vector< vector<Plane*> > PlanesForThreads( NUM_THREADS );
	vector<thread> Threads;

	PRINT_LOG( "- Generate Lightmaps" );

	// Разбиваем треугольники для потока
	for ( int i = 0, NumTread = 1; i < Planes.size(); i++ )
	{
		if ( i + 1 > NumTread*CountPlanesForThread )
			NumTread++;

		Plane* Plane = &Planes[ i ];
		PlanesForThreads[ NumTread - 1 ].push_back( Plane );
	}

	// Создаем потоки для просчета освещения
	for ( int i = 0; i < NUM_THREADS; i++ )
		Threads.push_back( thread( &Lightmap::Calculate, ref( Mutex ), i*CountPlanesForThread, ref( PlanesForThreads[ i ] ), ref( Planes ), ref( PointLights ) ) );

	// Ждем завершения всех потоков
	for ( int i = 0; i < NUM_THREADS; i++ )
		Threads[ i ].join();

	PRINT_LOG( "- Lightmaps Generated" );
}

//-------------------------------------------------------------------------//

void Lightmap::EnableShadows( bool Enable )
{
	IsEnableShadows = Enable;
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
		Plane->LightMap.Create( Triangle->SizeLightmap.x, Triangle->SizeLightmap.y );

		for ( float x = 0; x < Triangle->SizeLightmap.x; x++ )
			for ( float y = 0; y < Triangle->SizeLightmap.y; y++ )
			{
				UVFactor = glm::vec2( ( x + 1.f / Triangle->SizeLightmap.x / 2 ) / Triangle->SizeLightmap.x, ( y + 1.f / Triangle->SizeLightmap.y / 2 ) / Triangle->SizeLightmap.y );

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

					if ( IsEnableShadows )
					{
						bool IsIntersect = false;
						for ( size_t IdPlane = 0; IdPlane < Geometry.size() && !IsIntersect; IdPlane++ )
							if ( Geometry[ IdPlane ] != *Triangle )
								IsIntersect = Ray.IntersectTriangle( Geometry[ IdPlane ].Triangles[ 0 ] ) || Ray.IntersectTriangle( Geometry[ IdPlane ].Triangles[ 1 ] );

						if ( IsIntersect ) continue;
					}

					Distance = glm::length( Ray.Direction );
					DiffuseFactor = glm::max( glm::dot( Triangle->Normal, Ray.Normalize_Direction ), 0.0f );
					Attenuation = glm::max( 1.0f - pow( Distance / PointLight->Radius, 2 ), 0.f );

					if ( DiffuseFactor != 0 )
						Color += PointLight->Color * Attenuation;
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