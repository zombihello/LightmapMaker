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
#include "Level\Level.h"
#include "Light\Lightmap.h"
#include "BuildNumber.h"

//-------------------------------------------------------------------------//

int main( int argc, char** argv )
{
	if ( argc > 1 )
	{
		sf::RenderWindow Window;
		Level Level;
		Lightmap Lightmap;

		// ***********************************
		// Инициализируем пути и считываем аргументы запуска

		ArgumentsStart::InitArgumentsStart( argc, argv );
		Directories::InitDirectories( argv[ 0 ], ArgumentsStart::RouteToMap, "shaders", "logs" );
		Logger::CreateLogFile();

		PRINT_LOG( LIGHTMAPMAKER << " (Build " << BUILD_NUMBER << ")\n" );
		PRINT_LOG( " - Route To Map: " << ArgumentsStart::RouteToMap << endl );
		PRINT_LOG( " - Max Size Lightmap: " << ArgumentsStart::MaxSizeLightmap << endl );
		PRINT_LOG( " - Size Render Texture: " << ArgumentsStart::SizeRenderTexture << endl );
		PRINT_LOG( " - Radiosity Number Passes: " << ArgumentsStart::RadiosityNumberPasses << endl );
		PRINT_LOG( "\n" );

		// ***********************************
		// Инициализируем контекст OpenGL'a и все шейдера

		OpenGL_API::InitOpenGL( Window );

		// ***********************************
		// Загружаем карту и генерируем карту освещения

		if ( !Level.LoadLevel( ArgumentsStart::RouteToMap ) )
			Error( "Error Load Level", "Error: Level Not Loaded. Look Log File For Details", -1 );

		// ***********************************
		// Инициализируем данный для просчета карт освещения и генерируем ее

		PRINT_LOG( "\n" );
		Lightmap.InitLightmap( Level );
		Lightmap.Generate();

		PRINT_LOG( "\n" );
		if ( !ArgumentsStart::IsSaveLog ) Logger::DeleteLogFile();
	}
	else
		ArgumentsStart::ShowHelp();

	return 0;
}

//-------------------------------------------------------------------------//