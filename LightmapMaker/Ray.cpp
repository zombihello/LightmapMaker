#include "Ray.h"

//-------------------------------------------------------------------------//

void Ray::SetRay( const glm::vec3& StartRay, const glm::vec3& EndRay )
{
	this->StartRay = StartRay;
	this->EndRay = EndRay;

	Direction = EndRay - StartRay;
	Normalize_Direction = glm::normalize( Direction );
}

//-------------------------------------------------------------------------//

bool Ray::IntersectTriangle( Triangle& Triangle )
{
	float Dist1 = glm::dot( StartRay - Triangle.A, Triangle.Normal );
	float Dist2 = glm::dot( EndRay - Triangle.A, Triangle.Normal );

	if ( Dist1 * Dist2 >= 0 )
		return false;

	if ( Dist1 == Dist2 )
		return false;

	glm::vec3 Tmp = StartRay + Direction * ( -Dist1 / ( Dist2 - Dist1 ) );

	glm::vec3 vTest;

	vTest = glm::cross( Triangle.Normal, Triangle.B - Triangle.A );
	if ( glm::dot( vTest, Tmp - Triangle.A ) < 0 )
		return false;

	vTest = glm::cross( Triangle.Normal, Triangle.C - Triangle.B );
	if ( glm::dot( vTest, Tmp - Triangle.B ) < 0 )
		return false;

	vTest = glm::cross( Triangle.Normal, Triangle.A - Triangle.C );
	if ( glm::dot( vTest, Tmp - Triangle.A ) < 0 )
		return false;

	return true;
}

//-------------------------------------------------------------------------//
