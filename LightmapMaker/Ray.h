//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// ����� �� ����:		https://vk.com/zombihello
// ����������� ������:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef RAY_H
#define RAY_H

////////////////
// GLM
////////////////
#include <glm\glm.hpp>

///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "Triangle.h"

class Ray
{
public:
	/* ������ ��� */
	void SetRay( const glm::vec3& StartRay, const glm::vec3& EndRay );

	/* ���������� �� ��� ����������� */
	bool IntersectTriangle( Triangle& Triangle );

	glm::vec3 StartRay;
	glm::vec3 EndRay;
	glm::vec3 Direction;
	glm::vec3 Normalize_Direction;
};

#endif // RAY_H
