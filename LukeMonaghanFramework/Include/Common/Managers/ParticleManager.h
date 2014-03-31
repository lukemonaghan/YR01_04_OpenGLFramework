//---------------------------
//------ Luke Monaghan ------
//---------------------------
#ifndef PARTICLEMANAGER_H_
#define PARTICLEMANAGER_H_
//--------------------------- Includes
#include <map>
#include <queue>
#include "Common/Emitter.h"
//--------------------------- Class
class cParticleManager{
public:
//--------------------------- De/Constructor
	cParticleManager();
	void Initialise();
	void Shutdown();
//--------------------------- Functions
	unsigned int CreateEmitter(cSquare *Particle);
	unsigned int CreateEmitter(cSquare *Particle, float startx, float starty, float startdepth, float endx, float endy, float enddepth, float lifetimeinsec);

	void DestroyEmitter(unsigned int EmitterID);

	void SetParticlesPerStep(unsigned int EmitterID, float amount);
	void SetOpacity         (unsigned int EmitterID, float f_Opacity);
	void SetLifetime        (unsigned int EmitterID, float lifetimeinsec);
	void SetSpeed           (unsigned int EmitterID, float xspeed,float yspeed);
	void SetPosition        (unsigned int EmitterID, float x     , float y     , float depth, bool start0_end1 = 0);
	void SetSize            (unsigned int EmitterID, float Width , float Height             , bool start0_end1 = 0);
	void SetColour          (unsigned int EmitterID, float f_Red, float f_Green, float f_Blue, float f_Alpha,bool start0_end1 = 0);
	void SetOffset          (unsigned int EmitterID, int i_XOffset, int i_YOffset);
	void SetRotation        (unsigned int EmitterID, float f_AmountPerStep,bool start0_end1);

	void AddtoQueue(int EmitterID,bool Camera0_world1);
	void Update(float f_DeltaTime);
	int Draw  (int uLocation,cFramework *FW);
private:
	unsigned int uiEmitterID;
	std::map<unsigned int,cEmitter> EmitterMap;
	std::map<unsigned int,cEmitter>::iterator EmitterMapIt;
	std::queue<cSquare> SpritesQueue;
	std::queue<cSquare> TempParticlesQueue;
	std::queue<bool> CameraWorldQueue;
	unsigned int VAO,VBO,IBO;
};

#endif