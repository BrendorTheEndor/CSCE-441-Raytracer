#pragma once
#include <glm/glm.hpp>

class Light
{
public:
	Light();
	~Light();
	Light(glm::vec3 position, glm::vec3 color);

private:
	glm::vec3 position;
	glm::vec3 color;
};
