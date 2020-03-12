#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include<glm/mat4x4.hpp>
#include <iostream>
#include<math.h>
#include"Mat2.h"

using namespace glm;

#define PI 3.1415926

const char* vertexShaderSource = 
"#version 330 core\n"
"#pragma STDGL invariant(all) \n"
"layout(location = 0)in vec2 position;\n"
"layout(location = 1)in vec3 color;"
"out vec4 fColor;"
"uniform float angle;"
"uniform float scale;"
"uniform float depth;"
"mat4 rotateMatrix = mat4(cos(angle),-sin(angle),0,0,sin(angle),cos(angle),0,0,0,0,1,0,0,0,0,1);"
"mat4 scaleMatrix = mat4(scale,0,0,0,0,scale,0,0,0,0,0,scale,0,0,0,1);"

//测试用代码
"uniform mat {"
"mat4 projectionMatrix;"
"mat4 modelViewMatrix;"
"} matrix;"

"uniform mat1 {"
"mat4 projectionMatrix;"
"mat4 modelViewMatrix;"
"} matrix1;"

"void main(){\n"
"vec4 pos = vec4(position,0,1);"
"pos.z *= depth;"
"gl_Position = scaleMatrix * rotateMatrix * pos;\n"
"fColor = vec4(color,1);"
"}";

const char* fragmentShaderSource = 
"#version 330 core\n"
"#pragma STDGL invariant(all)\n"
"in vec4 fColor;\n"
"void main(){\n"
	"gl_FragColor = fColor;\n"
"}";

float radius = 0;
float scale = 1;
float depth = 0;

void keyEvent(GLFWwindow* window, int a, int b, int c, int d) {
	std::cout << a << "--" << b << "--" << c << "--" << d << std::endl;
	if (a == 87) {
		//bigger
		//scale += .1;
		depth += .1f;
	};
	if (a == 83) {
		//smaller
		//scale -= .1;
		depth -= .1f;
	};
}

GLuint getProgram() {
	GLint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int info;
	char c[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &info);
	if (!info) {
		glGetShaderInfoLog(vertexShader, 512, NULL, c);
		std::cout << c << std::endl;
	}

	GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &info);
	if (!info) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, c);
		std::cout << c << std::endl;
	}

	GLint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &info);
	if (!info) {
		glGetProgramInfoLog(program, 512, NULL, c);
		std::cout << c << std::endl;
		return -1;
	}

	return program;
};

GLuint getVAO() {
	float vertices[] = {
		-.5f,.5f,			1.f,0.f,0.f,	
		.5f,.5f,			0.f,1.f,0.f,
		.5f,-.5f,			0.f,0.f,1.f,
		-.5f,-.5f,			1.f,0.f,1.f
	};
	GLuint VAO;
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint VBO[2];
	glGenBuffers(2, VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	std::cout << VAO << std::endl;;
	return VAO;
};

int main() {
	
	mat4 m = mat4();

	if (!glfwInit()) {
		std::cout << " error " << std::endl;
		return -1;
	}

	const int width = 640, height = 640;

	GLFWwindow* window = glfwCreateWindow(width, height, "hello", NULL, NULL);
	if (!window) {
		std::cout << " create window failed " << std::endl;
		glfwTerminate();
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwMakeContextCurrent(window);

	

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	GLuint program = getProgram();
	GLuint VAO = getVAO();
	
	GLint info;
	GLuint index = glGetUniformBlockIndex(program, "matrix1");
	glGetActiveUniformBlockiv(program, index, GL_UNIFORM_BLOCK_DATA_SIZE, &info);
	std::cout << info << std::endl;
	//获取矩阵的地址
	GLuint angle = glGetUniformLocation(program, "angle");
	GLuint s = glGetUniformLocation(program, "scale");
	GLuint d = glGetUniformLocation(program, "depth");

	glfwSwapInterval(1);

	glViewport(0, 0, width, height);
	glfwSetKeyCallback(window, keyEvent);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_DEPTH_BUFFER_BIT);
		glUseProgram(program);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glUniform1f(angle, radius);
		glUniform1f(s, scale);
		glUniform1f(d, depth);
		radius += (float)PI / 180;
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return -1;
}