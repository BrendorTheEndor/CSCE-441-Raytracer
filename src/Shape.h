#pragma once
#include <glm/glm.hpp>
#include <iostream>
#include "Record.h"

class Shape {
public:
	Shape(void);
	~Shape(void);
	Shape(glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float s);

	// Get the point of intersection (and other data) of a ray with the shape
	virtual float Intersect(glm::vec3 rayDirection, glm::vec3 rayOrigin, float t0, float t1) { return 0.0f; }
	// Returns the normal vector of the shape
	virtual glm::vec3 GetNormal() { return glm::vec3(0.0f, 0.0f, 0.0f); }

	glm::vec3 GetKa() { return ka; }
	glm::vec3 GetKd() { return kd; }
	glm::vec3 GetKs() { return ks; }
	glm::vec3 GetKm() { return km; }
	float GetS() { return s; }

private:
	// Material properties
	glm::vec3 ka;
	glm::vec3 kd;
	glm::vec3 ks;
	glm::vec3 km;
	float s; // This is "n"
};
