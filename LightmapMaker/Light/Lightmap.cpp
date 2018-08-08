///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
///////////////////////////
#include <sstream>
#include <iomanip>
#include <glm\gtx\transform.hpp>
using namespace std;

///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "Lightmap.h"

//-------------------------------------------------------------------------//

Lightmap::~Lightmap()
{
	ResourcesManager::DeleteAllShaders();
}

//-------------------------------------------------------------------------//

void Lightmap::InitLightmap( Level& Level )
{
	vector<Brush*>	Brushes = Level.GetBrushes();
	vector<Plane*>*	BrushPlanes;

	Projection = glm::perspective( glm::radians( 90.f ), 1.f, 0.1f, 1000.f );
	RenderTexture.Create( ArgumentsStart::SizeRenderTexture, ArgumentsStart::SizeRenderTexture );

	// ***********************************
	// Разбиваем браши на плоскости

	for ( size_t Id_Brush = 0; Id_Brush < Brushes.size(); Id_Brush++ )
	{
		BrushPlanes = &Brushes[ Id_Brush ]->GetPlanes();

		for ( size_t Id_Plane = 0; Id_Plane < BrushPlanes->size(); Id_Plane++ )
		{
			Plane* Plane = BrushPlanes->at( Id_Plane );
			Planes.push_back( Plane );
			PlanesRender[ Plane->GL_DiffuseMap ].push_back( Plane );
		}
	}

	AmbienceColor = Level.GetAmbienceColor();
	PointLights = &Level.GetPointLights();
	SpotLights = &Level.GetSpotLights();
	DirectionalLights = &Level.GetDirectionalLights();

	// ***********************************
	// Загружаем шейдер для рендера сцены

	Shader_RenderPlane = ResourcesManager::CreateShader( "RenderPlane" );
	Shader_RenderLight = ResourcesManager::CreateShader( "RenderLight" );

	map<string, int> AttribLocation;
	AttribLocation[ "Position" ] = 0;
	AttribLocation[ "TexCoord0" ] = 1;
	AttribLocation[ "TexCoord1" ] = 2;
	Shader_RenderPlane->SetAttribLocation( AttribLocation );

	AttribLocation.clear();
	AttribLocation[ "Position" ] = 0;
	Shader_RenderLight->SetAttribLocation( AttribLocation );

	if ( !Shader_RenderPlane->LoadFromFile( Directories::ShaderDirectory + "\\RenderPlane.vs", Directories::ShaderDirectory + "\\RenderPlane.fs" ) ||
		 !Shader_RenderLight->LoadFromFile( Directories::ShaderDirectory + "\\RenderLight.vs", Directories::ShaderDirectory + "\\RenderLight.fs" ) )
		Error( "Error Shader Load", "Error In Load Shader. Look Log File For Details", -1 );

	Shader_RenderPlane->SetUniform( "DiffuseMap", 0 );
	Shader_RenderPlane->SetUniform( "LightMap", 1 );
}

//-------------------------------------------------------------------------//

