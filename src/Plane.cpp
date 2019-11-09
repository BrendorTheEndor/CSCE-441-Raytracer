#include "Plane.h"


Plane::Plane() {
}

Plane::~Plane() {
}

Plane::Plane(glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float s, glm::vec3 center, glm::vec3 normal) {
	Shape(ka, kd, ks, km, s);
	this->center = center;
	this->normal = normal;
}

float Plane::Intersect(glm::vec3 rayDirection, float t0, float t1) {
	// TODO
}
