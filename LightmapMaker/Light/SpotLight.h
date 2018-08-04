//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// Связь со мной:		https://vk.com/zombihello
// Репозиторий движка:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
///////////////////////////
#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>
#include <tinyxml.h>

class SpotLight
{
public:
	/* КОНСТРУКТОР */
	SpotLight();
	SpotLight( TiXmlElement& ElementEntity );

	/* ВЫЧИСЛИТЬ ЗАТУХАНИЕ СВЕТА */
	float CalculateAttenuation( float Distance );

	float			Intensivity;
	float			SpotCutoff;
	float			Radius;
	float			Height;

	glm::vec3		Position;
	glm::vec3		SpotDirection;
	glm::vec3		Rotation;
	glm::vec3		Color;
};

#endif // !SPOT_LIGHT_H

