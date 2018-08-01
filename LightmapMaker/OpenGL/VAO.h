//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// Связь со мной:		https://vk.com/zombihello
// Репозиторий движка:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef VAO_H
#define VAO_H

#define VERT_POSITION 0
#define VERT_TEXCOORD0 1
#define VERT_TEXCOORD1 2

///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
///////////////////////////
#include <vector>
#include <glew\glew.h>
using namespace std;

//-------------------------------------------------------------------------//

namespace OpenGL_API
{
	//-------------------------------------------------------------------------//

	class VAO
	{
	public:

		//-------------------------------------------------------------------------//

		enum TypeBuffer
		{
			Vertex_Buffer = GL_ARRAY_BUFFER,
			Index_Buffer = GL_ELEMENT_ARRAY_BUFFER
		};

		//-------------------------------------------------------------------------//

		enum TypeUpdate
		{
			Static_Draw = GL_STATIC_DRAW,
			Dynamic_Draw = GL_DYNAMIC_DRAW,
			Stream_Draw = GL_STREAM_DRAW
		};

		//-------------------------------------------------------------------------//

		/* КОНСТРУКТОР */
		VAO();

		/* ДЕСТРУКТОР */
		~VAO();

		/* СОЗДАТЬ БУФФЕР ДЛЯ VAO */
		template<typename T> static GLuint& CreateBuffer( TypeBuffer TypeBuffer, vector<T> Data, TypeUpdate Usage );

		/* СОЗДАТЬ VAO */
		template<typename T, typename C> void Create( const vector<T>& Data_VertexBuffer, TypeUpdate Usage_VertexBuffer, const vector<C>& Data_IndexBuffer, TypeUpdate Usage_IndexBuffer, const void* PointerPosition, const void* PointerTexCoord0, const void* PointerTexCoord1 );
		template<typename T, typename C> void Create( const GLuint& VertexBuffer, const vector<C>& Data_IndexBuffer, TypeUpdate Usage_IndexBuffer, const void* PointerPosition, const void* PointerTexCoord0, const void* PointerTexCoord1 );
		template<typename T, typename C> void Create( const vector<T>& Data_VertexBuffer, TypeUpdate Usage_VertexBuffer, const GLuint& IndexBuffer, const void* PointerPosition, const void* PointerTexCoord0, const void* PointerTexCoord1 );
		template<typename T> void Create( const GLuint& VertexBuffer, const GLuint& IndexBuffer, const void* PointerPosition, const void* PointerTexCoord0, const void* PointerTexCoord1 );

		/* СДЕЛАТЬ АКТИВНЫМ VAO */
		void Bind();

		/* ДЕАКТИВИРОВАТЬ VAO */
		void Unbind();

		/* УДАЛИТЬ VAO */
		void Delete();

		/* УДАЛИТЬ БУФФЕР */
		static void DeleteBuffer( GLuint& Buffer );

		/* СОЗДАН ЛИ VAO */
		bool IsCreated();

	private:
		bool			Created;

		GLuint			VertexBuffer;
		GLuint			ArrayBuffer;
		GLuint			IndexBuffer;
	};

	//-------------------------------------------------------------------------//

	template<typename T>
	inline GLuint& VAO::CreateBuffer( TypeBuffer TypeBuffer, vector<T> Data, TypeUpdate Usage )
	{
		GLuint Buffer;

		glGenBuffers( 1, &Buffer );
		glBindBuffer( TypeBuffer, Buffer );
		glBufferData( TypeBuffer, Data.size() * sizeof( T ), Data.data(), Usage );
		glBindBuffer( TypeBuffer, 0 );

		return Buffer;
	}

	//-------------------------------------------------------------------------//

