//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// —в¤зь со мной:		https://vk.com/zombihello
// –епозиторий движка:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef ARGUMENTS_START_H
#define ARGUMENTS_START_H

///////////////////////////
// —»—“≈ћЌџ≈ Ѕ»ЅЋ»ќ“≈ »
///////////////////////////
#include <string>
using namespace std;

struct ArgumentsStart
{
	/* —читать аргументы запуска программы */
	static void InitArgumentsStart( int argc, char** argv );

	/* ѕоказать все комманды запуска программы */
	static void ShowHelp();

	static bool					IsDisableShadow;
	static bool					IsSaveLog;
	
	static unsigned int			MaxSizeLightmap;
	static unsigned int			RadiosityNumberPasses;

	static string				RouteToMap;
};

#endif // !ARGUMENTS_START_H

