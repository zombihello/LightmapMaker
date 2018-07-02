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
		/* КОНСТРУКТОР */
		Shader();
		Shader( map<string, int>& AttribLocation );

		/* ДЕСТРУКТОР */
		~Shader();

		/* АКТИВИРОВАТЬ ВЫБРАНЫЙ ШЕЙДЕР */
		static void Bind( const Shader* Shader );

		/* ЗАГРУЗИТЬ ШЕЙДЕР С ФАЙЛА */
		bool LoadFromFile( const string& VertexShader, const string& FragmentShader );
		bool LoadFromFile( const string& VertexShader, const string& GeometryShader, const string& FragmentShader );

		/* ЗАГРУЗИТЬ ШЕЙДЕР С ПАМЯТИ */
		bool LoadFromMemory( const string& VertexShader, const string& FragmentShader );
		bool LoadFromMemory( const string& VertexShader, const string& GeometryShader, const string& FragmentShader );

		/* ЗАДАТЬ ПОЗИЦИЮ АТРИБУТОВ ВЕРШИН В ШЕЙДЕРЕ (ПРИМЕНЯТЬ ПЕРЕД ЗАГРУЗКОЙ ШЕЙДЕРА) */
		void SetAttribLocation( map<string, int>& AttribLocation );

		/* ЗАДАТЬ ЗНАЧЕНИЕ ЮНИФОРМ-ПЕРЕМЕННОЙ */
		void SetUniform( const std::string& Name, bool X );	
		void SetUniform( const std::string& Name, int X );
		void SetUniform( const std::string& Name, float X );
		void SetUniform( const std::string& Name, GLuint& X );
		void SetUniform( const std::string& Name, glm::mat4& Matrix );
		void SetUniform( const std::string& Name, glm::vec2& Vector2 );
		void SetUniform( const std::string& Name, glm::vec3& Vector3 );
		void SetUniform( const std::string& Name, glm::vec4& Vector4 );

		/* ПОЛУЧИТЬ ID ШЕЙДЕРА В OPENGL */
		const GLuint& GetNativeHandle();

	private:

		/* СКОМПИЛИРОВАТЬ ШЕЙДЕР */
		bool Compile( const string& VertexShader, const string& GeometryShader, const string& FragmentShader );

		/* ПОЛУЧИТЬ ИДЕНТИФИГАТОР РАСПОЛОЖЕНИЯ ЮНИФОРМ-ПЕРЕМЕННОЙ */
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
