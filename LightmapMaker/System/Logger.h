//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// —в¤зь со мной:		https://vk.com/zombihello
// –епозиторий движка:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef LOGGER_H
#define LOGGER_H

#define LIGHTMAPMAKER "LightmapMaker 1.1.0"
#define PRINT_LOG( X ) { Logger::Log << Logger::GetTime() << X << endl; cout << Logger::GetTime() << X << endl; }

///////////////////////////
// —»—“≈ћЌџ≈ Ѕ»ЅЋ»ќ“≈ »
///////////////////////////
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
using namespace std;

class Logger
{
public:
	/* —оздать файл логов */
	static void CreateLogFile();

	/* ”далить файл логов */
	static void DeleteLogFile();

	/* ѕолучить врем¤, чтобы записать в лог */
	static string  GetTime();

	static ofstream		Log;

private:
	static string		NameLog;
	static time_t		RawTime;
	static tm*			NowTime;
};

#endif // !LOGGER_H

