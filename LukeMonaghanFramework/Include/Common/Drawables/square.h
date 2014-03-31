//---------------------------
//------ Luke Monaghan ------
//---------------------------
#ifndef SQUARE_H_
#define SQUARE_H_
//---------------------------
#include "MATH/Vector2.h"
#include "MATH/Vector3.h"
#include "MATH/Vector4.h"
//---------------------------
#include "renderable.h" 
//---------------------------
struct sSquareInformation{
	Vector3 Size;
	Vector2 UV;
	Vector4 Colour;
};
//---------------------------
class cSquare : public cRenderable {
public:
	cSquare();
	cSquare(const char* path, int width, int height, int xoffset, int yoffset);
	void UpdateVerts();
protected:
	sSquareInformation Verticies[4];
};

#endif