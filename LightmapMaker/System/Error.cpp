///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
///////////////////////////
#include <Windows.h>

///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "Logger.h"

//-------------------------------------------------------------------------//

void Error( const string& NameError, const string& Message, int ReturnCode )
{
	// Выводим сообщение об ошибке и завершаем программу

	MessageBox( NULL, wstring( Message.begin(), Message.end() ).c_str(), wstring( NameError.begin(), NameError.end() ).c_str(), MB_OK | MB_ICONERROR );
	PRINT_LOG( Message << endl );

	exit( ReturnCode );
}

//-------------------------------------------------------------------------//