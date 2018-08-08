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
#include "Sphere.h"

struct PointLight
{
	/* КОНСТРУКТОР */
	PointLight();
	PointLight( const PointLight& Copy );
	PointLight( TiXmlElement& Element );

	/* ВЫЧИСЛИТЬ ЗАТУХАНИЕ СВЕТА */
	float CalculateAttenuation( float Distance );

	PointLight& operator=( const PointLight& Copy );

	float				Intensivity;
	float				Radius;

	Sphere				Sphere;

	glm::vec3			Position;
	glm::vec3			Color;
};

#endif // !POINT_LIGHT_H
