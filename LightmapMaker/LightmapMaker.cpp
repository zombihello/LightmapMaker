//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// Связь со мной:		https://vk.com/zombihello
// Репозиторий движка:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#define LIGHTMAPMAKER "LightmapMaker 1.0.0"

///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
///////////////////////////
#include <iostream>
#include <Windows.h>
using namespace std;

///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "Logger.h"
#include "Level.h"
#include "Lightmap.h"

//-------------------------------------------------------------------------//

int main( int argc, char** argv )
{
	PRINT_LOG( LIGHTMAPMAKER );

	if ( argc > 2 )
	{
		string RouteMap = argv[ 1 ];
		string NameMap = RouteMap;

		int IdLastSlash = NameMap.find_last_of( "/" );
		int IdLastDot = NameMap.find_last_of( "." );

		if ( IdLastSlash != -1 )
			NameMap.erase( 0, IdLastSlash );

		if ( IdLastDot != -1 )
			NameMap.erase( IdLastDot, NameMap.size() );

		PRINT_LOG( "  - Route to map: " << argv[ 1 ] );
		PRINT_LOG( "  - Size Lightmap: " << argv[ 2 ] );
		PRINT_LOG( "" );

		Level Level;

		if ( !Level.LoadLevel( RouteMap ) )
		{
			Logger::SaveInFile( "Build.log" );
			system( "pause" );
			return -1;
		}

		PRINT_LOG( "" );
		
		wstringstream wStringStream;
		wStringStream << "lm-";
		wStringStream << wstring( NameMap.begin(), NameMap.end() );
		CreateDirectory( wStringStream.str().c_str(), NULL );

		Lightmap::SetDirectoryForLightmaps( "lm-" + NameMap );
		Lightmap::Generate( atoi( argv[ 2 ] ), Level.GetTriangles(), Level.GetPointLights() );
	}
	else
		cout << "usage: lm <route_to_map> <size_light_maps>\n";

	Logger::SaveInFile( "Build.log" );
	system( "pause" );
    return 0;
}

//-------------------------------------------------------------------------//