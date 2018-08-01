//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// Связь со мной:		https://vk.com/zombihello
// Репозиторий движка:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef LIGHTMAP_H
#define LIGHTMAP_H

///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "../OpenGL/OpenGL.h"
#include "../Level/Level.h"
#include "../System/Camera.h"
#include "../System/Logger.h"
#include "../System/Directories.h"
#include "../System/Error.h"

class Lightmap
{
public:
	/* ДЕСТРУКТОР */
	~Lightmap();

	/* ИНИЦИАЛИЗИРОВАТЬ ИНФОРМАЦИЮ ДЛЯ ПРОСЧЕТОВ */
	void InitLightmap( Level& Level );

	/* СГЕНЕРИРОВАТЬ КАРТУ ОСВЕЩЕНИЯ */
	void Generate();

private:
	/* ОТРИСОВАТЬ СЦЕНУ СО ВЗГЛЯДА ПАТЧА */
	sf::Color PathRender();

	/* ОТРИСОВАТЬ СЦЕНУ */
	void RenderScene();

	glm::mat4						Projection;
	glm::mat4						PV; // Projection * View
	glm::mat4						PVT; // Projection * View * Transform

	OpenGL_API::RenderTexture		RenderTexture;
	OpenGL_API::Shader*				Shader_RenderPlane;
	OpenGL_API::Shader*				Shader_RenderLight;
	Camera							Camera;

	vector<Plane*>					Planes;
	vector<PointLight>*				PointLights;
};

#endif // !LIGHTMAP_H