void RESIZE( unsigned char* src, unsigned char* dest, int ws, int hs, int wd, int hd )
{
	int xx, yy;
	int x, y;
	int ixx, iyy;
	int ix, iy;
	int cx, cy;
	int cxy, cc;
	int pin, pout, p;
	int b, g, r, a;
	int *ikx, *iky;
	int *kx, *ky;

	cx = ( ws - 1 ) / wd + 2;
	cy = ( hs - 1 ) / hd + 2;
	x = cx * wd;
	y = cy * hd;

	ikx = ( int * ) _alloca( x * 4 );
	iky = ( int * ) _alloca( y * 4 );
	kx = ( int * ) _alloca( x * 4 );
	ky = ( int * ) _alloca( y * 4 );

	for ( xx = 0; xx < x; xx++ )
	{
		ikx[ xx ] = 0;
		kx[ xx ] = 0;
	}

	for ( yy = 0; yy < y; yy++ )
	{
		iky[ yy ] = 0;
		ky[ yy ] = 0;
	}

	if ( ws >= wd )
	{
		cxy = ws;
		pin = 0; pout = 1; p = 0;
		for ( ;;)
		{
			cc = pout * ws - pin * wd;
			if ( cc >= wd )
			{
				kx[ p ] = wd;
			}
			else
			{
				kx[ p ] = cc;
				ikx[ p ] = pin;
				p = pout * cx;
				pout += 1;
				kx[ p ] = wd - cc;
			}
			ikx[ p ] = pin;
			pin += 1;
			if ( pin >= ws ) break;
			p += 1;
		}
	}
	else
	{
		cxy = wd;
		for ( x = 0; x < wd; x++ )
		{
			p = x * 2;
			kx[ p + 1 ] = x * ( ws - 1 ) % ( wd - 1 );
			ikx[ p ] = x * ( ws - 1 ) / ( wd - 1 );
			kx[ p ] = wd - kx[ p + 1 ];
			ikx[ p + 1 ] = ( ikx[ p ] + 1 ) % ws;
		}
	}

	if ( hs >= hd )
	{
		cxy *= hs;
		pin = 0; pout = 1; p = 0;
		for ( ;;)
		{
			cc = pout * hs - pin * hd;
			if ( cc >= hd )
			{
				ky[ p ] = hd;
			}
			else
			{
				ky[ p ] = cc;
				iky[ p ] = pin;
				p = pout * cy;
				pout += 1;
				ky[ p ] = hd - cc;
			}
			iky[ p ] = pin;
			pin += 1;
			if ( pin >= hs ) break;
			p += 1;
		}
	}
	else
	{
		cxy *= hd;
		for ( y = 0; y < hd; y++ )
		{
			p = y * 2;
			ky[ p + 1 ] = y * ( hs - 1 ) % ( hd - 1 );
			iky[ p ] = y * ( hs - 1 ) / ( hd - 1 );
			ky[ p ] = hd - ky[ p + 1 ];
			iky[ p + 1 ] = ( iky[ p ] + 1 ) % hs;
		}
	}

	iyy = 0;
	for ( yy = 0; yy < hd; yy++ )
	{
		ixx = 0;
		for ( xx = 0; xx < wd; xx++ )
		{
			b = g = r = a = 0;
			iy = iyy;
			for ( y = 1; y <= cy; y++ )
			{
				ix = ixx;
				for ( x = 1; x <= cx; x++ )
				{
					b += src[ ( ikx[ ix ] + iky[ iy ] * ws ) * 4 + 0 ] * kx[ ix ] * ky[ iy ];
					g += src[ ( ikx[ ix ] + iky[ iy ] * ws ) * 4 + 1 ] * kx[ ix ] * ky[ iy ];
					r += src[ ( ikx[ ix ] + iky[ iy ] * ws ) * 4 + 2 ] * kx[ ix ] * ky[ iy ];
					a += src[ ( ikx[ ix ] + iky[ iy ] * ws ) * 4 + 3 ] * kx[ ix ] * ky[ iy ];
					ix += 1;
				}
				iy += 1;
			}
			dest[ ( xx + yy * wd ) * 4 + 0 ] = b / cxy;
			dest[ ( xx + yy * wd ) * 4 + 1 ] = g / cxy;
			dest[ ( xx + yy * wd ) * 4 + 2 ] = r / cxy;
			dest[ ( xx + yy * wd ) * 4 + 3 ] = a / cxy;
			ixx += cx;
		}
		iyy += cy;
	}
	return;
}

