//---------------------------
//------ Luke Monaghan ------
//---------------------------
#ifndef _VECTORLIB
#define _VECTORLIB
//constants
#define PI      3.14159265358979323846f
#define RAD2DEG 57.2957795130823208768f
#define DEG2RAD 0.01745329251994329577f
//convert between rad and degree
float radToDegree(float rad);
float degreeToRad(float degree);
//reciprocal
float Recipf(float x);
//min max
float Minf(float x, float y);
float Maxf(float x, float y);
//power
int PowerUp(int value);
int PowerDown(int value);
int PowerClosest(int value);

float Lerp(float f_1, float f_2, float t);
#endif