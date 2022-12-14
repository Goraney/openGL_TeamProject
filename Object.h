#pragma once
#include "stdafx.h"

class Object
{
public:
	Object();
	Object(glm::mat4 position, glm::vec4 look);
	~Object();

	virtual void Rotate(glm::vec3 axis, float angle);
	virtual void Translate(float speed);
	virtual glm::mat4 Get_worldTR();
	virtual void Move();

	virtual void Animate();

public:
	int id;

	glm::mat4 world_Ry;
	glm::mat4 world_Tr;

	glm::vec4 position;
	glm::vec4 look;
	glm::vec4 up;
	glm::vec4 right;

};

class Player : public Object
{
public:
	Player();
	~Player();

	//virtual void Rotate(glm::vec3 axis, float angle);
	//virtual void Move();

	void Fire();

	virtual void Animate();
};