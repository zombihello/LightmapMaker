//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// Связь со мной:		https://vk.com/zombihello
// Репозиторий движка:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef IMAGE_H
#define IMAGE_H

///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
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
	/* Создать изображение и заполнить ее цветом */
	void Create( size_t Width, size_t Height, const glm::vec4& Color = glm::vec4( 0, 0, 0, 255 ) );
	
	/* Сохранить изображение в файл */
	void SaveInFile( const string& Route );

	/* Очистить массив пикселей */
	void Clear();

	/* Задать цвет пикселя */
	void SetPixel( size_t X, size_t Y, const glm::vec4& Color );

private:
	glm::vec2			Size;
	vector<uint8_t>		Pixels;
};

#endif // IMAGE_H