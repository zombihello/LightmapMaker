//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// Связь со мной:		https://vk.com/zombihello
// Репозиторий движка:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef PLANE_H
#define PLANE_H

///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "../OpenGL/OpenGL.h"
#include "../System/ArgumentsStart.h"
#include "BrushVertex.h"

class Plane
{
public:
	/* КОНСТРУКТОР */
	Plane();

	/* ДЕСТРУКТОР */
	~Plane();

	/* ИНИЦИАЛИЗИРОВАТЬ ПЛОСКОСТЬ */
	void InitPlane( const GLuint& VertexBuffer, const vector<unsigned int>& PlaneIdVertex, const vector<BrushVertex>& PlaneVertexes );

	/* ОТРЕНДЕРИТЬ ПЛОСКОСТЬ */
	void Render();

	/* СГЕНЕРИРОВАТЬ OPENGL-ОВСКУЮ ТЕКСТУРУ С Data_LightMap */
	void GenerateGLTexture();

	/* ПОЛУЧИТЬ ПОЗИЦИЮ ФРАГМЕНТА В МИРЕ */
	void GetPositionFragment( float UFactor, float VFactor, glm::vec3& PositionOut );

	/* ПОЛУЧИТЬ РАЗМЕР КАРТЫ ОСВЕЩЕНИЯ */
	glm::vec2& GetSizeLightmap();

	/* ПОЛУЧИТЬ НОРМАЛЬ ПЛОСКОСТИ */
	glm::vec3& GetNormal();

	/* ПОЛУЧИТЬ КАРТУ ОСВЕЩЕНИЯ */
	sf::Image& GetDataLightMap();

private:
	unsigned int			CountIndexs;

	GLuint					GL_LightMap;
	sf::Image				Data_LightMap;
	OpenGL_API::VAO			VAO;

	glm::vec2				SizeLightmap;
	glm::vec3				Normal;
	glm::vec3				UVVector;
	glm::vec3				Edge1;
	glm::vec3				Edge2;
};

#endif // !PLANE_H
