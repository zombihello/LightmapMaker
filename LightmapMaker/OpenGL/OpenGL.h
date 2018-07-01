//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// Связь со мной:		https://vk.com/zombihello
// Репозиторий движка:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef OPENGL_H
#define OPENGL_H

///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
///////////////////////////
#include <glew\glew.h>
#include <glm\glm.hpp>
#include <SFML\Graphics.hpp>

///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "Shader.h"

//-------------------------------------------------------------------------//

namespace OpenGL_API
{
	/* Инициализировать OpenGL */
	void InitOpenGL( sf::RenderWindow& RenderWindow );
}

//-------------------------------------------------------------------------//

#endif // !OPENGL_H
