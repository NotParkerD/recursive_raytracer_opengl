#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Light
{
public:

	Light();
	~Light();

	Light(glm::vec3 position, glm::vec3 color);
	glm::vec3 getPositon() { return position; };
	glm::vec3 getColor () { return color; };


private:
	glm::vec3 position;
	glm::vec3 color;
};
