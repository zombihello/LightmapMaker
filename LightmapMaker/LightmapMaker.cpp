﻿//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// Связь со мной:		https://vk.com/zombihello
// Репозиторий движка:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#define LIGHTMAPMAKER "LightmapMaker 1.0.1"

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

void InitRoutes( const string& RouteMap )
{
	int TempId = 0;

	string RouteToMap = RouteMap;
	string NameMap;
	string DirectoryForLightmaps;

	// Заменяем в пути '/' на '\'
	for ( size_t id = 0; id < RouteToMap.size(); id++ )
		if ( RouteToMap[ id ] == '/' )
			RouteToMap[ id ] = '\\';

	NameMap = DirectoryForLightmaps = RouteToMap;

	// Получаем название карты
	TempId = NameMap.find_last_of( '\\' );

	if ( TempId != -1 )
		NameMap.erase( 0, TempId+1 );

	TempId = NameMap.find_last_of( '.' );

	if ( TempId != -1 )
		NameMap.erase( TempId, NameMap.size() );

	// Получаем директорию в которой нах. карта
	TempId = DirectoryForLightmaps.find_last_of( '\\' );

	if ( TempId != -1 )
		DirectoryForLightmaps.erase( TempId+1, DirectoryForLightmaps.size() );
	else
		DirectoryForLightmaps = "";
	
	wstringstream wStringStream;
	wStringStream << wstring( DirectoryForLightmaps.begin(), DirectoryForLightmaps.end() );
	wStringStream << "lm-";
	wStringStream << wstring( NameMap.begin(), NameMap.end() );
	CreateDirectory( wStringStream.str().c_str(), NULL );

	Lightmap::SetDirectoryForLightmaps( DirectoryForLightmaps + "lm-" + NameMap );
}

//-------------------------------------------------------------------------//

int main( int argc, char** argv )
{
	PRINT_LOG( LIGHTMAPMAKER );

	if ( argc > 2 )
	{
		InitRoutes( argv[ 1 ] );

		PRINT_LOG( "  - Route to map: " << argv[ 1 ] );
		PRINT_LOG( "  - Size Lightmap: " << argv[ 2 ] );
		PRINT_LOG( "" );

		Level Level;

		if ( !Level.LoadLevel( argv[ 1 ] ) )
		{
			Logger::SaveInFile( "Build.log" );
			system( "pause" );
			return -1;
		}

		PRINT_LOG( "" );
		Lightmap::Generate( atoi( argv[ 2 ] ), Level.GetTriangles(), Level.GetPointLights() );
	}
	else
		cout << "usage: lm <route_to_map> <size_light_maps>\n";

	Logger::SaveInFile( "Build.log" );
	system( "pause" );
    return 0;
}

//-------------------------------------------------------------------------//