void Lightmap::Generate()
{
	PRINT_LOG( "*** Lightmaps Generate ***\n" );

	PRINT_LOG( " - Generate Primary Illumination\n" );
	GeneratePrimaryIllumination();

	if ( !ArgumentsStart::IsNoRadiosity )
	{
		for ( size_t IdPlane = 0; IdPlane < Planes.size(); IdPlane++ )
		{
			Plane* Plane = Planes[ IdPlane ];
			vector<unsigned char> Pixels( Plane->SizeLightmap_SecondaryLight->x * Plane->SizeLightmap_SecondaryLight->y * 4 );
			RESIZE( ( unsigned char* ) Plane->LightMap_PrimaryIllumination.getPixelsPtr(), &Pixels[ 0 ], Plane->SizeLightmap_PrimaryIllumination->x, Plane->SizeLightmap_PrimaryIllumination->y, Plane->SizeLightmap_SecondaryLight->x, Plane->SizeLightmap_SecondaryLight->y );

			for ( int x = 0; x < Plane->SizeLightmap_SecondaryLight->x; x++ )
				for ( int y = 0; y < Plane->SizeLightmap_SecondaryLight->y; y++ )
				{
					unsigned char* Ptr = &Pixels[ ( x + y * Plane->SizeLightmap_SecondaryLight->x ) * 4 ];
					Plane->LightMap_SecondaryLight.setPixel( x, y, sf::Color( Ptr[ 0 ], Ptr[ 1 ], Ptr[ 2 ], Ptr[ 3 ] ) );
				}

			Planes[ IdPlane ]->GenerateGLTexture();
			//Planes[ IdPlane ]->LightMap_SecondaryLight.saveToFile( Directories::SaveLightmapDirectory + "\\lm_" + to_string( IdPlane ) + ".png" );
		}

		PRINT_LOG( "\n" );
		PRINT_LOG( " - Generate Secondary Light\n" );
		GenerateSecondaryLight();
	}

	for ( size_t IdPlane = 0; IdPlane < Planes.size(); IdPlane++ )
	{
		Plane* Plane = Planes[ IdPlane ];
		vector<unsigned char> Pixels( Plane->SizeLightmap_PrimaryIllumination->x * Plane->SizeLightmap_PrimaryIllumination->y * 4 );
		RESIZE( (unsigned char*) Plane->LightMap_SecondaryLight.getPixelsPtr(), &Pixels[0], Plane->SizeLightmap_SecondaryLight->x, Plane->SizeLightmap_SecondaryLight->y, Plane->SizeLightmap_PrimaryIllumination->x, Plane->SizeLightmap_PrimaryIllumination->y );

		for ( int x = 0; x < Plane->SizeLightmap_PrimaryIllumination->x; x++ )
			for ( int y = 0; y < Plane->SizeLightmap_PrimaryIllumination->y; y++ )
			{
				unsigned char* Ptr = &Pixels[ ( x + y * Plane->SizeLightmap_PrimaryIllumination->x ) * 4 ];

				sf::Color Pixel_PrimaryIllumination = Plane->LightMap_PrimaryIllumination.getPixel( x, y );
				sf::Color Pixel_SecondaryLight = sf::Color( Ptr[ 0 ], Ptr[ 1 ], Ptr[ 2 ], Ptr[3] );

				Plane->LightMap_PrimaryIllumination.setPixel( x, y, Pixel_PrimaryIllumination + Pixel_SecondaryLight );
			}

		Planes[ IdPlane ]->LightMap_PrimaryIllumination.saveToFile( Directories::SaveLightmapDirectory + "\\lm_" + to_string( IdPlane ) + ".png" );
	}

	PRINT_LOG( "*** Lightmaps Generated ***\n" );
}

//-------------------------------------------------------------------------//

