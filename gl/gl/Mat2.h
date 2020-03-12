#include "Mat.h"
#pragma once
#ifndef _MAT_MAT2_H_
#define _MAT_MAT2_H_

class Mat2 : public Mat {
private :
	float data[4] = {1.f,0.f,0.f,1.f};
	int dimension = 2;
public :
	Mat2() = default;
	Mat2(float data[4]) {
		for (int i = 0; i < 4; i++) {
			this->data[i] = data[i];
		}
	}
	float det() {
		return data[0] * data[3] - data[1] * data[2];
	}
	//矩阵转置
	float * transpose() {
		float tmp[] = {
			data[0],data[2],
			data[1],data[3]
		};
		return tmp;
	}
	//矩阵求逆
	float* invert() {
		float det = this->det();
		float d[] = {
			1 / det * data[3],1 / det * data[2],
			1 / det * data[1],1 / det * data[0]
		};
		return d;
	}
	//获取矩阵数据
	float* getData() {
		return this->data;
	}
	static Mat2 createMat2() {
		return Mat2();
	}

};

#endif