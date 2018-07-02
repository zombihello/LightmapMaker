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

class Plane
{
public:
	/* ИНИЦИАЛИЗИРОВАТЬ ПЛОСКОСТЬ */
	void InitPlane( const GLuint& VertexBuffer, const vector<unsigned int>& PlaneIdVertex );

	/* ОТРЕНДЕРИТЬ ПЛОСКОСТЬ */
	void Render();

private:
	unsigned int			CountIndexs;

	GLuint					LightMap;
	OpenGL_API::VAO			VAO;
};

#endif // !PLANE_H