void Lightmap::GeneratePrimaryIllumination()
{
	float			Distance = 0, DiffuseFactor = 0, SpotFactor = 0, Attenuation = 0, MaxValue = 0;
	glm::vec2		UVFactor;
	glm::vec3		Newedge1, Newedge2, PositionFragment;
	stringstream	StreamMessage;
	size_t			CountPlanes = Planes.size(), ReadyPlanes = 0;
	Ray				Ray;
	Timer			Timer;
	Time			Time;

	// ******************************
	// Выводим прогресс бар начала

	Logger::PrintProgressBar( 0, CountPlanes, 30, "" );

	for ( size_t Id = 0; Id < Planes.size(); Id++ )
	{
		Plane* Plane = Planes[ Id ];
		Timer.Start();

		// **************************************************
		// Просчитываем освещение для каждого
		// пикселя карты освещения

		for ( size_t x = 0; x < Plane->SizeLightmap_PrimaryIllumination->x; x++ )
			for ( size_t y = 0; y < Plane->SizeLightmap_PrimaryIllumination->y; y++ )
			{
				Plane->GetPositionFragment( ( ( float ) x + 0.5f ) / ( float ) Plane->SizeLightmap_PrimaryIllumination->x, ( ( float ) y + 0.5f ) / ( float ) Plane->SizeLightmap_PrimaryIllumination->y, PositionFragment );

				glm::vec3 Color;

				// ************************************
				// Просчитываем точечное освещение

				for ( size_t IdPointLights = 0; IdPointLights < PointLights->size(); IdPointLights++ )
				{
					PointLight* PointLight = &PointLights->at( IdPointLights );
					Ray.SetRay( PointLight->Position, PositionFragment );

					if ( !ArgumentsStart::IsNoShadow )
					{
						bool IsIntersect = false;
						for ( size_t IdPlane = 0; IdPlane < Planes.size() && !IsIntersect; IdPlane++ )
							if ( *Planes[ IdPlane ] != *Plane )
								IsIntersect = Planes[ IdPlane ]->IsRayIntersect( Ray );

						if ( IsIntersect ) continue;
					}

					Distance = glm::length( Ray.Direction );
					DiffuseFactor = glm::max( glm::dot( *Plane->Normal, Ray.Normalize_Direction ), 0.0f );
					Attenuation = PointLight->CalculateAttenuation( Distance );

					Color += ( PointLight->Color + AmbienceColor ) * Attenuation * DiffuseFactor * PointLight->Intensivity;
				}

				// ************************************
				// Просчитываем прожекторное освещение

				for ( size_t IdSpotLights = 0; IdSpotLights < SpotLights->size(); IdSpotLights++ )
				{
					SpotLight* SpotLight = &SpotLights->at( IdSpotLights );
					Ray.SetRay( SpotLight->Position, PositionFragment );

					if ( !ArgumentsStart::IsNoShadow )
					{
						bool IsIntersect = false;
						for ( size_t IdPlane = 0; IdPlane < Planes.size() && !IsIntersect; IdPlane++ )
							if ( *Planes[ IdPlane ] != *Plane )
								IsIntersect = Planes[ IdPlane ]->IsRayIntersect( Ray );

						if ( IsIntersect ) continue;
					}

					Distance = glm::length( Ray.Direction );
					DiffuseFactor = glm::max( glm::dot( *Plane->Normal, Ray.Normalize_Direction ), 0.0f );
					SpotFactor = glm::dot( SpotLight->SpotDirection, -Ray.Normalize_Direction );
					SpotFactor = glm::clamp( ( SpotFactor - SpotLight->SpotCutoff ) / ( 1.0f - SpotLight->SpotCutoff ), 0.0f, 1.0f );
					Attenuation = SpotLight->CalculateAttenuation( Distance );

					Color += ( SpotLight->Color + AmbienceColor ) * Attenuation * DiffuseFactor * SpotFactor * SpotLight->Intensivity;
				}

				// ************************************
				// Просчитываем направленное освещение

				for ( size_t IdDirectionalLights = 0; IdDirectionalLights < DirectionalLights->size(); IdDirectionalLights++ )
				{
					DirectionalLight* DirectionalLight = &DirectionalLights->at( IdDirectionalLights );
					Ray.SetRay( DirectionalLight->Position + PositionFragment, PositionFragment );

					if ( !ArgumentsStart::IsNoShadow )
					{
						bool IsIntersect = false;
						for ( size_t IdPlane = 0; IdPlane < Planes.size() && !IsIntersect; IdPlane++ )
							if ( *Planes[ IdPlane ] != *Plane )
								IsIntersect = Planes[ IdPlane ]->IsRayIntersect( Ray );

						if ( IsIntersect ) continue;
					}

					DiffuseFactor = glm::max( glm::dot( glm::normalize( DirectionalLight->Position ), *Plane->Normal ), 0.0f );
					Color += ( DirectionalLight->Color + AmbienceColor ) * DirectionalLight->Intensivity * DiffuseFactor;
				}

				// **************************************************
				// Нормализуем цветовые каналы и заносим цвет
				// в пиксель карты освещения

				MaxValue = glm::max( Color.x, glm::max( Color.y, Color.z ) );

				if ( MaxValue > 255.f )
				{
					float Value = 255.f / MaxValue;
					Color.x *= Value;
					Color.y *= Value;
					Color.z *= Value;
				}

				Plane->LightMap_PrimaryIllumination.setPixel( x, y, sf::Color( Color.x, Color.y, Color.z, 255 ) );
			}

		// **************************************************
		// Выводим прогресс бар и сколько время осталось
		// до конца (время приблизительное)

		Timer.End();
		Time = Timer.GetTime() * ( CountPlanes - ReadyPlanes );

		StreamMessage.str( "" );
		StreamMessage << " | Time Left: "
			<< setw( 2 ) << setfill( '0' ) << Time.Hours << ":"
			<< setw( 2 ) << setfill( '0' ) << Time.Minutes << ":"
			<< setw( 2 ) << setfill( '0' ) << Time.Seconds;
		Logger::PrintProgressBar( Id, CountPlanes, 30, StreamMessage.str() );
	}

	Logger::PrintProgressBar( CountPlanes, CountPlanes, 30, "                      " );
	END_LOG;
}

