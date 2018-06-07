#include "Lightmap.h"

//-------------------------------------------------------------------------//

string Lightmap::DirectoryLightmaps = string();

//-------------------------------------------------------------------------//

void Lightmap::Generate( size_t Size, vector<Triangle>& Triangles, vector<PointLight>& PointLights )
{
	PRINT_LOG( "- Generate Lightmaps" );

	float Distance = 0, DiffuseFactor = 0, Attenuation = 0, MaxValue = 0;
	glm::vec2 UVFactor;
	glm::vec3 Newedge1, Newedge2, PositionFragment;
	Ray Ray;

	for ( size_t Id = 0; Id < Triangles.size(); Id++ )
	{
		Triangle* Triangle = &Triangles[ Id ];
		Triangle->LightMap.Create( Size, Size );

		for ( int x = 0; x < Size; x++ )
			for ( int y = 0; y < Size; y++ )
			{
				UVFactor = glm::vec2( (float) x / Size, ( float ) y / Size );

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

					bool IsIntersect = false;
					for ( size_t IdTriangle = 0; IdTriangle < Triangles.size(); IdTriangle++ )
						if ( Triangles[ IdTriangle ] != *Triangle && Ray.IntersectTriangle( Triangles[ IdTriangle ] ) )
						{
							IsIntersect = true;
							break;
						}

					if ( IsIntersect ) 
						continue;

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

		Triangle->LightMap.SaveInFile( DirectoryLightmaps + "/lm_" + to_string(Id) + ".png" );
	}

	PRINT_LOG( "- Lightmaps Generated" );
}

//-------------------------------------------------------------------------//

void Lightmap::SetDirectoryForLightmaps( const string& Directory )
{
	DirectoryLightmaps = Directory;
}

//-------------------------------------------------------------------------//