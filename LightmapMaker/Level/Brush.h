//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// Связь со мной:		https://vk.com/zombihello
// Репозиторий движка:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef BRUSH_H
#define BRUSH_H

///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
///////////////////////////
#include <vector>
#include <tinyxml.h>
using namespace std;

///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "Plane.h"

class Brush
{
public:
	/* ДЕСТРУКТОР */
	~Brush();

	/* СОЗДАТЬ БРАШ */
	void Create( TiXmlElement& Element );

	/* ОТРЕНДЕРИТЬ БРАШ */
	void Render();

	/* ПОЛУЧИТЬ ВСЕ ПЛОСКОСТИ БРАША */
	vector<Plane*>& GetPlanes();

private:
	GLuint							VertexBuffer;
	vector<Plane*>					Planes;

	static vector<unsigned int>		IdVertex;
};

#endif // !BRUSH_H

