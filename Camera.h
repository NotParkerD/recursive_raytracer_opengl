#pragma once
#include <vector>
#include "Scene.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>





class Camera
{
public:

	Camera();
	~Camera();

	Camera(int widthRes, int heightRes, float fovy, float focalDistance, glm::vec3 eye, glm::vec3 lookAt, glm::vec3 up);

	glm::vec3 ComputeRayColor(Scene *scene, glm::vec3 origin, glm::vec3 ray, float t0, float t1, int depth);

	void TakePicture(Scene *scene);
	float* GetRenderedImage() { return renderedImage; };

private:

	int widthRes;
	int heightRes;
	float fovy;
	float focalDistance;
	glm::vec3 eye;
	glm::vec3 lookAt;
	glm::vec3 up;
	
	float *renderedImage;
};
