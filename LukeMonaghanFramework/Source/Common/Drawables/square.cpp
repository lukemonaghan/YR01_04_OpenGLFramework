//---------------------------
//------ Luke Monaghan ------
//---------------------------
#include "Common/Drawables/square.h"
//--------------------------- OpenGL
#include "GL/glew.h"
#include <iostream>
//---------------------------
cSquare::cSquare(){
	Verticies[0].Size = Vector3(0,0,0);
	Verticies[1].Size = Vector3(0,0,0);
	Verticies[2].Size = Vector3(0,0,0);
	Verticies[3].Size = Vector3(0,0,0);

	Verticies[0].UV  = Vector2(UVMinMax[0],UVMinMax[1]);
	Verticies[1].UV  = Vector2(UVMinMax[2],UVMinMax[1]);
	Verticies[2].UV  = Vector2(UVMinMax[2],UVMinMax[3]);
	Verticies[3].UV  = Vector2(UVMinMax[0],UVMinMax[3]);

	Verticies[0].Colour = Vector4(fColour[0],fColour[1],fColour[2],fColour[3]);
	Verticies[1].Colour = Vector4(fColour[0],fColour[1],fColour[2],fColour[3]);
	Verticies[2].Colour = Vector4(fColour[0],fColour[1],fColour[2],fColour[3]);
	Verticies[3].Colour = Vector4(fColour[0],fColour[1],fColour[2],fColour[3]);
}
cSquare::cSquare(const char* path, int width, int height, int xoffset, int yoffset){
	uiWidth = width;
	uiHeight = height;

	xOff = float(xoffset)/float(uiWidth);
	yOff = float(yoffset)/float(uiHeight);

	uiSpriteID = TextureLoad(path);

	uiWidthCONST = width;
	uiHeightCONST = height;
}
void cSquare::UpdateVerts(){
	Verticies[0].Size = Vector3(-(uiWidth*     (xOff)),-(uiHeight*(1.0f-yOff)),0.0f);
	Verticies[1].Size = Vector3( (uiWidth*(1.0f-xOff)),-(uiHeight*(1.0f-yOff)),0.0f);
	Verticies[2].Size = Vector3( (uiWidth*(1.0f-xOff)), (uiHeight*     (yOff)),0.0f);
	Verticies[3].Size = Vector3(-(uiWidth*     (xOff)), (uiHeight*     (yOff)),0.0f);

	Verticies[0].UV  = Vector2(UVMinMax[0],UVMinMax[1]);
	Verticies[1].UV  = Vector2(UVMinMax[2],UVMinMax[1]);
	Verticies[2].UV  = Vector2(UVMinMax[2],UVMinMax[3]);
	Verticies[3].UV  = Vector2(UVMinMax[0],UVMinMax[3]);

	Verticies[0].Colour = Vector4(fColour[0],fColour[1],fColour[2],fColour[3]);
	Verticies[1].Colour = Vector4(fColour[0],fColour[1],fColour[2],fColour[3]);
	Verticies[2].Colour = Vector4(fColour[0],fColour[1],fColour[2],fColour[3]);
	Verticies[3].Colour = Vector4(fColour[0],fColour[1],fColour[2],fColour[3]);

	glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(Verticies),Verticies);
}