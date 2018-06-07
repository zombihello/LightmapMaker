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

#define PRINT_LOG( X ) Logger::Log << X << endl; cout << X << endl;

///////////////////////////
// —»—“≈ћЌџ≈ Ѕ»ЅЋ»ќ“≈ »
///////////////////////////
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Logger
{
public:
	/* —охранить логи в файл */
	static void SaveInFile( const string& Route );

	/* ќчистить логи */
	static void Clear();

	static stringstream		Log;
};

#endif // LOGGER_H

