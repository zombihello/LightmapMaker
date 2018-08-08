//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// яБЪГЭ ЯН ЛМНИ:		https://vk.com/zombihello
// пЕОНГХРНПХИ ДБХФЙЮ:  https://github.com/zombihello/LightmapMaker
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
	/* йнмярпсйрнп */
	Sphere();
	Sphere( const Sphere& Copy );

	/* деярпсйрнп */
	~Sphere();

	/* хмхжхюкхгхпнбюрэ ятепс */
	void InitSphere( const float& Radius );

	/* нрпемдепхрэ ятепс */
	void Render();

	/* гюдюрэ онгхжхч */
	void SetPosition( const glm::vec3& Position );

	/* гюдюрэ пюдхся */
	void SetRadius( const float& Radius );

	/* онксвхрэ пюдхся ятепш */
	const float& GetRadius();

	/* онксвхрэ онгхжхч ятепш */
	const glm::vec3& GetPosition();

	/* онксвхрэ люрпхжс рпюмятнплюжхх */
	glm::mat4& GetTransformation();

	Sphere& operator=( const Sphere& Copy );

private:
	/* яцемепхпнбюрэ бепьхмш ятепш */
	vector<glm::vec3>	CreateSphere( const float& Radius );

	bool							Created;
	float							Radius;

	OpenGL_API::VAO					VAO;
	glm::vec3						Position;
	glm::mat4						Transformation;

	static vector<unsigned int>		IdVertex;
};


#endif // !SPHERE_H

