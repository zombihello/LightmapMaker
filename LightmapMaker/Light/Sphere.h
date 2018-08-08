//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// ����� �� ����:		https://vk.com/zombihello
// ����������� ������:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef SPHERE_H
#define SPHERE_H

///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "../OpenGL/OpenGL.h"

class Sphere
{
public:
	/* ����������� */
	Sphere();
	Sphere( const Sphere& Copy );

	/* ���������� */
	~Sphere();

	/* ���������������� ����� */
	void InitSphere( const float& Radius );

	/* ����������� ����� */
	void Render();

	/* ������ ������� */
	void SetPosition( const glm::vec3& Position );

	/* ������ ������ */
	void SetRadius( const float& Radius );

	/* �������� ������ ����� */
	const float& GetRadius();

	/* �������� ������� ����� */
	const glm::vec3& GetPosition();

	/* �������� ������� ������������� */
	glm::mat4& GetTransformation();

	Sphere& operator=( const Sphere& Copy );

private:
	/* ������������� ������� ����� */
	vector<glm::vec3>	CreateSphere( const float& Radius );

	bool							Created;
	float							Radius;

	OpenGL_API::VAO					VAO;
	glm::vec3						Position;
	glm::mat4						Transformation;

	static vector<unsigned int>		IdVertex;
};


#endif // !SPHERE_H

