//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// ����� �� ����:		https://vk.com/zombihello
// ����������� ������:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef TRIANGLE_H
#define TRIANGLE_H

///////////////////////////
// ��������� ����������
///////////////////////////
#include <glm\glm.hpp>

///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "../System/ArgumentsStart.h"
#include "BrushVertex.h"

struct Triangle
{
	/* ����������� */
	Triangle();
	Triangle( const BrushVertex& Vertex_A, const BrushVertex& Vertex_B, const BrushVertex& Vertex_C );

	/* ���������������� ����������� */
	void InitTriangle( const BrushVertex& Vertex_A, const BrushVertex& Vertex_B, const BrushVertex& Vertex_C );

	BrushVertex		Vertex_A;
	BrushVertex		Vertex_B;
	BrushVertex		Vertex_C;

	glm::vec2		SizeLightmap;
	glm::vec3		Normal;
	glm::vec3		UVVector;
	glm::vec3		Edge1;
	glm::vec3		Edge2;

private:

	/* ����� ����������� �������� � �������� */
	void FindMin( const glm::vec2& Vec1, const glm::vec2& Vec2, glm::vec2& Out );

	/* ����� ������������ �������� � �������� */
	void FindMax( const glm::vec2& Vec1, const glm::vec2& Vec2, glm::vec2& Out );
};

#endif // !TRIANGLE_H
