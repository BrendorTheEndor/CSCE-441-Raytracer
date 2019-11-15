#include "Sphere.h"

Sphere::Sphere() {
}

Sphere::~Sphere() {
}

Sphere::Sphere(glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float s, glm::vec3 position, float radius) : Shape(ka, kd, ks, km, s) {
	this->position = position;
	this->radius = radius;
}

float Sphere::Intersect(glm::vec3 rayDirection, glm::vec3 rayOrigin, float t0, float t1) {

	float a = glm::dot(rayDirection, rayDirection);
	float b = 2.0f * glm::dot((rayOrigin - this->position), rayDirection);
	float c = glm::dot(rayOrigin - this->position, rayOrigin - this->position) - pow(this->radius, 2);

	float intersectionTerm = pow(b, 2) - (4 * a * c);

	// If term is > 0, take the lowest of two "t" vals
	if(intersectionTerm > 0) {

		float tPlus = (-b + sqrt(intersectionTerm)) / (2 * a);
		float tMinus = (-b - sqrt(intersectionTerm)) / (2 * a);

		float t = glm::min(tPlus, tMinus);

		glm::vec3 P = rayOrigin + (t * rayDirection);
		lastNormal = glm::normalize(P - this->position);

		if(t >= t0 && t <= t1) {
			return t;
		}
		else {
			return std::numeric_limits<float>::max();
		}
	}
	// If term = 0, only one "t" term so take that
	else if(abs(intersectionTerm) <= FLT_EPSILON) {

		float t = (-b + sqrt(intersectionTerm)) / (2 * a);

		glm::vec3 P = rayOrigin + (t * rayDirection);
		lastNormal = glm::normalize(P - this->position);

		if(t >= t0 && t <= t1) {
			return t;
		}
		else {
			return std::numeric_limits<float>::max();
		}
	}
	// If term < 0, no intersection
	else if(intersectionTerm < 0) {
		return std::numeric_limits<float>::max();
	}
}

glm::vec3 Sphere::GetNormal() {
	return lastNormal;
}