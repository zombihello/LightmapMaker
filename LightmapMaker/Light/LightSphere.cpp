﻿///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
///////////////////////////
#include <glm\gtx\transform.hpp>

///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "LightSphere.h"
#include "../System/Logger.h"
//-------------------------------------------------------------------------//

vector<unsigned int> LightSphere::IdVertex =
{
	0, 1, 2,
	3, 4, 5,
	4, 6, 5,
	7, 8, 9,
	7, 10, 8,
	6, 11, 5,
	11, 12, 5,
	7, 13, 10,
	7, 14, 13,
	12, 15, 5,
	15, 16, 5,
	7, 17, 14,
	7, 18, 17,
	16, 19, 5,
	19, 20, 5,
	7, 21, 18,
	0, 22, 23,
	20, 24, 5,
	24, 25, 5,
	0, 26, 22,
	0, 27, 26,
	25, 28, 5,
	28, 29, 5,
	0, 30, 27,
	0, 31, 30,
	29, 32, 5,
	32, 33, 5,
	0, 34, 31,
	0, 35, 34,
	33, 36, 5,
	36, 3, 5,
	0, 2, 35,
	35, 2, 37,
	35, 37, 38,
	38, 37, 39,
	38, 39, 40,
	40, 39, 41,
	40, 41, 42,
	42, 41, 43,
	42, 43, 44,
	44, 43, 45,
	44, 45, 46,
	46, 45, 47,
	46, 47, 48,
	48, 47, 49,
	48, 49, 50,
	50, 49, 51,
	50, 51, 52,
	52, 51, 53,
	52, 53, 54,
	54, 53, 55,
	54, 55, 56,
	56, 55, 57,
	55, 58, 57,
	57, 58, 59,
	57, 59, 60,
	60, 59, 61,
	60, 61, 62,
	3, 36, 62,
	3, 62, 61,
	63, 62, 36,
	63, 36, 33,
	64, 60, 62,
	64, 62, 63,
	65, 57, 60,
	65, 60, 64,
	66, 56, 57,
	66, 57, 65,
	67, 54, 56,
	67, 56, 66,
	68, 52, 54,
	68, 54, 67,
	69, 50, 52,
	69, 52, 68,
	70, 48, 50,
	70, 50, 69,
	71, 46, 48,
	71, 48, 70,
	72, 44, 46,
	72, 46, 71,
	73, 42, 44,
	73, 44, 72,
	74, 40, 42,
	74, 42, 73,
	75, 38, 40,
	75, 40, 74,
	34, 35, 38,
	34, 38, 75,
	31, 34, 75,
	31, 75, 76,
	76, 75, 74,
	76, 74, 77,
	77, 74, 73,
	77, 73, 78,
	78, 73, 72,
	78, 72, 79,
	79, 72, 71,
	79, 71, 80,
	80, 71, 70,
	80, 70, 81,
	81, 70, 69,
	81, 69, 82,
	82, 69, 68,
	82, 68, 83,
	83, 68, 67,
	83, 67, 84,
	84, 67, 66,
	84, 66, 85,
	85, 66, 65,
	85, 65, 86,
	86, 65, 64,
	86, 64, 87,
	87, 64, 63,
	87, 63, 88,
	88, 63, 33,
	88, 33, 32,
	89, 88, 32,
	89, 32, 29,
	90, 87, 88,
	90, 88, 89,
	91, 86, 87,
	91, 87, 90,
	92, 85, 91,
	85, 86, 91,
	93, 84, 85,
	93, 85, 92,
	94, 83, 84,
	94, 84, 93,
	95, 82, 83,
	95, 83, 94,
	96, 81, 82,
	96, 82, 95,
	97, 80, 81,
	97, 81, 96,
	98, 79, 80,
	98, 80, 97,
	99, 78, 79,
	99, 79, 98,
	100, 77, 78,
	100, 78, 99,
	101, 76, 77,
	101, 77, 100,
	30, 31, 76,
	30, 76, 101,
	27, 30, 101,
	27, 101, 102,
	102, 101, 100,
	102, 100, 103,
	103, 100, 99,
	103, 99, 104,
	104, 99, 98,
	104, 98, 105,
	105, 98, 97,
	105, 97, 106,
	106, 97, 96,
	106, 96, 107,
	107, 96, 95,
	107, 95, 108,
	108, 95, 94,
	108, 94, 109,
	109, 94, 93,
	109, 93, 110,
	110, 93, 92,
	110, 92, 111,
	111, 92, 112,
	92, 91, 112,
	112, 91, 90,
	112, 90, 113,
	113, 90, 89,
	113, 89, 114,
	114, 89, 29,
	114, 29, 28,
	115, 114, 28,
	115, 28, 25,
	116, 113, 114,
	116, 114, 115,
	117, 112, 113,
	117, 113, 116,
	118, 111, 117,
	111, 112, 117,
	119, 110, 111,
	119, 111, 118,
	120, 109, 110,
	120, 110, 119,
	121, 108, 109,
	121, 109, 120,
	122, 107, 108,
	122, 108, 121,
	123, 106, 107,
	123, 107, 122,
	124, 105, 106,
	124, 106, 123,
	125, 104, 105,
	125, 105, 124,
	126, 103, 104,
	126, 104, 125,
	127, 102, 103,
	127, 103, 126,
	26, 27, 102,
	26, 102, 127,
	22, 26, 127,
	22, 127, 128,
	128, 127, 126,
	128, 126, 129,
	129, 126, 125,
	129, 125, 130,
	130, 125, 124,
	130, 124, 131,
	131, 124, 123,
	131, 123, 132,
	132, 123, 122,
	132, 122, 133,
	133, 122, 121,
	133, 121, 134,
	134, 121, 120,
	134, 120, 135,
	135, 120, 119,
	135, 119, 136,
	136, 119, 118,
	136, 118, 137,
	137, 118, 138,
	118, 117, 138,
	138, 117, 116,
	139, 140, 141,
	141, 140, 142,
	116, 115, 142,
	142, 115, 25,
	142, 25, 24,
	143, 142, 24,
	143, 24, 20,
	144, 141, 142,
	144, 142, 143,
	145, 139, 141,
	145, 141, 144,
	146, 147, 145,
	147, 139, 145,
	148, 149, 147,
	148, 147, 146,
	150, 151, 149,
	150, 149, 148,
	152, 153, 151,
	152, 151, 150,
	154, 155, 153,
	154, 153, 152,
	156, 157, 154,
	157, 155, 154,
	158, 159, 157,
	158, 157, 156,
	160, 161, 159,
	160, 159, 158,
	162, 163, 161,
	162, 161, 160,
	164, 165, 163,
	164, 163, 162,
	23, 22, 128,
	21, 165, 164,
	18, 21, 164,
	18, 164, 166,
	166, 164, 162,
	166, 162, 167,
	167, 162, 160,
	167, 160, 168,
	168, 160, 158,
	168, 158, 169,
	169, 158, 156,
	169, 156, 170,
	170, 156, 171,
	156, 154, 171,
	171, 154, 152,
	171, 152, 172,
	172, 152, 150,
	172, 150, 173,
	173, 150, 148,
	173, 148, 174,
	174, 148, 146,
	174, 146, 175,
	175, 146, 145,
	175, 145, 176,
	176, 145, 144,
	176, 144, 177,
	177, 144, 143,
	177, 143, 178,
	178, 143, 20,
	178, 20, 19,
	179, 178, 19,
	179, 19, 16,
	180, 177, 178,
	180, 178, 179,
	181, 176, 177,
	181, 177, 180,
	182, 175, 176,
	182, 176, 181,
	183, 174, 175,
	183, 175, 182,
	184, 173, 174,
	184, 174, 183,
	185, 172, 173,
	185, 173, 184,
	186, 171, 172,
	186, 172, 185,
	187, 170, 186,
	170, 171, 186,
	188, 169, 170,
	188, 170, 187,
	189, 168, 169,
	189, 169, 188,
	190, 167, 168,
	190, 168, 189,
	191, 166, 167,
	191, 167, 190,
	17, 18, 166,
	17, 166, 191,
	14, 17, 191,
	14, 191, 192,
	192, 191, 190,
	192, 190, 193,
	193, 190, 189,
	193, 189, 194,
	194, 189, 188,
	194, 188, 195,
	195, 188, 187,
	195, 187, 196,
	196, 187, 197,
	187, 186, 197,
	197, 186, 185,
	197, 185, 198,
	198, 185, 184,
	198, 184, 199,
	199, 184, 183,
	199, 183, 200,
	200, 183, 182,
	200, 182, 201,
	201, 182, 202,
	182, 181, 202,
	202, 181, 180,
	202, 180, 203,
	203, 180, 179,
	203, 179, 204,
	204, 179, 16,
	204, 16, 15,
	205, 204, 15,
	205, 15, 12,
	206, 203, 204,
	206, 204, 205,
	207, 202, 203,
	207, 203, 206,
	208, 201, 202,
	208, 202, 207,
	209, 200, 201,
	209, 201, 208,
	210, 199, 200,
	210, 200, 209,
	211, 198, 199,
	211, 199, 210,
	212, 197, 198,
	212, 198, 211,
	213, 196, 197,
	213, 197, 212,
	214, 195, 196,
	214, 196, 213,
	215, 194, 195,
	215, 195, 214,
	216, 193, 194,
	216, 194, 215,
	217, 192, 193,
	217, 193, 216,
	13, 14, 192,
	13, 192, 217,
	10, 13, 217,
	10, 217, 218,
	218, 217, 216,
	218, 216, 219,
	219, 216, 215,
	219, 215, 220,
	220, 215, 214,
	220, 214, 221,
	221, 214, 213,
	221, 213, 222,
	222, 213, 212,
	222, 212, 223,
	223, 212, 211,
	223, 211, 224,
	224, 211, 210,
	224, 210, 225,
	225, 210, 209,
	225, 209, 226,
	226, 209, 208,
	226, 208, 227,
	227, 208, 207,
	227, 207, 228,
	228, 207, 206,
	228, 206, 229,
	229, 206, 205,
	229, 205, 230,
	230, 205, 12,
	230, 12, 11,
	231, 230, 11,
	231, 11, 6,
	232, 229, 230,
	232, 230, 231,
	233, 228, 229,
	233, 229, 232,
	234, 227, 228,
	234, 228, 233,
	235, 226, 227,
	235, 227, 234,
	236, 225, 226,
	236, 226, 235,
	237, 224, 225,
	237, 225, 236,
	238, 223, 224,
	238, 224, 237,
	239, 222, 223,
	239, 223, 238,
	240, 221, 222,
	240, 222, 239,
	241, 220, 221,
	241, 221, 240,
	242, 219, 220,
	242, 220, 241,
	243, 218, 219,
	243, 219, 242,
	8, 10, 218,
	8, 218, 243,
	9, 8, 243,
	9, 243, 244,
	244, 243, 242,
	244, 242, 245,
	245, 242, 241,
	245, 241, 246,
	246, 241, 240,
	246, 240, 247,
	247, 240, 239,
	247, 239, 248,
	248, 239, 238,
	248, 238, 249,
	249, 238, 237,
	249, 237, 250,
	250, 237, 236,
	250, 236, 251,
	251, 236, 235,
	251, 235, 252,
	252, 235, 234,
	252, 234, 253,
	253, 234, 233,
	253, 233, 254,
	254, 233, 232,
	254, 232, 255,
	255, 232, 231,
	255, 231, 256,
	256, 231, 6,
	256, 6, 4,
	4, 3, 61,
	4, 61, 256,
	59, 255, 256,
	59, 256, 61,
	58, 254, 255,
	58, 255, 59,
	55, 253, 254,
	55, 254, 58,
	53, 252, 253,
	53, 253, 55,
	51, 251, 252,
	51, 252, 53,
	49, 250, 251,
	49, 251, 51,
	47, 249, 250,
	47, 250, 49,
	45, 248, 47,
	248, 249, 47,
	43, 247, 45,
	247, 248, 45,
	41, 246, 247,
	41, 247, 43,
	39, 245, 41,
	245, 246, 41,
	37, 257, 39,
	257, 245, 39,
	2, 1, 37,
	1, 257, 37
};

