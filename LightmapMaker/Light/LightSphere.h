//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// Связь со мной:		https://vk.com/zombihello
// Репозиторий движка:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef LIGHT_SPHERE_H
#define LIGHT_SPHERE_H

///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "../OpenGL/OpenGL.h"

class LightSphere
{
public:
	/* КОНСТРУКТОР */
	LightSphere();
	LightSphere( const LightSphere& Copy );

	/* ДЕСТРУКТОР */
	~LightSphere();

	/* ИНИЦИАЛИЗИРОВАТЬ СФЕРУ */
	void InitSphere( const float& Radius );

	/* ОТРЕНДЕРИТЬ СФЕРУ */
	void Render();

	/* ЗАДАТЬ ПОЗИЦИЮ */
	void SetPosition( const glm::vec3& Position );

	/* ЗАДАТЬ РАДИУС */
	void SetRadius( const float& Radius );

	/* ПОЛУЧИТЬ РАДИУС СФЕРЫ */
	const float& GetRadius();

	/* ПОЛУЧИТЬ ПОЗИЦИЮ СФЕРЫ */
	const glm::vec3& GetPosition();

	/* ПОЛУЧИТЬ МАТРИЦУ ТРАНСФОРМАЦИИ */
	glm::mat4& GetTransformation();

	LightSphere& operator=( const LightSphere& Copy );

private:
	/* СГЕНЕРИРОВАТЬ ВЕРШИНЫ СФЕРЫ */
	vector<glm::vec3>	CreateSphere( const float& Radius );

	bool							Created;
	float							Radius;

	OpenGL_API::VAO					VAO;
	glm::vec3						Position;
	glm::mat4						Transformation;

	static vector<unsigned int>		IdVertex;
};

#endif // !LIGHT_SPHERE_H

