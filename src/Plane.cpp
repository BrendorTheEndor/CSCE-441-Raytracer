#include "Plane.h"


Plane::Plane() {
}

Plane::~Plane() {
}

Plane::Plane(glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float s, glm::vec3 center, glm::vec3 normal) : Shape(ka, kd, ks, km, s) {
	this->center = center;
	this->normal = normal;
}

float Plane::Intersect(glm::vec3 rayDirection, glm::vec3 rayOrigin, float t0, float t1) {
	float t = glm::dot((center - rayOrigin), normal) / glm::dot(rayDirection, normal);

	if(t >= t0 && t <= t1) {
		return t;
	}
	else {
		return std::numeric_limits<float>::max();
	}
}

glm::vec3 Plane::GetNormal() {
	return normal;
}