#include "ShaderUtil.h"
#ifndef SHADER_H
#define SHADER_H

#include<glad/glad.h>

#include<iostream>
#include<fstream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>


ShaderUtil::ShaderUtil(const char* vs, const char* fs)
{
	ifstream vFile = ifstream(vs, ios::in);
	ifstream fFile = ifstream(fs, ios::in);
	if (vFile.is_open() && fFile.is_open()) {
		char tmp[1024];
		while (vFile.getline(tmp, sizeof(tmp))) {
			ShaderUtil::vscode.append(tmp);
			ShaderUtil::vscode.append("\n");
		}
		while (fFile.getline(tmp, sizeof(tmp))) {
			ShaderUtil::fscode.append(tmp);
			ShaderUtil::fscode.append("\n");
		}
		ShaderUtil::init();
	}
	else {
		cout << " error ： read file failed " << std::endl;
	}
}

GLuint ShaderUtil::initShader(GLuint type, const char* const code)
{
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &code, NULL);
	glCompileShader(shader);

	int success;
	char info[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, sizeof(info), NULL, info);
		std::cout << " generate shader failed : " << info << std::endl;
	}
	std::cout << " generate shader success !!!" << std::endl;
	return shader;
}

void ShaderUtil::init()
{
	ShaderUtil::initProgram();
}

void ShaderUtil::initProgram()
{
	ShaderUtil::program = glCreateProgram();
	ShaderUtil::vShader = initShader(GL_VERTEX_SHADER, ShaderUtil::vscode.data());
	ShaderUtil::fShader = initShader(GL_FRAGMENT_SHADER, ShaderUtil::fscode.data());

	glAttachShader(program, ShaderUtil::vShader);
	glAttachShader(program, ShaderUtil::fShader);

	glLinkProgram(program);

	char info[512];
	int success;
	glGetProgramiv(program,GL_LINK_STATUS,&success);
	if (!success) {
		glGetProgramInfoLog(program, sizeof(info), NULL, info);
		std::cout << " generate progrom failed : " << info << std::endl;
	}
	std::cout << " generate program success " << std::endl;
	glDeleteShader(ShaderUtil::vShader);
	glDeleteShader(ShaderUtil::fShader);
}

string ShaderUtil::getVscode()
{
	return ShaderUtil::vscode;
}

string ShaderUtil::getFscode()
{
	return ShaderUtil::fscode;
}

GLuint ShaderUtil::getvShader()
{
	return ShaderUtil::vShader;
}

GLuint ShaderUtil::getfShader()
{
	return ShaderUtil::fShader;
}

GLuint ShaderUtil::getProgram()
{
	return ShaderUtil::program;
}

GLuint ShaderUtil::createVAO()
{
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	return vao;
}

GLuint ShaderUtil::createVBO(float * data,int count)
{
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glBufferData(GL_ARRAY_BUFFER, count, data, GL_STATIC_DRAW);
	return vbo;
}

GLuint ShaderUtil::createEBO(int * data,int count)
{
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, data, GL_STATIC_DRAW);
	return GLuint();
}

GLuint ShaderUtil::createFBO()
{
	return GLuint();
}

GLuint ShaderUtil::createTexture(const char* path)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// 加载并生成纹理
	int width, height, nrChannels;
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	//解绑texture
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}

void ShaderUtil::setVec3(int location, float* vec3,int count)
{
	ShaderUtil::createVBO(vec3,count);
	glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(location);
}

void ShaderUtil::setVec2(int location, float* vec2,int count)
{
	ShaderUtil::createVBO(vec2,count);
	glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
	glEnableVertexAttribArray(location);
}

void ShaderUtil::setMat4(const char* name, float* mat4)
{
	GLuint p = glGetUniformLocation(ShaderUtil::program, name);
	glUniformMatrix4fv(p, 1, GL_FALSE, mat4);
}

void ShaderUtil::setMat3(const char* name, float* mat3)
{
	GLuint p = glGetUniformLocation(ShaderUtil::program, name);
	glUniformMatrix3fv(p, 1, GL_FALSE, mat3);
}

void ShaderUtil::setInt(const char* name, int val)
{
	GLuint p = glGetUniformLocation(ShaderUtil::program, name);
	glUniform1i(p, val);
}

void ShaderUtil::setFloat(const char* name, float val)
{
	GLuint p = glGetUniformLocation(ShaderUtil::program, name);
	glUniform1f(p, val);
}

void ShaderUtil::setVec3U(const char* name, float* vec3)
{
	GLuint p = glGetUniformLocation(ShaderUtil::program, name);
	glUniform3fv(p, 1, vec3);
}

void ShaderUtil::setVec2U(const char* name, float* vec2)
{
	GLuint p = glGetUniformLocation(ShaderUtil::program, name);
	glUniform2fv(p, 1, vec2);
}

#endif