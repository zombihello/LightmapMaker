///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "Plane.h"
#include "BrushVertex.h"

#define OFFSET_BRUSH_POSITION ( void* ) offsetof( BrushVertex, Position )
#define OFFSET_BRUSH_TEXCOORD ( void* ) offsetof( BrushVertex, TextureCoord_LightMap )

//-------------------------------------------------------------------------//

Plane::Plane() :
	GL_LightMap( 0 )
{}

//-------------------------------------------------------------------------//

Plane::~Plane()
{
	if ( GL_LightMap )
		glDeleteTextures( 1, &GL_LightMap );
}

//-------------------------------------------------------------------------//

void Plane::InitPlane( const GLuint& VertexBuffer, const vector<unsigned int>& PlaneIdVertex, const vector<BrushVertex>& PlaneVertexes )
{
	int Flag = 0;
	float Distance, X, Y, Z;
	glm::vec2 UVMin, UVMax, UVDelta, UV[ 3 ];
	glm::vec3 Vect1, Vect2;

	CountIndexs = PlaneIdVertex.size();
	VAO.Create<BrushVertex>( VertexBuffer, PlaneIdVertex, OpenGL_API::VAO::Static_Draw, OFFSET_BRUSH_POSITION, OFFSET_BRUSH_TEXCOORD );
	
	const BrushVertex* Vertex_A = &PlaneVertexes[ 0 ];
	const BrushVertex* Vertex_B = &PlaneVertexes[ 1 ];
	const BrushVertex* Vertex_C = &PlaneVertexes[ 2 ];

	Normal = glm::normalize( glm::cross( Vertex_B->Position - Vertex_A->Position, Vertex_C->Position - Vertex_A->Position ) );
	Distance = -( Normal.x * Vertex_A->Position.x + Normal.y * Vertex_A->Position.y + Normal.z * Vertex_A->Position.z );

	// ****************************
	// Определяем тип плоскости

	if ( abs( Normal.x ) > abs( Normal.y ) && abs( Normal.x ) > abs( Normal.z ) )
	{
		Flag = 1;

		UV[ 0 ].x = Vertex_A->Position.y;
		UV[ 0 ].y = Vertex_A->Position.z;

		UV[ 1 ].x = Vertex_B->Position.y;
		UV[ 1 ].y = Vertex_B->Position.z;

		UV[ 2 ].x = Vertex_C->Position.y;
		UV[ 2 ].y = Vertex_C->Position.z;
	}
	else if ( abs( Normal.y ) > abs( Normal.x ) && abs( Normal.y ) > abs( Normal.z ) )
	{
		Flag = 2;

		UV[ 0 ].x = Vertex_A->Position.x;
		UV[ 0 ].y = Vertex_A->Position.z;

		UV[ 1 ].x = Vertex_B->Position.x;
		UV[ 1 ].y = Vertex_B->Position.z;

		UV[ 2 ].x = Vertex_C->Position.x;
		UV[ 2 ].y = Vertex_C->Position.z;
	}
	else
	{
		Flag = 3;

		UV[ 0 ].x = Vertex_A->Position.x;
		UV[ 0 ].y = Vertex_A->Position.y;

		UV[ 1 ].x = Vertex_B->Position.x;
		UV[ 1 ].y = Vertex_B->Position.y;

		UV[ 2 ].x = Vertex_C->Position.x;
		UV[ 2 ].y = Vertex_C->Position.y;
	}

	// ****************************
	// Находим минимальные, максимальные и разницу текстурных координат

	UVMin = UV[ 0 ];
	UVMax = UV[ 0 ];

	for ( int i = 0; i < 3; i++ )
	{
		if ( UV[ i ].x < UVMin.x )
			UVMin.x = UV[ i ].x;

		if ( UV[ i ].y < UVMin.y )
			UVMin.y = UV[ i ].y;

		if ( UV[ i ].x > UVMax.x )
			UVMax.x = UV[ i ].x;

		if ( UV[ i ].y > UVMax.y )
			UVMax.y = UV[ i ].y;
	}

	// ****************************
	// Задаем границы размера карты освещения

	UVDelta = glm::abs( UVMax - UVMin );
	SizeLightmap = UVDelta * 8.f;

	if ( SizeLightmap.x < 4 )
		SizeLightmap.x = 4;

	if ( SizeLightmap.y < 4 )
		SizeLightmap.y = 4;

	if ( SizeLightmap.x > ArgumentsStart::MaxSizeLightmap )
		SizeLightmap.x = ( float ) ArgumentsStart::MaxSizeLightmap;

	if ( SizeLightmap.y > ArgumentsStart::MaxSizeLightmap )
		SizeLightmap.y = ( float ) ArgumentsStart::MaxSizeLightmap;

	// ****************************
	// Находим координаты

	switch ( Flag )
	{
	case 1: // YZ Плоскость
		X = -( Normal.y * UVMin.x + Normal.z * UVMin.y + Distance ) / Normal.x;
		UVVector.x = X;
		UVVector.y = UVMin.x;
		UVVector.z = UVMin.y;

		X = -( Normal.y * UVMax.x + Normal.z * UVMin.y + Distance ) / Normal.x;
		Vect1.x = X;
		Vect1.y = UVMax.x;
		Vect1.z = UVMin.y;

		X = -( Normal.y * UVMin.x + Normal.z * UVMax.y + Distance ) / Normal.x;
		Vect2.x = X;
		Vect2.y = UVMin.x;
		Vect2.z = UVMax.y;
		break;

	case 2: // XZ Плоскость
		Y = -( Normal.x * UVMin.x + Normal.z * UVMin.y + Distance ) / Normal.y;
		UVVector.x = UVMin.x;
		UVVector.y = Y;
		UVVector.z = UVMin.y;

		Y = -( Normal.x * UVMax.x + Normal.z * UVMin.y + Distance ) / Normal.y;
		Vect1.x = UVMax.x;
		Vect1.y = Y;
		Vect1.z = UVMin.y;

		Y = -( Normal.x * UVMin.x + Normal.z * UVMax.y + Distance ) / Normal.y;
		Vect2.x = UVMin.x;
		Vect2.y = Y;
		Vect2.z = UVMax.y;
		break;

	case 3: // XY Плоскость
		Z = -( Normal.x * UVMin.x + Normal.y * UVMin.y + Distance ) / Normal.z;
		UVVector.x = UVMin.x;
		UVVector.y = UVMin.y;
		UVVector.z = Z;

		Z = -( Normal.x * UVMax.x + Normal.y * UVMin.y + Distance ) / Normal.z;
		Vect1.x = UVMax.x;
		Vect1.y = UVMin.y;
		Vect1.z = Z;

		Z = -( Normal.x * UVMin.x + Normal.y * UVMax.y + Distance ) / Normal.z;
		Vect2.x = UVMin.x;
		Vect2.y = UVMax.y;
		Vect2.z = Z;
		break;
	}

	Edge1 = Vect1 - UVVector;
	Edge2 = Vect2 - UVVector;

	Data_LightMap.create( SizeLightmap.x, SizeLightmap.y );
	GenerateGLTexture();
}

