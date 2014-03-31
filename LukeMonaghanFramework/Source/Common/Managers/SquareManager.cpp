//---------------------------
//------ Luke Monaghan ------
//---------------------------
#include "Common/Managers/SquareManager.h"
//--------------------------- OpenGL
#include "GL/glew.h"
//--------------------------- Functions
cSquareManager::cSquareManager(){}
void cSquareManager::Initialise(){
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
void cSquareManager::Shutdown(){
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers     (1, &VBO);
	glDeleteBuffers     (1, &IBO);
	while(SpritesMap.size() > 0){
		Remove(SpritesMap.begin()->second.GetID());
	}
	SpritesMap.clear();	
}
void cSquareManager::Move(int spriteID, float x, float y, float depth){
	SpritesMapIt = SpritesMap.find(spriteID);
	if (SpritesMapIt != SpritesMap.end()){
		SpritesMapIt->second.Translate(x,y,depth);
	}
}
void cSquareManager::Rotate(int spriteID, float angle){
	SpritesMapIt = SpritesMap.find(spriteID);
	if (SpritesMapIt != SpritesMap.end()){
		SpritesMapIt->second.Rotate(angle);
	}
}
void cSquareManager::Scale(int spriteID, float xscale, float yscale){
	SpritesMapIt = SpritesMap.find(spriteID);
	if (SpritesMapIt != SpritesMap.end()){
		SpritesMapIt->second.Scale(xscale,yscale);
	}
}
void cSquareManager::Resize(int spriteID, int width, int height){
	SpritesMapIt = SpritesMap.find(spriteID);
	if (SpritesMapIt != SpritesMap.end()){
		SpritesMapIt->second.Resize(width,height);
	}
}
void cSquareManager::UV(int spriteID, float uMin, float vMin, float uMax, float vMax){
	SpritesMapIt = SpritesMap.find(spriteID);
	if (SpritesMapIt != SpritesMap.end()){
		SpritesMapIt->second.SetUV(uMin,vMin,uMax,vMax);
	}
}
void cSquareManager::Colour(int spriteID, float f_Red, float f_Green, float f_Blue, float f_Alpha){
	SpritesMapIt = SpritesMap.find(spriteID);
	if (SpritesMapIt != SpritesMap.end()){
		SpritesMapIt->second.SetColour(f_Red,f_Green,f_Blue,f_Alpha);
	}
}

cSquare cSquareManager::GetcSquare(int spriteID){
	SpritesMapIt = SpritesMap.find(spriteID);
	if (SpritesMapIt != SpritesMap.end()){
		return SpritesMapIt->second;
	}
}

void cSquareManager::AddtoQueue(int spriteID,bool Camera0_world1){
	SpritesMapIt = SpritesMap.find(spriteID);
	if (SpritesMapIt != SpritesMap.end()){
		SpritesQueue.push(SpritesMapIt->second);
		//CameraWorldQueue.push(Camera0_world1);
	}
}
int cSquareManager::Draw(int uLocation,cFramework *FW){
	int returnamount = (int)SpritesQueue.size();
	if ( returnamount > 0){
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER,VBO);
		for (unsigned int id = 0; id < returnamount; id++){
			SpritesQueue.front().UpdateVerts();
			SpritesQueue.front().Draw(uLocation,FW,1/*CameraWorldQueue.front()*/);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			//CameraWorldQueue.pop();
			SpritesQueue.pop();
		}
		glBindBuffer(GL_ARRAY_BUFFER,0);
		glBindVertexArray(0);
		return returnamount;
	}
	return 0;
}
//--------------------------- Create Remove
int cSquareManager::Create(char* path, int width, int height, int xoff, int yoff){
	cSquare tSqr(path,width,height,xoff,yoff);
	SpritesMap.insert(std::pair<unsigned int,cSquare>(tSqr.GetID(),tSqr));
	return (tSqr.GetID());
}
void cSquareManager::Remove(int spriteID){
	SpritesMapIt = SpritesMap.find(spriteID);
	if (SpritesMapIt != SpritesMap.end()){
		SpritesMapIt->second.Delete();
		SpritesMap.erase(spriteID);
	}
}