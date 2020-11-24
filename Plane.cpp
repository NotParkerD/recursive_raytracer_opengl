#include "Plane.h"


Plane::Plane()
{
}

Plane::~Plane()
{
}

Plane::Plane(glm::vec3 position, glm::vec3 normal, glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float s)
{
	this->position = position;
	this->normal = normal;
	this->position = position;
	this->ka = ka;
	this->kd = kd;
	this->ks = ks;
	this->km = km;
	this->s = s;
}

float Plane::Intersect(glm::vec3 origin, glm::vec3 direction, float t0, float t1)
{
	// Check if ray intersects with plane - return parameter of intersection
	float t = dot(position - origin, normal) / dot(direction, normal);
	if (t > t0 && t < t1)
		return t;
	else
		return t1; // If no intersect, return upper bound
}

glm::vec3 Plane::GetNormal(glm::vec3 origin, glm::vec3 direction, float t)
{
	return normal;
}