//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// Связь со мной:		https://vk.com/zombihello
// Репозиторий движка:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef SHADER_H
#define SHADER_H

///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
///////////////////////////
#include <string>
#include <map>
#include <glew\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
using namespace std;

//-------------------------------------------------------------------------//

namespace OpenGL_API
{
	class Shader
	{
	public:
		/* Конструктор */
		Shader();
		Shader( map<string, int>& AttribLocation );

		/* Деструктор */
		~Shader();

		/* Активировать выбранный шейдер */
		static void Bind( const Shader* Shader );

		/* Загрузить шейдер с файла */
		bool LoadFromFile( const string& VertexShader, const string& FragmentShader );
		bool LoadFromFile( const string& VertexShader, const string& GeometryShader, const string& FragmentShader );

		/* Загрузить шейдер с памяти */
		bool LoadFromMemory( const string& VertexShader, const string& FragmentShader );
		bool LoadFromMemory( const string& VertexShader, const string& GeometryShader, const string& FragmentShader );

		/* Задать позицию атрибутов вершин в шейдере (применять перед загрузкой шейдера) */
		void SetAttribLocation( map<string, int>& AttribLocation );

		/* Задать значение юниформ переменной */
		void SetUniform( const std::string& Name, bool X );	
		void SetUniform( const std::string& Name, int X );
		void SetUniform( const std::string& Name, float X );
		void SetUniform( const std::string& Name, GLuint& X );
		void SetUniform( const std::string& Name, glm::mat4& Matrix );
		void SetUniform( const std::string& Name, glm::vec2& Vector2 );
		void SetUniform( const std::string& Name, glm::vec3& Vector3 );
		void SetUniform( const std::string& Name, glm::vec4& Vector4 );

		/* Получить ID шейдера в OpenGL */
		const GLuint& GetNativeHandle();

	private:

		/* Скомпилировать шейдер */
		bool Compile( const string& VertexShader, const string& GeometryShader, const string& FragmentShader );

		/* Получить идентификатор расположения юниформ переменной */
		int GetUniformLocation( const string& NameUniform );

		GLuint					VertexID;
		GLuint					GeometryID;
		GLuint					FragmentID;
		GLuint					ProgramID;

		map<string, int>		AttribLocation;
		map<string, int>		Uniforms;
	};
}

//-------------------------------------------------------------------------//

#endif // !SHADER_H
