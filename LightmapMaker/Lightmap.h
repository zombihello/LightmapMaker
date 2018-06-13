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
	void Generate( vector<Plane>& Planes, vector<PointLight>& PointLights );
	
	/* Задать директорию в которую будут сохраняться освещение */
	static void SetDirectoryForLightmaps( const string& Directory );

private:
	/* Просчитать карту освещения */
	void Calculate( mutex& Mutex, int IdStartTriangle, vector<Plane*>& Planes, vector<Plane>& Geometry, vector<PointLight>& PointLights );

	int					CountCalculateLightMaps;	
	static string		DirectoryLightmaps;
};

//-------------------------------------------------------------------------//

#endif //LIGHTMAP_H

