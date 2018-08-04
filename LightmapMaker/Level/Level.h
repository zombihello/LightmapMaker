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
#include <string>
#include <glm\glm.hpp>
#include <tinyxml.h>
using namespace std;

///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "../System/ResourcesManager.h"
#include "../Light/PointLight.h"
#include "../Light/SpotLight.h"
#include "../Light/DirectionalLight.h"
#include "Brush.h"

class Level
{
public:
	/* ДЕСТРУКТОР */
	~Level();

	/* ЗАГРУЗИТЬ УРОВЕНЬ */
	bool LoadLevel( const string& Route );

	/* ОЧИСТИТЬ УРОВЕНЬ */
	void Clear();

	/* ПОЛУЧИТЬ ЦВЕТ ОКРУЩАЮЩЕЙ СРЕДЫ */
	glm::vec3& GetAmbienceColor();

	/* ПОЛУЧИТЬ БРАШИ УРОВНЯ */
	vector<Brush*>& GetBrushes();

	/* ПОЛУЧИТЬ ТОЧЕЧНЫЕ ИСТОЧНИКИ СВЕТА */
	vector<PointLight>& GetPointLights();

	/* ПОЛУЧИТЬ ПРОЖЕКТОРНЫЕ ИСТОЧНИКИ СВЕТА */
	vector<SpotLight>& GetSpotLights();

	/* ПОЛУЧИТЬ НАПРАВЛЕНЫЕ ИСТОЧНИКИ СВЕТА */
	vector<DirectionalLight>& GetDirectionalLights();

private:
	glm::vec3						AmbienceColor;

	vector<Brush*>					Brushes;
	vector<PointLight>				PointLights;
	vector<SpotLight>				SpotLights;
	vector<DirectionalLight>		DirectionalLights;
};

#endif // !LEVEL_H

