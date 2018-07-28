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
// LIGHTMAPMAKER
///////////////////////////
#include "../Level/Level.h"

class Lightmap
{
public:
	/* ���������������� ���������� ��� ��������� */
	void InitLightmap( Level& Level );

	/* ������������� ����� ��������� */
	void Generate( sf::RenderWindow& Window );

private:

	vector<Plane*>		Planes;
};

#endif // !LIGHTMAP_H
