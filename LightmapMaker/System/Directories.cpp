///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
///////////////////////////
#include <Windows.h>
using namespace std;

///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "Directories.h"

//-------------------------------------------------------------------------//

string Directories::WorkDirectory = "";
string Directories::ShaderDirectory = "";
string Directories::LogDirectory = "";
string Directories::TexturesDirectory = "";
string Directories::SaveLightmapDirectory = "";

//-------------------------------------------------------------------------//

void Directories::InitDirectories( const string& ExecutablePath, const string& RouteToMap, const string& ShaderDirectory, const string& LogDirectory )
{
	int TempId = 0;

	string ExecutableDir = ExecutablePath;
	string MapName = RouteToMap;
	string MapDir = RouteToMap;

	// *********************************
	// Заменяем в пути '/' на '\'

	for ( size_t Id = 0; Id < ExecutableDir.size(); Id++ )
		if ( ExecutableDir[ Id ] == '/' )
			ExecutableDir[ Id ] = '\\';

	for ( size_t Id = 0; Id < MapName.size(); Id++ )
		if ( MapName[ Id ] == '/' )
			MapName[ Id ] = '\\';

	MapDir = MapName;

	// *********************************
	// Получаем путь к директории с исполняемым файлом и картой

	ExecutableDir.erase( ExecutableDir.find_last_of( '\\' ), ExecutableDir.size() );
	TempId = MapDir.find_last_of( '\\' );

	if ( TempId != -1 )
		MapDir.erase( TempId + 1, MapDir.size() );
	else
		MapDir = "";

	// *********************************
	// Получаем название карты

	TempId = MapName.find_last_of( '\\' );

	if ( TempId != -1 )
		MapName.erase( 0, TempId + 1 );

	TempId = MapName.find_last_of( '.' );

	if ( TempId != -1 )
		MapName.erase( TempId, MapName.size() );

	// *********************************
	// Инициализируем пути к директориям

	Directories::WorkDirectory = ExecutableDir;
	Directories::ShaderDirectory = ExecutableDir + "\\" + ShaderDirectory;
	Directories::LogDirectory = ExecutableDir + "\\" + LogDirectory;
	Directories::SaveLightmapDirectory = MapDir + "lm-" + MapName;

	// *********************************
	// Создаем директорию для сохранения лайтмапов

	CreateDirectory( wstring( Directories::SaveLightmapDirectory.begin(), Directories::SaveLightmapDirectory.end() ).c_str(), NULL );
	CreateDirectory( wstring( Directories::LogDirectory.begin(), Directories::LogDirectory.end() ).c_str(), NULL );
}

//-------------------------------------------------------------------------//
