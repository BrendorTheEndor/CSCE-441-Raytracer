#include "Camera.h"

Camera::Camera() {
}

Camera::~Camera() {
	//delete renderedImage;
}

Camera::Camera(int widthRes, int heightRes, glm::vec3 eye, glm::vec3 lookAt, glm::vec3 up, float fovY, float focalDistance) {
	this->widthRes = widthRes;
	this->heightRes = heightRes;
	this->eye = eye;
	this->lookAt = lookAt;
	this->up = up;
	this->fovY = fovY;
	this->focalDistance = focalDistance;
	renderedImage = new float[widthRes * heightRes * 3];
}

glm::vec3 ComputeRayColor(glm::vec3 rayDirection, glm::vec3 rayOrigin, float t0, float t1, Scene* scene, int counter) {

	if(counter >= RECURSION_MAX) { return glm::vec3(0.0f, 0.0f, 0.0f); }

	Record* record = new Record();

	// If we hit something
	if(scene->Hit(rayDirection, rayOrigin, t0, t1, record)) {

		glm::vec3 P = record->P;
		glm::vec3 normal = record->normal;

		// Ambient term of color
		glm::vec3 color = record->ka;

		glm::vec3 E = glm::normalize(rayOrigin - P); // Eye - P

		std::vector<Light*> lights = scene->GetLights();

		// Compute color based on lights (specular and diffuse)
		for(int i = 0; i < lights.size(); i++) {
			float tLight = sqrt(glm::dot(lights[i]->GetPosition()
				- P, lights[i]->GetPosition() - P))
				/ sqrt(glm::dot(rayDirection, rayDirection));

			glm::vec3 shadowRay = glm::normalize(lights[i]->GetPosition() - P);
			Record dummyRecord;

			// Test if object in shadow or not
			if(!scene->Hit(shadowRay, P, epsilon, tLight, &dummyRecord)) {

				glm::vec3 L = glm::normalize(lights[i]->GetPosition() - P);
				glm::vec3 R = 2.0f * normal * (glm::dot(L, normal)) - L;

				color += lights[i]->GetColor()
					* ((record->kd * glm::max(0.0f, glm::dot(L, normal)))
						+ (record->ks * pow(glm::max(0.0f, glm::dot(R, E)), record->s)));
			}
		}

		// recursive call for reflection
		if(record->km == glm::vec3(0.0f, 0.0f, 0.0f)) { 
			delete record;
			return color; 
		}

		glm::vec3 reflectiveDirection = (-2 * glm::dot(normal, rayDirection) * normal) + rayDirection;
		color = color + (record->km * ComputeRayColor(reflectiveDirection, P, epsilon, t1, scene, counter + 1));

		delete record;
		return color;
	}
	else {
		// return background color
		delete record;
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}
}

void Camera::TakePicture(Scene* scene) {

	memset(renderedImage, 0, sizeof(float) * widthRes * heightRes * 3);

	std::cout << "Called TakePicture" << std::endl;

	glm::vec3 viewDirection = glm::normalize(lookAt - eye);
	glm::vec3 Ic = eye + viewDirection * focalDistance;
	float ly = 2 * focalDistance * tan(fovY / 2.0f);
	float lx = (ly * widthRes) / heightRes;
	glm::vec3 w = glm::normalize(eye - lookAt);
	glm::vec3 u = glm::normalize(glm::cross(up, w));
	glm::vec3 v = glm::cross(w, u);
	glm::vec3 O = Ic - ((lx / 2.0f) * u) - ((ly / 2.0f) * v);
	float Pw = ly / heightRes;

	for(int i = 0; i < widthRes; i++) {
		for(int j = 0; j < heightRes; j++) {
			glm::vec3 Pc = O + ((i + .5f) * Pw * u) + ((j + .5f) * Pw * v); // Is this order right?
			glm::vec3 rayDirection = glm::normalize(Pc - eye);
			glm::vec3 colorAtPixel = ComputeRayColor(rayDirection, eye, 0, std::numeric_limits<float>::max(), scene, 0);

			// assign this returned color to renderedImage
			renderedImage[(j * widthRes + i) * 3 + 0] = colorAtPixel[0];
			renderedImage[(j * widthRes + i) * 3 + 1] = colorAtPixel[1];
			renderedImage[(j * widthRes + i) * 3 + 2] = colorAtPixel[2];
		}
	}
	std::cout << "Finished TakePicture" << std::endl;
}
