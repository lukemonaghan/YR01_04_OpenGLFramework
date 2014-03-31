//---------------------------
//------ Luke Monaghan ------
//---------------------------
#ifndef FW_WRAPPER_H_
#define FW_WRAPPER_H_
//--------------------------- Includes
#include "Common/Framework.h"
#include "Common/Managers/SquareManager.h"
#include "Common/Managers/ModelManager.h"
#include "Common/Managers/ShaderManager.h"
#include "Common/Managers/FontManager.h"
#include "Common/Managers/SoundManager.h"
#include "Common/Managers/ParticleManager.h"
#include"Common/XboxController.h"
//--------------------------- Class
class FW_Wrapper{ 
public:
	FW_Wrapper(){};
	bool Initialise(char* title, unsigned int width, unsigned int height, bool fullscreen,float fLeftOff, float fRightOff, float fBottomOff, float fTopOff);
	bool Update();
	void ClearScreen();
	void BGColour(Vector4 Colour);
	void ResizeWindow(unsigned int width,unsigned int height);
	void Fullscreen(bool fullscr);
	void BlendMode(int i_Begin, int i_Final, int i_Equation);
	void Shutdown();
//--------------------------- Camera
	void Move(float x, float y);
	void Rotate(float angle);
	void Zoom(float amount);
//--------------------------- Image
	int  SpriteCreate(char* path, int width, int height,int xoffset, int yoffset);

	void SpriteMove  (int SpriteID, float x, float y, float depth);
	void SpriteRotate(int SpriteID, float angle);
	void SpriteScale (int SpriteID, float xscale, float yscale);
	void SpriteResize(int SpriteID, int width , int height);
	void SpriteUVset (int SpriteID, float uMin, float vMin, float uMax, float vMax);
	void SpriteColour(int SpriteID, float f_Red, float f_Green, float f_Blue, float f_Alpha);

	void SpriteDraw  (int SpriteID,bool Camera0_world1);
	void SpriteRemove(int SpriteID);
//--------------------------- Particle Emitters
	unsigned int ParticleEmitterLoad(int SpriteID);
	unsigned int ParticleEmitterLoad(int SpriteID, float startx, float starty,float startdepth, float endx, float endy, float enddepth, float lifetimeinsec);
	void         ParticleEmitterUnload(unsigned int EmitterID);
	void         ParticleEmitterPerStep(unsigned int EmitterID,float amount);
	void         ParticleEmitterSetPosition(unsigned int EmitterID,float x     , float y     , float depth, bool start0_end1);
	void         ParticleEmitterSetSize    (unsigned int EmitterID,float Width , float Height             , bool start0_end1);
	void         ParticleEmitterSetColour  (unsigned int EmitterID, float f_Red, float f_Green, float f_Blue, float f_Alpha, bool start0_end1);
	void         ParticleEmitterSetOffset  (unsigned int EmitterID, int i_XOffset, int i_YOffset);
	void         ParticleEmitterSetRotation(unsigned int EmitterID, float f_AmountPerStep,bool start0_end1);
	
	void         ParticleEmitterDraw(int EmitterID,bool Camera0_world1);
//--------------------------- Model
	int  ModelCreate(char* path);
	void ModelMove  (int ModelID, float x, float y, float depth);
	void ModelRotate(int ModelID, float angle);
	void ModelScale (int ModelID, float xscale, float yscale);
	void ModelResize(int ModelID, int width, int height);
	void ModelDraw  (int ModelID,bool Camera0_world1);
	void ModelRemove(int ModelID);
//--------------------------- Fonts
	int  FontLoad(char* path);
	void FontUnload(int FontID);
	void FontColour(int FontID, float f_Red, float f_Green, float f_Blue, float f_Alpha);
//--------------------------- Drawing Text
	void DrawString(int FontID,char* string,float x, float y,float depth,bool center,bool Camera0_world1);
	void DrawInt   (int FontID,int Value   ,float x, float y,float depth,bool center,bool Camera0_world1);
	void DrawFloat (int FontID,float Value ,float x, float y,float depth,bool center,bool Camera0_world1);
//--------------------------- Shaders
	int  ShaderLoad(char* relativepath);
	void ShaderUse (int ShaderID);
	void ShaderUnload(int ShaderID);
//--------------------------- Sound
    #if defined(_WIN32)
	unsigned int SoundSourceAdd(char* path);
	void         SoundSourceRemove(unsigned int SoundSourceID);
	void		 SoundRestart(bool sndmngr);
	void		 SoundShutdown();
//--------------------------- Controls
	unsigned int SoundPlay(unsigned int SoundSourceID,bool loop,float volume, float speed);
	void         SoundPause(unsigned int SoundInstanceID);
	void         SoundResume(unsigned int SoundInstanceID);
	void         SoundStop(unsigned int SoundInstanceID);
//--------------------------- Volume
	void		 SoundVolume(unsigned int SoundInstanceID,float value);
	void		 SoundSpeed (unsigned int SoundInstanceID,float value);
//--------------------------- Advanced features
	void		 SoundLoop(unsigned int SoundInstanceID);
	void		 SoundMainVolume(float value);
	void		 SoundStopAll();
	void		 SoundPauseAll(bool paused);
//--------------------------- Xbox Input
	unsigned int ControllerAdd();
	void ControllerRemove(unsigned int ID);

	bool		 ControllerConnected (unsigned int ControllerID);
			    
	bool		 ControllerButton    (unsigned int ControllerID,int ButtonID);
	bool		 ControllerThumbstick(unsigned int ControllerID,bool L0_R1,bool X0_Y1,float &ReturnVal);
	bool		 ControllerTrigger   (unsigned int ControllerID,bool L0_R1,float &ReturnVal);
	void		 ControllerVibrate   (unsigned int ControllerID,unsigned short leftamount,unsigned short rightamount);
    #endif
//--------------------------- Get default ID's
	int  TexID() {return TextureShaderID;}
	int  FontID(){return DefaultFontID;}
	int  InstanceCount(){return iInstanceCount;}
//--------------------------- MISC

	cFramework* Framework;
private:
	int TextureShaderID,DefaultFontID,iInstanceCount;

	cParticleManager  ParticleManager;
	cSquareManager      SpriteManager;
	cModelManager        ModelManager;
	cShaderManager      ShaderManager;
	cFontManager          FontManager;
    #if defined(_WIN32)
	cSoundManager	     SoundManager;
	cXboxController*   Controllers[4];
    #endif
};

#endif