//-------------------------------------------------------------------------//

LightSphere::LightSphere() :
	Created( false ),
	Radius( 0 )
{}

//-------------------------------------------------------------------------//

LightSphere::LightSphere( const LightSphere& Copy ) :
	Created( Copy.Created ),
	Radius( Copy.Radius ),
	Position( Copy.Position ),
	Transformation( Copy.Transformation )
{
	if ( Created ) InitSphere( Radius );
}

//-------------------------------------------------------------------------//

LightSphere::~LightSphere()
{}

//-------------------------------------------------------------------------//

void LightSphere::InitSphere( const float& Radius )
{
	if ( Created ) VAO.Delete();
	
	this->Radius = Radius;
	vector<glm::vec3> Vertexs = CreateSphere( Radius );

	VAO.Create( Vertexs, OpenGL_API::VAO::Static_Draw, IdVertex, OpenGL_API::VAO::Static_Draw, 0, 0 );

	Created = true;
}

//-------------------------------------------------------------------------//

void LightSphere::Render()
{
	VAO.Bind();
	glDrawElements( GL_TRIANGLES, IdVertex.size(), GL_UNSIGNED_INT, 0 );
	VAO.Unbind();
}

//-------------------------------------------------------------------------//

void LightSphere::SetPosition( const glm::vec3& Position )
{
	this->Position = Position;
	Transformation = glm::translate( Position );
}

