#include "Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

Camera::Camera(int widthRes, int heightRes, float fovy, float focalDistance, glm::vec3 eye, glm::vec3 lookAt, glm::vec3 up)
{
	this->widthRes = widthRes;
	this->heightRes = heightRes;
	this->fovy = fovy;
	this->focalDistance = focalDistance;
	this->eye = eye;
	this->lookAt = lookAt;
	this->up = up;
	renderedImage = new float[widthRes * heightRes * 3];
}

glm::vec3 Camera::ComputeRayColor(Scene* scene, glm::vec3 origin, glm::vec3 ray, float t0, float t1, int depth)
{
	// Store scene lights in local vector
	std::vector<Light*> lights = scene->getLights();

	// Initialize ray vectors for coloring/shading
	glm::vec4 shadowRay;
	glm::vec4 reflectRay;
	glm::vec4 eyeRay;

	// Initialize vectors for storing colors
	glm::vec3 color(0.0f);
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 reflect;

	// Check if the ray intersects with any object in the scene
	rec hitRec = scene->Hit(origin, ray, t0, t1); // Returns data about the closest object
	if (hitRec.shape != NULL)
	{
		color = hitRec.shape->ka; // Set color to ambient color of the object

		// For each light in the scene
		for (int k = 0; k < lights.size(); k++)
		{
			shadowRay = glm::normalize(glm::vec4(lights[k]->getPositon(), 1) - glm::vec4(hitRec.intersect, 1)); // Generate the shadow ray
			eyeRay = glm::normalize(glm::vec4(origin, 1) - glm::vec4(hitRec.intersect, 1)); // Generate the vector from origin to intersect point
			reflectRay = 2.0f * glm::dot(shadowRay, glm::vec4(hitRec.hitNormal, 0)) * glm::vec4(hitRec.hitNormal, 0) - shadowRay; // Generate the reflection vector relative to the light

			float tlight = glm::dot(glm::vec4(lights[k]->getPositon(), 1) - glm::vec4(hitRec.intersect, 1), shadowRay) / glm::dot(shadowRay, shadowRay); // Calculate the light's t parameter
			rec shadowRec = scene->Hit(hitRec.intersect, shadowRay, 0.001f, tlight); // Check if the shadow ray intersects with objects in scene
			if (shadowRec.shape == NULL) // If the shadow ray does not hit an object
			{
				// Calculate the diffuse and specular light colors
				diffuse = hitRec.shape->kd * glm::max(0.0f, dot(shadowRay, glm::vec4(hitRec.hitNormal, 0)));
				specular = hitRec.shape->ks * pow(glm::max(0.0f, glm::dot(reflectRay, eyeRay)), hitRec.shape->s);
				color += (lights[k]->getColor() * (diffuse + specular));	
			}
		}
		if (depth >= 5)
			return color;
		else
		{
			// Recursively calculate the reflection colors
			glm::vec4 V = glm::normalize(glm::vec4(origin, 1) - glm::vec4(hitRec.intersect, 1)); // Generate vector from origin to the intersect
			glm::vec3 R = 2.0f * glm::dot(V, glm::vec4(hitRec.hitNormal, 0)) * glm::vec4(hitRec.hitNormal, 0) - V; // Generate the reflected vector relative to the viewing angle
			return color + hitRec.shape->km * ComputeRayColor(scene, hitRec.intersect, R, 0.001f, INFINITY, ++depth);
		}
	}
	return color;
}

void Camera::TakePicture(Scene* scene)
{
	// Define coordinate system of the camera
	glm::vec3 a = eye - lookAt;
	glm::vec3 b = up;
	glm::vec3 w = glm::normalize(a);
	glm::vec3 u = glm::normalize(glm::cross(b, w));
	glm::vec3 v = glm::cross(w, u);

	// Calculating pixel location in camera space
	float ly = 2.0 * focalDistance * tan(fovy / 2);
	float lx = ly * widthRes / heightRes;

	float pixelWidth = ly / heightRes;

	glm::vec3 Ic = eye + focalDistance * (-w);
	glm::vec3 screenOrigin = Ic - lx / 2 * u - ly / 2 * v;

	glm::vec3 Pc;
	glm::vec3 primaryRay;


	// For each pixel
	for (int i = 0; i < heightRes; i++)
	{
		for (int j = 0; j < widthRes; j++)
		{
			Pc = screenOrigin + float((j + 0.5) * pixelWidth) * u + float((i + 0.5) * pixelWidth) * v; // Calculate center of the pixel
			primaryRay = glm::normalize(Pc - eye); // Calculate the primary ray direction

			// Fill the framebuffer with appropriate color values
			glm::vec3 color = ComputeRayColor(scene, eye, primaryRay, .001f, INFINITY, 0);
			renderedImage[widthRes * i * 3 + 3 * j + 0] = color.x;
			renderedImage[widthRes * i * 3 + 3 * j + 1] = color.y;
			renderedImage[widthRes * i * 3 + 3 * j + 2] = color.z;
		}
	}

	//memset(renderedImage, 0, sizeof(float) * widthRes * heightRes * 3);
}
