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
	//std::cout << "Called child Intersect" << std::endl;

	// TODO
	float a = glm::dot(rayDirection, rayDirection);
	float b = 2.0f * glm::dot((rayOrigin - this->position), rayDirection);
	float c = glm::dot(rayOrigin - this->position, rayOrigin - this->position) - pow(this->radius, 2);

	float intersectionTerm = pow(b, 2) - (4 * a * c);

	if(intersectionTerm > 0) {
		//std::cout << "Two intersections" << std::endl;
		float tPlus = (-b + sqrt(intersectionTerm)) / (2 * a);
		float tMinus = (-b - sqrt(intersectionTerm)) / (2 * a);

		//std::cout << "tPlus: " << tPlus << " tMinus: " << tMinus << std::endl;

		float t = glm::min(tPlus, tMinus);

		//std::cout << "t: " << t << std::endl;

		glm::vec3 P = rayOrigin + (t * rayDirection);
		lastNormal = glm::normalize(P - this->position);

		if(t >= t0 && t <= t1) {
			return t;
		}
		else {
			return std::numeric_limits<float>::max();
		}
	}
	else if(abs(intersectionTerm) <= FLT_EPSILON) { // I think this is right?
		std::cout << "One intersection" << std::endl;
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
	else if(intersectionTerm < 0) {
		//std::cout << "No intersections" << std::endl;
		return std::numeric_limits<float>::max();
	}
}

glm::vec3 Sphere::GetNormal() {
	return lastNormal;
}