	template<typename T, typename C>
	inline void VAO::Create( const vector<T>& Data_VertexBuffer, TypeUpdate Usage_VertexBuffer, const vector<C>& Data_IndexBuffer, TypeUpdate Usage_IndexBuffer, const void* PointerPosition, const void* PointerTexCoord0, const void* PointerTexCoord1 )
	{
		glGenVertexArrays( 1, &ArrayBuffer );  // VAO
		glGenBuffers( 1, &VertexBuffer ); // буффер вершин
		glGenBuffers( 1, &IndexBuffer ); // буффер индексов

		glBindVertexArray( ArrayBuffer );

		// ************************
		// Заполняем буффер вершин

		glBindBuffer( GL_ARRAY_BUFFER, VertexBuffer );
		glBufferData( GL_ARRAY_BUFFER, Data_VertexBuffer.size() * sizeof( T ), Data_VertexBuffer.data(), Usage_VertexBuffer );

		// ************************
		// Заполняем буффер индексов

		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, IndexBuffer );
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, Data_IndexBuffer.size() * sizeof( C ), Data_IndexBuffer.data(), Usage_IndexBuffer );

		// ************************
		// Задаем атрибуты для вершин в шейдере

		glVertexAttribPointer( VERT_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof( T ), PointerPosition );
		glEnableVertexAttribArray( VERT_POSITION );

		glVertexAttribPointer( VERT_TEXCOORD0, 2, GL_FLOAT, GL_FALSE, sizeof( T ), PointerTexCoord0 );
		glEnableVertexAttribArray( VERT_TEXCOORD0 );

		glVertexAttribPointer( VERT_TEXCOORD1, 2, GL_FLOAT, GL_FALSE, sizeof( T ), PointerTexCoord1 );
		glEnableVertexAttribArray( VERT_TEXCOORD1 );

		glBindVertexArray( 0 );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

		Created = true;
	}

	//-------------------------------------------------------------------------//

	template<typename T, typename C>
	inline void VAO::Create( const GLuint& VertexBuffer, const vector<C>& Data_IndexBuffer, TypeUpdate Usage_IndexBuffer, const void * PointerPosition, const void * PointerTexCoord0, const void* PointerTexCoord1 )
	{
		glGenVertexArrays( 1, &ArrayBuffer );  // VAO
		glGenBuffers( 1, &IndexBuffer ); // буффер индексов

		glBindVertexArray( ArrayBuffer );
		glBindBuffer( GL_ARRAY_BUFFER, VertexBuffer );

		// ************************
		// Заполняем буффер индексов

		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, IndexBuffer );
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, Data_IndexBuffer.size() * sizeof( C ), Data_IndexBuffer.data(), Usage_IndexBuffer );

		// ************************
		// Задаем атрибуты для вершин в шейдере

		glVertexAttribPointer( VERT_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof( T ), PointerPosition );
		glEnableVertexAttribArray( VERT_POSITION );

		glVertexAttribPointer( VERT_TEXCOORD0, 2, GL_FLOAT, GL_FALSE, sizeof( T ), PointerTexCoord0 );
		glEnableVertexAttribArray( VERT_TEXCOORD0 );

		glVertexAttribPointer( VERT_TEXCOORD1, 2, GL_FLOAT, GL_FALSE, sizeof( T ), PointerTexCoord1 );
		glEnableVertexAttribArray( VERT_TEXCOORD1 );

		glBindVertexArray( 0 );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

		Created = true;
	}

	//-------------------------------------------------------------------------//

	template<typename T, typename C>
	inline void VAO::Create( const vector<T>& Data_VertexBuffer, TypeUpdate Usage_VertexBuffer, const GLuint & IndexBuffer, const void * PointerPosition, const void * PointerTexCoord0, const void* PointerTexCoord1 )
	{
		glGenVertexArrays( 1, &ArrayBuffer );  // VAO
		glGenBuffers( 1, &VertexBuffer ); // буффер вершин

		glBindVertexArray( ArrayBuffer );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, IndexBuffer );

		// ************************
		// Заполняем буффер вершин

		glBindBuffer( GL_ARRAY_BUFFER, VertexBuffer );
		glBufferData( GL_ARRAY_BUFFER, Data_VertexBuffer.size() * sizeof( T ), Data_VertexBuffer.data(), Usage_VertexBuffer );

		// ************************
		// Задаем атрибуты для вершин в шейдере

		glVertexAttribPointer( VERT_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof( T ), PointerPosition );
		glEnableVertexAttribArray( VERT_POSITION );

		glVertexAttribPointer( VERT_TEXCOORD0, 2, GL_FLOAT, GL_FALSE, sizeof( T ), PointerTexCoord0 );
		glEnableVertexAttribArray( VERT_TEXCOORD0 );

		glVertexAttribPointer( VERT_TEXCOORD1, 2, GL_FLOAT, GL_FALSE, sizeof( T ), PointerTexCoord1 );
		glEnableVertexAttribArray( VERT_TEXCOORD1 );

		glBindVertexArray( 0 );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

		Created = true;
	}

	//-------------------------------------------------------------------------//

	template<typename T>
	inline void VAO::Create( const GLuint & VertexBuffer, const GLuint & IndexBuffer, const void * PointerPosition, const void * PointerTexCoord0, const void* PointerTexCoord1 )
	{
		glGenVertexArrays( 1, &ArrayBuffer );  // VAO

		glBindVertexArray( ArrayBuffer );
		glBindBuffer( GL_ARRAY_BUFFER, VertexBuffer );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, IndexBuffer );


		// ************************
		// Задаем атрибуты для вершин в шейдере

		glVertexAttribPointer( VERT_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof( T ), PointerPosition );
		glEnableVertexAttribArray( VERT_POSITION );

		glVertexAttribPointer( VERT_TEXCOORD0, 2, GL_FLOAT, GL_FALSE, sizeof( T ), PointerTexCoord0 );
		glEnableVertexAttribArray( VERT_TEXCOORD0 );

		glVertexAttribPointer( VERT_TEXCOORD1, 2, GL_FLOAT, GL_FALSE, sizeof( T ), PointerTexCoord1 );
		glEnableVertexAttribArray( VERT_TEXCOORD1 );

		glBindVertexArray( 0 );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

		Created = true;
	}

	//-------------------------------------------------------------------------//
}

//-------------------------------------------------------------------------//

#endif // !VAO_H
