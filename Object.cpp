#include "Object.h"

Object::Object()
{
	world_Ry = glm::mat4(1.0);
	world_Tr = glm::mat4(1.0);
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
	world_Ry = glm::rotate(world_Ry, glm::radians(angle), axis);
}

void Object::Translate(glm::vec3 translate)
{
	world_Tr = glm::translate(world_Tr, translate);
}

glm::mat4 Object::Get_worldTR()
{
	return world_Tr * world_Ry;
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