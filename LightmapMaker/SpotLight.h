//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// ����� �� ����:		https://vk.com/zombihello
// ����������� ������:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

////////////////
// GLM
////////////////
#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>

//////////
// XML
//////////
#include <tinyxml.h>

class SpotLight
{
public:
	/* ����������� */
	SpotLight();

	/* ����������� */
	SpotLight( TiXmlElement& ElementEntity );

	/* ��������� ��������� ����� */
	float CalculateAttenuation( float Distance );

	float			Intensivity;
	float			SpotCutoff;
	float			Radius;
	float			Height;

	glm::vec3		Position;
	glm::vec3		SpotDirection;
	glm::vec3		Rotation;
	glm::vec4		Color;
};

#endif // SPOT_LIGHT_H