//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// Связь со мной:		https://vk.com/zombihello
// Репозиторий движка:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "System\ArgumentsStart.h"
#include "System\Directories.h"
#include "System\Logger.h"
#include "System\Error.h"
#include "OpenGL\OpenGL.h"
#include "Level\Level.h"
#include "BuildNumber.h"

//-------------------------------------------------------------------------//

int main( int argc, char** argv )
{
	if ( argc > 1 )
	{
		sf::RenderWindow Window;
		Level Level;

		// ***********************************
		// Инициализируем пути и считываем аргументы запуска

		ArgumentsStart::InitArgumentsStart( argc, argv );
		Directories::InitDirectories( argv[ 0 ], ArgumentsStart::RouteToMap, "shaders", "logs" );
		Logger::CreateLogFile();

		PRINT_LOG( LIGHTMAPMAKER << " (Build " << BUILD_NUMBER << ")" );
		PRINT_LOG( " - Route To Map: " << ArgumentsStart::RouteToMap );
		PRINT_LOG( " - Max Size Lightmap: " << ArgumentsStart::MaxSizeLightmap );
		PRINT_LOG( " - Radiosity Number Passes: " << ArgumentsStart::RadiosityNumberPasses );
		PRINT_LOG( "" );

		// ***********************************
		// Инициализируем контекст OpenGL'a и все шейдера

		OpenGL_API::InitOpenGL( Window );

		// ***********************************
		// Загружаем карту и генерируем карту освещения

		if ( !Level.LoadLevel( ArgumentsStart::RouteToMap ) )
			Error( "Error Load Level", "Error: Level Not Loaded. Look Log File For Details", -1 );

		/*
		// ТЕСТОВЫЙ КОД ДЛЯ ПРОВЕРКИ РЕНДЕРА БРАШЕЙ И ТОЧЕЧНОГО ИСТОЧНИКА СВЕТА

		sf::Event Event;
		glm::mat4 Pojection = glm::perspective( glm::radians( 75.f ), 1.f, 0.1f, 1500.f );
		Camera Camera( glm::vec3( 0, 90, 0 ), glm::vec3( -64, 0, -64 ), glm::vec3( 0, 1, 0 ) );
		map<string, int> Attrib;

		Attrib[ "Position" ] = 0;
		Attrib[ "TexCoord" ] = 1;

		OpenGL_API::Shader Shader( Attrib );
		Shader.LoadFromFile( Directories::ShaderDirectory + "\\vs.vs", Directories::ShaderDirectory + "\\fs.fs" );
	
		Attrib.clear();
		Attrib[ "Position" ] = 0;

		OpenGL_API::Shader ShaderLight( Attrib );
		ShaderLight.LoadFromFile( Directories::ShaderDirectory + "\\vsl.vs", Directories::ShaderDirectory + "\\fsl.fs" );

		glEnable( GL_DEPTH_TEST );

		vector<Brush*>* Brushes = &Level.GetBrushes();
		vector<PointLight>* PointLights = &Level.GetPointLights();

		while ( Window.isOpen() )
		{
			while ( Window.pollEvent( Event ) )
				if ( Event.type == sf::Event::Closed )
					Window.close();

			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

			glm::vec3 Position = Camera.GetPosition();

			if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )
				Position.x -= 0.05;

			if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )
				Position.x += 0.05;

			if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) )
				Position.z += 0.05;

			if ( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) )
				Position.z -= 0.05;

			Camera.SetPosition( Position );

			glm::mat4 PV = Pojection * Camera.GetViewMatrix();
			Shader.SetUniform( "PV", PV );
			ShaderLight.SetUniform( "PV", PV );

			OpenGL_API::Shader::Bind( &Shader );
			for ( size_t i = 0; i < Brushes->size(); i++ )
				Brushes->at( i )->Render();

			OpenGL_API::Shader::Bind( &ShaderLight );

			for ( size_t i = 0; i < PointLights->size(); i++ )
			{
				glm::vec4 Color = PointLights->at( i ).Color;
				glm::mat4 Mat = PointLights->at( i ).LightSphere.GetTransformation();

				ShaderLight.SetUniform( "Color", Color );
				ShaderLight.SetUniform( "TR", Mat );
				PointLights->at( i ).LightSphere.Render();
			}

			OpenGL_API::Shader::Bind( NULL );

			Window.display();
		}*/

		PRINT_LOG( "" );
		if ( !ArgumentsStart::IsSaveLog ) Logger::DeleteLogFile();
	}
	else
		ArgumentsStart::ShowHelp();

	system( "pause" );
	return 0;
}

//-------------------------------------------------------------------------//