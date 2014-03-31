//---------------------------
//------ Luke Monaghan ------
//---------------------------
#ifndef RENDERABLE_H_
#define RENDERABLE_H_
//---------------------------
#include "object.h"
#include "Common/Framework.h"
//---------------------------
class cRenderable : public cObject {
public:
	cRenderable();
	unsigned int TextureLoad(const char* path);
	void Create(const char* path,unsigned int width, unsigned int height, int xoff, int yoff);
	void SetColour(float f_Red, float f_Green, float f_Blue, float f_Alpha);
	void SetUV(float uMin,float vMin,float uMax,float vMax);
	unsigned int GetID();
	void Draw(int uLocation,cFramework *FW,bool Camera0_world1);
	void Resize(int width, int height);
	int  GetWidthHeight(bool width0_height1);
	void Delete();
protected:
	unsigned int uiSpriteID;
	unsigned int uiWidth,uiHeight;
	unsigned int uiWidthCONST,uiHeightCONST;
	float xOff,yOff;
	float UVMinMax[4];
	float fColour[4];
};

#endif