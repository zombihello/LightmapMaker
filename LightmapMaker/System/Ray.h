//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// Связь со мной:		https://vk.com/zombihello
// Репозиторий движка:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef RAY_H
#define RAY_H

///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
///////////////////////////
#include <glm\glm.hpp>

///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "../Level/Triangle.h"

class Ray
{
public:
	/* ЗАДАТЬ ЛУЧ */
	void SetRay( const glm::vec3& StartRay, const glm::vec3& EndRay );

	/* ПЕРЕСИКАЕТ ЛИ ЛУЧ ТРЕУГОЛЬНИК */
	bool IntersectTriangle( Triangle& Triangle );

	glm::vec3 StartRay;
	glm::vec3 EndRay;
	glm::vec3 Direction;
	glm::vec3 Reverse_Direction;
	glm::vec3 Normalize_Direction;
};

#endif // !RAY_H