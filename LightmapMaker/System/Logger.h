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

#define LIGHTMAPMAKER "LightmapMaker 1.1.0"
#define PRINT_LOG( X ) { Logger::Log << Logger::GetTime() << X; cout << Logger::GetTime() << X; }
#define BACK_LOG { Logger::Log << "\r"; cout << "\r"; }
#define END_LOG { Logger::Log << "\n"; cout << "\n"; }

///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
///////////////////////////
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
using namespace std;

class Logger
{
public:
	/* СОЗДАТЬ ФАЙЛ ЛОГОВ */
	static void CreateLogFile();

	/* НАРИСОВАТЬ ПРОГРЕСС БАР */
	static void PrintProgressBar( size_t TempValue, size_t MaxValue, size_t SizeProgressBar, const string& Message );

	/* УДАЛИТЬ ФАЙЛ ЛОГОВ */
	static void DeleteLogFile();

	/* ПОЛУЧИТЬ ВРЕМЯ ДЛЯ ЛОГОВ */
	static string  GetTime();

	static ofstream		Log;

private:
	static string		NameLog;
	static time_t		RawTime;
	static tm*			NowTime;
};

#endif // !LOGGER_H

