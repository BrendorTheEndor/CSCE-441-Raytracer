#include "Scene.h"

Scene::~Scene() {
}

Scene::Scene() {

}

Scene::Scene(std::vector<Shape*> shapes, std::vector<Light*> lights) {
	this->shapes = shapes;
	this->lights = lights;
}

bool Scene::Hit(glm::vec3 rayDirection, float t0, float t1, Record* record) {

	float minT = std::numeric_limits<float>::max(); // Initialize at float max
	Shape* shapeWithMinT;

	for(int i = 0; i < shapes.size(); i++) {
		float t = shapes[i]->Intersect(rayDirection, t0, t1);
		if(t < minT) {
			minT = t;
			shapeWithMinT = shapes[i];
		}
	}

	
}
