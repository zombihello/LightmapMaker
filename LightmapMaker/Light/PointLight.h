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

///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "LightSphere.h"

struct PointLight
{
	/* КОНСТРУКТОР */
	PointLight();
	PointLight( const PointLight& Copy );
	PointLight( TiXmlElement& Element );

	PointLight& operator=( const PointLight& Copy );

	float				Intensivity;
	float				Radius;

	glm::vec3			Position;
	glm::vec4			Color;
	LightSphere			LightSphere;
};

#endif // !POINT_LIGHT_H
