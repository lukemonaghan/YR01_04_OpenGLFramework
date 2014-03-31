//---------------------------
//------ Luke Monaghan ------
//---------------------------
#include "Common/Managers/ModelManager.h"
//--------------------------- OpenGL
#include "GL/glew.h"
//--------------------------- Functions
cModelManager::cModelManager(){}
void cModelManager::Initialise(){
	ModelsMap.clear();
	ModelsQueue.empty();
}
void cModelManager::Shutdown(){
	while(ModelsMap.size()>0){
		Remove(ModelsMap.begin()->second.GetID());
	}
	ModelsMap.clear();
}
void cModelManager::Move(int ModelID, float x, float y, float depth){
	ModelsMapIt = ModelsMap.find(ModelID);
	ModelsMapIt->second.Translate(x,y,depth);
}
void cModelManager::Rotate(int ModelID, float angle){
	ModelsMapIt = ModelsMap.find(ModelID);
	ModelsMapIt->second.Rotate(angle);
}
void cModelManager::Scale(int ModelID, float xscale, float yscale){
	ModelsMapIt = ModelsMap.find(ModelID);
	ModelsMapIt->second.Scale(xscale,yscale);
}
void cModelManager::Resize(int ModelID, int width, int height){
	ModelsMapIt = ModelsMap.find(ModelID);
	ModelsMapIt->second.Resize(width,height);
}
void cModelManager::AddtoQueue(int ModelID,bool Camera0_world1){
	ModelsMapIt = ModelsMap.find(ModelID);
	ModelsQueue.push(ModelsMapIt->second);
	CameraWorldQueue.push(Camera0_world1);
}
int cModelManager::Draw(int uLocation,cFramework *FW){
	int returnamount = ModelsQueue.size();
	if ( returnamount > 0){
		for (unsigned int id = 0; id < returnamount; id++){
			ModelsQueue.front().UpdateVerts();
			ModelsQueue.front().Draw(uLocation,FW,CameraWorldQueue.front());
			CameraWorldQueue.pop();
			ModelsQueue.pop();
		}
		return returnamount;
	}
	return 0;
}
//--------------------------- Create Remove
int cModelManager::Create(char* path){
	cModel tSqr(path);
	ModelsMap.insert(std::pair<unsigned int,cModel>(tSqr.GetID(),tSqr));
	return (tSqr.GetID());
}
void cModelManager::Remove(int ModelID){
	ModelsMapIt = ModelsMap.find(ModelID);
	ModelsMapIt->second.Delete();
	ModelsMap.erase(ModelID);
}