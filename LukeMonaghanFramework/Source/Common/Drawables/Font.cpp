//---------------------------
//------ Luke Monaghan ------
//---------------------------
#include "Common/Drawables/Font.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
//--------------------------- Constructor
cFont::cFont(char* Path){
	LoadFont(Path);
}
//--------------------------- Draw
std::queue<cSquare> cFont::DrawString(char* string,float x, float y,float depth,bool center){
	std::queue<cSquare> TempQueue;
	float tSize = 1.0f;
	offset = 0;
	if (center){
		x-=StrLen(string)*1.5f;
	}
//Get SIZE
	if (size!=lineheight){
		tSize = size/(float)lineheight;
	}
	for (int i = 0; i < (int)strlen(string); i++){
//Get the CHAR ID
		charid = string[i];
//Draw Letter
		FontMap.SetUV(vChars[charid].UV[0],
					  vChars[charid].UV[1],
					  vChars[charid].UV[2],
					  vChars[charid].UV[3]);
		FontMap.Resize(int(vChars[charid].width  * tSize),
					   int(vChars[charid].height * tSize));
		FontMap.Translate(x+offset+((vChars[charid].xoffset) * tSize),
						  y       -((vChars[charid].yoffset) * tSize)
						  ,depth);
//Move to the next offset
		TempQueue.push(FontMap);
		offset+=(int)(vChars[charid].xadvance * tSize);
	}
	return TempQueue;
}
std::queue<cSquare> cFont::DrawInt(int value ,float x, float y, float depth, bool center){
	sprintf(iBuff, "%i", value);
	return DrawString(iBuff,x,y,depth,center);
}

std::queue<cSquare> cFont::DrawFloat(float value ,float x, float y, float depth, bool center){
	sprintf(iBuff, "%f", value);
	return DrawString(iBuff,x,y,depth,center);
}

