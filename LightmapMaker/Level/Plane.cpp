///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "Plane.h"
#include "BrushVertex.h"

#define OFFSET_BRUSH_POSITION ( void* ) offsetof( BrushVertex, Position )
#define OFFSET_BRUSH_TEXCOORD ( void* ) offsetof( BrushVertex, TextureCoord_LightMap )

//-------------------------------------------------------------------------//

void Plane::InitPlane( const GLuint& VertexBuffer, const vector<unsigned int>& PlaneIdVertex, const vector<BrushVertex>& PlaneVertexes )
{
	CountIndexs = PlaneIdVertex.size();
	VAO.Create<BrushVertex>( VertexBuffer, PlaneIdVertex, OpenGL_API::VAO::Static_Draw, OFFSET_BRUSH_POSITION, OFFSET_BRUSH_TEXCOORD );

	for ( size_t Id = 0; Id < PlaneVertexes.size() / 3; Id += 3 )
		Triangles.push_back( Triangle( PlaneVertexes[ Id ], PlaneVertexes[ Id + 1 ], PlaneVertexes[ Id + 2 ] ) );
}

//-------------------------------------------------------------------------//

void Plane::Render()
{
	VAO.Bind();
	glDrawElements( GL_TRIANGLES, CountIndexs, GL_UNSIGNED_INT, 0 );
	VAO.Unbind();
}

//-------------------------------------------------------------------------//

vector<Triangle>& Plane::GetTriangles()
{
	return Triangles;
}

//-------------------------------------------------------------------------//