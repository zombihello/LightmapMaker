//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// Связь со мной:		https://vk.com/zombihello
// Репозиторий движка:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
///////////////////////////
#include <glm\glm.hpp>
#include <tinyxml.h>
using namespace std;

struct PointLight
{
	/* КОНСТРУКТОР */
	PointLight();
	PointLight( TiXmlElement& Element );

	/* ВЫЧИСЛИТЬ ЗАТУХАНИЕ СВЕТА */
	float CalculateAttenuation( float Distance );

	float				Intensivity;
	float				Radius;

	glm::vec3			Position;
	glm::vec3			Color;
};

#endif // !POINT_LIGHT_H
