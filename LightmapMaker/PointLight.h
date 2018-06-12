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

////////////////
// GLM
////////////////
#include <glm\glm.hpp>

//////////
// XML
//////////
#include <tinyxml.h>

class PointLight
{
public:
	/* Конструктор */
	PointLight();

	/* Конструктор */
	PointLight( TiXmlElement& ElementEntity );

	/* Вычислить затухание света */
	float CalculateAttenuation( float Distance );

	float			Intensivity;
	float			Radius;

	glm::vec3		Position;
	glm::vec4		Color;
};

#endif //POINT_LIGHT_H
