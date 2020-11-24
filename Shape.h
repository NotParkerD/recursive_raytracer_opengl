#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shape
{
public:

	Shape(void);
	~Shape(void);
	Shape(glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float s);

	virtual float Intersect(glm::vec3 origin, glm::vec3 direction, float t0, float t1) = 0;
	virtual glm::vec3 GetNormal(glm::vec3 origin, glm::vec3 direction, float t) = 0;

	glm::vec3 ka;
	glm::vec3 kd;
	glm::vec3 ks;
	glm::vec3 km;
	float s;
};
