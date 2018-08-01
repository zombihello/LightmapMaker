#include "../System/Logger.h"
#include "RenderTexture.h"

//-------------------------------------------------------------------------//

OpenGL_API::RenderTexture::RenderTexture() :
	IsCreate( false ),
	NumLevelsMipmap( 0 ),
	FrameBuffer( 0 ),
	Texture( 0 ),
	DepthBuffer( 0 )
{}

//-------------------------------------------------------------------------//

OpenGL_API::RenderTexture::RenderTexture( size_t Width, size_t Height ) :
	IsCreate( false ),
	NumLevelsMipmap( 0 ),
	FrameBuffer( 0 ),
	Texture( 0 ),
	DepthBuffer( 0 )
{
	Create( Width, Height );
}

//-------------------------------------------------------------------------//

OpenGL_API::RenderTexture::~RenderTexture()
{
	if ( IsCreate )
	{
		glDeleteTextures( 1, &Texture );
		glDeleteRenderbuffers( 1, &DepthBuffer );
		glDeleteFramebuffers( 1, &FrameBuffer );
	}
}

//-------------------------------------------------------------------------//

bool OpenGL_API::RenderTexture::Create( size_t Width, size_t Height )
{
	// **********************
	// Генерируем буфферы

	if ( !IsCreate )
	{
		glGenTextures( 1, &Texture );
		glGenRenderbuffers( 1, &DepthBuffer );
		glGenFramebuffers( 1, &FrameBuffer );
	}

	// ***************************************** //
	// Инициализируем текстуру для рендера

	glBindTexture( GL_TEXTURE_2D, Texture );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_FLOAT, NULL );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0 );
	glTexParameteri( GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE );

	// ***************************************** //
	// Инициализируем буффер глубины и привязываем его

	glBindRenderbuffer( GL_RENDERBUFFER, DepthBuffer );
	glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH_COMPONENT, Width, Height );

	// ***************************************** //
	// Привязываем к буфферу текстуру

	glBindFramebuffer( GL_FRAMEBUFFER, FrameBuffer );
	glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, Texture, 0 );
	glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, DepthBuffer );

	glDrawBuffer( GL_COLOR_ATTACHMENT0 );
	glReadBuffer( GL_COLOR_ATTACHMENT0 );

	// ***************************************** //
	// Проверяем статус FBO, создан ли он без ошибок

	GLenum Status = glCheckFramebufferStatus( GL_FRAMEBUFFER );

	if ( Status != GL_FRAMEBUFFER_COMPLETE )
	{
		PRINT_LOG( "Error: Render Texture Not Initialized. Framebuffer Status [0x" << Status << "]\n" );

		glDeleteTextures( 1, &Texture );
		glDeleteRenderbuffers( 1, &DepthBuffer );
		glDeleteFramebuffers( 1, &FrameBuffer );
		IsCreate = false;
	}
	else
	{
		IsCreate = true;
		NumLevelsMipmap = 1 + floor( log2( glm::max( Width, Height ) ) );
		Size = glm::vec2( Width, Height );
	}

	glBindTexture( GL_TEXTURE_2D, 0 );
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );
	glBindRenderbuffer( GL_RENDERBUFFER, 0 );

	return IsCreate;
}

//-------------------------------------------------------------------------//

glm::vec3 OpenGL_API::RenderTexture::GetMediumColorTexture()
{
	glm::vec3 ColorPixel;

	glBindTexture( GL_TEXTURE_2D, Texture );
	glGenerateMipmap( GL_TEXTURE_2D );
	glGetTexImage( GL_TEXTURE_2D, NumLevelsMipmap - 1, GL_RGB, GL_FLOAT, &ColorPixel );

	glBindTexture( GL_TEXTURE_2D, 0 );
	return ColorPixel;
}

//-------------------------------------------------------------------------//

void OpenGL_API::RenderTexture::Bind()
{
	glBindFramebuffer( GL_FRAMEBUFFER, FrameBuffer );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

//-------------------------------------------------------------------------//

void OpenGL_API::RenderTexture::Unbind()
{
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

//-------------------------------------------------------------------------//

GLuint& OpenGL_API::RenderTexture::GetTexture()
{
	return Texture;
}

//-------------------------------------------------------------------------//