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

///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
///////////////////////////
#include <glm\glm.hpp>

class Triangle
{
public:
	/* КОНСТРУКТОР */
	Triangle();
	Triangle( const glm::vec3& Vertex_A, const glm::vec3& Vertex_B, const glm::vec3& Vertex_C );

	/* ИНИЦИАЛИЗИРОВАТЬ ТРЕУГОЛЬНИК */
	void InitTriangle( const glm::vec3& Vertex_A, const glm::vec3& Vertex_B, const glm::vec3& Vertex_C );

	glm::vec3		A;
	glm::vec3		B;
	glm::vec3		C;
	glm::u8vec2		SizeLightmap;
	glm::vec3		Normal;
	glm::vec3		UVVector;
	glm::vec3		Edge1;
	glm::vec3		Edge2;
};

#endif // !TRIANGLE_H
