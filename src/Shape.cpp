#include "Shape.h"

Shape::Shape(void) {
}

Shape::~Shape(void) {
}

Shape::Shape(glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float s) {
	this->ka = ka;
	this->kd = kd;
	this->ks = ks;
	this->km = km;
	this->s = s;
}