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

glm::vec3 ComputeRayColor(glm::vec3 rayDirection, float t0, float t1, Scene* scene) {
	return glm::vec3(0.0f, 0.0f, 0.0f);

	Record record;

	if(scene->Hit(rayDirection, t0, t1, &record)) {
		// TODO
		// How do I get these terms I don't have?
		//glm::vec3 color = record.ka * A;
		//for(int i = 0; i < scene->GetLights().size(); i++) {
		//	color += scene->GetLights()[i]->GetColor() * ((record.kd * glm::max(0, glm::dot(Li, N)))
		//		+ (record.ks * pow(glm::max(0, glm::dot(Ri, E)), n)));
		//}
		//return color;
	}
	else {
		// return background color
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}
}

void Camera::TakePicture(Scene* scene) {

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
			glm::vec3 colorAtPixel = ComputeRayColor(rayDirection, 0, std::numeric_limits<float>::max(), scene);
			// TODO assign this returned color to renderedImage
		}
	}

	memset(renderedImage, 0, sizeof(float) * widthRes * heightRes * 3);
}
