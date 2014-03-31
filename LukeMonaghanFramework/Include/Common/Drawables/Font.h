//---------------------------
//------ Luke Monaghan ------
//---------------------------
#ifndef FONT_H_
#define FONT_H_
//--------------------------- Vector
//#include <vector>
#include <map>
#include <queue>
//--------------------------- Sprite
#include "Common/Drawables/Square.h"
//--------------------------- TinyXML
#include "TXML/tinyxml.h"
#include "TXML/tinystr.h"
//--------------------------- Char Typedef
typedef struct sCharacter{
	int	id;
	float UV[4];
	int	width,height;
	int	xoffset,yoffset;
	int	xadvance;
	int	page;
	int	channel;
}Tchar;
//--------------------------- Font Class
class cFont {
public:
//--------------------------- Constructor
	cFont(char* Path);
	~cFont(){};
//--------------------------- Delete
	void Delete();
//--------------------------- Draw
	std::queue<cSquare> DrawString(char* string,float x, float y,float depth,bool center);
	std::queue<cSquare> DrawInt   (int value   ,float x, float y,float depth,bool center);
	std::queue<cSquare> DrawFloat(float value ,float x, float y, float depth, bool center);
	void SetColour(float f_Red, float f_Green, float f_Blue, float f_Alpha);
	int StrLen(char* String);
	void SetSize(int T_size);
//--------------------------- Getters
	int ID(){return iID;}
private:
	bool LoadFont(char* Path);
//--------------------------- Info
	char* face;
	char* SpritePath;
	int size,charset,unicode,stretchH,padding[4],spacing[2],pageID,offset;
	int bold,italic,smooth,aa,outline;
//--------------------------- Common
	int lineheight,Base,Pages,Packed,Colour[4],TexW,TexH,charid;
//--------------------------- Chars
	std::map<char,sCharacter> vChars;
	char iBuff[100];
	float umin,vmin,umax,vmax;
//--------------------------- Sprite
	cSquare FontMap;
	int iID;

};

#endif