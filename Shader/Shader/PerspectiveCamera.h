#pragma once
#ifndef _PERSPECTIVE_CAMERA_H_
#define _PERSPECTIVE_CAMERA_H_

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>


struct PerspectiveCamera
{
public:
	glm::mat4 matrix = glm::mat4(1.0f);
	glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f);
	glm::vec3 lookAt = glm::vec3(0.0f,0.0f,-1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view = glm::mat4(1.0f);
public:
	PerspectiveCamera() = default;
	PerspectiveCamera(float fov, float aspect, float near, float far);
	void setPosition(float x, float y, float z);
	void setPosition(glm::vec3 vec);
	void setUp(float x, float y, float z);
	void setUp(glm::vec3 vec);
	void setLookAt(float x, float y, float z);
	void setLookAt(glm::vec3 vec);
	void CalView();

};

#endif