//-------------------------------------------------------------------------//

void LightSphere::SetRadius( const float& Radius )
{
	this->Radius = Radius;
	InitSphere( Radius );
}

//-------------------------------------------------------------------------//

const float& LightSphere::GetRadius()
{
	return Radius;
}

//-------------------------------------------------------------------------//

const glm::vec3& LightSphere::GetPosition()
{
	return Position;
}

//-------------------------------------------------------------------------//

const glm::mat4& LightSphere::GetTransformation()
{
	return Transformation;
}

//-------------------------------------------------------------------------//

LightSphere& LightSphere::operator=( const LightSphere& Copy )
{
	Created = Copy.Created;
	Radius = Copy.Radius;
	Position = Copy.Position;
	Transformation = Copy.Transformation;

	if ( Created ) InitSphere( Radius );

	return *this;
}

//-------------------------------------------------------------------------//

vector<glm::vec3> LightSphere::CreateSphere( const float& Radius )
{
	return vector<glm::vec3>
	{
		{ -0.00000f * Radius, 1.000000f * Radius, 0.00000f * Radius },
		{ 0.180240f * Radius, 0.980785f * Radius, 0.074658f * Radius },
		{ 0.195090f * Radius, 0.980785f * Radius, 0.000001f * Radius },
		{ 0.195090f * Radius, -0.980785f * Radius, -0.000001f * Radius },
		{ 0.180240f * Radius, -0.980785f * Radius, 0.074657f * Radius },
		{ 0.00000f * Radius, -1.000000f * Radius, -0.000001f * Radius },
		{ 0.137950f * Radius, -0.980785f * Radius, 0.137949f * Radius },
		{ -0.00000f * Radius, 1.000000f * Radius, 0.00000f * Radius },
		{ 0.137950f * Radius, 0.980785f * Radius, 0.137950f * Radius },
		{ 0.180240f * Radius, 0.980785f * Radius, 0.074658f * Radius },
		{ 0.074658f * Radius, 0.980785f * Radius, 0.180240f * Radius },
		{ 0.074658f * Radius, -0.980785f * Radius, 0.180239f * Radius },
		{ -0.00000f * Radius, -0.980785f * Radius, 0.195090f * Radius },
		{ -0.00000f * Radius, 0.980785f * Radius, 0.195091f * Radius },
		{ -0.074658f * Radius, 0.980785f * Radius, 0.180240f * Radius },
		{ -0.074658f * Radius, -0.980785f * Radius, 0.180239f * Radius },
		{ -0.137950f * Radius, -0.980785f * Radius, 0.137949f * Radius },
		{ -0.137950f * Radius, 0.980785f * Radius, 0.137950f * Radius },
		{ -0.180240f * Radius, 0.980785f * Radius, 0.074658f * Radius },
		{ -0.180240f * Radius, -0.980785f * Radius, 0.074657f * Radius },
		{ -0.195090f * Radius, -0.980785f * Radius, -0.000001f * Radius },
		{ -0.195090f * Radius, 0.980785f * Radius, 0.000001f * Radius },
		{ -0.180240f * Radius, 0.980785f * Radius, -0.074657f * Radius },
		{ -0.195090f * Radius, 0.980785f * Radius, 0.000001f * Radius },
		{ -0.180240f * Radius, -0.980785f * Radius, -0.074658f * Radius },
		{ -0.137950f * Radius, -0.980785f * Radius, -0.137950f * Radius },
		{ -0.137949f * Radius, 0.980785f * Radius, -0.137949f * Radius },
		{ -0.074658f * Radius, 0.980785f * Radius, -0.180239f * Radius },
		{ -0.074658f * Radius, -0.980785f * Radius, -0.180241f * Radius },
		{ 0.00000f * Radius, -0.980785f * Radius, -0.195091f * Radius },
		{ 0.00000f * Radius, 0.980785f * Radius, -0.195089f * Radius },
		{ 0.074658f * Radius, 0.980785f * Radius, -0.180239f * Radius },
		{ 0.074658f * Radius, -0.980785f * Radius, -0.180240f * Radius },
		{ 0.137950f * Radius, -0.980785f * Radius, -0.137950f * Radius },
		{ 0.137949f * Radius, 0.980785f * Radius, -0.137949f * Radius },
		{ 0.180240f * Radius, 0.980785f * Radius, -0.074657f * Radius },
		{ 0.180240f * Radius, -0.980785f * Radius, -0.074658f * Radius },
		{ 0.382683f * Radius, 0.923880f * Radius, 0.000001f * Radius },
		{ 0.353553f * Radius, 0.923880f * Radius, -0.146446f * Radius },
		{ 0.555570f * Radius, 0.831470f * Radius, 0.000001f * Radius },
		{ 0.513280f * Radius, 0.831470f * Radius, -0.212607f * Radius },
		{ 0.707106f * Radius, 0.707107f * Radius, 0.000001f * Radius },
		{ 0.653281f * Radius, 0.707107f * Radius, -0.270597f * Radius },
		{ 0.831469f * Radius, 0.555570f * Radius, 0.00000f * Radius },
		{ 0.768178f * Radius, 0.555570f * Radius, -0.318189f * Radius },
		{ 0.923879f * Radius, 0.382683f * Radius, 0.00000f * Radius },
		{ 0.853553f * Radius, 0.382684f * Radius, -0.353553f * Radius },
		{ 0.980785f * Radius, 0.195090f * Radius, 0.00000f * Radius },
		{ 0.906127f * Radius, 0.195090f * Radius, -0.375330f * Radius },
		{ 0.999999f * Radius, -0.00000f * Radius, 0.00000f * Radius },
		{ 0.923879f * Radius, 0.00000f * Radius, -0.382683f * Radius },
		{ 0.980785f * Radius, -0.195090f * Radius, -0.00000f * Radius },
		{ 0.906127f * Radius, -0.195090f * Radius, -0.375330f * Radius },
		{ 0.923879f * Radius, -0.382683f * Radius, -0.00000f * Radius },
		{ 0.853553f * Radius, -0.382683f * Radius, -0.353553f * Radius },
		{ 0.831469f * Radius, -0.555570f * Radius, -0.00000f * Radius },
		{ 0.768178f * Radius, -0.555570f * Radius, -0.318190f * Radius },
		{ 0.653281f * Radius, -0.707107f * Radius, -0.270598f * Radius },
		{ 0.707106f * Radius, -0.707107f * Radius, -0.00000f * Radius },
		{ 0.555570f * Radius, -0.831470f * Radius, -0.000001f * Radius },
		{ 0.513280f * Radius, -0.831469f * Radius, -0.212608f * Radius },
		{ 0.382683f * Radius, -0.923880f * Radius, -0.000001f * Radius },
		{ 0.353553f * Radius, -0.923879f * Radius, -0.146447f * Radius },
		{ 0.270598f * Radius, -0.923879f * Radius, -0.270599f * Radius },
		{ 0.392847f * Radius, -0.831469f * Radius, -0.392848f * Radius },
		{ 0.500000f * Radius, -0.707106f * Radius, -0.500000f * Radius },
		{ 0.587938f * Radius, -0.555570f * Radius, -0.587938f * Radius },
		{ 0.653281f * Radius, -0.382683f * Radius, -0.653282f * Radius },
		{ 0.693520f * Radius, -0.195090f * Radius, -0.693520f * Radius },
		{ 0.707106f * Radius, 0.00000f * Radius, -0.707106f * Radius },
		{ 0.693520f * Radius, 0.195091f * Radius, -0.693519f * Radius },
		{ 0.653281f * Radius, 0.382684f * Radius, -0.653281f * Radius },
		{ 0.587938f * Radius, 0.555570f * Radius, -0.587937f * Radius },
		{ 0.500000f * Radius, 0.707107f * Radius, -0.499999f * Radius },
		{ 0.392847f * Radius, 0.831470f * Radius, -0.392847f * Radius },
		{ 0.270598f * Radius, 0.923880f * Radius, -0.270597f * Radius },
		{ 0.146446f * Radius, 0.923880f * Radius, -0.353553f * Radius },
		{ 0.212607f * Radius, 0.831470f * Radius, -0.513279f * Radius },
		{ 0.270598f * Radius, 0.707107f * Radius, -0.653281f * Radius },
		{ 0.318190f * Radius, 0.555571f * Radius, -0.768177f * Radius },
		{ 0.353553f * Radius, 0.382684f * Radius, -0.853553f * Radius },
		{ 0.375330f * Radius, 0.195091f * Radius, -0.906127f * Radius },
		{ 0.382683f * Radius, 0.000001f * Radius, -0.923879f * Radius },
		{ 0.375330f * Radius, -0.195090f * Radius, -0.906127f * Radius },
		{ 0.353553f * Radius, -0.382683f * Radius, -0.853553f * Radius },
		{ 0.318190f * Radius, -0.555570f * Radius, -0.768178f * Radius },
		{ 0.270598f * Radius, -0.707106f * Radius, -0.653282f * Radius },
		{ 0.212608f * Radius, -0.831469f * Radius, -0.513281f * Radius },
		{ 0.146447f * Radius, -0.923879f * Radius, -0.353554f * Radius },
		{ 0.00000f * Radius, -0.923879f * Radius, -0.382684f * Radius },
		{ 0.00000f * Radius, -0.831469f * Radius, -0.555571f * Radius },
		{ 0.00000f * Radius, -0.707106f * Radius, -0.707107f * Radius },
		{ 0.00000f * Radius, -0.555570f * Radius, -0.831470f * Radius },
		{ 0.00000f * Radius, -0.382683f * Radius, -0.923880f * Radius },
		{ 0.00000f * Radius, -0.195090f * Radius, -0.980785f * Radius },
		{ 0.00000f * Radius, 0.000001f * Radius, -1.000000f * Radius },
		{ 0.00000f * Radius, 0.195091f * Radius, -0.980785f * Radius },
		{ 0.00000f * Radius, 0.382684f * Radius, -0.923879f * Radius },
		{ 0.00000f * Radius, 0.555571f * Radius, -0.831469f * Radius },
		{ 0.00000f * Radius, 0.707107f * Radius, -0.707106f * Radius },
		{ 0.00000f * Radius, 0.831470f * Radius, -0.555569f * Radius },
		{ -0.00000f * Radius, 0.923880f * Radius, -0.382683f * Radius },
		{ -0.146447f * Radius, 0.923880f * Radius, -0.353553f * Radius },
		{ -0.212607f * Radius, 0.831470f * Radius, -0.513279f * Radius },
		{ -0.270598f * Radius, 0.707107f * Radius, -0.653281f * Radius },
		{ -0.318190f * Radius, 0.555571f * Radius, -0.768177f * Radius },
		{ -0.353553f * Radius, 0.382684f * Radius, -0.853553f * Radius },
		{ -0.375330f * Radius, 0.195091f * Radius, -0.906127f * Radius },
		{ -0.382683f * Radius, 0.000001f * Radius, -0.923879f * Radius },
		{ -0.375330f * Radius, -0.195090f * Radius, -0.906127f * Radius },
		{ -0.353553f * Radius, -0.382683f * Radius, -0.853553f * Radius },
		{ -0.318190f * Radius, -0.555570f * Radius, -0.768178f * Radius },
		{ -0.270598f * Radius, -0.707106f * Radius, -0.653282f * Radius },
		{ -0.212608f * Radius, -0.831469f * Radius, -0.513281f * Radius },
		{ -0.146447f * Radius, -0.923879f * Radius, -0.353554f * Radius },
		{ -0.270598f * Radius, -0.923879f * Radius, -0.270599f * Radius },
		{ -0.392847f * Radius, -0.831469f * Radius, -0.392848f * Radius },
		{ -0.500000f * Radius, -0.707106f * Radius, -0.500000f * Radius },
		{ -0.587938f * Radius, -0.555570f * Radius, -0.587938f * Radius },
		{ -0.653281f * Radius, -0.382683f * Radius, -0.653282f * Radius },
		{ -0.693520f * Radius, -0.195090f * Radius, -0.693520f * Radius },
		{ -0.707107f * Radius, 0.00000f * Radius, -0.707107f * Radius },
		{ -0.693520f * Radius, 0.195091f * Radius, -0.693520f * Radius },
		{ -0.653281f * Radius, 0.382684f * Radius, -0.653281f * Radius },
		{ -0.587938f * Radius, 0.555570f * Radius, -0.587937f * Radius },
		{ -0.500000f * Radius, 0.707107f * Radius, -0.499999f * Radius },
		{ -0.392847f * Radius, 0.831470f * Radius, -0.392847f * Radius },
		{ -0.270598f * Radius, 0.923880f * Radius, -0.270597f * Radius },
		{ -0.353553f * Radius, 0.923880f * Radius, -0.146446f * Radius },
		{ -0.513280f * Radius, 0.831470f * Radius, -0.212607f * Radius },
		{ -0.653281f * Radius, 0.707107f * Radius, -0.270598f * Radius },
		{ -0.768178f * Radius, 0.555570f * Radius, -0.318189f * Radius },
		{ -0.853553f * Radius, 0.382684f * Radius, -0.353553f * Radius },
		{ -0.906127f * Radius, 0.195090f * Radius, -0.375330f * Radius },
		{ -0.923879f * Radius, 0.00000f * Radius, -0.382683f * Radius },
		{ -0.906127f * Radius, -0.195090f * Radius, -0.375330f * Radius },
		{ -0.853553f * Radius, -0.382683f * Radius, -0.353554f * Radius },
		{ -0.768178f * Radius, -0.555570f * Radius, -0.318190f * Radius },
		{ -0.653281f * Radius, -0.707107f * Radius, -0.270598f * Radius },
		{ -0.653281f * Radius, -0.707107f * Radius, -0.270598f * Radius },
		{ -0.392847f * Radius, -0.831469f * Radius, -0.392848f * Radius },
		{ -0.513280f * Radius, -0.831469f * Radius, -0.212608f * Radius },
		{ -0.353553f * Radius, -0.923879f * Radius, -0.146447f * Radius },
		{ -0.382683f * Radius, -0.923880f * Radius, -0.000001f * Radius },
		{ -0.555570f * Radius, -0.831470f * Radius, -0.000001f * Radius },
		{ -0.707107f * Radius, -0.707107f * Radius, -0.000001f * Radius },
		{ -0.831469f * Radius, -0.555570f * Radius, -0.00000f * Radius },
		{ -0.768178f * Radius, -0.555570f * Radius, -0.318190f * Radius },
		{ -0.923879f * Radius, -0.382683f * Radius, -0.00000f * Radius },
		{ -0.853553f * Radius, -0.382683f * Radius, -0.353554f * Radius },
		{ -0.980785f * Radius, -0.195090f * Radius, -0.00000f * Radius },
		{ -0.906127f * Radius, -0.195090f * Radius, -0.375330f * Radius },
		{ -1.000000f * Radius, -0.00000f * Radius, -0.00000f * Radius },
		{ -0.923879f * Radius, 0.00000f * Radius, -0.382683f * Radius },
		{ -0.980785f * Radius, 0.195090f * Radius, 0.00000f * Radius },
		{ -0.906127f * Radius, 0.195090f * Radius, -0.375330f * Radius },
		{ -0.923879f * Radius, 0.382683f * Radius, 0.00000f * Radius },
		{ -0.853553f * Radius, 0.382684f * Radius, -0.353553f * Radius },
		{ -0.831469f * Radius, 0.555570f * Radius, 0.00000f * Radius },
		{ -0.768178f * Radius, 0.555570f * Radius, -0.318189f * Radius },
		{ -0.707107f * Radius, 0.707107f * Radius, 0.00000f * Radius },
		{ -0.653281f * Radius, 0.707107f * Radius, -0.270598f * Radius },
		{ -0.555570f * Radius, 0.831470f * Radius, 0.000001f * Radius },
		{ -0.513280f * Radius, 0.831470f * Radius, -0.212607f * Radius },
		{ -0.382683f * Radius, 0.923880f * Radius, 0.000001f * Radius },
		{ -0.353553f * Radius, 0.923880f * Radius, -0.146446f * Radius },
		{ -0.353553f * Radius, 0.923880f * Radius, 0.146447f * Radius },
		{ -0.513280f * Radius, 0.831470f * Radius, 0.212608f * Radius },
		{ -0.653281f * Radius, 0.707107f * Radius, 0.270598f * Radius },
		{ -0.768178f * Radius, 0.555570f * Radius, 0.318190f * Radius },
		{ -0.853553f * Radius, 0.382683f * Radius, 0.353554f * Radius },
		{ -0.906127f * Radius, 0.195090f * Radius, 0.375330f * Radius },
		{ -0.923879f * Radius, -0.00000f * Radius, 0.382683f * Radius },
		{ -0.906127f * Radius, -0.195091f * Radius, 0.375330f * Radius },
		{ -0.853553f * Radius, -0.382684f * Radius, 0.353553f * Radius },
		{ -0.768178f * Radius, -0.555570f * Radius, 0.318189f * Radius },
		{ -0.653281f * Radius, -0.707107f * Radius, 0.270597f * Radius },
		{ -0.513280f * Radius, -0.831470f * Radius, 0.212607f * Radius },
		{ -0.353553f * Radius, -0.923880f * Radius, 0.146446f * Radius },
		{ -0.270598f * Radius, -0.923880f * Radius, 0.270597f * Radius },
		{ -0.392847f * Radius, -0.831470f * Radius, 0.392847f * Radius },
		{ -0.500000f * Radius, -0.707107f * Radius, 0.499999f * Radius },
		{ -0.587938f * Radius, -0.555571f * Radius, 0.587937f * Radius },
		{ -0.653281f * Radius, -0.382684f * Radius, 0.653281f * Radius },
		{ -0.693520f * Radius, -0.195091f * Radius, 0.693520f * Radius },
		{ -0.707107f * Radius, -0.000001f * Radius, 0.707107f * Radius },
		{ -0.693520f * Radius, 0.195090f * Radius, 0.693520f * Radius },
		{ -0.653281f * Radius, 0.382683f * Radius, 0.653282f * Radius },
		{ -0.587938f * Radius, 0.555570f * Radius, 0.587938f * Radius },
		{ -0.500000f * Radius, 0.707107f * Radius, 0.500000f * Radius },
		{ -0.392847f * Radius, 0.831469f * Radius, 0.392848f * Radius },
		{ -0.270598f * Radius, 0.923879f * Radius, 0.270599f * Radius },
		{ -0.146447f * Radius, 0.923879f * Radius, 0.353554f * Radius },
		{ -0.212607f * Radius, 0.831469f * Radius, 0.513280f * Radius },
		{ -0.270598f * Radius, 0.707106f * Radius, 0.653282f * Radius },
		{ -0.318190f * Radius, 0.555570f * Radius, 0.768178f * Radius },
		{ -0.353553f * Radius, 0.382683f * Radius, 0.853554f * Radius },
		{ -0.375330f * Radius, 0.195090f * Radius, 0.906127f * Radius },
		{ -0.382683f * Radius, -0.000001f * Radius, 0.923879f * Radius },
		{ -0.375330f * Radius, -0.195091f * Radius, 0.906127f * Radius },
		{ -0.353553f * Radius, -0.382684f * Radius, 0.853553f * Radius },
		{ -0.318190f * Radius, -0.555571f * Radius, 0.768177f * Radius },
		{ -0.270598f * Radius, -0.707107f * Radius, 0.653281f * Radius },
		{ -0.212608f * Radius, -0.831470f * Radius, 0.513279f * Radius },
		{ -0.146447f * Radius, -0.923880f * Radius, 0.353553f * Radius },
		{ -0.00000f * Radius, -0.923880f * Radius, 0.382683f * Radius },
		{ -0.00000f * Radius, -0.831470f * Radius, 0.555570f * Radius },
		{ -0.00000f * Radius, -0.707107f * Radius, 0.707106f * Radius },
		{ -0.00000f * Radius, -0.555571f * Radius, 0.831469f * Radius },
		{ -0.00000f * Radius, -0.382684f * Radius, 0.923879f * Radius },
		{ -0.00000f * Radius, -0.195091f * Radius, 0.980785f * Radius },
		{ -0.00000f * Radius, -0.000001f * Radius, 1.000000f * Radius },
		{ -0.00000f * Radius, 0.195090f * Radius, 0.980785f * Radius },
		{ 0.00000f * Radius, 0.382683f * Radius, 0.923880f * Radius },
		{ -0.00000f * Radius, 0.555570f * Radius, 0.831470f * Radius },
		{ -0.00000f * Radius, 0.707106f * Radius, 0.707107f * Radius },
		{ 0.00000f * Radius, 0.831469f * Radius, 0.555571f * Radius },
		{ -0.00000f * Radius, 0.923879f * Radius, 0.382684f * Radius },
		{ 0.146447f * Radius, 0.923879f * Radius, 0.353554f * Radius },
		{ 0.212607f * Radius, 0.831469f * Radius, 0.513280f * Radius },
		{ 0.270598f * Radius, 0.707106f * Radius, 0.653282f * Radius },
		{ 0.318190f * Radius, 0.555570f * Radius, 0.768178f * Radius },
		{ 0.353553f * Radius, 0.382683f * Radius, 0.853554f * Radius },
		{ 0.375330f * Radius, 0.195090f * Radius, 0.906128f * Radius },
		{ 0.382683f * Radius, -0.000001f * Radius, 0.923879f * Radius },
		{ 0.375330f * Radius, -0.195091f * Radius, 0.906127f * Radius },
		{ 0.353553f * Radius, -0.382684f * Radius, 0.853553f * Radius },
		{ 0.318190f * Radius, -0.555571f * Radius, 0.768177f * Radius },
		{ 0.270598f * Radius, -0.707107f * Radius, 0.653281f * Radius },
		{ 0.212608f * Radius, -0.831470f * Radius, 0.513279f * Radius },
		{ 0.146447f * Radius, -0.923880f * Radius, 0.353553f * Radius },
		{ 0.270598f * Radius, -0.923880f * Radius, 0.270597f * Radius },
		{ 0.392847f * Radius, -0.831470f * Radius, 0.392847f * Radius },
		{ 0.500000f * Radius, -0.707107f * Radius, 0.500000f * Radius },
		{ 0.587938f * Radius, -0.555571f * Radius, 0.587937f * Radius },
		{ 0.653281f * Radius, -0.382684f * Radius, 0.653281f * Radius },
		{ 0.693520f * Radius, -0.195091f * Radius, 0.693520f * Radius },
		{ 0.707107f * Radius, -0.000001f * Radius, 0.707107f * Radius },
		{ 0.693520f * Radius, 0.195090f * Radius, 0.693520f * Radius },
		{ 0.653282f * Radius, 0.382683f * Radius, 0.653282f * Radius },
		{ 0.587938f * Radius, 0.555570f * Radius, 0.587938f * Radius },
		{ 0.500000f * Radius, 0.707107f * Radius, 0.500000f * Radius },
		{ 0.392847f * Radius, 0.831469f * Radius, 0.392848f * Radius },
		{ 0.270598f * Radius, 0.923879f * Radius, 0.270599f * Radius },
		{ 0.353553f * Radius, 0.923880f * Radius, 0.146447f * Radius },
		{ 0.513280f * Radius, 0.831470f * Radius, 0.212608f * Radius },
		{ 0.653281f * Radius, 0.707107f * Radius, 0.270599f * Radius },
		{ 0.768178f * Radius, 0.555570f * Radius, 0.318190f * Radius },
		{ 0.853553f * Radius, 0.382683f * Radius, 0.353554f * Radius },
		{ 0.906127f * Radius, 0.195090f * Radius, 0.375330f * Radius },
		{ 0.923880f * Radius, -0.00000f * Radius, 0.382683f * Radius },
		{ 0.906127f * Radius, -0.195091f * Radius, 0.375330f * Radius },
		{ 0.853553f * Radius, -0.382684f * Radius, 0.353553f * Radius },
		{ 0.768178f * Radius, -0.555570f * Radius, 0.318189f * Radius },
		{ 0.653281f * Radius, -0.707107f * Radius, 0.270598f * Radius },
		{ 0.513280f * Radius, -0.831470f * Radius, 0.212607f * Radius },
		{ 0.353553f * Radius, -0.923880f * Radius, 0.146446f * Radius },
		{ 0.353553f * Radius, 0.923880f * Radius, 0.146447f * Radius },
	};
}

//-------------------------------------------------------------------------//