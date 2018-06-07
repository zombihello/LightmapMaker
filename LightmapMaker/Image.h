//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// ����� �� ����:		https://vk.com/zombihello
// ����������� ������:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef IMAGE_H
#define IMAGE_H

///////////////////////////
// ��������� ����������
///////////////////////////
#include <vector>
using namespace std;

////////////////
// GLM
////////////////
#include <glm\glm.hpp>

///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "Logger.h"

class Image
{
public:
	/* ������� ����������� � ��������� �� ������ */
	void Create( size_t Width, size_t Height, const glm::vec4& Color = glm::vec4( 0, 0, 0, 255 ) );
	
	/* ��������� ����������� � ���� */
	void SaveInFile( const string& Route );

	/* �������� ������ �������� */
	void Clear();

	/* ������ ���� ������� */
	void SetPixel( size_t X, size_t Y, const glm::vec4& Color );

private:
	glm::vec2			Size;
	vector<uint8_t>		Pixels;
};

#endif // IMAGE_H