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

///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
///////////////////////////
#include <glm\glm.hpp>
#include <tinyxml.h>

class DirectionalLight
{
public:
	/* КОНСТРУКТОР */
	DirectionalLight();
	DirectionalLight( TiXmlElement& ElementEntity );

	float			Intensivity;

	glm::vec3		Position;
	glm::vec3		Color;
};

#endif // !DIRECTIONAL_LIGHT_H