#include "Scene.h"

Scene::~Scene()
{
}

Scene::Scene()
{
	// Generate shapes and populate the scene
	Light* light01 = new Light(glm::vec3(0.0f, 3.0f, -2.0f), glm::vec3(0.2f, 0.2f, 0.2f));
	lights.push_back(light01);

	Light* light02 = new Light(glm::vec3(-2.0f, 1.0f, 4.0f), glm::vec3(0.5f, 0.5f, 0.5f));
	lights.push_back(light02);

	Sphere* sphere01 = new Sphere(glm::vec3(-1.0, -0.7, 3.0), 0.3, glm::vec3(0.1, 0.1, 0.1), glm::vec3(0.2, 1.0, 0.2), glm::vec3(1.0, 1.0, 1.0), glm::vec3(0.0, 0.0, 0.0), 100);
	shapes.push_back(sphere01);

	Sphere* sphere02 = new Sphere(glm::vec3(1.0f, -0.5f, 3.0f), 0.5, glm::vec3(0.1, 0.1, 0.1), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0, 1.0, 1.0), glm::vec3(0.0, 0.0, 0.0), 10);
	shapes.push_back(sphere02);

	Sphere* sphere03 = new Sphere(glm::vec3(-1.0f, 0.0f, 0.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.0f);
	shapes.push_back(sphere03);

	Sphere* sphere04 = new Sphere(glm::vec3(1.0f, 0.0f, -1.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.8f, 0.8f, 0.8f), 0.0f);
	shapes.push_back(sphere04);

	Plane* plane01 = new Plane(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0);
	shapes.push_back(plane01);

	Plane* plane02 = new Plane(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f);
	shapes.push_back(plane02);
}

rec Scene::Hit(glm::vec3 origin, glm::vec3 ray, float t0, float t1)
{
	rec returnVals;

	float t;
	float mint = t1;
	int closestShapeIndex = -1;

	// For each shape in the scene
	for (int i = 0; i < shapes.size(); i++)
	{
		t = shapes[i]->Intersect(origin, ray, t0, t1); // Check if ray intersects object using virtual intersect function
		// If the intersect is closer than previous intersects, set new intersect as closest
		if (t < mint && t > t0)
		{
			mint = t;
			closestShapeIndex = i; // Save the index of the closest object
		}
	}
	if (closestShapeIndex >= 0) // If any object intersects with the ray
	{
		// Populate return struct with closest shape's data
		returnVals.shape = shapes[closestShapeIndex]; // Pointer to shape
		returnVals.hitNormal = shapes[closestShapeIndex]->GetNormal(origin, ray, mint); // Shape's normal at intersection
		returnVals.intersect = origin + mint * ray; // Intersection parameter
	}
	

	return returnVals;
}
