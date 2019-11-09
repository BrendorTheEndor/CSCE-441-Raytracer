#include "Sphere.h"

Sphere::Sphere()
{
}

Sphere::~Sphere()
{
}

Sphere::Sphere(glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float s, glm::vec3 position, float radius) {
	Shape(ka, kd, ks, km, s);
	this->position = position;
	this->radius = radius;
}