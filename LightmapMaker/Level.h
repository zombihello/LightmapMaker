//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// ����� �� ����:		https://vk.com/zombihello
// ����������� ������:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef LEVEL_H
#define LEVEL_H

///////////////////////////
// ��������� ����������
///////////////////////////
#include <vector>
using namespace std;

//////////
// XML
//////////
#include <tinyxml.h>

///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "Logger.h"
#include "Triangle.h"
#include "PointLight.h"

class Level
{
public:
	/* ��������� ������� */
	bool LoadLevel( const string& Route );

	/* �������� ��� ����������� �� ������ */
	vector<Triangle>& GetTriangles();

	/* �������� ��� �������� ��������� ����� �� ������ */
	vector<PointLight>& GetPointLights();
private:
	vector<Triangle>		Triangles;
	vector<PointLight>		PointLights;
};

#endif // LEVEL_H