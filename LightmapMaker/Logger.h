//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// Связь со мной:		https://vk.com/zombihello
// Репозиторий движка:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef LOGGER_H
#define LOGGER_H

#define PRINT_LOG( X ) Logger::Log << X << endl; cout << X << endl;

///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
///////////////////////////
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Logger
{
public:
	/* Сохранить логи в файл */
	static void SaveInFile( const string& Route );

	/* Очистить логи */
	static void Clear();

	static stringstream		Log;
};

#endif // LOGGER_H

