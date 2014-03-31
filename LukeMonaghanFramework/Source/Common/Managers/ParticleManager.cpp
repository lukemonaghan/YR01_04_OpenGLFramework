//---------------------------
//------ Luke Monaghan ------
//---------------------------
#include "Common/Managers/ParticleManager.h"
//--------------------------- OpenGL
#include "GL/glew.h"
//--------------------------- Constuctor/Create
cParticleManager::cParticleManager(){}
void cParticleManager::Initialise(){
	uiEmitterID = 0;
	unsigned int Indices[6] = { 0, 1, 2,
                                0, 2, 3 };
	glGenBuffers     (1, &VBO);
	glGenBuffers     (1, &IBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IBO);

	glBufferData(GL_ARRAY_BUFFER        ,sizeof(sSquareInformation)*4,NULL   ,GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(Indices)             ,Indices,GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(sSquareInformation), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE , sizeof(sSquareInformation), (void*)12);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_TRUE , sizeof(sSquareInformation), (void*)20);
	
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}
void cParticleManager::Shutdown(){
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers     (1, &VBO);
	glDeleteBuffers     (1, &IBO);
	EmitterMap.clear();
	uiEmitterID = 0;
}
unsigned int cParticleManager::CreateEmitter(cSquare *Particle){
	uiEmitterID++;
	cEmitter tEmit;
	tEmit.Create(Particle);
	EmitterMap.insert(std::pair<unsigned int,cEmitter>(uiEmitterID,tEmit));
	return (uiEmitterID);
}
unsigned int cParticleManager::CreateEmitter(cSquare *Particle, float startx, float starty,float startdepth, float endx, float endy, float enddepth, float lifetimeinsec){
	uiEmitterID++;
	cEmitter tEmit;
	tEmit.Create(Particle,startx,starty,startdepth,endx,endy,enddepth, lifetimeinsec);
	EmitterMap.insert(std::pair<unsigned int,cEmitter>(uiEmitterID,tEmit));
	return (uiEmitterID);
}

void cParticleManager::DestroyEmitter(unsigned int EmitterID){
	EmitterMapIt = EmitterMap.find(EmitterID);
	if (EmitterMapIt != EmitterMap.end()){
		EmitterMap.erase(EmitterID);
	}
}

void cParticleManager::SetParticlesPerStep(unsigned int EmitterID,float amount){
	EmitterMapIt = EmitterMap.find(EmitterID);
	if (EmitterMapIt != EmitterMap.end()){
		EmitterMapIt->second.SetParticlesPerStep(amount);
	}
}

void cParticleManager::SetPosition(unsigned int EmitterID, float x, float y, float depth, bool start0_end1){
	EmitterMapIt = EmitterMap.find(EmitterID);
	if (EmitterMapIt != EmitterMap.end()){
		EmitterMapIt->second.SetPosition(x,y,depth,start0_end1);
	}
}
void cParticleManager::SetSize(unsigned int EmitterID,float Width, float Height, bool start0_end1){
	EmitterMapIt = EmitterMap.find(EmitterID);
	if (EmitterMapIt != EmitterMap.end()){
		EmitterMapIt->second.SetSize(Width,Height,start0_end1);
	}
}
void cParticleManager::SetColour(unsigned int EmitterID, float f_Red, float f_Green, float f_Blue, float f_Alpha, bool start0_end1){
	EmitterMapIt = EmitterMap.find(EmitterID);
	EmitterMapIt->second.SetColour(f_Red,f_Green,f_Blue,f_Alpha,start0_end1);
}
void cParticleManager::SetOffset(unsigned int EmitterID, int i_XOffset, int i_YOffset){
	EmitterMapIt = EmitterMap.find(EmitterID);
	EmitterMapIt->second.SetOffset(i_XOffset,i_YOffset);
}
void cParticleManager::SetRotation(unsigned int EmitterID, float f_AmountPerStep,bool start0_end1){
	EmitterMapIt = EmitterMap.find(EmitterID);
	EmitterMapIt->second.SetRotation(f_AmountPerStep,start0_end1);
}

void cParticleManager::AddtoQueue(int EmitterID,bool Camera0_world1){
	EmitterMapIt = EmitterMap.find(EmitterID);
	if (EmitterMapIt != EmitterMap.end()){
		TempParticlesQueue = EmitterMapIt->second.Draw();
		int TempSize = TempParticlesQueue.size();
		for (int i = 0; i < TempSize; i++){
			SpritesQueue.push(TempParticlesQueue.front());
			CameraWorldQueue.push(Camera0_world1);
			TempParticlesQueue.pop();
		}
	}
	TempParticlesQueue.empty();
}
void cParticleManager::Update(float f_DeltaTime){
	for (EmitterMapIt = EmitterMap.begin(); EmitterMapIt != EmitterMap.end(); EmitterMapIt++){
		EmitterMapIt->second.Update(f_DeltaTime);
	}
}
int cParticleManager::Draw(int uLocation,cFramework *FW){
	int returnamount = SpritesQueue.size();
	if ( returnamount > 0){
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER,VBO);
		for (unsigned int id = 0; id < returnamount; id++){
			SpritesQueue.front().UpdateVerts();
			SpritesQueue.front().Draw(uLocation,FW,CameraWorldQueue.front());
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			CameraWorldQueue.pop();
			SpritesQueue.pop();
		}
		glBindBuffer(GL_ARRAY_BUFFER,0);
		glBindVertexArray(0);
		return returnamount;
	}
	return 0;
}