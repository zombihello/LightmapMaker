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

///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "Directories.h"

struct ArgumentsStart
{
	/* СЧИТАТЬ АРГУМЕНТЫ ЗАПУСКА ПРОГРАММЫ */
	static void InitArgumentsStart( int argc, char** argv );

	/* ПОКАЗАТЬ ВСЕ КОММАНДЫ ЗАПУСКА ПРОГРАММЫ */
	static void ShowHelp();

	static bool					IsSaveLog;
	static bool					IsNoShadow;
	static bool					IsNoRadiosity;
	
	static unsigned int			MaxSizeLightmap;
	static unsigned int			RadiosityNumberPasses;
	static unsigned int			SizeRenderTexture;

	static string				RouteToMap;
};

#endif // !ARGUMENTS_START_H

