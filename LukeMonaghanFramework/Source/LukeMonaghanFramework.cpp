#include "LukeMonaghanFramework.h"
#include "FrameworkWrapper.h"
#include "Common/Utilities.h"
//--------------------------- Framework Class
FW_Wrapper FrameworkDLL;
//--------------------------- Framework
bool FrameworkInitialise(char* title, unsigned int width, unsigned int height, bool fullscreen, float fLeftOff, float fRightOff, float fBottomOff, float fTopOff){
	return FrameworkDLL.Initialise(title, width, height, fullscreen, fLeftOff, fRightOff, fBottomOff, fTopOff);
}
bool FrameworkUpdate(){
	return FrameworkDLL.Update();
}
void FrameworkClearScreen(){
	FrameworkDLL.ClearScreen();
}
void FrameworkBGColour(float r,float g,float b,float a){
	FrameworkDLL.BGColour(Vector4(r,g,b,a));
}
void FrameworkWindowResize(int width, int height){
	FrameworkDLL.ResizeWindow(width,height);
}
void FrameworkFullscreen(bool fullscr){
	FrameworkDLL.Fullscreen(fullscr);
}
void FrameworkBlendMode(int i_Begin, int i_Final, int i_Equation){
	FrameworkDLL.BlendMode(i_Begin,i_Final,i_Equation);
}
void FrameworkShutdown(){
	FrameworkDLL.Shutdown();
}
//--------------------------- Camera
void CameraMove(float xoff, float yoff){
	FrameworkDLL.Move(xoff,yoff);
}
void CameraRotate(float angle){
	FrameworkDLL.Rotate(angle);
}
void CameraZoom(float amount){
	FrameworkDLL.Zoom(amount);
}
//--------------------------- Image
int  SpriteLoad  (char* path, int width, int height,int xoffset, int yoffset){
	return FrameworkDLL.SpriteCreate(path,width,height,xoffset,yoffset);
}
void SpriteMove  (int SpriteID, float x, float y, float depth){
	FrameworkDLL.SpriteMove(SpriteID,x,y,depth);
}
void SpriteRotate(int SpriteID, float angle, bool add){
	FrameworkDLL.SpriteRotate(SpriteID,angle);
}
void SpriteScale (int SpriteID, float xscale, float yscale){
	FrameworkDLL.SpriteScale(SpriteID,xscale,yscale);
}
void SpriteResize(int SpriteID, int width , int height){
	FrameworkDLL.SpriteResize(SpriteID,width,height);
}
void SpriteUVset(int SpriteID,float uMin, float vMin, float uMax, float vMax){
	FrameworkDLL.SpriteUVset(SpriteID,uMin,vMin,uMax,vMax);
}
void SpriteColour(int SpriteID, float f_Red, float f_Green, float f_Blue, float f_Alpha){
	FrameworkDLL.SpriteColour(SpriteID,f_Red,f_Green,f_Blue,f_Alpha);
}

void SpriteDraw  (int SpriteID,bool Camera0_world1){
	FrameworkDLL.SpriteDraw(SpriteID, Camera0_world1);
}
void SpriteUnload(int SpriteID){
	FrameworkDLL.SpriteRemove(SpriteID);
}
//--------------------------- Particle Emitters
unsigned int ParticleEmitterLoad(int SpriteID){
	return FrameworkDLL.ParticleEmitterLoad(SpriteID);
}
unsigned int ParticleEmitterLoad(int SpriteID, float startx, float starty,float startdepth, float endx, float endy, float enddepth, float lifetimeinsec){
	return FrameworkDLL.ParticleEmitterLoad(SpriteID,startx,starty,startdepth,endx,endy,enddepth,lifetimeinsec);
}

void ParticleEmitterUnload(unsigned int EmitterID){
	FrameworkDLL.ParticleEmitterUnload(EmitterID);
}

