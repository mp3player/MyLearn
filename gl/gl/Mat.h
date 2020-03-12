#pragma once
#ifndef _MAT_MAT_H_
#define _MAT_MAT_H_

class Mat {
public :
	virtual float det() = 0;
	virtual float* transpose() = 0;
	virtual float* invert() = 0;
	virtual float* getData() = 0;
};


#endif // !_MAT_MAT_H_
