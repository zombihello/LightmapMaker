//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// Связь со мной:		https://vk.com/zombihello
// Репозиторий движка:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#define LIGHTMAPMAKER "LightmapMaker 1.0.3"

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
		NameMap.erase( 0, TempId + 1 );

	TempId = NameMap.find_last_of( '.' );

	if ( TempId != -1 )
		NameMap.erase( TempId, NameMap.size() );

	// Получаем директорию в которой нах. карта
	TempId = DirectoryForLightmaps.find_last_of( '\\' );

	if ( TempId != -1 )
		DirectoryForLightmaps.erase( TempId + 1, DirectoryForLightmaps.size() );
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

		if ( argc > 3 && strstr( argv[ 3 ], "-ds" ) )
			Lightmap::EnableShadows( false );

		Lightmap::MaxSizeLightmap = ( float ) atof( argv[ 2 ] );

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
		Lightmap::Generate( Level.GetPlanes(), Level.GetPointLights() );
	}
	else
	{
		cout << "Must Be Run With Parameter: \n";
		cout << "lm.exe [File.lmap] [Size Lightmaps] [-ds]\n";
		cout << " -ds: Disable Shadows In Lightmaps\n";
		system( "pause" );
		return 0;
	}

	Logger::SaveInFile( "Build.log" );
	system( "pause" );
	return 0;
}

//-------------------------------------------------------------------------//