//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// —в¤зь со мной:		https://vk.com/zombihello
// –епозиторий движка:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef IMAGE_H
#define IMAGE_H

///////////////////////////
// —»—“≈ћЌџ≈ Ѕ»ЅЋ»ќ“≈ »
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
	/* —оздать изображение и заполнить ее цветом */
	void Create( size_t Width, size_t Height, const glm::vec4& Color = glm::vec4( 0, 0, 0, 255 ) );
	
	/* —охранить изображение в файл */
	void SaveInFile( const string& Route );

	/* ќчистить массив пикселей */
	void Clear();

	/* «адать цвет пиксел¤ */
	void SetPixel( size_t X, size_t Y, const glm::vec4& Color );

private:
	glm::vec2			Size;
	vector<uint8_t>		Pixels;
};

#endif // IMAGE_H