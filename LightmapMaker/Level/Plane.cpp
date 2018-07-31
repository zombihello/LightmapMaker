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

	for ( size_t TriangleCount = 0, Vertex_Id = 0; TriangleCount < PlaneVertexes.size() / 3; TriangleCount++, Vertex_Id += 3 )
		Triangles.push_back( Triangle( PlaneVertexes[ Vertex_Id ], PlaneVertexes[ Vertex_Id + 1 ], PlaneVertexes[ Vertex_Id + 2 ] ) );
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