void cFont::SetColour(float f_Red, float f_Green, float f_Blue, float f_Alpha){
	FontMap.SetColour(f_Red,f_Green,f_Blue,f_Alpha);
}
void cFont::SetSize(int T_size){
	size = T_size;
}
int cFont::StrLen(char* string){
	offset = 0;
	for (int i = 0; i < (int)strlen(string); i++){
		offset+=(int)(vChars[string[i]].xadvance * (size/(float)lineheight));
	}
	return offset;
}
//--------------------------- Delete 
void cFont::Delete(){
	FontMap.Delete();
}
//--------------------------- Load
bool cFont::LoadFont(char* Path){
//Load the XML
	//printf("------------- Loading XML file of path : '%s' \n",Path);
	TiXmlDocument doc(Path);
    if (doc.LoadFile()){
//Check its a font
	TiXmlNode* xFont = doc.FirstChild("font");
	if (!xFont){
		printf("----------------------------------- Could not find 'font' Node. \n");
		return false;
	};
//Check it has info
	TiXmlNode* xInfo = xFont->FirstChild("info");
	if (!xInfo){
		printf("----------------------------------- Could not find 'info' Node. \n");
		return false;
	}
	TiXmlElement * xInfoElement = xInfo->ToElement();
//Define all the INFO variables
	face = (char*)xInfoElement->Attribute("face");
	xInfoElement->QueryIntAttribute("size",&size);
	xInfoElement->QueryIntAttribute("charset",&charset);
	xInfoElement->QueryIntAttribute("unicode",&unicode);
	xInfoElement->QueryIntAttribute("stretchH",&stretchH);
	char* temppadd = (char*)xInfoElement->Attribute("padding");
	for (int i = 0; i < (int)strlen(temppadd); i+=2){
	padding[i] = (int)temppadd[i] - '0';
	}
	char* tempspac = (char*)xInfoElement->Attribute("spacing");
	for (int i = 0; i < (int)strlen(tempspac); i+=2){
	spacing[i] = (int)tempspac[i] - '0';
	}
	xInfoElement->QueryIntAttribute("bold",&bold);
	xInfoElement->QueryIntAttribute("italic",&italic);
	xInfoElement->QueryIntAttribute("smooth",&smooth);
	xInfoElement->QueryIntAttribute("aa",&aa);
	xInfoElement->QueryIntAttribute("outline",&outline);
//Check it has common
	TiXmlNode* xCommon = xFont->FirstChild("common");
	if (!xCommon){
		printf("----------------------------------- Could not find 'common' Node. \n");
		return false;
	}
//Define all the COMMON vars
	TiXmlElement * xCommonElement = xCommon->ToElement();
	xCommonElement->QueryIntAttribute("lineHeight",&lineheight);
	xCommonElement->QueryIntAttribute("base"      ,&Base);
	xCommonElement->QueryIntAttribute("scaleW"    ,&TexW);
	xCommonElement->QueryIntAttribute("scaleH"    ,&TexH);
	xCommonElement->QueryIntAttribute("pages"     ,&Pages);
	xCommonElement->QueryIntAttribute("packed"    ,&Packed);
	xCommonElement->QueryIntAttribute("alphaChnl" ,&Colour[3]);
	xCommonElement->QueryIntAttribute("redChnl"   ,&Colour[0]);
	xCommonElement->QueryIntAttribute("greenChnl" ,&Colour[1]);
	xCommonElement->QueryIntAttribute("blueChnl"  ,&Colour[2]);
//Check it has pages
	TiXmlNode* xPages = xFont->FirstChild("pages");
	if (!xFont){
		printf("----------------------------------- Could not find 'pages' Node. \n");
		return false;
	}
	TiXmlElement * xPage = xPages->FirstChildElement();
	xPage->QueryIntAttribute("id",&pageID);
	SpritePath = (char*)xPage->Attribute("file");
//Create Font
	std::string tStr;
	tStr.append(Path);

	int found = (int)tStr.find_last_of('/');
	tStr = tStr.substr(0,found+1);
	tStr.append(SpritePath);

	FontMap.Create(tStr.c_str(),TexW,TexH,0,0);
	iID = FontMap.GetID();
//Check it has chars
	TiXmlNode* xChars = xFont->FirstChild("chars");
	if (!xFont){
		printf("----------------------------------- Could not find 'chars' Node. \n");
		return false;
	}
	TiXmlElement * xCharsElement = xChars->ToElement();
	TiXmlElement * XChar = xCharsElement->FirstChildElement();
//Loop through the chars, assigning them to the Array
	int x,y;
	do {
	XChar->QueryIntAttribute("id",&charid);
	vChars.insert(std::pair<char,sCharacter>(charid,sCharacter()));
	vChars[charid].id = charid;
	XChar->QueryIntAttribute("x",&x);
	XChar->QueryIntAttribute("y",&y);
	XChar->QueryIntAttribute("width",&vChars[charid].width);
	XChar->QueryIntAttribute("height",&vChars[charid].height);
	vChars[charid].UV[0] =        x                       /(float)TexW ;
	vChars[charid].UV[1] = 1.0f-((y+vChars[charid].height)/(float)TexH);
	vChars[charid].UV[2] =       (x+vChars[charid].width )/(float)TexW ;
	vChars[charid].UV[3] = 1.0f-( y                       /(float)TexH);
	XChar->QueryIntAttribute("xoffset",&vChars[charid].xoffset);
	XChar->QueryIntAttribute("yoffset",&vChars[charid].yoffset);
	XChar->QueryIntAttribute("xadvance",&vChars[charid].xadvance);
	XChar->QueryIntAttribute("page",&vChars[charid].page);
	XChar->QueryIntAttribute("chnl",&vChars[charid].channel);
	XChar = XChar->NextSiblingElement();
	}while (XChar != NULL);
	//printf("------------- Loaded XML file of path : '%s' \n\n",Path);
	return true;
	}else{
	printf("------------- Error Loading XML file of path : '%s' \n\n",Path);
	return false;
	}
}