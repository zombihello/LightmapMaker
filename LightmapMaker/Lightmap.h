//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// ����� �� ����:		https://vk.com/zombihello
// ����������� ������:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef LIGHTMAP_H
#define LIGHTMAP_H

///////////////////////////
// ��������� ����������
///////////////////////////
#include <vector>
#include <string>
using namespace std;

///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "Level.h"
#include "Ray.h"

class Lightmap
{
public:
	/* ������������� ����� ��������� */
	static void Generate( size_t Size, vector<Triangle>& Triangles, vector<PointLight>& PointLights );
	
	/* ������ ���������� � ������� ����� ����������� ��������� */
	static void SetDirectoryForLightmaps( const string& Directory );

private:
	static string DirectoryLightmaps;
};

#endif //LIGHTMAP_H

