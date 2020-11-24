#include "Sphere.h"

Sphere::Sphere()
{
}

Sphere::~Sphere()
{
}

Sphere::Sphere(glm::vec3 position, float radius, glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float s)
{
	this->position = position;
	this->radius = radius;
	this->ka = ka;
	this->kd = kd;
	this->ks = ks;
	this->km = km;
	this->s = s;
}

float Sphere::Intersect(glm::vec3 origin, glm::vec3 direction, float t0, float t1)
{
	// Check if ray intersects with sphere
	float a, b, c, t;
	a = glm::dot(direction, direction);
	b = glm::dot(2.0f * (origin - position), direction);
	c = glm::dot(origin - position, origin - position) - pow(radius, 2);

	float sol = pow(b, 2) - 4.0f * a * c;

	// If number of solutions greater than 0, return lower t
	if (sol >= 0)
		t = (-b - sqrt(sol)) / (2 * a);
	else
		t = t1; // Otherwise, return upper bound t1

	return t;
}

glm::vec3 Sphere::GetNormal(glm::vec3 origin, glm::vec3 direction, float t)
{
	return glm::normalize(origin + t * direction - position);
}
