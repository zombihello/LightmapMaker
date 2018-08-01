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
	const glm::vec4& GetAmbienceColor();

	/* ПОЛУЧИТЬ БРАШИ УРОВНЯ */
	vector<Brush*>& GetBrushes();

	/* ПОЛУЧИТЬ ТОЧЕЧНЫЕ ИСТОЧНИКИ СВЕТА */
	vector<PointLight>& GetPointLights();

private:
	glm::vec4				AmbienceColor;

	vector<Brush*>			Brushes;
	vector<PointLight>		PointLights;
};

#endif // !LEVEL_H

