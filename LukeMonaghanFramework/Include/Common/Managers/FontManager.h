//---------------------------
//------ Luke Monaghan ------
//---------------------------
#ifndef FONTMANAGER_H_
#define FONTMANAGER_H_
//--------------------------- Includes
#include <map>
#include <queue>
#include "Common/Drawables/Font.h"
//--------------------------- Class
class cFontManager{
public:
//--------------------------- De/Constructor
	cFontManager();
	void Initialise();
	void Shutdown();
//--------------------------- Create Remove
	int  Create(char* path);
	void Remove(int FontID);
	int Draw(int uLocation,cFramework *FW);
	void Colour(int FontID, float f_Red, float f_Green, float f_Blue, float f_Alpha);
	void String(int FontID,char* string,float x, float y,float depth,bool center,bool Camera0_world1);
	void Int   (int FontID,int Value   ,float x, float y,float depth,bool center,bool Camera0_world1);
	void Float (int FontID,float Value ,float x, float y,float depth,bool center,bool Camera0_world1);
private:
	std::map<unsigned int,cFont> FontsMap;
	std::map<unsigned int,cFont>::iterator FontsMapIt;
	std::queue<cSquare> LettersQueue;
	std::queue<cSquare> TempWordLettersQueue;
	std::queue<bool> CameraWorldQueue;
	unsigned int VAO,VBO,IBO;
};

#endif