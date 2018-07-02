///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "VAO.h"
#include "../System/Logger.h"
using namespace OpenGL_API;

//-------------------------------------------------------------------------//

VAO::VAO() :
	Created( false ),
	VertexBuffer( 0 ),
	ArrayBuffer( 0 ),
	IndexBuffer( 0 )
{}

//-------------------------------------------------------------------------//

VAO::~VAO()
{
	Delete();
}

//-------------------------------------------------------------------------//

void VAO::Bind()
{
	glBindVertexArray( ArrayBuffer );
}

//-------------------------------------------------------------------------//

void VAO::Unbind()
{
	glBindVertexArray( 0 );
}

//-------------------------------------------------------------------------//

void VAO::Delete()
{
	if ( Created )
	{
		glDeleteVertexArrays( 1, &ArrayBuffer );
		Created = false;
	}

	DeleteBuffer( VertexBuffer );
	DeleteBuffer( IndexBuffer );
}

//-------------------------------------------------------------------------//

void OpenGL_API::VAO::DeleteBuffer( GLuint& Buffer )
{
	if ( Buffer )
		glDeleteBuffers( 1, &Buffer );
}

//-------------------------------------------------------------------------//

bool VAO::IsCreated()
{
	return Created;
}

//-------------------------------------------------------------------------//