void ParticleEmitterPerStep(unsigned int EmitterID,float amount){
	FrameworkDLL.ParticleEmitterPerStep(EmitterID,amount);
}
void ParticleEmitterSetPosition(unsigned int EmitterID,float x, float y, float depth, bool start0_end1){
	FrameworkDLL.ParticleEmitterSetPosition(EmitterID,x,y,depth,start0_end1);
}
void ParticleEmitterSetSize(unsigned int EmitterID,float Width, float Height, bool start0_end1){
	FrameworkDLL.ParticleEmitterSetSize(EmitterID,Width,Height,start0_end1);
}
void ParticleEmitterSetColour(unsigned int EmitterID, float f_Red, float f_Green, float f_Blue, float f_Alpha, bool start0_end1){
	FrameworkDLL.ParticleEmitterSetColour(EmitterID,f_Red,f_Green,f_Blue,f_Alpha,start0_end1);
}
void ParticleEmitterSetOffset(unsigned int EmitterID, int i_XOffset, int i_YOffset){
	FrameworkDLL.ParticleEmitterSetOffset(EmitterID,i_XOffset,i_YOffset);
}
void ParticleEmitterSetRotation(unsigned int EmitterID, float f_AmountPerStep,bool start0_end1){
	FrameworkDLL.ParticleEmitterSetRotation(EmitterID,f_AmountPerStep, start0_end1);
}