//-------------------------------------------------------------------------//

void Lightmap::GenerateSecondaryLight()
{
	stringstream		StreamMessage;
	glm::vec3			PositionFragment, NormalizeCenter, Center, Right;
	Plane*				Plane;
	size_t				CountPlanes = Planes.size() * ArgumentsStart::RadiosityNumberPasses, ReadyPlanes = 0;
	Timer				Timer;
	Time				Time;

	glEnable( GL_DEPTH_TEST );
	glEnable( GL_CULL_FACE );
	glEnable( GL_TEXTURE_2D );

	// ****************************
	// Генерируем карты освещения

	RenderTexture.Bind();
	Logger::PrintProgressBar( 0, CountPlanes, 30, "" );

	for ( size_t RadiosityStep = 0; RadiosityStep < ArgumentsStart::RadiosityNumberPasses; RadiosityStep++ )
	{
		for ( size_t IdPlane = 0; IdPlane < Planes.size(); IdPlane++, ReadyPlanes++ )
		{
			Timer.Start();
			Plane = Planes[ IdPlane ];

			// **************************************************
			// Рендерим сцену со взгляда патча и заносим
			// средний цвет в пиксель карты освещения

			for ( size_t x = 0; x < Plane->SizeLightmap_SecondaryLight->x; x++ )
				for ( size_t y = 0; y < Plane->SizeLightmap_SecondaryLight->y; y++ )
				{
					Plane->GetPositionFragment( ( ( float ) x + 0.5f ) / Plane->SizeLightmap_SecondaryLight->x, ( ( float ) y + 0.5f ) / Plane->SizeLightmap_SecondaryLight->y, PositionFragment );

					Center = PositionFragment + *Plane->Normal;
					NormalizeCenter = glm::normalize( Center );
					Right = glm::normalize( glm::cross( glm::vec3( 0, 1, 0 ), NormalizeCenter ) );

					Camera.SetPosition( PositionFragment );
					Camera.SetTargetPoint( PositionFragment + *Plane->Normal );
					Camera.SetAxisVertical( glm::normalize( glm::cross( NormalizeCenter, Right ) ) );

					RenderScene();

					Plane->LightMap_SecondaryLight.setPixel( x, y, Plane->LightMap_SecondaryLight.getPixel(x,y) + RenderTexture.GetMediumColorTexture() );
				}

			// **************************************************
			// Выводим прогресс бар, какой шаг радиосити и
			// сколько время осталось до конца (время приблизительное)

			Timer.End();
			Time = Timer.GetTime() * ( CountPlanes - ReadyPlanes );

			StreamMessage.str( "" );
			StreamMessage << "| Radiosity Step: "
				<< RadiosityStep + 1 << "/" << ArgumentsStart::RadiosityNumberPasses
				<< " | Time Left: "
				<< setw( 2 ) << setfill( '0' ) << Time.Hours << ":"
				<< setw( 2 ) << setfill( '0' ) << Time.Minutes << ":"
				<< setw( 2 ) << setfill( '0' ) << Time.Seconds;
			Logger::PrintProgressBar( ReadyPlanes, CountPlanes, 30, StreamMessage.str() );
		}

		// **************************************************
		// Обновляем карты освещения в OpenGL'e

		for ( size_t IdPlane = 0; IdPlane < Planes.size(); IdPlane++ )
			Planes[ IdPlane ]->GenerateGLTexture();
	}

	glBindTexture( GL_TEXTURE_2D, 0 );
	RenderTexture.Unbind();
	Logger::PrintProgressBar( CountPlanes, CountPlanes, 30, "                      " );
	END_LOG;

	glDisable( GL_DEPTH_TEST );
	glDisable( GL_CULL_FACE );
	glDisable( GL_TEXTURE_2D );
}

