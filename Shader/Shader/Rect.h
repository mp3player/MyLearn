#pragma once
#ifndef _RECT_H_
#define _RECT_H_

namespace Rect {
	float position[] = {
		-.5f,-.5f,.0f,
		.5f,-.5f,.0f,
		.5f,.5f,.0f,
		-.5f,.5f,.0f
	};
	float color[] = {
		1.f,.0f,.0f,
		0.f,0.f,1.f,
		0.f,1.f,0.f,
		1.f,0.f,1.f
	};
	float uv[] = {
		0.0f,0.0f,
		1.f,0.f,
		1.f,1.f,
		0.f,1.f
	};
	int index[] = {
		0,1,2,
		0,2,3
	};
	int length = 6;
}


#endif