void ParticleEmitterDraw(int EmitterID,bool Camera0_world1){
	FrameworkDLL.ParticleEmitterDraw(EmitterID, Camera0_world1);
}
//--------------------------- Model
int  ModelLoad  (char* path){
	return FrameworkDLL.ModelCreate(path);
}
void ModelMove  (int ModelID, float x, float y, float depth){
	FrameworkDLL.ModelMove(ModelID,x,y,depth);
}
void ModelRotate(int ModelID, float angle, bool add){
	FrameworkDLL.ModelRotate(ModelID,angle);
}
void ModelScale (int ModelID, float xscale, float yscale){
	FrameworkDLL.ModelScale(ModelID,xscale,yscale);
}
void ModelResize(int ModelID, int width , int height){
	FrameworkDLL.ModelResize(ModelID,width,height);
}
void ModelDraw  (int ModelID,bool Camera0_world1){
	FrameworkDLL.ModelDraw(ModelID, Camera0_world1);
}
void ModelUnload(int ModelID){
	FrameworkDLL.ModelRemove(ModelID);
}
//--------------------------- Fonts
int  FontLoad(char* path){
	return FrameworkDLL.FontLoad(path);
}
void FontUnload(int FontID){
	FrameworkDLL.FontUnload(FontID);
}
void FontColour(int FontID, float f_Red, float f_Green, float f_Blue, float f_Alpha){
	FrameworkDLL.FontColour(FontID,f_Red,f_Green,f_Blue,f_Alpha);
}
//--------------------------- Text
void DrawString(int FontID,char* string,float x, float y,bool Camera0_world1,float depth,bool center){
	FrameworkDLL.DrawString(FontID,string,x,y,depth,center, Camera0_world1);			
}
void DrawInt   (int FontID,int Value,float x, float y,bool Camera0_world1,float depth,bool center){
	FrameworkDLL.DrawInt(FontID,Value,x,y,depth,center, Camera0_world1);
}
void DrawFloat (int FontID,float Value ,float x, float y,bool Camera0_world1,float depth,bool center){
	FrameworkDLL.DrawFloat(FontID,Value,x,y,depth,center, Camera0_world1);
}
//--------------------------- ID's
int  GetDefaultShaderID(){
	return FrameworkDLL.TexID();
}
int  GetDefaultFontID(){
	return FrameworkDLL.FontID();
}
int  GetInstanceCount(){
	return FrameworkDLL.InstanceCount();
}
//--------------------------- Shaders
int  ShaderLoad(char* relativepath){
	return FrameworkDLL.ShaderLoad(relativepath);
}
void ShaderUse (int ShaderID){
	FrameworkDLL.ShaderUse(ShaderID);
}
void ShaderUnload(int ShaderID){
	FrameworkDLL.ShaderUnload(ShaderID);
}
//--------------------------- VSync
void VSyncSet(int mode){
	VSync(mode);
}
//--------------------------- DeltaTime
void DeltaTimeSet(){
	SetDeltaTime();
}
float DeltaTimeGet(){
	return GetDeltaTime();
}
float FPSGet(){
	return GetFPS();
}
float FPSAvGet(){
	return GetFPSAv();
}
//--------------------------- Drawing Lines
void lineDraw(){
	printf("THIS DOES NOTHING YET!\n");
}
//--------------------------- Key Checking
int KeyDown(int key){
	return KeyDownGet(key);
}
int KeyUp(int key){
	return KeyUpGet(key);
}
int KeyPressed(int key){
	return KeyPressedGet(key);
}
int KeyReleased(int key){
	return KeyReleasedGet(key);
}
//--------------------------- Mouse Get/Set
void MousePosGet(int &x, int &y){
	MousePositionGet(FrameworkDLL.Framework,x,y);
}
void MousePosSet(int  x, int  y){
	MousePositionSet(FrameworkDLL.Framework,x,y);
}
//--------------------------- Mouse Checking
int MouseDown(int MouseButton){
	return MouseDownGet(MouseButton);
}
int MouseUp(int MouseButton){
	return MouseUpGet(MouseButton);
}
int MousePressed(int MouseButton){	
	return MousePressedGet(MouseButton);
}
int MouseReleased(int MouseButton){
	return MouseReleasedGet(MouseButton);
}
int MouseScrollGet(){
	return MouseScrollWheelGet();
}
#if defined(_WIN32)
//--------------------------- Sound
unsigned int SoundLoad(char* path){
	return FrameworkDLL.SoundSourceAdd(path);
}
void SoundUnload(unsigned int SoundSourceID){
	FrameworkDLL.SoundSourceRemove(SoundSourceID);
}
void SoundRestart(bool sndmngr){
	FrameworkDLL.SoundRestart(sndmngr);
}
void SoundShutdown(){
	FrameworkDLL.SoundShutdown();
}
//--------------------------- Controls
unsigned int SoundPlay(unsigned int SoundSourceID,bool loop,float volume, float speed){
	return FrameworkDLL.SoundPlay(SoundSourceID,loop,volume,speed);
}
void SoundPause(unsigned int SoundInstanceID){
	FrameworkDLL.SoundPause(SoundInstanceID);
}
void SoundResume(unsigned int SoundInstanceID){
	FrameworkDLL.SoundResume(SoundInstanceID);
}
void SoundStop(unsigned int SoundInstanceID){
	FrameworkDLL.SoundStop(SoundInstanceID);
}
//--------------------------- Volume
void SoundVolume(unsigned int SoundInstanceID,float value){
	FrameworkDLL.SoundVolume(SoundInstanceID,value);
}
void SoundSpeed(unsigned int SoundInstanceID,float value){
	FrameworkDLL.SoundSpeed(SoundInstanceID,value);
}
//--------------------------- Advanced features
void SoundLoop(unsigned int SoundInstanceID){
	FrameworkDLL.SoundLoop(SoundInstanceID);
}
void SoundVolumeMain(float value){
	FrameworkDLL.SoundMainVolume(value);
}
void SoundStopAll(){
	FrameworkDLL.SoundStopAll();
}
void SoundPauseAll(bool paused){
	FrameworkDLL.SoundPauseAll(paused);
}
//--------------------------- Xbox Input
unsigned int ControllerAdd(){
	return FrameworkDLL.ControllerAdd();
}
void ControllerRemove(unsigned int ControllerID){
	FrameworkDLL.ControllerRemove(ControllerID);
}
bool ControllerConnected(unsigned int ControllerID){
	return FrameworkDLL.ControllerConnected(ControllerID);
}	    
bool ControllerButton(unsigned int ControllerID,int ButtonID){
	return FrameworkDLL.ControllerButton(ControllerID,ButtonID);
}
bool ControllerThumbstick(unsigned int ControllerID,bool L0_R1,bool X0_Y1,float &ReturnVal){
	return FrameworkDLL.ControllerThumbstick(ControllerID,L0_R1,X0_Y1,ReturnVal);
}
bool ControllerTrigger(unsigned int ControllerID,bool L0_R1,float &ReturnVal){
	return FrameworkDLL.ControllerTrigger(ControllerID,L0_R1,ReturnVal);
}
void ControllerVibrate(unsigned int ControllerID,unsigned short leftamount,unsigned short rightamount){
	return FrameworkDLL.ControllerVibrate(ControllerID,leftamount,rightamount);
}
#endif