//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// Связь со мной:		https://vk.com/zombihello
// Репозиторий движка:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef RESOURCES_MANAGER_H
#define RESOURCES_MANAGER_H

///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
///////////////////////////
#include <string>
#include <map>
using namespace std;

///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "../OpenGL/OpenGL.h"
#include "Logger.h"

class ResourcesManager
{
public:
	/* ЗАГРУЗИТЬ OPENGL ТЕКСТУРУ */
	static bool LoadGlTexture( const string& NameTexture, const string& RouteToFile );

	/* СОЗДАТЬ ШЕЙДЕР */
	static OpenGL_API::Shader* CreateShader( const string& NameShader );

	/* УДАЛИТЬ OPENGL ТЕКСТУРУ */
	static void DeleteGlTexture( const string& NameTexture );

	/* УДАЛИТЬ ШЕЙДЕР */
	static void DeleteShader( const string& NameShader );

	/* УДАЛИТЬ OPENGL ТЕКСТУРУ */
	static void DeleteAllGlTexture();

	/* УДАЛИТЬ ВСЕ ШЕЙДЕРА */
	static void DeleteAllShaders();

	/* УДАЛИТЬ ВСЕ РЕСУРСЫ */
	static void DeleteAllResources();

	/* ПОЛУЧИТЬ OPENGL ТЕКСТУРУ */
	static const GLuint GetGlTexture( const string& NameTexture );

	/* ПОЛУЧИТЬ ШЕЙДЕР */
	static OpenGL_API::Shader* GetShader( const string& NameShader );

private:
	static map<string, GLuint>						GlTextures;
	static map<string, OpenGL_API::Shader>			Shaders;
};

#endif // !RESOURCES_MANAGER_H
