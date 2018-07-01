//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// Связь со мной:		https://vk.com/zombihello
// Репозиторий движка:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef ERROR_H
#define ERROR_H

///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
///////////////////////////
#include <string>
using namespace std;

//-------------------------------------------------------------------------//

void Error( const string& NameError, const string& Message, int ReturnCode );

//-------------------------------------------------------------------------//

#endif // !ERROR_H

