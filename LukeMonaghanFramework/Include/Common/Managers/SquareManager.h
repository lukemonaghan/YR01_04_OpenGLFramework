//---------------------------
//------ Luke Monaghan ------
//---------------------------
#ifndef SQUAREMANAGER_H_
#define SQUAREMANAGER_H_
//--------------------------- Includes
#include <map>
#include <queue>
#include "Common/Drawables/square.h"
//--------------------------- Class
class cSquareManager{
public:
//--------------------------- De/Constructor
	cSquareManager();
	void Initialise();
	void Shutdown();
//--------------------------- Functions
	void Move  (int spriteID, float x, float y, float depth);
	void Rotate(int spriteID, float angle);
	void Scale (int spriteID, float xscale, float yscale);
	void Resize(int spriteID, int width , int height);
	void UV    (int spriteID, float uMin, float vMin, float uMax, float vMax);
	void Colour(int spriteID, float f_Red, float f_Green, float f_Blue, float f_Alpha);
	cSquare GetcSquare(int spriteID);

	void AddtoQueue(int spriteID,bool Camera0_world1);
	int Draw  (int uLocation,cFramework *FW);
//--------------------------- Create Remove
	int  Create(char* path, int width, int height, int xoff, int yoff);
	void Remove(int spriteID);
private:
	std::map<unsigned int,cSquare> SpritesMap;
	std::map<unsigned int,cSquare>::iterator SpritesMapIt;
	std::queue<cSquare> SpritesQueue;
	//std::queue<bool> CameraWorldQueue;
	unsigned int VAO,VBO,IBO;
};

#endif