//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// —в¤зь со мной:		https://vk.com/zombihello
// –епозиторий движка:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef LIGHTMAP_H
#define LIGHTMAP_H

///////////////////////////
// —»—“≈ћЌџ≈ Ѕ»ЅЋ»ќ“≈ »
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
	/* —генерировать карту освещени¤ */
	static void Generate( size_t Size, vector<Triangle>& Triangles, vector<PointLight>& PointLights );
	
	/* «адать директорию в которую будут сохран¤тьс¤ освещение */
	static void SetDirectoryForLightmaps( const string& Directory );

private:
	static string DirectoryLightmaps;
};

#endif //LIGHTMAP_H

