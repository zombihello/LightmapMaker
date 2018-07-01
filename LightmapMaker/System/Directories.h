//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// —в¤зь со мной:		https://vk.com/zombihello
// –епозиторий движка:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef DIRECTORIES_H
#define DIRECTORIES_H

///////////////////////////
// —»—“≈ћЌџ≈ Ѕ»ЅЋ»ќ“≈ »
///////////////////////////
#include <string>
using namespace std;

struct Directories
{
	/* »нициализировать все директории */
	static void InitDirectories( const string& ExecutablePath, const string& RouteToMap, const string& ShaderDirectory, const string& LogDirectory );

	static string		WorkDirectory;
	static string		ShaderDirectory;
	static string		LogDirectory;
	static string		SaveLightmapDirectory;
};

#endif // !DIRECTORIES_H
