#include "Lightmap.h"

//-------------------------------------------------------------------------//

string Lightmap::DirectoryLightmaps = string();
int Lightmap::CountCalculateLightMaps = 0;
bool Lightmap::IsEnableShadows = true;

//-------------------------------------------------------------------------//

void Lightmap::Generate( size_t Size, vector<Triangle>& Triangles, vector<PointLight>& PointLights )
{
	CountCalculateLightMaps = 0;
	int CountTrianglesForThread = Triangles.size() / NUM_THREADS;

	mutex Mutex;
	vector< vector<Triangle*> > TrianglesForThreads( NUM_THREADS );
	vector<thread> Threads;

	PRINT_LOG( "- Generate Lightmaps" );

	// Разбиваем треугольники для потока
	for ( int i = 0, NumTread = 1; i < Triangles.size(); i++ )
	{
		if ( i + 1 > NumTread*CountTrianglesForThread )
			NumTread++;

		Triangle* Triangle = &Triangles[ i ];
		TrianglesForThreads[ NumTread - 1 ].push_back( Triangle );
	}

	// Создаем потоки для просчета освещения
	for ( int i = 0; i < NUM_THREADS; i++ )
		Threads.push_back( thread( &Lightmap::Calculate, ref( Mutex ), Size, i*CountTrianglesForThread, TrianglesForThreads[ i ], Triangles, PointLights ) );

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

void Lightmap::Calculate( mutex& Mutex, size_t Size, int IdStartTriangle, vector<Triangle*>& Triangles, vector<Triangle>& Geometry, vector<PointLight>& PointLights )
{
	float Distance = 0, DiffuseFactor = 0, Attenuation = 0, MaxValue = 0;
	glm::vec2 UVFactor;
	glm::vec3 Newedge1, Newedge2, PositionFragment;
	Ray Ray;

	for ( size_t Id = 0, NumberTriangle = IdStartTriangle; Id < Triangles.size(); Id++, NumberTriangle++ )
	{
		Triangle* Triangle = Triangles[ Id ];
		Triangle->LightMap.Create( Size, Size );

		for ( int x = 0; x < Size; x++ )
			for ( int y = 0; y < Size; y++ )
			{
				UVFactor = glm::vec2( ( float ) x / Size, ( float ) y / Size );

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
						for ( size_t IdTriangle = 0; IdTriangle < Geometry.size(); IdTriangle++ )
							if ( Geometry[ IdTriangle ] != *Triangle && Ray.IntersectTriangle( Geometry[ IdTriangle ] ) )
							{
								IsIntersect = true;
								break;
							}

						if ( IsIntersect )
							continue;
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
				Triangle->LightMap.SetPixel( x, y, Color );
			}
		
		Triangle->LightMap.SaveInFile( DirectoryLightmaps + "\\lm_" + to_string( NumberTriangle ) + ".png" );

		Mutex.lock();
		CountCalculateLightMaps++;
		PRINT_LOG( "Calculate Lightmaps: " << CountCalculateLightMaps << "/" << Geometry.size() );
		Mutex.unlock();
	}
}

//-------------------------------------------------------------------------//