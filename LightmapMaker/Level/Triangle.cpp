﻿///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "../System/ArgumentsStart.h"
#include "Triangle.h"

//-------------------------------------------------------------------------//

Triangle::Triangle()
{}

//-------------------------------------------------------------------------//

Triangle::Triangle( const glm::vec3& Vertex_A, const glm::vec3& Vertex_B, const glm::vec3& Vertex_C )
{
	InitTriangle( Vertex_A, Vertex_B, Vertex_C );
}

//-------------------------------------------------------------------------//

void Triangle::InitTriangle( const glm::vec3& Vertex_A, const glm::vec3& Vertex_B, const glm::vec3& Vertex_C )
{
	int Flag = 0;
	float Distance, X, Y, Z;
	glm::vec2 UV[ 3 ];
	glm::vec3 Vect1, Vect2;

	A = Vertex_A;
	B = Vertex_B;
	C = Vertex_C;

	Normal = glm::normalize( glm::cross( B - A, C - A ) );
	Distance = -( Normal.x * A.x + Normal.y * A.y + Normal.z * A.z );

	// ****************************
	// Определяем тип плоскости

	if ( fabs( Normal.x ) > fabs( Normal.y ) && fabs( Normal.x ) > fabs( Normal.z ) )
	{
		Flag = 1;

		UV[ 0 ].x = A.y;
		UV[ 0 ].y = A.z;

		UV[ 1 ].x = B.y;
		UV[ 1 ].y = B.z;

		UV[ 2 ].x = C.y;
		UV[ 2 ].y = C.z;
	}
	else if ( fabs( Normal.y ) > fabs( Normal.x ) && fabs( Normal.y ) > fabs( Normal.z ) )
	{
		Flag = 2;

		UV[ 0 ].x = A.x;
		UV[ 0 ].y = A.z;

		UV[ 1 ].x = B.x;
		UV[ 1 ].y = B.z;

		UV[ 2 ].x = C.x;
		UV[ 2 ].y = C.z;
	}
	else
	{
		Flag = 3;

		UV[ 0 ].x = A.x;
		UV[ 0 ].y = A.y;

		UV[ 1 ].x = B.x;
		UV[ 1 ].y = B.y;

		UV[ 2 ].x = C.x;
		UV[ 2 ].y = C.y;
	}

	// ****************************
	// Находим минимальные, максимальные и разницу текстурных координат

	glm::vec2 UVMin = UV[ 0 ];
	glm::vec2 UVMax = UV[ 0 ];

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

	//TODO: [zombiHello] - 16 - это масштаб карты освещения для полгиноа. Нужно сделать, чтобы это значение считывалось с карты
	glm::vec2 UVDelta = glm::abs( UVMax - UVMin );
	SizeLightmap_PrimaryIllumination = UVDelta;
	SizeLightmap_SecondaryLight = UVDelta / 4.f;

	// ************************************************************************************

	if ( SizeLightmap_PrimaryIllumination.x < 4 )
		SizeLightmap_PrimaryIllumination.x = 4;

	if ( SizeLightmap_PrimaryIllumination.y < 4 )
		SizeLightmap_PrimaryIllumination.y = 4;

	if ( SizeLightmap_PrimaryIllumination.x > ArgumentsStart::MaxSizeLightmap )
		SizeLightmap_PrimaryIllumination.x = ArgumentsStart::MaxSizeLightmap;

	if ( SizeLightmap_PrimaryIllumination.y > ArgumentsStart::MaxSizeLightmap )
		SizeLightmap_PrimaryIllumination.y = ArgumentsStart::MaxSizeLightmap;

	// ************************************************************************************

	if ( SizeLightmap_SecondaryLight.x < 4 )
		SizeLightmap_SecondaryLight.x = 4;

	if ( SizeLightmap_SecondaryLight.y < 4 )
		SizeLightmap_SecondaryLight.y = 4;

	if ( SizeLightmap_SecondaryLight.x > ArgumentsStart::MaxSizeLightmap )
		SizeLightmap_SecondaryLight.x = ArgumentsStart::MaxSizeLightmap;

	if ( SizeLightmap_SecondaryLight.y > ArgumentsStart::MaxSizeLightmap )
		SizeLightmap_SecondaryLight.y = ArgumentsStart::MaxSizeLightmap;

	// ****************************
	// Находим координаты

	switch ( Flag )
	{
	case 1: //YZ Plane
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

	case 2: //XZ Plane
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

	case 3: //XY Plane
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