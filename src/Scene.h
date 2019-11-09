#pragma once
#include <vector>
#include <limits>
#include "Shape.h"
#include "Light.h"
#include "Sphere.h"
#include "Plane.h"

class Scene {
public:
	Scene();
	~Scene();
	Scene(std::vector<Shape*> shapes, std::vector<Light*> lights);
	bool Hit(glm::vec3 rayDirection, float t0, float t1, Record* record);

	std::vector<Light*> GetLights() { return lights; }

private:
	std::vector<Shape*> shapes;
	std::vector<Light*> lights;

};
