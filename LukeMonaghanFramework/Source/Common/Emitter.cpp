//---------------------------
//------ Luke Monaghan ------
//---------------------------
#include "Common/Emitter.h"
#include "MATH/Maths.h"
#include <math.h>
#include <iostream>

cEmitter::cEmitter(){}
void cEmitter::Create(cSquare *Particle){
	fParticlesPerStep = 0.0f;
	fParticleCreateStep = 0.0f;
	sqrParticle = *Particle;
	fLifeTime = 10.0f;

	SetPosition(0,0,0,0);
	SetPosition(0,1,0,0);

	SetSize(64,64,0);
	SetSize(64,64,1);

	SetColour(1,1,1,1,0);
	SetColour(1,1,1,1,1);
}
void cEmitter::Create(cSquare *Particle, float startx, float starty, float startdepth, float endx, float endy, float enddepth, float lifetimeinsec){
	fParticlesPerStep = 0.0f;
	fParticleCreateStep = 0.0f;
	sqrParticle = *Particle;

	SetPosition(startx,starty,startdepth,0);
	SetPosition(endx,endy,enddepth,1);

	SetSize(sqrParticle.GetWidthHeight(0),sqrParticle.GetWidthHeight(1),0);
	SetSize(0.0f,0.0f,1);

	SetColour(1.0f,1.0f,1.0f,1.0f,0);
	SetColour(1.0f,1.0f,1.0f,1.0f,1);

	SetRotation(0.0f,0);
	SetRotation(0.0f,1);

	SetOffset(50,50);

	sStartPosition.fTime = 0.0f;

	if (lifetimeinsec < 1.0f){lifetimeinsec = 1.0f;}
	fLifeTime = lifetimeinsec;
}

void cEmitter::Destroy(){
	fParticlesPerStep = 0.0f;
	fParticleCreateStep = 0.0f;
	Particles.clear();
}
void cEmitter::SetOffset(int i_x, int i_y){
	iOffsetX = i_x;
	iOffsetY = i_y;
	if (iOffsetX < 1.0f){iOffsetX = 1.0f;}
	if (iOffsetY < 1.0f){iOffsetY = 1.0f;}
}
void cEmitter::SetPosition(float x, float y, float depth, bool start0_end1){
	if (!start0_end1){
		sStartPosition.fx = x;
		sStartPosition.fy = y;
		sStartPosition.fDepth = depth;
	}else{
		sOffsets.fx = x;
		sOffsets.fy = y;
		sOffsets.fDepth = depth;
	}
}
void cEmitter::SetSize(float Width, float Height, bool start0_end1){
	if (!start0_end1){
		sStartPosition.fWidth  = Width;
		sStartPosition.fHeight = Height;
	}else{
		sOffsets.fWidth    = Width;
		sOffsets.fHeight   = Height;
	}
}
void cEmitter::SetColour(float f_Red, float f_Green, float f_Blue, float f_Alpha, bool start0_end1){
	if (!start0_end1){
		sStartPosition.fColour[0] = f_Red;
		sStartPosition.fColour[1] = f_Green;
		sStartPosition.fColour[2] = f_Blue;
		sStartPosition.fColour[3] = f_Alpha;
	}else{
		sOffsets.fColour[0] = f_Red;
		sOffsets.fColour[1] = f_Green;
		sOffsets.fColour[2] = f_Blue;
		sOffsets.fColour[3] = f_Alpha;
	}
}
void cEmitter::SetRotation(float f_AmountPerStep, bool start0_end1){
	if (!start0_end1){
		sStartPosition.fRotation = f_AmountPerStep;
	}else{
		sOffsets.fRotation = f_AmountPerStep;
	}
}
void cEmitter::Update(float f_DeltaTime){
	//Push back new particles
	float fCurrentLerp = 0.0f;
	fParticleCreateStep += fParticlesPerStep;
	sEmitterPosition TempStartPosition = sStartPosition;
	while (fParticleCreateStep >= 1.0f){
	
		TempStartPosition.fx += rand()%iOffsetX - (iOffsetX * 0.5);
		TempStartPosition.fy += rand()%iOffsetY - (iOffsetY * 0.5);
	
		TempStartPosition.fTime = rand()%100 * (fLifeTime * 0.25f);
	
		if (sOffsets.fRotation >= 2.0f){
			TempStartPosition.fRotation += rand()%(int)sOffsets.fRotation - (sOffsets.fRotation * 0.5);
		}else{
			TempStartPosition.fRotation = atan2(sStartPosition.fx - sOffsets.fx , sStartPosition.fy - sOffsets.fy) * RAD2DEG;
		}
	
		Particles.push_back(TempStartPosition);
		fParticleCreateStep -= 1.0f;
	}
	//start the iterator at the start of the vector
	ParticlesIT = Particles.begin();
	//run through all 
	while (ParticlesIT != Particles.end()) {
		if (ParticlesIT->fTime < fLifeTime) {
			if (ParticlesIT->fColour[3] <= 0.01f || ParticlesIT->fWidth <= 0.0f || ParticlesIT->fHeight <= 0.0f ){
				ParticlesIT = Particles.erase(ParticlesIT);
			}else{
				ParticlesIT->fx         += sOffsets.fx     * f_DeltaTime;
				ParticlesIT->fy         += sOffsets.fy     * f_DeltaTime;
				ParticlesIT->fDepth     += sOffsets.fDepth * f_DeltaTime;
				fCurrentLerp = ParticlesIT->fTime / fLifeTime;
				ParticlesIT->fColour[0]  = Lerp( sStartPosition.fColour[0] , sOffsets.fColour[0] , fCurrentLerp ) ;
				ParticlesIT->fColour[1]  = Lerp( sStartPosition.fColour[1] , sOffsets.fColour[1] , fCurrentLerp ) ;
				ParticlesIT->fColour[2]  = Lerp( sStartPosition.fColour[2] , sOffsets.fColour[2] , fCurrentLerp ) ;
				ParticlesIT->fColour[3]  = Lerp( sStartPosition.fColour[3] , sOffsets.fColour[3] , fCurrentLerp ) ;
				if (sOffsets.fWidth  != 0.0f){ ParticlesIT->fWidth  += sOffsets.fWidth ; }
				if (sOffsets.fHeight != 0.0f){ ParticlesIT->fHeight += sOffsets.fHeight; }
				if (sOffsets.fRotation >= 0.0f){
					ParticlesIT->fRotation  += sOffsets.fRotation * f_DeltaTime;
				}
				ParticlesIT->fTime+= f_DeltaTime;
				ParticlesIT++;
			}
		}else{
			ParticlesIT = Particles.erase(ParticlesIT);
		}
	}
}
std::queue<cSquare> cEmitter::Draw(){
	std::queue<cSquare> ReturnSquares;
	ParticlesIT = Particles.begin();
	while (ParticlesIT != Particles.end()) {
		sqrParticle.Translate(ParticlesIT->fx,ParticlesIT->fy,ParticlesIT->fDepth);
		sqrParticle.Rotate(ParticlesIT->fRotation);
		sqrParticle.Resize(ParticlesIT->fWidth,ParticlesIT->fHeight);
		sqrParticle.SetColour(ParticlesIT->fColour[0],ParticlesIT->fColour[1],ParticlesIT->fColour[2],ParticlesIT->fColour[3]);
		ReturnSquares.push(sqrParticle);
		ParticlesIT++;
	}
	return ReturnSquares;
}