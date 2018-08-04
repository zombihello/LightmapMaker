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
#include "../System/ResourcesManager.h"
#include "../System/Ray.h"
#include "BrushVertex.h"
#include "Triangle.h"

class Plane
{
public:
	/* КОНСТРУКТОР */
	Plane();

	/* ДЕСТРУКТОР */
	~Plane();

	/* ИНИЦИАЛИЗИРОВАТЬ ПЛОСКОСТЬ */
	void InitPlane( const GLuint& VertexBuffer, const vector<unsigned int>& PlaneIdVertex, const vector<BrushVertex>& PlaneVertexes, const string& NameTexture );

	/* ОТРЕНДЕРИТЬ ПЛОСКОСТЬ */
	void Render();

	/* СГЕНЕРИРОВАТЬ OPENGL-ОВСКУЮ ТЕКСТУРУ С Data_LightMap */
	void GenerateGLTexture();

	/* ПОЛУЧИТЬ ПОЗИЦИЮ ФРАГМЕНТА В МИРЕ */
	void GetPositionFragment( float UFactor, float VFactor, glm::vec3& PositionOut );

	/* ПЕРЕСИКАЕТ ЛИ ЛУЧ ПЛОСКОСТЬ */
	bool IsRayIntersect( Ray& Ray );

	bool operator!=( Plane& Plane );

	GLuint					GL_LightMap;
	GLuint					GL_DiffuseMap;
	sf::Image				Data_LightMap;

	glm::u8vec2*			SizeLightmap;
	glm::vec3*				Normal;

private:
	unsigned int			CountIndexs;
	
	Triangle				Triangles[ 2 ];
	OpenGL_API::VAO			VAO;
};

#endif // !PLANE_H
