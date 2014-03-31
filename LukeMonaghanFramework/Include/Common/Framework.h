//---------------------------
//------ Luke Monaghan ------
//---------------------------
#ifndef FRAMEWORK_H_
#define FRAMEWORK_H_
//--------------------------- Maths
#include "MATH/Matrix4.h"
#include "MATH/Vector4.h"
//--------------------------- Framework Class
class cFramework {
public:
//--------------------------- Constructors
	cFramework();
	cFramework(char* Title,const unsigned int a_Width, const unsigned int a_Height, bool a_Fullscreen, float f_Left,float f_Right,float f_Bottom,float f_Top);
	//void Create(char* Title,const unsigned int a_Width, const unsigned int a_Height, bool a_Fullscreen, float f_Left,float f_Right,float f_Bottom,float f_Top);
//--------------------------- Public Functions
	void ColourVertex(Vector4 vColour);
	void ColourBackground(Vector4 vColour);
	void ResizeWindow(int width, int height);
	void Fullscreen(bool fullscr);
	bool Update();
	void Clear();
	void Exit();
	void BlendMode(int i_Begin, int i_Final, int i_Equation);
//--------------------------- Camera Controls
	void Translate(float x, float y);
	void Rotate(float angle);
	void Scale(float amount);
//--------------------------- Public Vars
	Matrix4 WorldProj,WorldViewT,WorldViewR,WorldMVP;
	Matrix4 CamMVP;
	unsigned int uiWidth,uiHeight;
	float fLeft, fRight, fBottom, fTop;
private:
//--------------------------- Private Functions
	void Create();
//--------------------------- Private Vars
	char* csTitle;
	bool bFullscreen,bError;
};

#endif