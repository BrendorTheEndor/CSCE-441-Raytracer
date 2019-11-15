#pragma once
#include <vector>
#include <limits>
#include <iostream>
#include "Shape.h"
#include "Light.h"
#include "Sphere.h"
#include "Plane.h"

class Scene {
public:
	Scene();
	~Scene();
	Scene(std::vector<Shape*> shapes, std::vector<Light*> lights);

	// Checks if a ray hits any objects in the scene
	bool Hit(glm::vec3 rayDirection, glm::vec3 rayOrigin, float t0, float t1, Record* record);

	std::vector<Light*> GetLights() { return lights; }

private:
	std::vector<Shape*> shapes;
	std::vector<Light*> lights;

};
