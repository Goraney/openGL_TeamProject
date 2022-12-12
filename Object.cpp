#include "Object.h"

Object::Object()
{
	world = glm::mat4(1.0);

	//position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	//right = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
	//up = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
	//look = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);



}

Object::~Object()
{

}

void Object::Rotate(glm::vec3 axis, float angle)
{
	world = glm::rotate(world, glm::radians(angle), axis);
}

void Object::Move()
{

}

void Object::Animate()
{

}

/////////////

Player::Player()
{

}

Player::~Player()
{

}

void Player::Animate()
{

}