//---------------------------
//------ Luke Monaghan ------
//---------------------------
#ifndef OBJECT_H_
#define OBJECT_H_
//---------------------------
#include "MATH/Matrix4.h"
//---------------------------
class cObject {
public:
	cObject();
	void Translate(float x, float y, float depth) ;
	void Rotate(float angle);
	void Scale(float xscale, float yscale);
	void ResizeOBJ(int width, int height,int defaultwidth, int defaultheight);
protected:
	Matrix4 M4Matrix,M4Scale,M4Rotate,M4Translate;
};

#endif