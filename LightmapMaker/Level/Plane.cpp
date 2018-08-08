///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "Plane.h"
#include "BrushVertex.h"

#define OFFSET_BRUSH_POSITION ( void* ) offsetof( BrushVertex, Position )
#define OFFSET_BRUSH_TEXCOORD0 ( void* ) offsetof( BrushVertex, TextureCoord_DiffuseMap )
#define OFFSET_BRUSH_TEXCOORD1 ( void* ) offsetof( BrushVertex, TextureCoord_LightMap )

//-------------------------------------------------------------------------//

Plane::Plane() :
	GL_DiffuseMap( 0 ),
	GL_LightMap( 0 ),
	SizeLightmap_PrimaryIllumination( NULL ),
	SizeLightmap_SecondaryLight( NULL ),
	Normal( NULL )
{}

//-------------------------------------------------------------------------//

Plane::~Plane()
{
	if ( GL_LightMap )
		glDeleteTextures( 1, &GL_LightMap );
}

//-------------------------------------------------------------------------//
#include "../System/Logger.h"
void Plane::InitPlane( const GLuint& VertexBuffer, const vector<unsigned int>& PlaneIdVertex, const vector<BrushVertex>& PlaneVertexes, const string& NameTexture )
{
	CountIndexs = PlaneIdVertex.size();
	VAO.Create<BrushVertex>( VertexBuffer, PlaneIdVertex, OpenGL_API::VAO::Static_Draw, OFFSET_BRUSH_POSITION, OFFSET_BRUSH_TEXCOORD0, OFFSET_BRUSH_TEXCOORD1 );

	Triangles[ 0 ].InitTriangle( PlaneVertexes[ 0 ].Position, PlaneVertexes[ 1 ].Position, PlaneVertexes[ 2 ].Position );
	Triangles[ 1 ].InitTriangle( PlaneVertexes[ 3 ].Position, PlaneVertexes[ 4 ].Position, PlaneVertexes[ 5 ].Position );

	SizeLightmap_PrimaryIllumination = &Triangles[ 0 ].SizeLightmap_PrimaryIllumination;
	SizeLightmap_SecondaryLight = &Triangles[ 0 ].SizeLightmap_SecondaryLight;
	Normal = &Triangles[ 0 ].Normal;

	GL_DiffuseMap = ResourcesManager::GetGlTexture( NameTexture );
	LightMap_PrimaryIllumination.create( SizeLightmap_PrimaryIllumination->x, SizeLightmap_PrimaryIllumination->y );
	LightMap_SecondaryLight.create( SizeLightmap_SecondaryLight->x, SizeLightmap_SecondaryLight->y );
	GenerateGLTexture();
}

//-------------------------------------------------------------------------//

void Plane::Render()
{
	VAO.Bind();
	glDrawElements( GL_TRIANGLES, CountIndexs, GL_UNSIGNED_INT, 0 );
	VAO.Unbind();
}

//-------------------------------------------------------------------------//

void Plane::GenerateGLTexture()
{
	if ( GL_LightMap )
	{
		glDeleteTextures( 1, &GL_LightMap );
		GL_LightMap = 0;
	}

	glGenTextures( 1, &GL_LightMap );
	glBindTexture( GL_TEXTURE_2D, GL_LightMap );

	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, SizeLightmap_SecondaryLight->x, SizeLightmap_SecondaryLight->y, 0, GL_RGBA, GL_UNSIGNED_BYTE, LightMap_SecondaryLight.getPixelsPtr() );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glBindTexture( GL_TEXTURE_2D, 0 );
}

//-------------------------------------------------------------------------//
void Plane::GetPositionFragment( float UFactor, float VFactor, glm::vec3& PositionOut )
{
	glm::vec3 Newedge1, Newedge2;

	Newedge1.x = Triangles[ 0 ].Edge1.x * UFactor;
	Newedge1.y = Triangles[ 0 ].Edge1.y * UFactor;
	Newedge1.z = Triangles[ 0 ].Edge1.z * UFactor;
	Newedge2.x = Triangles[ 0 ].Edge2.x * VFactor;
	Newedge2.y = Triangles[ 0 ].Edge2.y * VFactor;
	Newedge2.z = Triangles[ 0 ].Edge2.z * VFactor;

	PositionOut = Triangles[ 0 ].UVVector + Newedge2 + Newedge1;
}

//-------------------------------------------------------------------------//

bool Plane::IsRayIntersect( Ray& Ray )
{
	return Ray.IntersectTriangle( Triangles[ 0 ] ) || Ray.IntersectTriangle( Triangles[ 1 ] );
}

//-------------------------------------------------------------------------//

bool Plane::operator!=( Plane& Plane )
{
	return 	Triangles[ 0 ].A != Plane.Triangles[ 0 ].A &&
		Triangles[ 0 ].B != Plane.Triangles[ 0 ].B &&
		Triangles[ 0 ].C != Plane.Triangles[ 0 ].C &&
		Triangles[ 1 ].A != Plane.Triangles[ 1 ].A &&
		Triangles[ 1 ].B != Plane.Triangles[ 1 ].B &&
		Triangles[ 1 ].C != Plane.Triangles[ 1 ].C;
}

//-------------------------------------------------------------------------//