//-------------------------------------------------------------------------//

void Lightmap::RenderScene()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	PV = Projection * Camera.GetViewMatrix();
	Shader_RenderPlane->SetUniform( "PVMatrix", PV );

	glCullFace( GL_BACK );
//	glDisable( GL_CULL_FACE );
	//OpenGL_API::Shader::Bind( Shader_RenderLight );

	//// ****************************
	//// Рендерим источники света

	//for ( size_t Id = 0; Id < PointLights->size(); Id++ )
	//{
	//	PointLight* PointLight = &( *PointLights )[ Id ];

	//	PVT = PV * PointLight->Sphere.GetTransformation();
	//	Shader_RenderLight->SetUniform( "PVTMatrix", PVT );
	//	Shader_RenderLight->SetUniform( "Intensivity", PointLight->Intensivity );
	//	Shader_RenderLight->SetUniform( "Light_Color", PointLight->Color );

	//	PointLight->Sphere.Render();
	//}

	// ****************************
	// Рендерим сцену

//	glEnable( GL_CULL_FACE );
	OpenGL_API::Shader::Bind( Shader_RenderPlane );
	Shader_RenderPlane->SetUniform( "IsCullBack", true );

	for ( auto It = PlanesRender.begin(); It != PlanesRender.end(); It++ )
	{
		glActiveTexture( GL_TEXTURE0 );
		glBindTexture( GL_TEXTURE_2D, It->first );

		for ( size_t Id = 0; Id < It->second.size(); Id++ )
		{
			Plane* Plane = It->second[ Id ];

			glActiveTexture( GL_TEXTURE1 );
			glBindTexture( GL_TEXTURE_2D, Plane->GL_LightMap );

			Plane->Render();
		}
	}

	// *************************************************
	// Рендерим сцену на изнанку, чтобы 
	// убрать "заползание" света сквозь геометрию

	Shader_RenderPlane->SetUniform( "IsCullBack", false );
	glCullFace( GL_FRONT );

	for ( auto It = PlanesRender.begin(); It != PlanesRender.end(); It++ )
	{
		for ( size_t Id = 0; Id < It->second.size(); Id++ )
			It->second[ Id ]->Render();
	}

	OpenGL_API::Shader::Bind( NULL );
}

//-------------------------------------------------------------------------//