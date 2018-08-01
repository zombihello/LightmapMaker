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
#include "../OpenGL/OpenGL.h"
#include "../Level/Level.h"
#include "../System/Camera.h"
#include "../System/Logger.h"
#include "../System/Directories.h"
#include "../System/Error.h"

class Lightmap
{
public:
	/* ���������������� ���������� ��� ��������� */
	void InitLightmap( Level& Level );

	/* ������������� ����� ��������� */
	void Generate( sf::RenderWindow& Window );

private:
	/* ���������� ����� �� ������� ����� */
	sf::Color PathRender();

	/* ���������� ����� */
	void RenderScene();

	glm::mat4						Projection;
	glm::mat4						PV; // Projection * View
	glm::mat4						PVT; // Projection * View * Transform

	OpenGL_API::RenderTexture		RenderTexture;
	OpenGL_API::Shader				Shader_RenderPlane;
	OpenGL_API::Shader				Shader_RenderLight;
	Camera							Camera;

	vector<Plane*>					Planes;
	vector<PointLight>*				PointLights;
};

#endif // !LIGHTMAP_H
