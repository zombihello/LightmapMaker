#include "Triangle.h"

//-------------------------------------------------------------------------//

Triangle::Triangle()
{
}

//-------------------------------------------------------------------------//

Triangle::Triangle( const BrushVertex& Vertex_A, const BrushVertex& Vertex_B, const BrushVertex& Vertex_C )
{
	InitTriangle( Vertex_A, Vertex_B, Vertex_C );
}

//-------------------------------------------------------------------------//

void Triangle::InitTriangle( const BrushVertex& Vertex_A, const BrushVertex& Vertex_B, const BrushVertex& Vertex_C )
{
	int Flag = 0;
	float Distance, X, Y, Z;
	glm::vec2 UVMin, UVMax, UVDelta;
	glm::vec3 Vect1, Vect2;

	this->Vertex_A = Vertex_A;
	this->Vertex_B = Vertex_B;
	this->Vertex_C = Vertex_C;

	Normal = glm::abs( glm::normalize( glm::cross( Vertex_B.Position - Vertex_A.Position, Vertex_C.Position - Vertex_A.Position ) ) );
	Distance = -( Normal.x * Vertex_A.Position.x + Normal.y * Vertex_A.Position.y + Normal.z * Vertex_A.Position.z );

	// ****************************
	// Определяем тип плоскости

	if ( Normal.x > Normal.y && Normal.x > Normal.z )
		Flag = 1;
	else if ( Normal.y > Normal.x && Normal.y > Normal.z )
		Flag = 2;
	else
		Flag = 3;

	// ****************************
	// Находим минимальные, максимальные и разницу текстурных координат

	UVMin = Vertex_A.TextureCoord_LightMap;
	UVMax = Vertex_A.TextureCoord_LightMap;

	FindMin( UVMin, Vertex_A.TextureCoord_LightMap, UVMin );
	FindMin( UVMin, Vertex_B.TextureCoord_LightMap, UVMin );
	FindMin( UVMin, Vertex_C.TextureCoord_LightMap, UVMin );

	FindMax( UVMax, Vertex_A.TextureCoord_LightMap, UVMax );
	FindMax( UVMax, Vertex_B.TextureCoord_LightMap, UVMax );
	FindMax( UVMax, Vertex_C.TextureCoord_LightMap, UVMax );

	UVDelta = glm::abs( UVMax - UVDelta );

	// ****************************
	// Задаем границы размера карты освещения

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
}

//-------------------------------------------------------------------------//

void Triangle::FindMin( const glm::vec2& Vec1, const glm::vec2& Vec2, glm::vec2& Out )
{
	if ( Vec2.x < Vec1.x ) Out.x = Vec2.x;
	if ( Vec2.y < Vec1.y ) Out.y = Vec2.y;
}

//-------------------------------------------------------------------------//

void Triangle::FindMax( const glm::vec2& Vec1, const glm::vec2& Vec2, glm::vec2& Out )
{
	if ( Vec2.x > Vec1.x ) Out.x = Vec2.x;
	if ( Vec2.y > Vec1.y ) Out.y = Vec2.y;
}

//-------------------------------------------------------------------------//