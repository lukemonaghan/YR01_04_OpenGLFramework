//---------------------------
//------ Luke Monaghan ------
//---------------------------
#ifndef UTILITIES_H_
#define UTILITIES_H_
//--------------------------- OpenGL
#include "Framework.h"
void VSync(int mode);

void SetDeltaTime();
float GetDeltaTime();
float GetFPS();
float GetFPSAv();

void Drawline();

int KeyDownGet(int key);
int KeyUpGet(int key);
int KeyPressedGet(int key);
int KeyReleasedGet(int key);

void MousePositionGet(cFramework *FW,int &x, int &y);
void MousePositionSet(cFramework *FW,int  x, int  y);

int MouseDownGet(int MouseButton);
int MouseUpGet(int MouseButton);
int MousePressedGet(int MouseButton);
int MouseReleasedGet(int MouseButton);

int MouseScrollWheelGet();

#endif