//---------------------------
//------ Luke Monaghan ------
//---------------------------
#include "Common/Utilities.h"
#include "GL/glfw.h"
//---------------------------
float fDeltaTime = 0.0f;
float fLastTime  = 0.0f;

float fFPS = 0.0f;
float fAvFPS = 0.0f;

long long AllFPS = 0;
int frames = 1;
//---------------------------
void VSync(int mode){
	glfwSwapInterval(mode);
	frames = 1;
	AllFPS = 0;
	fDeltaTime = 0.0f;
	fLastTime = 0.0f;
}
//---------------------------
void SetDeltaTime(){
	//Deltatime
	float dTime = (float)glfwGetTime();
	fDeltaTime = (float)(dTime - fLastTime);
	fLastTime = dTime;
	//Average FPS
	frames++;
	AllFPS+=(long long)(fFPS);
	//Fps Returns
	fFPS = 1/fDeltaTime;
	fAvFPS = (float)(AllFPS/(float)frames);
}
float GetDeltaTime(){
	return fDeltaTime;
}
//---------------------------
float GetFPS(){
	return fFPS;
}
float GetFPSAv(){
	return fAvFPS;
}
//---------------------------
int KeyDownGet(int key){
	return glfwGetKey(key);
}
int KeyUpGet(int key){
	return !glfwGetKey(key);
}
int KeyPressedGet(int key){
	return glfwGetKey(key);
}
int KeyReleasedGet(int key){
	return !glfwGetKey(key);
}
//---------------------------
void MousePositionGet(cFramework *FW,int &x, int &y){
	glfwGetMousePos(&x, &y);
	x-=(FW->uiWidth  * FW->fLeft);
	y-=(FW->uiHeight * FW->fTop);
	y*=-1;
}
void MousePositionSet(cFramework *FW,int  x, int  y){
	glfwSetMousePos(
		(FW->uiWidth  * FW->fLeft)+x,
		(FW->uiHeight * FW->fTop)-y
		);
}

int MouseDownGet(int MouseButton){
	return glfwGetMouseButton(MouseButton);
}
int MouseUpGet(int MouseButton){
	return !glfwGetMouseButton(MouseButton);
}
int MousePressedGet(int MouseButton){
	return glfwGetMouseButton(MouseButton);
}
int MouseReleasedGet(int MouseButton){
	return !glfwGetMouseButton(MouseButton);
}
//---------------------------
int MouseScrollWheelGet(){
	int temp = glfwGetMouseWheel();
	if (temp!=0){
		glfwSetMouseWheel(0);
	}
	return temp;
}