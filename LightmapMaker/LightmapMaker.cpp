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
#include "OpenGL\OpenGL.h"
#include "BuildNumber.h"

//-------------------------------------------------------------------------//

int main( int argc, char** argv )
{
	if ( argc > 1 )
	{
		sf::RenderWindow Window;

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



		PRINT_LOG( "" );
		if ( !ArgumentsStart::IsSaveLog ) Logger::DeleteLogFile();
	}
	else
		ArgumentsStart::ShowHelp();

	system( "pause" );
	return 0;
}

//-------------------------------------------------------------------------//