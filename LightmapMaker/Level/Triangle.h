//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// Ñâÿçü ñî ìíîé:		https://vk.com/zombihello
// Ğåïîçèòîğèé äâèæêà:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef TRIANGLE_H
#define TRIANGLE_H

///////////////////////////
// ÑÈÑÒÅÌÍÛÅ ÁÈÁËÈÎÒÅÊÈ
///////////////////////////
#include <glm\glm.hpp>

///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "../System/ArgumentsStart.h"
#include "BrushVertex.h"

struct Triangle
{
	/* ÊÎÍÑÒĞÓÊÒÎĞ */
	Triangle();
	Triangle( const BrushVertex& Vertex_A, const BrushVertex& Vertex_B, const BrushVertex& Vertex_C );

	/* ÈÍÈÖÈÀËÈÇÈĞÎÂÀÒÜ ÒĞÅÓÃÎËÜÍÈÊ */
	void InitTriangle( const BrushVertex& Vertex_A, const BrushVertex& Vertex_B, const BrushVertex& Vertex_C );

	BrushVertex		Vertex_A;
	BrushVertex		Vertex_B;
	BrushVertex		Vertex_C;

	glm::vec2		SizeLightmap;
	glm::vec3		Normal;
	glm::vec3		UVVector;
	glm::vec3		Edge1;
	glm::vec3		Edge2;
};

#endif // !TRIANGLE_H
