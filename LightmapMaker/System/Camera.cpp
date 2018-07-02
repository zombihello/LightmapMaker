///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
///////////////////////////
#include <glm\gtx\transform.hpp>

///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "Camera.h"

//-------------------------------------------------------------------------//

Camera::Camera() :
	IsUpdate( false )
{}

//-------------------------------------------------------------------------//

Camera::Camera( const glm::vec3& Position, const glm::vec3& TargetPoint, const glm::vec3& AxisVertical ) :
	IsUpdate( false ),
	Position( Position ),
	TargetPoint( TargetPoint ),
	AxisVertical( AxisVertical )
{}

//-------------------------------------------------------------------------//

void Camera::SetAxisVertical( const glm::vec3& AxisVertical )
{
	this->AxisVertical = AxisVertical;
	IsUpdate = false;
}

//-------------------------------------------------------------------------//

void Camera::SetPosition( const glm::vec3& Position )
{
	this->Position = Position;
	IsUpdate = false;
}

//-------------------------------------------------------------------------//

void Camera::SetTargetPoint( const glm::vec3& TargetPoint )
{
	this->TargetPoint = TargetPoint;
	IsUpdate = false;
}

//-------------------------------------------------------------------------//

const glm::vec3& Camera::GetAxisVertical()
{
	return AxisVertical;
}

//-------------------------------------------------------------------------//

const glm::vec3& Camera::GetPosition()
{
	return Position;
}

//-------------------------------------------------------------------------//

const glm::vec3& Camera::GetTargetPoint()
{
	return TargetPoint;
}

//-------------------------------------------------------------------------//

glm::mat4& Camera::GetViewMatrix()
{
	if ( !IsUpdate )
	{
		ViewMatrix = glm::lookAt( Position, TargetPoint, AxisVertical );
		IsUpdate = true;
	}

	return ViewMatrix;
}

//-------------------------------------------------------------------------//