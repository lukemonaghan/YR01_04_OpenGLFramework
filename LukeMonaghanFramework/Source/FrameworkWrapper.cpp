//---------------------------
//------ Luke Monaghan ------
//---------------------------
#include "FrameworkWrapper.h"
#include "Common/Drawables/Square.h"
#include "Common/Utilities.h"
#include <iostream>
//------------------------------------------------------------------------------------------------------------------------------------------------------------ Framework
bool FW_Wrapper::Initialise(char* cs_Title, unsigned int ui_Width, unsigned int ui_Height, bool b_Fullscreen,float fLeftOff, float fRightOff, float fBottomOff, float fTopOff){
	if (Framework == nullptr){
		Framework = new cFramework( cs_Title, ui_Width, ui_Height, b_Fullscreen, fLeftOff, fRightOff, fBottomOff, fTopOff);
		std::cout << "Framework Created" << std::endl;
        #if defined(_WIN32)
		SoundManager.Init();
        #endif
		SpriteManager.Initialise();
		ModelManager.Initialise();
		FontManager.Initialise();
		ParticleManager.Initialise();
		TextureShaderID = ShaderManager.Create("./Shaders/SimpleTexture");
		DefaultFontID = FontManager.Create("./Fonts/arial.fnt");
		ShaderUse(TextureShaderID);
	}
	if (Framework != nullptr){
		return true;
	}
	return false;
}
bool FW_Wrapper::Update(){
	iInstanceCount  = SpriteManager  .Draw(glGetUniformLocation(TextureShaderID,"MVP"),Framework);
	iInstanceCount += ModelManager   .Draw(glGetUniformLocation(TextureShaderID,"MVP"),Framework);
	iInstanceCount += FontManager    .Draw(glGetUniformLocation(TextureShaderID,"MVP"),Framework);
	iInstanceCount += ParticleManager.Draw(glGetUniformLocation(TextureShaderID,"MVP"),Framework);
	ParticleManager.Update(GetDeltaTime());
	if (Framework->Update()){
	return true;
	}
	return false;
}
void FW_Wrapper::ClearScreen(){
	Framework->Clear();
}
void FW_Wrapper::BGColour(Vector4 Colour){
	Framework->ColourBackground(Colour);
}
void FW_Wrapper::ResizeWindow(unsigned int ui_Width, unsigned int ui_Height){
	Framework->ResizeWindow(ui_Width,ui_Height);
}
void FW_Wrapper::Fullscreen(bool b_Fullscr){
	Framework->Fullscreen(b_Fullscr);
}
void FW_Wrapper::BlendMode(int i_Begin, int i_Final, int i_Equation){
	Framework->BlendMode(i_Begin,i_Final,i_Equation);
}

