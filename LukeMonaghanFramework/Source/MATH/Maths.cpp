//---------------------------
//------ Luke Monaghan ------
//---------------------------
#include "MATH/Maths.h"

float radToDegree(float rad){
	return (rad * RAD2DEG);
}
float degreeToRad(float degree){
	return (degree * DEG2RAD);
}
float Recipf(float x){
	return x/1.0f;
}
float Minf(float x, float y){
	return (x < y) ? x : y; // if x less    than y return x else y
}
float Maxf(float x, float y){
	return (x > y) ? x : y; // if x greater than y return x else y
}
int PowerUp(int value){
	int power = 1;
	while(power < value){//while power is less than the value
    power*=2;			 //times it by two
	}
	return power;
}
int PowerDown(int value){
	value = PowerUp(value);//get the top power of this value
	value/=2;//divide it by two to get the closest lower value
	return value;
}
int PowerClosest(int value){
	int up = PowerUp(value);
	int down = PowerDown(value);
	int v1 = value - up;   if (v1 < 0){v1*=-1;}
	int v2 = value - down; if (v2 < 0){v2*=-1;}
	if (v1 <= v2){
		return up;
	}else{
		return down;
	}
}
float Lerp(float f_1, float f_2, float t){
	return f_1+(f_2-f_1)*t;
}