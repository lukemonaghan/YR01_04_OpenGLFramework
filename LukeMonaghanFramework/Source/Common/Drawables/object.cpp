//---------------------------
//------ Luke Monaghan ------
//---------------------------
#include "Common/Drawables/object.h"
cObject::cObject(){
	M4Matrix    = Matrix4(1.0f);
	M4Scale	    = Matrix4(1.0f);
	M4Rotate    = Matrix4(1.0f);
	M4Translate = Matrix4(1.0f);
}
void cObject::Translate(float x, float y, float depth){
	M4Translate.Translate(x,y,-depth);
}
void cObject::Rotate(float angle){	
	angle = degreeToRad(angle);
	M4Rotate.RotateZ(angle);
}
void cObject::Scale(float xscale, float yscale){
	M4Scale.Scale(xscale,yscale,1.0f);
}
void cObject::ResizeOBJ(int width, int height,int defaultwidth, int defaultheight){
	M4Scale.Scale(float(float(width)/defaultwidth),float(float(height)/defaultheight),1.0f);
}