//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// ����� �� ����:		https://vk.com/zombihello
// ����������� ������:  https://github.com/zombihello/LightmapMaker
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
	/* ����������� */
	PointLight();

	/* ����������� */
	PointLight( TiXmlElement& ElementEntity );

	float			Intensivity;
	float			Radius;

	glm::vec3		Position;
	glm::vec4		Color;
};

#endif //POINT_LIGHT_H
