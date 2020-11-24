#pragma once
#include "Shape.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Plane : public Shape
{
public:

	Plane();
	~Plane();
	Plane(glm::vec3 position, glm::vec3 normal, glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float s);
	float Intersect(glm::vec3 origin, glm::vec3 direction, float t0, float t1) override;
	glm::vec3 GetNormal(glm::vec3 origin, glm::vec3 direction, float t) override;

private:

	glm::vec3 position;
	glm::vec3 normal;

};
