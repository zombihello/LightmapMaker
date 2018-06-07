//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// Связь со мной:		https://vk.com/zombihello
// Репозиторий движка:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef LIGHTMAP_H
#define LIGHTMAP_H

///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
///////////////////////////
#include <vector>
#include <string>
using namespace std;

///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "Level.h"
#include "Ray.h"

class Lightmap
{
public:
	/* Сгенерировать карту освещения */
	static void Generate( size_t Size, vector<Triangle>& Triangles, vector<PointLight>& PointLights );
	
	/* Задать директорию в которую будут сохраняться освещение */
	static void SetDirectoryForLightmaps( const string& Directory );

private:
	static string DirectoryLightmaps;
};

#endif //LIGHTMAP_H

