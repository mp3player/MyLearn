#pragma once

#ifndef _SHADER_UTIL_H_
#define _SHADER_UTIL_H_

#include <iostream>
#include<fstream>

#include<glad/glad.h>

using namespace std;


class ShaderUtil
{
private :
	string vscode;
	string fscode;
	GLuint program;
	GLuint vShader;
	GLuint fShader;
	float* rgba = new float[4];
public:
	ShaderUtil() = default;
	ShaderUtil(const char*, const char*);
	GLuint initShader(GLuint, const char* const);
	void init();
	void initProgram();
	string getVscode();
	string getFscode();
	GLuint getvShader();
	GLuint getfShader();
	GLuint getProgram();
	GLuint createVAO();
	GLuint createVBO(float *data,int count);
	GLuint createEBO(int * data,int count);
	GLuint createFBO();
	GLuint createTexture(const char* path);
	void setVec3(int location,float * vec3,int count);
	void setVec2(int location,float * vec2,int count);
	void setMat4(const char* name, float* mat4);
	void setMat3(const char* name, float* mat3);
	void setInt(const char* name, int val);
	void setFloat(const char* name, float val);
	void setVec3U(const char* name, float* vec3);
	void setVec2U(const char* name, float* vec2);
	void clear(float r, float g, float b, float a) {
		rgba[0] = r,rgba[1] = g,rgba[2] = b,rgba[3] = a;
	}
	void drawArrays(int mode, int count) {
		glDrawArrays(mode, 0, count);
	}
	void drawElements(int mode, int count) {
		glDrawElements(mode, count, GL_UNSIGNED_SHORT, 0);
	}

};

#endif