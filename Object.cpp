#include "Object.h"

Object::Object()
{
	world_Tr = glm::mat4(1.0);
	world_Ry = glm::mat4(1.0);
	
	position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	right = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
	up = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
	look = glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);



}

Object::Object(glm::mat4 position, glm::vec4 look)
{
	world_Tr = position;
	world_Ry = glm::mat4(1.0);

	this->look = look;
}

Object::~Object()
{

}

void Object::Rotate(glm::vec3 axis, float angle)
{
	world_Ry = glm::rotate(world_Ry, glm::radians(angle), axis);

	look = glm::normalize(world_Ry * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f));
}

void Object::Translate(float speed)
{
	glm::vec3 distance = glm::vec3(look.x, look.y, look.z);
	world_Tr = glm::translate(world_Tr, distance * speed);
}

glm::mat4 Object::Get_worldTR()
{
	return world_Tr * world_Ry;
}

glm::mat4 Object::Get_bulletTR()
{
	glm::mat4 Sc = glm::mat4(1.0);
	Sc = glm::scale(Sc, glm::vec3(0.2, 0.2, 0.2));
	return world_Tr * world_Ry * Sc;
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

void Player::Fire()
{
	
}

void Player::Animate()
{

}