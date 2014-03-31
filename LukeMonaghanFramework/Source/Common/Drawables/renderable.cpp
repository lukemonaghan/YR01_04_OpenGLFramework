//---------------------------
//------ Luke Monaghan ------
//---------------------------
#include "Common/Drawables/renderable.h"
//--------------------------- FreeImage
#include "FI/FreeImage.h"
//--------------------------- OpenGL
#include "GL/glew.h"
#include "GL/glfw.h"
//--------------------------- IO
#include <iostream>
//---------------------------
cRenderable::cRenderable(){
	uiSpriteID = 0;
	UVMinMax[0] = 0.0f;	UVMinMax[1] = 0.0f;
	UVMinMax[2] = 1.0f;	UVMinMax[3] = 1.0f;
	fColour[0]  = 1.0f;	fColour[1]  = 1.0f;
	fColour[2]  = 1.0f;	fColour[3]  = 1.0f;
	uiWidth = 0;
	uiHeight = 0;
	uiWidthCONST = 0;
	uiHeightCONST = 0;
}
void cRenderable::Create(const char* path,unsigned int width, unsigned int height, int xoff, int yoff){

	uiWidth = width;
	uiHeight = height;

	xOff = float(xoff)/float(uiWidth);
	yOff = float(yoff)/float(uiHeight);

	uiSpriteID = TextureLoad(path);

	uiWidthCONST = width;
	uiHeightCONST = height;

	SetColour(1.0f,1.0f,1.0f,1.0f);
}
void cRenderable::SetUV(float uMin,float vMin,float uMax,float vMax){
	UVMinMax[0] = uMin;
	UVMinMax[1] = vMin;
	UVMinMax[2] = uMax;
	UVMinMax[3] = vMax;
}
void cRenderable::SetColour(float f_Red, float f_Green, float f_Blue, float f_Alpha){
	fColour[0]  = f_Red;	
	fColour[1]  = f_Green;
	fColour[2]  = f_Blue;	
	fColour[3]  = f_Alpha;
}
unsigned int cRenderable::GetID(){
	return uiSpriteID;
}
void cRenderable::Draw(int uLocation,cFramework *FW,bool Camera0_world1){
	glBindTexture( GL_TEXTURE_2D, uiSpriteID );
	if (Camera0_world1){
		M4Matrix = FW->WorldMVP * M4Translate * M4Rotate * M4Scale; 
	}else{
		M4Matrix = FW->CamMVP * M4Translate * M4Rotate * M4Scale; 
	}
	glUniformMatrix4fv(uLocation,1,GL_FALSE,&M4Matrix.m[0]);
}
void cRenderable::Resize(int width, int height){
	ResizeOBJ(width,height,uiWidthCONST,uiHeightCONST);
}
int cRenderable::GetWidthHeight(bool width0_height1){
	if (width0_height1){
		return uiHeight;
	}else{
		return uiWidth;
	}
	return 0;
}
void cRenderable::Delete(){
	glDeleteTextures(1, &uiSpriteID);
}
unsigned int cRenderable::TextureLoad(const char* cTexPath){
	//variables
	//printf("------------- loading texture : '%s' \n",cTexPath);	
	FIBITMAP* pBitmap = nullptr;
	GLuint TextureID;
	FREE_IMAGE_FORMAT imgFormat = FreeImage_GetFileType(cTexPath,0);
	unsigned int uiBPP;
	//Load the image if it exists
	if (imgFormat != FIF_UNKNOWN && FreeImage_FIFSupportsReading(imgFormat)){
		pBitmap = FreeImage_Load(imgFormat,cTexPath);
	}
	//make sure we can see the image
	if (pBitmap == nullptr){
		printf("------------- Error loading texture : '%s' \n",cTexPath);
		return 0;
	}
	//check if we specifyed a width and height, if not set it to the image's
	if (uiWidth  == 0) {uiWidth  = FreeImage_GetWidth(pBitmap) ;}
	if (uiHeight == 0) {uiHeight = FreeImage_GetHeight(pBitmap);}
	//Check the Bits Per Pixel
	uiBPP = FreeImage_GetBPP(pBitmap);
	//Get the colour type of the image, RGBA RGB RBG
	FREE_IMAGE_COLOR_TYPE fiColourType = FreeImage_GetColorType(pBitmap);
	//Change it to RGBA
	if (fiColourType != FIC_RGBALPHA){
		FIBITMAP* ndib = FreeImage_ConvertTo32Bits(pBitmap);
		FreeImage_Unload(pBitmap);
		pBitmap = ndib;
		uiBPP = FreeImage_GetBPP(pBitmap);
		fiColourType = FreeImage_GetColorType(pBitmap);
	}
	//Get the pixel data from the image
	BYTE* pData = FreeImage_GetBits(pBitmap);
	FREE_IMAGE_TYPE fiType = FreeImage_GetImageType(pBitmap);
	GLenum eType = (fiType == FIT_RGBF || fiType == FIT_FLOAT) ? GL_FLOAT:GL_UNSIGNED_BYTE;
	//Finally create the visable Texture
	glGenTextures(1,&TextureID);
	glBindTexture(GL_TEXTURE_2D,TextureID);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,
				FreeImage_GetWidth (pBitmap),
				FreeImage_GetHeight(pBitmap),
				0,GL_BGRA,eType,pData);
	//filter and wrappers
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	//unbind the texture
	glBindTexture(GL_TEXTURE_2D,0);
	//Unlooad the Freeimage container
	FreeImage_Unload(pBitmap);
	//Return the texture ID from OpenGL
	//printf("------------- loaded texture : '%s' \n",cTexPath);	
	return TextureID;
}