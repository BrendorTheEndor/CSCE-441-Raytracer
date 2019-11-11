#pragma once
#include "Shape.h"

class Record {
public:
	glm::vec3 ka;
	glm::vec3 kd;
	glm::vec3 ks;
	glm::vec3 km;
	float s;
	glm::vec3 P; // O + td
	glm::vec3 normal; // Calculated differently for each object

	Record();
	Record(glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float s, glm::vec3 P, glm::vec3 normal);
};

