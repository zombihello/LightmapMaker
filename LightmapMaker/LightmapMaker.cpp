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
#include "ArgumentsStart.h"
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

void ShowHelp()
{
	cout << endl << LIGHTMAPMAKER << endl << endl;
	cout << "This Tool Generate Lightmaps For lifeEngine\n";
	cout << "Author: Egor Pogulyaka (vk.com/zombihello)\n";
	cout << "She Is Must Be Run With Parameters:\n";
	cout << "lm.exe [File.lmap] <Other Options>\n\n";
	cout << "--- Options ---\n\n";
	cout << "\t -map # \t : Route To Map *.lmap\n";
	cout << "\t -size # \t : Max Size Lightmap\n";
	cout << "\t -noshadow \t : Disable Shadows In Lightmaps\n";
	cout << "\t -savelog \t : Save Log In File\n";
	cout << "\t -threads # \t : Number Of Threads To Run\n";
	cout << "\t -help \t\t : Show Help\n";
}

//-------------------------------------------------------------------------//

int main( int argc, char** argv )
{
	if ( argc > 1 )
	{	
		Level			Level;
		Lightmap		Lightmap;

		for ( int i = 1; i < argc; i++ )
		{
			if ( strstr( argv[ i ], "-size" ) && i + 1 < argc )
			{
				ArgumentsStart::MaxSizeLightmap = ( int ) atof( argv[ i + 1 ] );
				i++;
			}
			else if ( strstr( argv[ i ], "-map" ) && i + 1 < argc )
			{
				ArgumentsStart::RouteToMap = argv[ i + 1 ];
				i++;
			}
			else if ( strstr( argv[ i ], "-threads" ) && i + 1 < argc )
			{
				ArgumentsStart::NumberThreads = ( int ) atof( argv[ i + 1 ] );
				i++;
			}
			else if ( strstr( argv[ i ], "-help" ) )
			{
				ShowHelp();
				return 0;
			}

			else if ( strstr( argv[ i ], "-noshadow" ) )	ArgumentsStart::IsDisableShadow = true;
			else if ( strstr( argv[ i ], "-savelog" ) )		ArgumentsStart::IsSaveLog = true;
		}

		PRINT_LOG( LIGHTMAPMAKER );
		PRINT_LOG( "  - Route to map: " << ArgumentsStart::RouteToMap );
		PRINT_LOG( "  - Size Lightmap: " << ArgumentsStart::MaxSizeLightmap );
		PRINT_LOG( "" );

		if ( !Level.LoadLevel( ArgumentsStart::RouteToMap ) )
		{
			if ( ArgumentsStart::IsSaveLog ) Logger::SaveInFile( "Build.log" );
			return -1;
		}

		InitRoutes( ArgumentsStart::RouteToMap );

		PRINT_LOG( "" );
		Lightmap.Generate( Level.GetPlanes(), Level.GetPointLights() );
	}
	else
		ShowHelp();

	if ( ArgumentsStart::IsSaveLog ) Logger::SaveInFile( "Build.log" );
	return 0;
}

//-------------------------------------------------------------------------//