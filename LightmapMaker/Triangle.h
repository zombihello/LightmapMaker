//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// Связь со мной:		https://vk.com/zombihello
// Репозиторий движка:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef TRIANGLE_H
#define TRIANGLE_H

////////////////
// GLM
////////////////
#include <glm\glm.hpp>

///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "Image.h"

class Triangle
{
public:
	/* Конструктор */
	Triangle();

	/* Конструктор */
	Triangle( const glm::vec3& Vertex_A, const glm::vec3& Vertex_B, const glm::vec3& Vertex_C  );

	bool operator!=( Triangle& Triangle );

	Image		LightMap;

	glm::vec3	A;
	glm::vec3	B;
	glm::vec3	C;
	glm::vec3	Normal;
	glm::vec3	UVVector;
	glm::vec3	Edge1;
	glm::vec3	Edge2;
};

#endif // TRIANGLE_H