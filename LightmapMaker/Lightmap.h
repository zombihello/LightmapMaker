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

#define NUM_THREADS thread::hardware_concurrency()

///////////////////////////
// —»—“≈ћЌџ≈ Ѕ»ЅЋ»ќ“≈ »
///////////////////////////
#include <vector>
#include <string>
#include <mutex>
#include <thread>
using namespace std;

///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "Level.h"
#include "Ray.h"

//-------------------------------------------------------------------------//

class Lightmap
{
public:
	/* —генерировать карту освещени¤ */
	static void Generate( size_t Size, vector<Triangle>& Triangles, vector<PointLight>& PointLights );
	
	/* Включить тени */
	static void EnableShadows( bool Enable );

	/* «адать директорию в которую будут сохран¤тьс¤ освещение */
	static void SetDirectoryForLightmaps( const string& Directory );
private:
	/* Просчитать карту освещения */
	static void Calculate( mutex& Mutex, size_t Size, int IdStartTriangle, vector<Triangle*>& Triangles, vector<Triangle>& Geometry, vector<PointLight>& PointLights );

	static bool IsEnableShadows;
	static int CountCalculateLightMaps;
	static string DirectoryLightmaps;
};

//-------------------------------------------------------------------------//

#endif //LIGHTMAP_H

