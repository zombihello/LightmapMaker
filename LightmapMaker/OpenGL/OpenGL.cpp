///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
///////////////////////////
#include <Windows.h>

///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "../System/Logger.h"
#include "../System/ArgumentsStart.h"
#include "../System/Error.h"
#include "OpenGL.h"

//-------------------------------------------------------------------------//

void OpenGL_API::InitOpenGL( sf::RenderWindow& RenderWindow )
{
	sf::ContextSettings ContextSettings;
	ContextSettings.depthBits = 24;
	ContextSettings.stencilBits = 8;
	glewExperimental = GL_TRUE;

	// TODO: [zombiHello] - 256 поменять на переменную отвечающую за размер RenderTexture
	RenderWindow.create( sf::VideoMode( 800, 600 ), "", sf::Style::Default, ContextSettings );
	//ShowWindow( RenderWindow.getSystemHandle(), false );

	// Выводим данные об OpenGL
	int MajorVersion = 0, MinorVersion = 0;
	string OpenGLVersion = ( const char* ) glGetString( GL_VERSION );
	string GLSLVersion = ( const char* ) glGetString( GL_SHADING_LANGUAGE_VERSION );

	PRINT_LOG( "*** OpenGL Info ***" );
	PRINT_LOG( "  OpenGL Version: " << OpenGLVersion );
	PRINT_LOG( "  OpenGL Vendor: " << glGetString( GL_VENDOR ) );
	PRINT_LOG( "  OpenGL Renderer: " << glGetString( GL_RENDERER ) );
	PRINT_LOG( "  OpenGL GLSL Version: " << GLSLVersion );
	PRINT_LOG( "*** OpenGL Info End ***" );
	PRINT_LOG( "" );

	if ( glewInit() != GLEW_OK )
		Error( "Error Init OpenGL", "Error: OpenGL Context Is Broken", -1 );

	// Проверяем, чтобы видеокарта поддерживала OpenGL 3.0
	sscanf( OpenGLVersion.c_str(), "%d.%d", &MajorVersion, &MinorVersion );
	if ( MajorVersion < 3 )
		Error( "Error Init OpenGL", "Error: OpenGL 3.0 Not Available", -1 );

	// Проверяем, чтобы видеокарта поддерживала GLSL 1.3
	sscanf( GLSLVersion.c_str(), "%d.%d", &MajorVersion, &MinorVersion );
	if ( MajorVersion < 1 || MajorVersion == 1 && MinorVersion < 3 )
		Error( "Error Init OpenGL", "Error: System Not Supported Shaders Version 1.3", -1 );
}

//-------------------------------------------------------------------------//