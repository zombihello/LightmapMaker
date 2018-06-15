//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// Связь со мной:		https://vk.com/zombihello
// Репозиторий движка:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

////////////////
// GLM
////////////////
#include <glm\glm.hpp>

//////////
// XML
//////////
#include <tinyxml.h>

class DirectionalLight
{
public:
	/* Конструктор */
	DirectionalLight();

	/* Конструктор */
	DirectionalLight( TiXmlElement& ElementEntity );

	float			Intensivity;

	glm::vec3		Position;
	glm::vec4		Color;
};

#endif // DIRECTIONAL_LIGHT_H