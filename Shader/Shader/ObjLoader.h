#pragma once
#ifndef _OBJ_LOADER_H_
#define _OBJ_LOADER_H_

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

class ObjLoader
{
public:
	float* position;
	float* color;
	float* uv;
	float* index;
public :
	ObjLoader(const char* path);
};

#endif