#include "Light.h"

Light::Light(void)
{
}

Light::~Light(void)
{
}

Light::Light(glm::vec3 position, glm::vec3 color) {
	this->position = position;
	this->color = color;
}