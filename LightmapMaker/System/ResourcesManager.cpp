#include "ResourcesManager.h"

//-------------------------------------------------------------------------//

map<string, GLuint> ResourcesManager::GlTextures = map<string, GLuint>();
map<string, OpenGL_API::Shader>	ResourcesManager::Shaders = map<string, OpenGL_API::Shader>();

//-------------------------------------------------------------------------//

bool ResourcesManager::LoadGlTexture( const string& NameTexture, const string& RouteToFile )
{
	if ( GlTextures.find( NameTexture ) == GlTextures.end() )
	{
		sf::Image Image;

		if ( !Image.loadFromFile( RouteToFile ) )
		{
			PRINT_LOG( "   Texture [" << RouteToFile << "] Not Found\n" );
			return false;
		}

		Image.flipVertically();

		GLuint Texture = 0;
		glGenTextures( 1, &Texture );
		glBindTexture( GL_TEXTURE_2D, Texture );
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, Image.getSize().x, Image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, Image.getPixelsPtr() );

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

		GlTextures[ NameTexture ] = Texture;

		PRINT_LOG( "   Texture With Name [" << NameTexture << "] Loaded\n" );
		return true;
	}

	return true;
}

//-------------------------------------------------------------------------//

OpenGL_API::Shader* ResourcesManager::CreateShader( const string& NameShader )
{
	if ( Shaders.find( NameShader ) == Shaders.end() )
	{
		Shaders[ NameShader ] = OpenGL_API::Shader();
		return &Shaders[ NameShader ];
	}

	return &Shaders[ NameShader ];
}

//-------------------------------------------------------------------------//

void ResourcesManager::DeleteGlTexture( const string& NameTexture )
{
	if ( GlTextures.find( NameTexture ) != GlTextures.end() )
	{
		glDeleteTextures( 1, &GlTextures[ NameTexture ] );
		PRINT_LOG( "   Texture With Name [" << NameTexture << "] Deleted\n" );
		GlTextures.erase( NameTexture );
	}
}

//-------------------------------------------------------------------------//

void ResourcesManager::DeleteShader( const string& NameShader )
{
	if ( Shaders.find( NameShader ) != Shaders.end() )
	{
		PRINT_LOG( "   Shader With Name [" << NameShader << "] Deleted\n" );
		Shaders.erase( NameShader );
	}
}

//-------------------------------------------------------------------------//

void ResourcesManager::DeleteAllGlTexture()
{
	for ( auto it = GlTextures.begin(); it != GlTextures.end(); it++ )
	{
		glDeleteTextures( 1, &it->second );
		PRINT_LOG( "   Texture With Name [" << it->first << "] Deleted\n" );
	}

	GlTextures.clear();
}

//-------------------------------------------------------------------------//

void ResourcesManager::DeleteAllShaders()
{
	for ( auto it = Shaders.begin(); it != Shaders.end(); it++ )
	PRINT_LOG( "   Shader With Name [" << it->first << "] Deleted\n" );

	Shaders.clear();
}

//-------------------------------------------------------------------------//

void ResourcesManager::DeleteAllResources()
{
	DeleteAllGlTexture();
	DeleteAllShaders();
}

//-------------------------------------------------------------------------//

const GLuint ResourcesManager::GetGlTexture( const string& NameTexture )
{
	if ( GlTextures.find( NameTexture ) != GlTextures.end() )
		return GlTextures[ NameTexture ];

	return 0;
}

//-------------------------------------------------------------------------//

OpenGL_API::Shader* ResourcesManager::GetShader( const string& NameShader )
{
	if ( Shaders.find( NameShader ) != Shaders.end() )
		return &Shaders[ NameShader ];

	return NULL;
}

//-------------------------------------------------------------------------//