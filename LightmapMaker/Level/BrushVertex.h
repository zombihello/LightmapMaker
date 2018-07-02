//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// Связь со мной:		https://vk.com/zombihello
// Репозиторий движка:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef BRUSH_VERTEX_H
#define BRUSH_VERTEX_H

///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
///////////////////////////
#include <glm\glm.hpp>

struct BrushVertex
{
	glm::vec3		Position;
	glm::vec2		TextureCoord_LightMap;

	bool operator==( BrushVertex& BrushVertex );
};

#endif // !BRUSH_VERTEX_H

