//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// Связь со мной:		https://vk.com/zombihello
// Репозиторий движка:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef DIRECTORIES_H
#define DIRECTORIES_H

///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
///////////////////////////
#include <string>
using namespace std;

struct Directories
{
	/* ИНИЦИАЛИЗИРОВАТЬ ВСЕ ДИРЕКТОРИИ */
	static void InitDirectories( const string& ExecutablePath, const string& RouteToMap, const string& ShaderDirectory, const string& LogDirectory );

	static string		WorkDirectory;
	static string		ShaderDirectory;
	static string		LogDirectory;
	static string		TexturesDirectory;
	static string		SaveLightmapDirectory;
};

#endif // !DIRECTORIES_H
