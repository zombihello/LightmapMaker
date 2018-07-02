//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// Связь со мной:		https://vk.com/zombihello
// Репозиторий движка:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef CAMERA_H
#define CAMERA_H

///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
///////////////////////////
#include <glm\glm.hpp>

class Camera
{
public:
	/* КОНСТРУКТОР */
	Camera();
	Camera( const glm::vec3& Position, const glm::vec3& TargetPoint, const glm::vec3& AxisVertical );

	/* ЗАДАТЬ ВЕКТОР ВВЕРХ */
	void SetAxisVertical( const glm::vec3& AxisVertical );

	/* ЗАДАТЬ ПОЗИЦИЮ КАМЕРЫ */
	void SetPosition( const glm::vec3& Position );

	/* ЗАДАТЬ ТОЧКУ ВЗГЛЯДА */
	void SetTargetPoint( const glm::vec3& TargetPoint );

	/* ПОЛУЧИТЬ ВЕКТОР ВВЕРХ */
	const glm::vec3& GetAxisVertical();

	/* ПОЛУЧИТЬ ПОЗИЦИЮ КАМЕРЫ */
	const glm::vec3& GetPosition();

	/* ПОЛУЧИТЬ ТОЧКУ ВЗГЛЯДА */
	const glm::vec3& GetTargetPoint();

	/* ПОЛУЧИТЬ ВИДОВУЮ МАТРИЦУ */
	glm::mat4& GetViewMatrix();

private:
	bool			IsUpdate;

	glm::vec3		Position;
	glm::vec3		TargetPoint;
	glm::vec3		AxisVertical;
	glm::mat4		ViewMatrix;
};

#endif // !CAMERA_H
