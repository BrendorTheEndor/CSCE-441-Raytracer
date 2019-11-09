#pragma once
#include <glm/glm.hpp>
#include "Record.h"

class Shape
{
public:
	Shape(void);
	~Shape(void);
	Shape(glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float s);

	virtual float Intersect(glm::vec3 rayDirection, float t0, float t1);

	glm::vec3 GetKa() { return ka; }
	glm::vec3 GetKd() { return kd; }
	glm::vec3 GetKs() { return ks; }
	glm::vec3 GetKm() { return km; }
	float GetS() { return s; }

private:
	glm::vec3 ka;
	glm::vec3 kd;
	glm::vec3 ks;
	glm::vec3 km; // I think this is "a"
	float s; // I think this is "n"
};
