//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// Связь со мной:		https://vk.com/zombihello
// Репозиторий движка:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef ARGUMENTS_START_H
#define ARGUMENTS_START_H

///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
///////////////////////////
#include <string>
using namespace std;

struct ArgumentsStart
{
	static bool			IsDisableShadow;
	static bool			IsSaveLog;

	static int			MaxSizeLightmap;
	static int			NumberThreads;

	static string		RouteToMap;
};

#endif // ARGUMENTS_START_H
