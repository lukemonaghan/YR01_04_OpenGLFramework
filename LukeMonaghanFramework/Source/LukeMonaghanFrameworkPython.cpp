//---------------------------
//------ Luke Monaghan ------
//---------------------------
#include "LukeMonaghanFrameworkPython.h"
#include "LukeMonaghanFramework.h"
#include <iostream>
#include <map>
//--------------------------- linkage "boilerplate code"
void  ParsePyTupleError(const char* a_pFunction, int a_Line ){
	std::cout << "Error Parsing Tuple\nFunction: " <<  a_pFunction << "\nLine#   : " << a_Line << std::endl;
	PyErr_Print();
}
PyObject* GetHandleToPythonFunction( PyObject* a_pModule, const char* a_pFunctionName ){
	PyObject* pFunction = PyObject_GetAttrString(a_pModule, a_pFunctionName);
    if( !(pFunction && PyCallable_Check(pFunction))){
        if (PyErr_Occurred()){PyErr_Print();}
        std::cout << stderr << "\nCannot find function \"" << a_pFunctionName << "\"\n" << std::endl;
    }
	return pFunction;
}
PyObject* CallPythonFunction( PyObject* a_pyFunction, PyObject* a_pyFuncArguments){
	PyObject* pReturnValue = PyObject_CallObject( a_pyFunction, a_pyFuncArguments );
	if (!pReturnValue){
		PyErr_Print();
		fprintf(stderr,"Call failed\n");
    }
	return pReturnValue;
}
//--------------------------- Framework Controller
 PyObject* LMF_FrameworkInitialise(PyObject *self, PyObject *args){
	char* title;
	int width,height; 
	int fullscr;
	float fLeftOff, fRightOff, fBottomOff, fTopOff;
	if (!PyArg_ParseTuple(args, "siiiffff", &title, &width, &height, &fullscr, &fLeftOff, &fRightOff, &fBottomOff, &fTopOff)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	int Updated = FrameworkInitialise(title,width,height,fullscr, fLeftOff, fRightOff, fBottomOff, fTopOff);
	return Py_BuildValue("i", Updated);
}
 PyObject* LMF_FrameworkUpdate(PyObject *self, PyObject *args){
	int Updated = FrameworkUpdate();
	return Py_BuildValue("i", Updated);
}
 PyObject* LMF_FrameworkClearScreen(PyObject *self, PyObject *args){
	FrameworkClearScreen();
	Py_RETURN_NONE;
}
 PyObject* LMF_FrameworkBGColour(PyObject *self, PyObject *args){
	float fR,fG,fB,fA;
	if (!PyArg_ParseTuple(args, "ffff", &fR,&fG,&fB,&fA)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	FrameworkBGColour(fR,fG,fB,fA);
	Py_RETURN_NONE;
}
 PyObject* LMF_FrameworkWindowResize(PyObject *self, PyObject *args){
	int width, height;
	if (!PyArg_ParseTuple(args, "ii", &width,&height)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	FrameworkWindowResize(width,height);
	Py_RETURN_NONE;
}
 PyObject* LMF_FrameworkFullscreen(PyObject *self, PyObject *args){
	int fullscr;
	if (!PyArg_ParseTuple(args, "i", &fullscr)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	FrameworkFullscreen(fullscr);
	Py_RETURN_NONE;
}
 PyObject* LMF_FrameworkBlendMode(PyObject *self, PyObject *args){
	int iBegin, iFinal, iEqu;
	if (!PyArg_ParseTuple(args, "iii", &iBegin, &iFinal, &iEqu)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	FrameworkBlendMode(iBegin,iFinal,iEqu);
	Py_RETURN_NONE;
}
 PyObject* LMF_FrameworkShutdown(PyObject *self, PyObject *args){
	FrameworkShutdown();
	Py_RETURN_NONE;
}
//--------------------------- Camera
 PyObject* LMF_CameraMove(PyObject *self, PyObject *args){
	float fX,fY;
	if (!PyArg_ParseTuple(args, "ff", &fX,&fY)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	CameraMove(fX,fY);
	Py_RETURN_NONE;
}
 PyObject* LMF_CameraRotate(PyObject *self, PyObject *args){
	float fRot;
	if (!PyArg_ParseTuple(args, "f", &fRot)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	CameraRotate(fRot);
	Py_RETURN_NONE;
}
 PyObject* LMF_CameraZoom(PyObject *self, PyObject *args){
	float fValue;
	if (!PyArg_ParseTuple(args, "f", &fValue)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	CameraZoom(fValue);
	Py_RETURN_NONE;
}
//--------------------------- Sprite
 PyObject* LMF_SpriteLoad(PyObject *self, PyObject *args){
	char* title;
	int width, height;
	int xoff , yoff;
	if (!PyArg_ParseTuple(args, "siiii", &title, &width, &height, &xoff, &yoff)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	unsigned int SpriteID = SpriteLoad(title,width,height,xoff,yoff);
	int returnSprID = SpriteID;
	return Py_BuildValue("i", returnSprID);
}
 PyObject* LMF_SpriteMove(PyObject *self, PyObject *args){
	unsigned int SpriteID;
	float fX,fY,fDepth;
	if (!PyArg_ParseTuple(args, "ifff", &SpriteID, &fX, &fY, &fDepth)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	SpriteMove(SpriteID,fX,fY,fDepth);
	Py_RETURN_NONE;
}
 PyObject* LMF_SpriteRotate(PyObject *self, PyObject *args){
	unsigned int SpriteID;
	float fAngle;
	if (!PyArg_ParseTuple(args, "if", &SpriteID, &fAngle)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	SpriteRotate(SpriteID,fAngle);
	Py_RETURN_NONE;
}
 PyObject* LMF_SpriteScale(PyObject *self, PyObject *args){
	unsigned int SpriteID;
	float xScale,yScale;
	if (!PyArg_ParseTuple(args, "iff", &SpriteID, &xScale, &yScale)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	SpriteScale(SpriteID,xScale,yScale);
	Py_RETURN_NONE;
}
 PyObject* LMF_SpriteResize(PyObject *self, PyObject *args){
	unsigned int SpriteID;
	int iWidth,iHeight;
	if (!PyArg_ParseTuple(args, "iii", &SpriteID, &iWidth, &iHeight)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	SpriteResize(SpriteID,iWidth,iHeight);
	Py_RETURN_NONE;
}
 PyObject* LMF_SpriteUVset(PyObject *self, PyObject *args){
	unsigned int SpriteID;
	float fuMin,fvMin,fuMax,fvMax;
	if (!PyArg_ParseTuple(args, "iffff", &SpriteID, &fuMin,&fvMin,&fuMax,&fvMax)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	SpriteUVset(SpriteID,fuMin,fvMin,fuMax,fvMax);
	Py_RETURN_NONE;
}
 PyObject* LMF_SpriteColour(PyObject *self, PyObject *args){
	unsigned int SpriteID;
	float fRed,fGreen,fBlue,fAlpha;
	if (!PyArg_ParseTuple(args, "iffff", &SpriteID, &fRed,&fGreen,&fBlue,&fAlpha)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	SpriteColour(SpriteID,fRed,fGreen,fBlue,fAlpha);
	Py_RETURN_NONE;
}
 PyObject* LMF_SpriteDraw(PyObject *self, PyObject *args){
	unsigned int SpriteID, Camera0_world1;
	if (!PyArg_ParseTuple(args, "ii", &SpriteID,&Camera0_world1)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	SpriteDraw(SpriteID,Camera0_world1);
	Py_RETURN_NONE;
}
 PyObject* LMF_SpriteUnload(PyObject *self, PyObject *args){
	unsigned int SpriteID;
	if (!PyArg_ParseTuple(args, "i", &SpriteID)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	SpriteUnload(SpriteID);
	Py_RETURN_NONE;
}
//--------------------------- Particle Emitters
 PyObject* LMF_ParticleEmitterLoadEmpty(PyObject *self, PyObject *args){
	unsigned int SpriteID;
	if (!PyArg_ParseTuple(args, "i", &SpriteID)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	unsigned int EmitterID = ParticleEmitterLoad(SpriteID);
	return Py_BuildValue("i", EmitterID);
}
 PyObject* LMF_ParticleEmitterLoad(PyObject *self, PyObject *args){
	int SpriteID;
	float startx, starty, startdepth;
	float endx, endy, enddepth,lifetime;
	if (!PyArg_ParseTuple(args, "ifffffff", &SpriteID, &startx, &starty, &startdepth, &endx, &endy, &enddepth, &lifetime)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	unsigned int EmitterID = ParticleEmitterLoad(SpriteID,startx, starty, startdepth, endx, endy, enddepth,lifetime);
	return Py_BuildValue("i", EmitterID);
}
 PyObject* LMF_ParticleEmitterUnload(PyObject *self, PyObject *args){
	unsigned int EmitterID;
	if (!PyArg_ParseTuple(args, "i", &EmitterID)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	ParticleEmitterUnload(EmitterID);
	Py_RETURN_NONE;
}
 PyObject* LMF_ParticleEmitterPerStep(PyObject *self, PyObject *args){
	unsigned int EmitterID;
	float amount;
	if (!PyArg_ParseTuple(args, "if", &EmitterID, &amount)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	ParticleEmitterPerStep(EmitterID,amount);
	Py_RETURN_NONE;
}

 PyObject* LMF_ParticleEmitterSetPosition(PyObject *self, PyObject *args){
	unsigned int EmitterID;
	float x,y,depth;
	int startend;
	if (!PyArg_ParseTuple(args, "ifffi", &EmitterID, &x, &y, &depth, &startend)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	ParticleEmitterSetPosition(EmitterID,x,y,depth,startend);
	Py_RETURN_NONE;
}
 PyObject* LMF_ParticleEmitterSetSize(PyObject *self, PyObject *args){
	unsigned int EmitterID;
	float width,height;
	int startend;
	if (!PyArg_ParseTuple(args, "iffi", &EmitterID, &width, &height, &startend)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	ParticleEmitterSetSize(EmitterID,width,height,startend);
	Py_RETURN_NONE;
}
 PyObject* LMF_ParticleEmitterSetColour   (PyObject *self, PyObject *args){
	unsigned int EmitterID;
	float fRed,fGreen,fBlue,fAlpha;
	int startend;
	if (!PyArg_ParseTuple(args, "iffffi", &EmitterID, &fRed, &fGreen, &fBlue, &fAlpha, &startend)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	ParticleEmitterSetColour(EmitterID,fRed,fGreen,fBlue,fAlpha,startend);
	Py_RETURN_NONE;
}
 PyObject* LMF_ParticleEmitterSetOffset   (PyObject *self, PyObject *args){
	unsigned int EmitterID;
	int xPos,yPos;
	if (!PyArg_ParseTuple(args, "iii", &EmitterID, &xPos, &yPos)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	ParticleEmitterSetOffset(EmitterID,xPos,yPos);
	Py_RETURN_NONE;
}
 PyObject* LMF_ParticleEmitterSetRotation (PyObject *self, PyObject *args){
	unsigned int EmitterID;
	float fAngle;
	int startend;
	if (!PyArg_ParseTuple(args, "ifi", &EmitterID, &fAngle, &startend)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	ParticleEmitterSetRotation(EmitterID,fAngle,startend);
	Py_RETURN_NONE;
}

 PyObject* LMF_ParticleEmitterDraw(PyObject *self, PyObject *args){
	unsigned int EmitterID, Camera0_world1;
	if (!PyArg_ParseTuple(args, "ii", &EmitterID, &Camera0_world1)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	ParticleEmitterDraw(EmitterID, Camera0_world1);
	Py_RETURN_NONE;
}
//--------------------------- Model
 PyObject* LMF_ModelLoad(PyObject *self, PyObject *args){
	char* path;
	if (!PyArg_ParseTuple(args, "s", &path)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	unsigned int ModelID = ModelLoad(path);
	return Py_BuildValue("i", ModelID);
}
 PyObject* LMF_ModelMove(PyObject *self, PyObject *args){
	unsigned int ModelID;
	float fX,fY,fDepth;
	if (!PyArg_ParseTuple(args, "ifff", &ModelID,&fX,&fY,&fDepth)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	ModelMove(ModelID,fX,fY,fDepth);
	Py_RETURN_NONE;
}
 PyObject* LMF_ModelRotate(PyObject *self, PyObject *args){
	unsigned int ModelID;
	float fRot;
	if (!PyArg_ParseTuple(args, "if", &ModelID,&fRot)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	ModelRotate(ModelID,fRot);
	Py_RETURN_NONE;
}
 PyObject* LMF_ModelScale(PyObject *self, PyObject *args){
	unsigned int ModelID;
	float fXscale,fYscale;
	if (!PyArg_ParseTuple(args, "iff", &ModelID,&fXscale, &fYscale)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	ModelScale(ModelID,fXscale,fYscale);
	Py_RETURN_NONE;
}
 PyObject* LMF_ModelResize(PyObject *self, PyObject *args){
	unsigned int ModelID;
	int iWidth,iHeight;
	if (!PyArg_ParseTuple(args, "iii", &ModelID,&iWidth, &iHeight)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	ModelResize(ModelID,iWidth,iHeight);
	Py_RETURN_NONE;
}
 PyObject* LMF_ModelDraw(PyObject *self, PyObject *args){
	unsigned int ModelID, Camera0_world1;
	if (!PyArg_ParseTuple(args, "i", &ModelID, &Camera0_world1)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	ModelDraw(ModelID, Camera0_world1);
	Py_RETURN_NONE;
}
 PyObject* LMF_ModelUnload(PyObject *self, PyObject *args){
	unsigned int ModelID;
	if (!PyArg_ParseTuple(args, "i", &ModelID)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	ModelUnload(ModelID);
	Py_RETURN_NONE;
}
//--------------------------- Fonts
 PyObject* LMF_FontLoad(PyObject *self, PyObject *args){
	char* path;
	if (!PyArg_ParseTuple(args, "s", &path)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	unsigned int FontID = FontLoad(path);
	return Py_BuildValue("i", FontID);
}
 PyObject* LMF_FontUnload(PyObject *self, PyObject *args){
	unsigned int FontID;
	if (!PyArg_ParseTuple(args, "i", &FontID)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	FontUnload(FontID);
	Py_RETURN_NONE;
}
 PyObject* LMF_FontColour(PyObject *self, PyObject *args){
	unsigned int FontID;
	float fRed,fGreen,fBlue,fAlpha;
	if (!PyArg_ParseTuple(args, "iffff", &FontID, &fRed, &fGreen, &fBlue, &fAlpha)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	FontColour(FontID,fRed,fGreen,fBlue,fAlpha);
	Py_RETURN_NONE;
}
 PyObject* LMF_DrawString(PyObject *self, PyObject *args){
	unsigned int FontID;
	char* cString;
	float fX,fY,fDepth;
	int bCenter;
	if (!PyArg_ParseTuple(args, "isfffi", &FontID, &cString, &fX, &fY, &fDepth, &bCenter)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	DrawString(FontID,cString,fX,fY,1,fDepth,bCenter);
	Py_RETURN_NONE;
}
 PyObject* LMF_DrawInt(PyObject *self, PyObject *args){
	unsigned int FontID;
	int iValue;
	float fX,fY,fDepth;
	int bCenter;
	if (!PyArg_ParseTuple(args, "iifffi", &FontID, &iValue, &fX, &fY, &fDepth, &bCenter)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	DrawInt(FontID,iValue,fX,fY,1,fDepth,bCenter);
	Py_RETURN_NONE;
}
 PyObject* LMF_DrawFloat(PyObject *self, PyObject *args){
	unsigned int FontID;
	float fValue;
	float fX,fY,fDepth;
	int bCenter;
	if (!PyArg_ParseTuple(args, "iffffi", &FontID, &fValue, &fX, &fY, &fDepth, &bCenter)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	DrawFloat(FontID,fValue,fX,fY,1,fDepth,bCenter);
	Py_RETURN_NONE;
}
//--------------------------- Shaders
 PyObject* LMF_ShaderLoad(PyObject *self, PyObject *args){
	char* cPath;
	if (!PyArg_ParseTuple(args, "s", &cPath)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	unsigned int ShaderID = ShaderLoad(cPath);
	return Py_BuildValue("i", ShaderID);
}
 PyObject* LMF_ShaderUse(PyObject *self, PyObject *args){
	unsigned int ShaderID;
	if (!PyArg_ParseTuple(args, "i", &ShaderID)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	ShaderUse(ShaderID);
	Py_RETURN_NONE;
}
 PyObject* LMF_ShaderUnload(PyObject *self, PyObject *args){
	int ShaderID;
	if (!PyArg_ParseTuple(args, "i", &ShaderID)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	ShaderUnload(ShaderID);
	Py_RETURN_NONE;
}
//--------------------------- ID's
 PyObject* LMF_TextureShaderID(PyObject *self, PyObject *args){
	unsigned int DefShaderID = GetDefaultShaderID();
	return Py_BuildValue("i", DefShaderID);
}
 PyObject* LMF_DefaultFontID  (PyObject *self, PyObject *args){
	unsigned int DefFontID = GetDefaultFontID();
	return Py_BuildValue("i", DefFontID);
}
 PyObject* LMF_GetInstanceCount(PyObject *self, PyObject *args){
	unsigned int InstanceCount = GetInstanceCount();
	return Py_BuildValue("i", InstanceCount);
}
//--------------------------- MISC
 PyObject* LMF_VSyncSet(PyObject *self, PyObject *args){
	int vSyncMode;
	if (!PyArg_ParseTuple(args, "i", &vSyncMode)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	VSyncSet(vSyncMode);
	Py_RETURN_NONE;
}
//--------------------------- DeltaTime
 PyObject* LMF_DeltaTimeSet(PyObject *self, PyObject *args){
	DeltaTimeSet();
	Py_RETURN_NONE;
}
 PyObject* LMF_DeltaTimeGet(PyObject *self, PyObject *args){
	float DeltaTime = DeltaTimeGet();
	return Py_BuildValue("f", DeltaTime);
}
//--------------------------- FPS
 PyObject* LMF_FPSGet  (PyObject *self, PyObject *args){
	float fFPS = FPSGet();
	return Py_BuildValue("f", fFPS);
}
 PyObject* LMF_FPSAvGet(PyObject *self, PyObject *args){
	float fFPSav = FPSAvGet();
	return Py_BuildValue("f", fFPSav);
}
//---------------------------
 PyObject* LMF_lineDraw(PyObject *self, PyObject *args){
	lineDraw();
	Py_RETURN_NONE;
}
//--------------------------- Key Checking
 PyObject* LMF_KeyDown(PyObject *self, PyObject *args){
	int iKeyCode;
	if (!PyArg_ParseTuple(args, "i", &iKeyCode)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	int iKeyDown = KeyDown(iKeyCode);
	return Py_BuildValue("i", iKeyDown);
}
 PyObject* LMF_KeyUp  (PyObject *self, PyObject *args){
	int iKeyCode;
	if (!PyArg_ParseTuple(args, "i", &iKeyCode)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	int iKeyUp = KeyUp(iKeyCode);
	return Py_BuildValue("i", iKeyUp);
}
 PyObject* LMF_KeyPressed (PyObject *self, PyObject *args){
	int iKeyCode;
	if (!PyArg_ParseTuple(args, "i", &iKeyCode)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	int iKeyUp = KeyPressed(iKeyCode);
	return Py_BuildValue("i", iKeyUp);
}
 PyObject* LMF_KeyReleased(PyObject *self, PyObject *args){
	int iKeyCode;
	if (!PyArg_ParseTuple(args, "i", &iKeyCode)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	int iKeyUp = KeyReleased(iKeyCode);
	return Py_BuildValue("i", iKeyUp);
}
//--------------------------- Mouse Position Getting
 PyObject* LMF_MousePosGet(PyObject *self, PyObject *args){
	int iX,iY;
	MousePosGet(iX,iY);
	return Py_BuildValue("ii", iX,iY);
}
 PyObject* LMF_MousePosSet(PyObject *self, PyObject *args){
	int iX,iY;
	if (!PyArg_ParseTuple(args, "ii", &iX, &iY)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	MousePosSet(iX,iY);
	Py_RETURN_NONE;
}
//--------------------------- Mouse Button Checking
 PyObject* LMF_MouseDown     (PyObject *self, PyObject *args){
	int iMouseButton;
	if (!PyArg_ParseTuple(args, "i", &iMouseButton)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	int iMouseState = MouseDown(iMouseButton);
	return Py_BuildValue("i", iMouseState);
}
 PyObject* LMF_MouseUp       (PyObject *self, PyObject *args){
	int iMouseButton;
	if (!PyArg_ParseTuple(args, "i", &iMouseButton)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	int iMouseState = MouseUp(iMouseButton);
	return Py_BuildValue("i", iMouseState);
}
 PyObject* LMF_MousePressed  (PyObject *self, PyObject *args){
	int iMouseButton;
	if (!PyArg_ParseTuple(args, "i", &iMouseButton)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	int iMouseState = MousePressed(iMouseButton);
	return Py_BuildValue("i", iMouseState);
}
 PyObject* LMF_MouseReleased (PyObject *self, PyObject *args){
	int iMouseButton;
	if (!PyArg_ParseTuple(args, "i", &iMouseButton)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	int iMouseState = MouseReleased(iMouseButton);
	return Py_BuildValue("i", iMouseState);
}
//--------------------------- Scrollwheel
 PyObject* LMF_MouseScrollGet(PyObject *self, PyObject *args){
	int iMouseState = MouseScrollGet();
	return Py_BuildValue("i", iMouseState);
}
#if defined(_WIN32)
//--------------------------- Sound
 PyObject* LMF_SoundLoad     (PyObject *self, PyObject *args){
	char* cPath;
	if (!PyArg_ParseTuple(args, "s", &cPath)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	int SoundID = SoundLoad(cPath);
	return Py_BuildValue("i", SoundID);
}
 PyObject* LMF_SoundUnload   (PyObject *self, PyObject *args){
	int SoundID;
	if (!PyArg_ParseTuple(args, "i", &SoundID)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	SoundUnload(SoundID);
	Py_RETURN_NONE;
}
 PyObject* LMF_SoundRestart  (PyObject *self, PyObject *args){
	int bManager;
	if (!PyArg_ParseTuple(args, "i", &bManager)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	SoundRestart(bManager);
	Py_RETURN_NONE;
}
 PyObject* LMF_SoundShutdown (PyObject *self, PyObject *args){
	SoundShutdown();
	Py_RETURN_NONE;
}
//--------------------------- Controls
 PyObject* LMF_SoundPlay  (PyObject *self, PyObject *args){
	int iSoundID;
	int bLoop;
	float fVol,fSpeed;
	if (!PyArg_ParseTuple(args, "iiff", &iSoundID, &bLoop, &fVol, &fSpeed)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	unsigned int iSound = SoundPlay(iSoundID,bLoop,fVol,fSpeed);
	return Py_BuildValue("i", iSound);
}
 PyObject* LMF_SoundPause (PyObject *self, PyObject *args){
	int iSoundID;
	if (!PyArg_ParseTuple(args, "i", &iSoundID)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	SoundPause(iSoundID);
	Py_RETURN_NONE;
}
 PyObject* LMF_SoundResume(PyObject *self, PyObject *args){
	int iSoundID;
	if (!PyArg_ParseTuple(args, "i", &iSoundID)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	SoundResume(iSoundID);
	Py_RETURN_NONE;
}
 PyObject* LMF_SoundStop  (PyObject *self, PyObject *args){
	int iSoundID;
	if (!PyArg_ParseTuple(args, "i", &iSoundID)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	SoundStop(iSoundID);
	Py_RETURN_NONE;
}
//--------------------------- Volume
 PyObject* LMF_SoundVolume(PyObject *self, PyObject *args){
	int iSoundID;
	float fVol;
	if (!PyArg_ParseTuple(args, "if", &iSoundID, &fVol)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	SoundVolume(iSoundID,fVol);
	Py_RETURN_NONE;
}
 PyObject* LMF_SoundSpeed (PyObject *self, PyObject *args){
	int iSoundID;
	float fSpeed;
	if (!PyArg_ParseTuple(args, "if", &iSoundID, &fSpeed)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	SoundSpeed(iSoundID,fSpeed);
	Py_RETURN_NONE;
}
//--------------------------- Advanced features
 PyObject* LMF_SoundLoop      (PyObject *self, PyObject *args){
	int iSoundID;
	if (!PyArg_ParseTuple(args, "i", &iSoundID)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	SoundLoop(iSoundID);
	Py_RETURN_NONE;
}
 PyObject* LMF_SoundVolumeMain(PyObject *self, PyObject *args){
	float fVol;
	if (!PyArg_ParseTuple(args, "f", &fVol)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	SoundVolumeMain(fVol);
	Py_RETURN_NONE;
}
 PyObject* LMF_SoundStopAll   (PyObject *self, PyObject *args){
	SoundStopAll();
	Py_RETURN_NONE;
}
 PyObject* LMF_SoundPauseAll  (PyObject *self, PyObject *args){
	int bPaused;
	if (!PyArg_ParseTuple(args, "i", &bPaused)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	SoundPauseAll(bPaused);
	Py_RETURN_NONE;
}
//--------------------------- Xbox Input
 PyObject* LMF_ControllerAdd        (PyObject *self, PyObject *args){
	unsigned int iControllerID = ControllerAdd();
	return Py_BuildValue("i", iControllerID);
}
 PyObject* LMF_ControllerRemove     (PyObject *self, PyObject *args){
	int iControllerID;
	if (!PyArg_ParseTuple(args, "i", &iControllerID)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	ControllerRemove(iControllerID);
	Py_RETURN_NONE;
}
 PyObject* LMF_ControllerConnected  (PyObject *self, PyObject *args){
	int iControllerID;
	if (!PyArg_ParseTuple(args, "i", &iControllerID)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	int iBConConnected = ControllerConnected(iControllerID);
	return Py_BuildValue("i", iBConConnected);
}						    
 PyObject* LMF_ControllerButton     (PyObject *self, PyObject *args){
	int iControllerID,iButton;
	if (!PyArg_ParseTuple(args, "ii", &iControllerID, &iButton)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	int iButtonValue = ControllerButton(iControllerID,iButton);
	return Py_BuildValue("i", iButtonValue);
}
 PyObject* LMF_ControllerThumbstick (PyObject *self, PyObject *args){
	int iControllerID;
	int bXY,bLR;
	float fValue;
	if (!PyArg_ParseTuple(args, "iii", &iControllerID, &bXY, &bLR)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	int iButtonValue = ControllerThumbstick(iControllerID,bXY,bLR,fValue);
	return Py_BuildValue("if", iButtonValue, fValue);
}
 PyObject* LMF_ControllerTrigger    (PyObject *self, PyObject *args){
	int iControllerID;
	int bLR;
	float fValue;
	if (!PyArg_ParseTuple(args, "ii", &iControllerID, &bLR)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	int iButtonValue = ControllerTrigger(iControllerID,bLR,fValue);
	return Py_BuildValue("if", iButtonValue, fValue);
}
 PyObject* LMF_ControllerVibrate    (PyObject *self, PyObject *args){
	int iControllerID,iLVal,iRVal;
	if (!PyArg_ParseTuple(args, "iii", &iControllerID, &iLVal, &iRVal)) {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	ControllerVibrate(iControllerID,iLVal,iRVal);
	Py_RETURN_NONE;
}
#endif
//--------------------------- Lookup Table
PyMethodDef LMF_Functions[] = 
{
	{"FrameworkInitialise"       ,LMF_FrameworkInitialise       ,METH_VARARGS  ,"Initilise the LM Framework."},
	{"FrameworkUpdate"           ,LMF_FrameworkUpdate           ,METH_VARARGS  ,"Update the framework."},
	{"FrameworkClearScreen"      ,LMF_FrameworkClearScreen      ,METH_VARARGS  ,"Clear the screen."},
	{"FrameworkBGColour"         ,LMF_FrameworkBGColour         ,METH_VARARGS  ,"Change background Colour."},
	{"FrameworkWindowResize"     ,LMF_FrameworkWindowResize     ,METH_VARARGS  ,"Resize the window."},
	{"FrameworkFullscreen"       ,LMF_FrameworkFullscreen       ,METH_VARARGS  ,"Really bad and fake \"Fullscreen\"."},
	{"FrameworkBlendMode"        ,LMF_FrameworkBlendMode        ,METH_VARARGS  ,"Shutdown the framework."},
	{"FrameworkShutdown"         ,LMF_FrameworkShutdown         ,METH_VARARGS  ,"Shutdown the framework."},
					             		    					 			   
	{"CameraMove"                ,LMF_CameraMove                ,METH_VARARGS  ,"Move the Camera."},
	{"CameraRotate"              ,LMF_CameraRotate              ,METH_VARARGS  ,"Rotate the Camera."},
	{"CameraZoom"                ,LMF_CameraZoom                ,METH_VARARGS  ,"Set zoom level of the Camera."},
				                 								 			   
	{"SpriteLoad"                ,LMF_SpriteLoad                ,METH_VARARGS  ,"Load a sprite for use, Returning the ID."},
	{"SpriteMove"                ,LMF_SpriteMove                ,METH_VARARGS  ,"Move a sprite with given ID."},
	{"SpriteRotate"              ,LMF_SpriteRotate              ,METH_VARARGS  ,"Rotate a sprite with given ID."},
	{"SpriteScale"               ,LMF_SpriteScale               ,METH_VARARGS  ,"Scale a sprite with given ID."},
	{"SpriteResize"              ,LMF_SpriteResize              ,METH_VARARGS  ,"Resize a sprite with given ID."},
	{"SpriteUVset"               ,LMF_SpriteUVset               ,METH_VARARGS  ,"Set UV of a sprite with given ID."},
	{"SpriteColour"              ,LMF_SpriteColour              ,METH_VARARGS  ,"Set UV of a sprite with given ID."},
	{"SpriteDraw"                ,LMF_SpriteDraw                ,METH_VARARGS  ,"Draw a sprite with given ID."},
	{"SpriteUnload"              ,LMF_SpriteUnload              ,METH_VARARGS  ,"Unload a sprite with given ID."},
				            											   
	{"ParticleEmitterLoadEmpty"  ,LMF_ParticleEmitterLoadEmpty  ,METH_VARARGS  ,"NULL"},
	{"ParticleEmitterLoad"       ,LMF_ParticleEmitterLoad       ,METH_VARARGS  ,"NULL"},
	{"ParticleEmitterUnload"     ,LMF_ParticleEmitterUnload     ,METH_VARARGS  ,"NULL"},
	{"ParticleEmitterPerStep"    ,LMF_ParticleEmitterPerStep    ,METH_VARARGS  ,"NULL"},
	{"ParticleEmitterSetPosition",LMF_ParticleEmitterSetPosition,METH_VARARGS  ,"NULL"},
	{"ParticleEmitterSetSize"    ,LMF_ParticleEmitterSetSize    ,METH_VARARGS  ,"NULL"},
	{"ParticleEmitterSetColour"  ,LMF_ParticleEmitterSetColour  ,METH_VARARGS  ,"NULL"},
	{"ParticleEmitterSetOffset"  ,LMF_ParticleEmitterSetOffset  ,METH_VARARGS  ,"NULL"},
	{"ParticleEmitterSetRotation",LMF_ParticleEmitterSetRotation,METH_VARARGS  ,"NULL"},
	{"ParticleEmitterDraw"       ,LMF_ParticleEmitterDraw       ,METH_VARARGS  ,"NULL"},

	{"ModelLoad"                 ,LMF_ModelLoad                 ,METH_VARARGS  ,"NULL"},
	{"ModelMove"                 ,LMF_ModelMove                 ,METH_VARARGS  ,"NULL"},
	{"ModelRotate"               ,LMF_ModelRotate               ,METH_VARARGS  ,"NULL"},
	{"ModelScale"                ,LMF_ModelScale                ,METH_VARARGS  ,"NULL"},
	{"ModelResize"               ,LMF_ModelResize               ,METH_VARARGS  ,"NULL"},
	{"ModelDraw"                 ,LMF_ModelDraw                 ,METH_VARARGS  ,"NULL"},
	{"ModelUnload"               ,LMF_ModelUnload               ,METH_VARARGS  ,"NULL"},
				                 								 			   
	{"FontLoad"                  ,LMF_FontLoad                  ,METH_VARARGS  ,"NULL"},
	{"FontUnload"                ,LMF_FontUnload                ,METH_VARARGS  ,"NULL"},
	{"FontColour"                ,LMF_FontColour                ,METH_VARARGS  ,"NULL"},

	{"DrawString"                ,LMF_DrawString                ,METH_VARARGS  ,"NULL"},
	{"DrawInt"                   ,LMF_DrawInt                   ,METH_VARARGS  ,"NULL"},
	{"DrawFloat"                 ,LMF_DrawFloat                ,METH_VARARGS  ,"NULL"},
				                 								 			   
	{"ShaderLoad"                ,LMF_ShaderLoad                ,METH_VARARGS  ,"NULL"},
	{"ShaderUse"                 ,LMF_ShaderUse                 ,METH_VARARGS  ,"NULL"},
	{"ShaderUnload"              ,LMF_ShaderUnload              ,METH_VARARGS  ,"NULL"},
				                 								 			   
	{"TextureShaderID"           ,LMF_TextureShaderID           ,METH_VARARGS  ,"NULL"},
	{"DefaultFontID"             ,LMF_DefaultFontID             ,METH_VARARGS  ,"NULL"},
	{"GetInstanceCount"          ,LMF_GetInstanceCount          ,METH_VARARGS  ,"NULL"},
				                 								 			   
	{"VSyncSet"                  ,LMF_VSyncSet                  ,METH_VARARGS  ,"NULL"},
				                 								 			   
	{"DeltaTimeSet"              ,LMF_DeltaTimeSet              ,METH_VARARGS  ,"NULL"},
	{"DeltaTimeGet"              ,LMF_DeltaTimeGet              ,METH_VARARGS  ,"NULL"},
				                 								 			   
	{"FPSGet"                    ,LMF_FPSGet                    ,METH_VARARGS  ,"NULL"},
	{"FPSAvGet"                  ,LMF_FPSAvGet                  ,METH_VARARGS  ,"NULL"},
				                 								 			   
	{"lineDraw"                  ,LMF_lineDraw                  ,METH_VARARGS  ,"NULL"},
				                 								 			   
	{"KeyDown"                   ,LMF_KeyDown                   ,METH_VARARGS  ,"NULL"},
	{"KeyUp"                     ,LMF_KeyUp                     ,METH_VARARGS  ,"NULL"},
	{"KeyPressed"                ,LMF_KeyPressed                ,METH_VARARGS  ,"NULL"},
	{"KeyReleased"               ,LMF_KeyReleased               ,METH_VARARGS  ,"NULL"},
				                 								 			   
	{"MousePosGet"               ,LMF_MousePosGet               ,METH_VARARGS  ,"NULL"},
	{"MousePosSet"               ,LMF_MousePosSet               ,METH_VARARGS  ,"NULL"},
				                 								 			   
	{"MouseDown"                 ,LMF_MouseDown                 ,METH_VARARGS  ,"NULL"},
	{"MouseUp"                   ,LMF_MouseUp                   ,METH_VARARGS  ,"NULL"},
	{"MousePressed"              ,LMF_MousePressed              ,METH_VARARGS  ,"NULL"},
	{"MouseReleased"             ,LMF_MouseReleased             ,METH_VARARGS  ,"NULL"},
				                 								 			   
	{"MouseScrollGet"            ,LMF_MouseScrollGet            ,METH_VARARGS  ,"NULL"},
	#if defined(_WIN32)			                 								 			   
	{"SoundLoad"                 ,LMF_SoundLoad                 ,METH_VARARGS  ,"NULL"},
	{"SoundRemove"               ,LMF_SoundUnload               ,METH_VARARGS  ,"NULL"},
	{"SoundRestart"              ,LMF_SoundRestart              ,METH_VARARGS  ,"NULL"},
	{"SoundShutdown"             ,LMF_SoundShutdown             ,METH_VARARGS  ,"NULL"},
				                 								 			   
	{"SoundPlay"                 ,LMF_SoundPlay                 ,METH_VARARGS  ,"NULL"},
	{"SoundPause"                ,LMF_SoundPause                ,METH_VARARGS  ,"NULL"},
	{"SoundResume"               ,LMF_SoundResume               ,METH_VARARGS  ,"NULL"},
	{"SoundStop"                 ,LMF_SoundStop                 ,METH_VARARGS  ,"NULL"},
				                 								 			   
	{"SoundVolume"               ,LMF_SoundVolume               ,METH_VARARGS  ,"NULL"},
	{"SoundSpeed"                ,LMF_SoundSpeed                ,METH_VARARGS  ,"NULL"},
				                 								 			   
	{"SoundLoop"                 ,LMF_SoundLoop                 ,METH_VARARGS  ,"NULL"},
	{"SoundVolumeMain"           ,LMF_SoundVolumeMain           ,METH_VARARGS  ,"NULL"},
	{"SoundStopAll"              ,LMF_SoundStopAll              ,METH_VARARGS  ,"NULL"},
	{"SoundPauseAll"             ,LMF_SoundPauseAll             ,METH_VARARGS  ,"NULL"},
    
	{"ControllerAdd"             ,LMF_ControllerAdd             ,METH_VARARGS  ,"NULL"},
	{"ControllerRemove"          ,LMF_ControllerRemove          ,METH_VARARGS  ,"NULL"},
	{"ControllerConnected"       ,LMF_ControllerConnected       ,METH_VARARGS  ,"NULL"},
	{"ControllerButton"          ,LMF_ControllerButton          ,METH_VARARGS  ,"NULL"},
	{"ControllerThumbstick"      ,LMF_ControllerThumbstick      ,METH_VARARGS  ,"NULL"},
	{"ControllerTrigger"         ,LMF_ControllerTrigger         ,METH_VARARGS  ,"NULL"},
	{"ControllerVibrate"         ,LMF_ControllerVibrate         ,METH_VARARGS  ,"NULL"},
    #endif
    {NULL, NULL, 0, NULL}
};
//--------------------------- Python Functions
 bool LMF_PyInitialise(){
	bool returnb = false;
	Py_Initialize();
	if (Py_IsInitialized()){
		PyObject* sysPath = PySys_GetObject((char*)"path");
		PyList_Append(sysPath, PyString_FromString("./Scripts"));
		Py_InitModule("LMF",LMF_Functions);
		returnb = true;
	}else{
		printf("Something broke with python...\n");
	}
	return returnb;
}
 bool LMF_PyInitialise(int argc, char* argv[]){
	bool returnb = false;
	if (LMF_PyInitialise()){
		PySys_SetArgv(argc, argv);
		returnb = true;
	}
	return returnb;
}
PyObject* LMF_ImportPythonModule( const char* a_pyModuleName ){
	PyObject* pObjName= PyString_FromString(a_pyModuleName);
	PyObject* pModule = PyImport_Import(pObjName);
	if (!pModule){
        PyErr_Print();
        std::cout << stderr << "Failed to load \"" << a_pyModuleName << "\"\n" << std::endl;
    }
    Py_DECREF(pObjName);
	return pModule;
}
void LMF_ReloadPythonModule( PyObject* a_pModule){
	PyObject* pModule = PyImport_ReloadModule(a_pModule);
	if (pModule == NULL){
		std::cout << stderr << "Failed to reload, Python returned NULL.\n" << std::endl;
		return;
	}
	a_pModule = pModule;
}
bool LMF_CallPythonFunction(PyObject* a_pModule, char* cs_FunctionName){
	bool bSuccess = false;
	PyObject* pFunction = GetHandleToPythonFunction( a_pModule, cs_FunctionName);
	if( pFunction ){
		PyObject* pReturnValue = CallPythonFunction( pFunction, nullptr );
		if( pReturnValue ){
			bSuccess = true;
		}
		Py_XDECREF(pFunction);	
	}
	return bSuccess;
}
bool LMF_CallPythonFunction(PyObject* a_pModule, char* cs_FunctionName,char* VarTypes,...){
	bool bSuccess = false;
	//This takes the arguments and converts to python args to pass
	int stringLength = strlen(VarTypes);
	va_list vaItems;
	va_start(vaItems,VarTypes);
	PyObject* pArgs;

	if (stringLength > 0){
		pArgs = PyTuple_New(stringLength);
		for (int i = 0; i < stringLength; i++){
			int iChar = VarTypes[i];
			switch (iChar){
			case 98: case 66://b B
				PyTuple_SetItem( pArgs, i, PyBool_FromLong( va_arg(vaItems,bool) ) );
				break;
			case 105: case 73://i I
				PyTuple_SetItem( pArgs, i, PyInt_FromLong( va_arg(vaItems,int) ) );
				break;
			case 108: case 76://l L
				PyTuple_SetItem( pArgs, i, PyLong_FromLong( va_arg(vaItems,long) ) );
				break;
			case 102: case 70://f F
			case 100: case 68://d D
				PyTuple_SetItem( pArgs, i, PyFloat_FromDouble(va_arg(vaItems,double) ) );
				break;
			case 99: case 67://c C
				PyTuple_SetItem( pArgs, i, Py_BuildValue("c",va_arg(vaItems,char) ) );
				break;
			case 115: case 83://s S
				PyTuple_SetItem( pArgs, i, PyString_FromString( va_arg(vaItems,char*) ) );
				break;
			}
		}
	}
	va_end(vaItems);
	//End of passer
	PyObject* pFunction = GetHandleToPythonFunction( a_pModule, cs_FunctionName);
	if( pFunction ){
		PyObject* pReturnValue = CallPythonFunction( pFunction, pArgs );
		if( pReturnValue ){
			bSuccess = true;
		}
		Py_XDECREF(pFunction);	
	}
	return bSuccess;
}
//---------------------------
//------ Luke Monaghan ------
//---------------------------