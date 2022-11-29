#pragma once
#include "stdafx.h"

class Object
{
public:
	Object();
	~Object();

	void Rotate();
	void Move();

	virtual void Animate();

public:
	int id;

	glm::mat4 world;

	glm::vec3 position;
	glm::vec3 look;
	glm::vec3 up;
	glm::vec3 right;

};

class Player : Object
{
public:
	Player();
	~Player();

	virtual void Animate();
};