//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// ����� �� ����:		https://vk.com/zombihello
// ����������� ������:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef PLANE_H
#define PLANE_H

///////////////////////////
// ��������� ����������
///////////////////////////
#include <vector>
using namespace std;

///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "Triangle.h"

struct Plane
{
	bool operator!=( Triangle& Triangle );

	Image			LightMap;
	Triangle		Triangles[2];
};

#endif // PLANE_H