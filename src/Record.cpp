#include "Record.h"

Record::Record() {

}

Record::Record(glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float s, glm::vec3 P, glm::vec3 normal) {
	this->ka = ka;
	this->kd = kd;
	this->ks = ks;
	this->km = km;
	this->s = s;
	this->P = P;
	this->normal = normal;
}