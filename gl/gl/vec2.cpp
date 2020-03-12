#include"Vec2.h"
#include<cmath>

float Vec2::length() {
	return powf(
		powf(this->x, 2) + powf(this->y, 2),
		.5f
	);
};

int Vec2::dimension() {
	return 2;
};

float Vec2::dot(Vec2 * v) {
	return this->x * v->x + this->y * v->y;
}

