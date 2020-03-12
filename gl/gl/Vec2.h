#include"Vec.h"
#pragma once
#ifndef _VEC_VEC2_H_
#define _VEC_VEC2_H_

class Vec2 : public Vec {
private :
	float x, y;
public :
	Vec2() :x(0.f), y(0.f) {};
	Vec2(float x = 0.f, float y = 0.f) :x(x), y(y) {};
	float length();
	int dimension();
	float dot(Vec2*);
};

#endif
