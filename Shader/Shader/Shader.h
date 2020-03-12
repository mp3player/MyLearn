#ifndef _SHADER_H_
#define _SHADER_H_

#include<iostream>
#include<fstream>
#include<string>
#include<glad/glad.h>
using namespace std;

class Shader {
private:
	string vertCode;
	string fragCode;
	GLuint program;
	GLuint vShader;
	GLuint fShader;
	bool init;
public:
	Shader(char* const vert, char* const frag) {
		fstream f1 = fstream(vert, ios::in);
		fstream f2 = fstream(frag, ios::in);
		if (f1.is_open() && f1.is_open()) {
			char c[1024];
			while (f1.getline(c, sizeof(c))) {
				vertCode.append(c);
				vertCode.append("\n");
			}

			while (f2.getline(c, sizeof(c))) {
				fragCode.append(c);
				fragCode.append("\n");
			}
			init = initProgram();

			std::cout << init << std::endl;

		}
		else {
			std::cout << "error , file read failed" << std::endl;
		}
	}
	string getVertCode() {
		return vertCode;
	}
	string getFragCode() {
		return fragCode;
	}
	//����shader
	GLuint initShader(GLint type, const char* source) {
		//����
		GLuint shader = glCreateShader(type);
		//��������
		glShaderSource(shader, 1, &source, NULL);
		//����shader
		glCompileShader(shader);
		//�ж��Ƿ�ɹ�
		char info[512];
		int success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (!success) {
			glGetShaderInfoLog(shader, sizeof(info), NULL, info);
			std::cout << info << std::endl;
			return NULL;
		}
		return shader;
	}
	//����program
	bool initProgram() {
		program = glCreateProgram();

		GLuint vShader = initShader(GL_VERTEX_SHADER, vertCode.data());
		GLuint fShader = initShader(GL_FRAGMENT_SHADER, fragCode.data());

		glAttachShader(program, vShader);
		glAttachShader(program, fShader);

		int success;
		char info[512];

		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(program, sizeof(info), NULL, info);
			std::cout << info << std::endl;
			return false;
		}
		return true;
	}

};

#endif