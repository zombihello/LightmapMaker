//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// Связь со мной:		https://vk.com/zombihello
// Репозиторий движка:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef RENDER_TEXTURE_H
#define RENDER_TEXTURE_H

///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
///////////////////////////
#include <SFML\Graphics.hpp>
#include <glew\glew.h>
#include <glm\glm.hpp>

//-------------------------------------------------------------------------//

namespace OpenGL_API
{
	class RenderTexture
	{
	public:
		/* КОНСТРУКТОР */
		RenderTexture();
		RenderTexture( size_t Width, size_t Height );

		/* ДЕСТРУКТОР */
		~RenderTexture();

		/* СОЗДАТЬ ТЕКСТУРУ */
		bool Create( size_t Width, size_t Height );

		/* ПОЛУЧИТЬ УСРЕДНЕНЫЙ ЦВЕТ ТЕКСТУРЫ */
		sf::Color GetMediumColorTexture();

		/* АКТИВИРОВАТЬ ТЕКСТУРУ ДЛЯ РЕНДЕРА В НЕЕ */
		void Bind();

		/* ОТВЯЗАТЬ ТЕКСТУРУ ОТ РЕНДЕРА */
		void Unbind();

		/* ПОЛУЧИТЬ ТЕКСТУРУ */
		GLuint& GetTexture();

	private:
		bool			IsCreate;
		int				NumLevelsMipmap;

		glm::vec2		Size;
		glm::vec3		MediumColor;

		GLuint			FrameBuffer;
		GLuint			Texture;
		GLuint			DepthBuffer;
	};
}

//-------------------------------------------------------------------------//

#endif // !RENDER_TEXTURE_H
