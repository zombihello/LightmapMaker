//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// Связь со мной:		https://vk.com/zombihello
// Репозиторий движка:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef LEVEL_H
#define LEVEL_H

///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
///////////////////////////
#include <vector>
using namespace std;

//////////
// XML
//////////
#include <tinyxml.h>

///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "Logger.h"
#include "Plane.h"
#include "PointLight.h"

class Level
{
public:
	/* Загрузить уровень */
	bool LoadLevel( const string& Route );

	/* Получить все плоскости на уровне */
	vector<Plane>& GetPlanes();

	/* Получить все точечные источники света на уровне */
	vector<PointLight>& GetPointLights();

private:
	vector<Plane>			Planes;
	vector<PointLight>		PointLights;
};

#endif // LEVEL_H