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
	glm::vec2 UVMin, UVMax, UVDelta, UV[ 3 ];
	glm::vec3 Vect1, Vect2;

	this->Vertex_A = Vertex_A;
	this->Vertex_B = Vertex_B;
	this->Vertex_C = Vertex_C;

	Normal = glm::normalize( glm::cross( Vertex_B.Position - Vertex_A.Position, Vertex_C.Position - Vertex_A.Position ) );
	Distance = -( Normal.x * Vertex_A.Position.x + Normal.y * Vertex_A.Position.y + Normal.z * Vertex_A.Position.z );

	// ****************************
	// Определяем тип плоскости

	if ( abs( Normal.x ) > abs( Normal.y ) && abs( Normal.x ) > abs( Normal.z ) )
	{
		Flag = 1;

		UV[ 0 ].x = Vertex_A.Position.y;
		UV[ 0 ].y = Vertex_A.Position.z;

		UV[ 1 ].x = Vertex_B.Position.y;
		UV[ 1 ].y = Vertex_B.Position.z;

		UV[ 2 ].x = Vertex_C.Position.y;
		UV[ 2 ].y = Vertex_C.Position.z;
	}
	else if ( abs( Normal.y ) > abs( Normal.x ) && abs( Normal.y ) > abs( Normal.z ) )
	{
		Flag = 2;

		UV[ 0 ].x = Vertex_A.Position.x;
		UV[ 0 ].y = Vertex_A.Position.z;

		UV[ 1 ].x = Vertex_B.Position.x;
		UV[ 1 ].y = Vertex_B.Position.z;

		UV[ 2 ].x = Vertex_C.Position.x;
		UV[ 2 ].y = Vertex_C.Position.z;
	}
	else
	{
		Flag = 3;

		UV[ 0 ].x = Vertex_A.Position.x;
		UV[ 0 ].y = Vertex_A.Position.y;

		UV[ 1 ].x = Vertex_B.Position.x;
		UV[ 1 ].y = Vertex_B.Position.y;

		UV[ 2 ].x = Vertex_C.Position.x;
		UV[ 2 ].y = Vertex_C.Position.y;
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

	UVDelta = glm::abs( UVMax - UVMin );

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