//-------------------------------------------------------------------------//

void Plane::Render()
{
	VAO.Bind();

	glBindTexture( GL_TEXTURE_2D, GL_LightMap );
	glDrawElements( GL_TRIANGLES, CountIndexs, GL_UNSIGNED_INT, 0 );
	glBindTexture( GL_TEXTURE_2D, 0 );

	VAO.Unbind();
}

//-------------------------------------------------------------------------//

void Plane::GenerateGLTexture()
{
	if ( GL_LightMap )
		glDeleteTextures( 1, &GL_LightMap );

	glGenTextures( 1, &GL_LightMap );
	glBindTexture( GL_TEXTURE_2D, GL_LightMap );

	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, SizeLightmap.x, SizeLightmap.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data_LightMap.getPixelsPtr() );

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

	Newedge1.x = Edge1.x * UFactor;
	Newedge1.y = Edge1.y * UFactor;
	Newedge1.z = Edge1.z * UFactor;
	Newedge2.x = Edge2.x * VFactor;
	Newedge2.y = Edge2.y * VFactor;
	Newedge2.z = Edge2.z * VFactor;

	PositionOut = UVVector + Newedge2 + Newedge1;
}

//-------------------------------------------------------------------------//

glm::vec2& Plane::GetSizeLightmap()
{
	return SizeLightmap;
}

//-------------------------------------------------------------------------//

glm::vec3& Plane::GetNormal()
{
	return Normal;
}

//-------------------------------------------------------------------------//

sf::Image& Plane::GetDataLightMap()
{
	return Data_LightMap;
}

//-------------------------------------------------------------------------//