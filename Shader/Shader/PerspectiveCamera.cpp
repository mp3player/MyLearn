#include "PerspectiveCamera.h"
using Camera = PerspectiveCamera;
PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float near, float far)
{
	Camera::matrix = glm::perspective<float>(fov, aspect, near, far);
	Camera::view = glm::lookAt<float>(Camera::position, Camera::lookAt, Camera::up);
}

void PerspectiveCamera::setPosition(float x, float y, float z)
{
	Camera::position = glm::vec3(x, y, z);
	Camera::CalView();
}

void PerspectiveCamera::setPosition(glm::vec3 vec)
{
	Camera::position = vec;
}

void PerspectiveCamera::setUp(float x, float y, float z)
{
	Camera::up = glm::vec3(x, y, z);
	Camera::CalView();
}

void PerspectiveCamera::setUp(glm::vec3 vec)
{
	Camera::up = vec;
}

void PerspectiveCamera::setLookAt(float x, float y, float z)
{
	Camera::lookAt = glm::vec3(x, y, z);
	Camera::CalView();
}

void PerspectiveCamera::setLookAt(glm::vec3 vec)
{
	Camera::lookAt = vec;
}

void PerspectiveCamera::CalView()
{
	Camera::view = glm::lookAt(Camera::position, Camera::lookAt, Camera::up);
}

