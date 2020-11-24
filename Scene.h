#pragma once
#include <vector>
#include "Shape.h"
#include "Light.h"
#include "Plane.h"
#include "Sphere.h"

struct rec
{
	Shape* shape = NULL;
	glm::vec3 hitNormal;
	glm::vec3 intersect;
};

class Scene
{
public:
	Scene();
	~Scene();
	rec Hit(glm::vec3 origin, glm::vec3 ray, float t0, float t1);
	std::vector<Light*> getLights() { return lights; };

private:

	std::vector<Shape*> shapes;
	std::vector<Light*> lights;
};
