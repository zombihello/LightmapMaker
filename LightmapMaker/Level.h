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
#include "SpotLight.h"
#include "DirectionalLight.h"

class Level
{
public:
	/* Загрузить уровень */
	bool LoadLevel( const string& Route );

	/* Получить цвет окружающей среды */
	glm::vec4& GetAmbienceColor();

	/* Получить все плоскости на уровне */
	vector<Plane>& GetPlanes();

	/* Получить все точечные источники света на уровне */
	vector<PointLight>& GetPointLights();

	/* Получить все прожекторные источники света на уровне */
	vector<SpotLight>& GetSpotLights();

	/* Получить все направленные источники света на уровне */
	vector<DirectionalLight>& GetDirectionalLights();

private:
	glm::vec4						AmbienceColor;

	vector<Plane>					Planes;
	vector<PointLight>				PointLights;
	vector<SpotLight>				SpotLights;
	vector<DirectionalLight>		DirectionalLights;
};

#endif // LEVEL_H