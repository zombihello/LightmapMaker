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

	Projection = glm::perspective( glm::radians( 90.f ), 1.f, 0.1f, 1500.f );
	RenderTexture.Create( ArgumentsStart::SizeRenderTexture, ArgumentsStart::SizeRenderTexture );

	// ***********************************
	// Разбиваем браши на плоскости

	for ( size_t Id_Brush = 0; Id_Brush < Brushes.size(); Id_Brush++ )
	{
		BrushPlanes = &Brushes[ Id_Brush ]->GetPlanes();

		for ( size_t Id_Plane = 0; Id_Plane < BrushPlanes->size(); Id_Plane++ )
			Planes.push_back( BrushPlanes->at( Id_Plane ) );
	}

	PointLights = &Level.GetPointLights();

	// ***********************************
	// Загружаем шейдера

	map<string, int> AttribLocation;
	AttribLocation[ "Position" ] = 0;
	AttribLocation[ "TexCoord0" ] = 1;
	AttribLocation[ "TexCoord1" ] = 2;

	Shader_RenderPlane = ResourcesManager::CreateShader( "RenderPlane" );
	Shader_RenderLight = ResourcesManager::CreateShader( "RenderLight" );

	Shader_RenderPlane->SetAttribLocation( AttribLocation );
	Shader_RenderLight->SetAttribLocation( AttribLocation );

	if ( !Shader_RenderPlane->LoadFromFile( Directories::ShaderDirectory + "\\vs.vs", Directories::ShaderDirectory + "\\fs.fs" ) ||
		!Shader_RenderLight->LoadFromFile( Directories::ShaderDirectory + "\\vsl.vs", Directories::ShaderDirectory + "\\fsl.fs" ) )
		Error( "Error Shader Load", "Error In Load Shader. Look Log File For Details", -1 );

	Shader_RenderPlane->SetUniform( "DiffuseMap", 0 );
	Shader_RenderPlane->SetUniform( "LightMap", 1 );
}

//-------------------------------------------------------------------------//

void Lightmap::Generate()
{
	PRINT_LOG( "*** Lightmaps Generate ***\n" );

	stringstream		StreamMessage;
	glm::vec3			PositionFragment, NormalizeCenter, Right;
	glm::vec2			SizeLightmap;
	Plane*				Plane;
	size_t				CountPlanes = Planes.size() * ArgumentsStart::RadiosityNumberPasses;
	size_t				ReadyPlanes = 0;

	glEnable( GL_DEPTH_TEST );
	Camera.SetAxisVertical( glm::vec3( 0, 1, 0 ) );

	// ****************************
	// Генерируем карты освещения

	for ( size_t RadiosityStep = 0; RadiosityStep < ArgumentsStart::RadiosityNumberPasses; RadiosityStep++ )
	{
		for ( size_t IdPlane = 0; IdPlane < Planes.size(); IdPlane++, ReadyPlanes++ )
		{
			StreamMessage.str( "" );
			StreamMessage << "| Radiosity Step: " << RadiosityStep + 1 << "/" << ArgumentsStart::RadiosityNumberPasses;

			Logger::PrintProgressBar( ReadyPlanes, CountPlanes, 30, StreamMessage.str() );


			Plane = Planes[ IdPlane ];
			SizeLightmap = Plane->GetSizeLightmap();

			for ( float x = 0; x < SizeLightmap.x; x++ )
				for ( float y = 0; y < SizeLightmap.y; y++ )
				{
					Plane->GetPositionFragment( ( x + 0.5f ) / SizeLightmap.x, ( y + 0.5f ) / SizeLightmap.y, PositionFragment );

					Camera.SetPosition( PositionFragment );
					Camera.SetTargetPoint( PositionFragment + Plane->GetNormal() );

					NormalizeCenter = glm::normalize( Camera.GetTargetPoint() );
					Right = glm::normalize( glm::cross( glm::vec3( 0, 1, 0 ), NormalizeCenter ) );

					Camera.SetAxisVertical( glm::normalize( glm::cross( NormalizeCenter, Right ) ) );

					Plane->GetDataLightMap().setPixel( ( size_t ) x, ( size_t ) y, PathRender() );
				}
		}

		for ( size_t IdPlane = 0; IdPlane < Planes.size(); IdPlane++ )
			Planes[ IdPlane ]->GenerateGLTexture();
	}

	for ( size_t IdPlane = 0; IdPlane < Planes.size(); IdPlane++ )
	{
		Plane = Planes[ IdPlane ];
		Plane->GetDataLightMap().saveToFile( Directories::SaveLightmapDirectory + "\\lm_" + to_string( IdPlane ) + ".png" );
	}

	StreamMessage.str( "" );
	StreamMessage << "| Radiosity Step: " << ArgumentsStart::RadiosityNumberPasses << "/" << ArgumentsStart::RadiosityNumberPasses;
	Logger::PrintProgressBar( CountPlanes, CountPlanes, 30, StreamMessage.str() );
	END_LOG;

	PRINT_LOG( "*** Lightmaps Generated ***\n" );
}

//-------------------------------------------------------------------------//

sf::Color Lightmap::PathRender()
{
	RenderTexture.Bind();
	RenderScene();
	RenderTexture.Unbind();

	glm::vec3 ColorPixel = RenderTexture.GetMediumColorTexture();
	return sf::Color( ColorPixel.x * 255.f, ColorPixel.y * 255.f, ColorPixel.z * 255.f, 255.f );
}

//-------------------------------------------------------------------------//

void Lightmap::RenderScene()
{
	PV = Projection * Camera.GetViewMatrix();
	Shader_RenderPlane->SetUniform( "PV", PV );

	// ****************************
	// Рендерим плоскости брашей

	glEnable( GL_TEXTURE_2D );
	glEnable( GL_CULL_FACE );

	OpenGL_API::Shader::Bind( Shader_RenderPlane );

	for ( size_t i = 0; i < Planes.size(); i++ )
		Planes[ i ]->Render();

	glDisable( GL_CULL_FACE );
	glDisable( GL_TEXTURE_2D );

	// ****************************
	// Рендерим источники света

	OpenGL_API::Shader::Bind( Shader_RenderLight );

	for ( size_t i = 0; i < PointLights->size(); i++ )
	{
		PVT = PV * PointLights->at( i ).LightSphere.GetTransformation();
		Shader_RenderLight->SetUniform( "PV", PVT );
		Shader_RenderLight->SetUniform( "Color", PointLights->at( i ).Color );

		PointLights->at( i ).LightSphere.Render();
	}

	OpenGL_API::Shader::Bind( NULL );
}

//-------------------------------------------------------------------------//