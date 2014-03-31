//---------------------------
//------ Luke Monaghan ------
//---------------------------
#ifndef EMITTER_H_
#define EMITTER_H_
//--------------------------- Includes
#include <vector>
#include <queue>
#include "Common/Drawables/square.h"
//--------------------------- Class
class cEmitter{
public:
//--------------------------- De/Constructor
	cEmitter();
//--------------------------- Functions
	void Create(cSquare *Particle);
	void Create(cSquare *Particle, float startx, float starty , float startdepth, float endx, float endy, float enddepth, float lifetimeinsec);

	void Destroy();

	void SetParticlesPerStep(float amount){fParticlesPerStep = amount;}
	void SetPosition(float x     , float y     , float depth, bool start0_end1 = 0);
	void SetSize    (float Width , float Height             , bool start0_end1 = 0);
	void SetColour  (float f_Red, float f_Green, float f_Blue, float f_Alpha, bool start0_end1 = 0);
	void SetOffset(int i_x, int i_y);
	void SetRotation(float f_AmountPerStep, bool start0_end1 = 0);
	void Update(float f_DeltaTime);
	std::queue<cSquare> Draw();
private:
	struct sEmitterPosition{
		float fx, fy, fDepth;
		float fWidth, fHeight;
		float fRotation;
		float fTime;
		float fColour[4];
	}sStartPosition,sOffsets;
	
	float fLifeTime;
	int iOffsetX, iOffsetY;

	cSquare sqrParticle;
	std::vector<sEmitterPosition> Particles;
	std::vector<sEmitterPosition>::iterator ParticlesIT;

	float fParticlesPerStep;
	float fParticleCreateStep;
};

#endif