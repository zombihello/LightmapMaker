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
	/* Сгенерировать карту освещения */
	static void Generate( vector<Plane>& Planes, vector<PointLight>& PointLights );
	
	/* Включить тени */
	static void EnableShadows( bool Enable );

	/* Задать директорию в которую будут сохраняться освещение */
	static void SetDirectoryForLightmaps( const string& Directory );

	static int MaxSizeLightmap;

private:
	/* Просчитать карту освещения */
	static void Calculate( mutex& Mutex, int IdStartTriangle, vector<Plane*>& Planes, vector<Plane>& Geometry, vector<PointLight>& PointLights );

	static bool IsEnableShadows;
	static int CountCalculateLightMaps;	
	static string DirectoryLightmaps;
};

//-------------------------------------------------------------------------//

#endif //LIGHTMAP_H

