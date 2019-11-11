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

glm::vec3 ComputeRayColor(glm::vec3 rayDirection, glm::vec3 rayOrigin, float t0, float t1, Scene* scene) {
	Record* record = new Record();

	//std::cout << "Called ComputeRayColor" << std::endl;

	// I think this is done?
	// FIXME Never hitting anything
	if(scene->Hit(rayDirection, rayOrigin, t0, t1, record)) {

		//std::cout << "Hit something" << std::endl;

		//glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f);

		glm::vec3 color = record->ka;

		glm::vec3 E = glm::normalize(rayOrigin - record->P); // Eye - P

		for(int i = 0; i < scene->GetLights().size(); i++) {

			glm::vec3 L = glm::normalize(scene->GetLights()[i]->GetPosition() - record->P);
			glm::vec3 R = 2.0f * record->normal * (glm::dot(L, record->normal)) - L;

			//std::cout << glm::dot(L, R) << std::endl;

			color += scene->GetLights()[i]->GetColor()
				* ((record->kd * glm::max(0.0f, glm::dot(L, record->normal)))
				+ (record->ks * pow(glm::max(0.0f, glm::dot(R, E)), record->s)));
		}
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
			glm::vec3 colorAtPixel = ComputeRayColor(rayDirection, eye, 0, std::numeric_limits<float>::max(), scene);

			//std::cout << "Red term" << colorAtPixel.r << std::endl;
			
			// assign this returned color to renderedImage
			//std::cout << "colors: " << colorAtPixel[0] << " " << colorAtPixel[1] << " " << colorAtPixel[2] << std::endl;
			// ALWAYS RETURNING BLACK
			renderedImage[(j * widthRes + i) * 3 + 0] = colorAtPixel[0];
			renderedImage[(j * widthRes + i) * 3 + 1] = colorAtPixel[1];
			renderedImage[(j * widthRes + i) * 3 + 2] = colorAtPixel[2];
		}
	}
	std::cout << "Finished TakePicture" << std::endl;
}
