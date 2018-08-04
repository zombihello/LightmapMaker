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
#include "../System/Timer.h"

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
	/* СГЕНЕРИРОВАТЬ ПЕРВИЧНОЕ ОСВЕЩЕНИЕ */
	void GeneratePrimaryIllumination();

	/* СГЕНЕРИРОВАТЬ ВТОРИЧНОЕ ОСВЕЩЕНИЕ */
	void GenerateSecondaryLight();

	/* ОТРИСОВАТЬ СЦЕНУ */
	void RenderScene();

	glm::vec3								AmbienceColor;
	glm::mat4								Projection;
	glm::mat4								PV; // Projection * View

	OpenGL_API::RenderTexture				RenderTexture;
	OpenGL_API::Shader*						Shader_RenderPlane;
	Camera									Camera;

	vector<Plane*>							Planes;
	map< GLuint, vector<Plane*> >			PlanesRender;
	vector<PointLight>*						PointLights;
	vector<SpotLight>*						SpotLights;
	vector<DirectionalLight>*				DirectionalLights;
};

#endif // !LIGHTMAP_H