void FW_Wrapper::Shutdown(){
	ShaderUnload(TextureShaderID);
	FontUnload(DefaultFontID);
    #if defined(_WIN32)
	SoundShutdown();
    #endif
	SpriteManager.Shutdown();
	ModelManager.Shutdown();
	FontManager.Shutdown();
	ParticleManager.Shutdown();
	Framework->Exit();
	delete Framework;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------ Cameras
void FW_Wrapper::Move(float f_x, float f_y){
	Framework->Translate(f_x,f_y);
}
void FW_Wrapper::Rotate(float f_Angle){
	Framework->Rotate(f_Angle);
}
void FW_Wrapper::Zoom(float f_Amount){
	Framework->Scale(f_Amount);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------ Image
int  FW_Wrapper::SpriteCreate(char* cs_Path, int i_Width, int i_Height,int i_XOffset, int i_YOffset){
	return SpriteManager.Create(cs_Path,i_Width,i_Height,i_XOffset,i_YOffset);
}
void FW_Wrapper::SpriteMove  (int i_SpriteID, float f_x, float f_y, float f_Depth){
	SpriteManager.Move(i_SpriteID,f_x,f_y,f_Depth);
}
void FW_Wrapper::SpriteRotate(int i_SpriteID, float f_Angle){
	SpriteManager.Rotate(i_SpriteID,f_Angle);
}
void FW_Wrapper::SpriteScale (int i_SpriteID, float xscale, float yscale){
	SpriteManager.Scale(i_SpriteID,xscale,yscale);
}
void FW_Wrapper::SpriteResize(int i_SpriteID, int width, int height){
	SpriteManager.Resize(i_SpriteID,width,height);
}
void FW_Wrapper::SpriteUVset (int i_SpriteID, float uMin, float vMin, float uMax, float vMax){
	SpriteManager.UV(i_SpriteID,uMin,vMin,uMax,vMax);
}
void FW_Wrapper::SpriteColour(int i_SpriteID, float f_Red, float f_Green, float f_Blue, float f_Alpha){
	SpriteManager.Colour(i_SpriteID,f_Red,f_Green,f_Blue,f_Alpha);
}
void FW_Wrapper::SpriteDraw  (int SpriteID,bool Camera0_world1){
	SpriteManager.AddtoQueue(SpriteID,Camera0_world1);
}
void FW_Wrapper::SpriteRemove(int SpriteID){
	SpriteManager.Remove(SpriteID);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------ Particle Emitters
unsigned int FW_Wrapper::ParticleEmitterLoad(int SpriteID){
	cSquare TempSquare = SpriteManager.GetcSquare(SpriteID);
	return ParticleManager.CreateEmitter(&TempSquare);
}
unsigned int FW_Wrapper::ParticleEmitterLoad(int SpriteID, float startx, float starty,float startdepth, float endx, float endy, float enddepth, float lifetimeinsec){
	cSquare TempSquare = SpriteManager.GetcSquare(SpriteID);
	return ParticleManager.CreateEmitter(&TempSquare, startx, starty, startdepth, endx, endy, enddepth, lifetimeinsec);
}
void FW_Wrapper::ParticleEmitterUnload(unsigned int EmitterID){
	ParticleManager.DestroyEmitter(EmitterID);
}
void FW_Wrapper::ParticleEmitterPerStep(unsigned int EmitterID,float amount){
	ParticleManager.SetParticlesPerStep(EmitterID,amount);
}
void FW_Wrapper::ParticleEmitterSetPosition(unsigned int EmitterID, float x, float y, float depth, bool start0_end1){
	ParticleManager.SetPosition(EmitterID,x,y,depth,start0_end1);
}
void FW_Wrapper::ParticleEmitterSetSize(unsigned int EmitterID, float Width, float Height, bool start0_end1){
	ParticleManager.SetSize(EmitterID,Width,Height,start0_end1);
}
void FW_Wrapper::ParticleEmitterSetColour(unsigned int EmitterID, float f_Red, float f_Green, float f_Blue, float f_Alpha, bool start0_end1){
	ParticleManager.SetColour(EmitterID,f_Red,f_Green,f_Blue,f_Alpha,start0_end1);
}
void FW_Wrapper::ParticleEmitterSetOffset(unsigned int EmitterID, int i_XOffset, int i_YOffset){
	ParticleManager.SetOffset(EmitterID,i_XOffset,i_YOffset);
}
void FW_Wrapper::ParticleEmitterSetRotation(unsigned int EmitterID, float f_AmountPerStep,bool start0_end1){
	ParticleManager.SetRotation(EmitterID,f_AmountPerStep,start0_end1);
}

void FW_Wrapper::ParticleEmitterDraw(int EmitterID,bool Camera0_world1){
	ParticleManager.AddtoQueue(EmitterID,Camera0_world1);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------ Model
int  FW_Wrapper::ModelCreate(char* path){
	return ModelManager.Create(path);
}
void FW_Wrapper::ModelMove  (int ModelID, float x, float y, float depth){
	ModelManager.Move(ModelID,x,y,depth);
}
void FW_Wrapper::ModelRotate(int ModelID, float angle){
	ModelManager.Rotate(ModelID,angle);
}
void FW_Wrapper::ModelScale (int ModelID, float xscale, float yscale){
	ModelManager.Scale(ModelID,xscale,yscale);
}
void FW_Wrapper::ModelResize(int ModelID, int width, int height){
	ModelManager.Resize(ModelID,width,height);
}
void FW_Wrapper::ModelDraw  (int ModelID,bool Camera0_world1){
	ModelManager.AddtoQueue(ModelID,Camera0_world1);
}
void FW_Wrapper::ModelRemove(int ModelID){
	ModelManager.Remove(ModelID);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------ Fonts
int  FW_Wrapper::FontLoad(char* path){
	return FontManager.Create(path);
}
void FW_Wrapper::FontUnload(int FontID){
	FontManager.Remove(FontID);
}
void FW_Wrapper::FontColour(int FontID, float f_Red, float f_Green, float f_Blue, float f_Alpha){
	FontManager.Colour(FontID,f_Red,f_Green,f_Blue,f_Alpha);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------ Shaders
int  FW_Wrapper::ShaderLoad(char* relativepath){
	return ShaderManager.Create(relativepath);
}
void FW_Wrapper::ShaderUse (int ShaderID){
	ShaderManager.Use(ShaderID);
}
void FW_Wrapper::ShaderUnload(int ShaderID){
	ShaderManager.Remove(ShaderID);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------ MISC
void FW_Wrapper::DrawString(int FontID,char* string,float x, float y,float depth,bool center,bool Camera0_world1){
	FontManager.String(FontID,string,x,y,depth,center,Camera0_world1);
}
void FW_Wrapper::DrawInt(int FontID,int Value,float x, float y,float depth,bool center,bool Camera0_world1){
	FontManager.Int(FontID,Value,x,y,depth,center,Camera0_world1);
}
void FW_Wrapper::DrawFloat (int FontID,float Value ,float x, float y,float depth,bool center,bool Camera0_world1){
	FontManager.Float(FontID,Value,x,y,depth,center,Camera0_world1);
}
#if defined(_WIN32)
//------------------------------------------------------------------------------------------------------------------------------------------------------------ Sound
unsigned int FW_Wrapper::SoundSourceAdd(char* path){
	return (SoundManager.Add(path));
}
void FW_Wrapper::SoundSourceRemove(unsigned int SoundSourceID){
	SoundManager.Remove(SoundSourceID);
}
void FW_Wrapper::SoundRestart(bool sndmngr){
	return (SoundManager.Restart(sndmngr));
}
void FW_Wrapper::SoundShutdown(){
	return (SoundManager.Shutdown());
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------ Controls
unsigned int FW_Wrapper::SoundPlay(unsigned int SoundSourceID,bool loop,float volume, float speed){
	return (SoundManager.Play(SoundSourceID,loop,volume,speed));
}
void FW_Wrapper::SoundPause(unsigned int SoundInstanceID){
	SoundManager.Pause(SoundInstanceID);
}
void FW_Wrapper::SoundResume(unsigned int SoundInstanceID){
	SoundManager.Resume(SoundInstanceID);
}
void FW_Wrapper::SoundStop(unsigned int SoundInstanceID){
	SoundManager.Stop(SoundInstanceID);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------ Volume
void FW_Wrapper::SoundVolume(unsigned int SoundInstanceID,float value){
	SoundManager.Volume(SoundInstanceID,value);
}
void FW_Wrapper::SoundSpeed (unsigned int SoundInstanceID,float value){
	SoundManager.Speed(SoundInstanceID,value);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------ Advanced features
void FW_Wrapper::SoundLoop(unsigned int SoundInstanceID){
	SoundManager.Loop(SoundInstanceID);
}
void FW_Wrapper::SoundMainVolume(float value){
	SoundManager.MainVolume(value);
}
void FW_Wrapper::SoundStopAll(){
	SoundManager.StopAll();
}
void FW_Wrapper::SoundPauseAll(bool paused){
	SoundManager.PauseAll(paused);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------ Xbox Input

unsigned int FW_Wrapper::ControllerAdd(){
	for(int i = 0; i < 4; i++){
		if (Controllers[i] == nullptr){
			Controllers[i] = new cXboxController(i);
			return (Controllers[i]->iID);
		}
	}
	return 5;
}
void FW_Wrapper::ControllerRemove(unsigned int ID){
	if (ID >= 0 && ID < 4){
		if (Controllers[ID] != nullptr){
			ControllerVibrate(ID,0,0);
			delete Controllers[ID];
			Controllers[ID] = nullptr;
			printf("----------------------- That controller was loaded.\n");
		}else{
			printf("----------------------- That controller wasnt loaded.\n");
		}
	}
}
bool FW_Wrapper::ControllerConnected(unsigned int ControllerID){
	return Controllers[ControllerID]->Connected();
} 
bool FW_Wrapper::ControllerButton(unsigned int ControllerID,int ButtonID){
	return Controllers[ControllerID]->Button(ButtonID);
}
bool FW_Wrapper::ControllerThumbstick(unsigned int ControllerID,bool L0_R1,bool X0_Y1,float &ReturnVal){
	return Controllers[ControllerID]->Thumbstick(L0_R1,X0_Y1,ReturnVal);
}
bool FW_Wrapper::ControllerTrigger(unsigned int ControllerID,bool L0_R1,float &ReturnVal){
	return Controllers[ControllerID]->Trigger(L0_R1,ReturnVal);
}
void FW_Wrapper::ControllerVibrate(unsigned int ControllerID,unsigned short leftamount,unsigned short rightamount){
	Controllers[ControllerID]->Vibrate(leftamount,rightamount);
}
#endif
//------------------------------------------------------------------------------------------------------------------------------------------------------------ EOF