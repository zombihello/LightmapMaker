#include "Plane.h"

//-------------------------------------------------------------------------//

bool Plane::operator!=( Triangle& Triangle )
{
	return Triangles[0] != Triangle && Triangles[1] != Triangle;
}

//-------------------------------------------------------------------------//
