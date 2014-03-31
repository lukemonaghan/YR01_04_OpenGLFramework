//---------------------------
//------ Luke Monaghan ------
//---------------------------
#ifndef MODELMANAGER_H_
#define MODELMANAGER_H_
//--------------------------- Includes
#include <map>
#include <queue>
#include "Common/Drawables/Model.h"
//--------------------------- Class
class cModelManager{
public:
//--------------------------- De/Constructor
	cModelManager();
	void Initialise();
	void Shutdown();
//--------------------------- Functions
	void Move  (int ModelID, float x, float y, float depth);
	void Rotate(int ModelID, float angle);
	void Scale (int ModelID, float xscale, float yscale);
	void Resize(int ModelID, int width , int height);
	void AddtoQueue(int ModelID,bool Camera0_world1);
	int Draw  (int uLocation,cFramework *FW);
//--------------------------- Create Remove
	int  Create(char* path);
	void Remove(int ModelID);
private:
	std::map<unsigned int,cModel> ModelsMap;
	std::map<unsigned int,cModel>::iterator ModelsMapIt;
	std::queue<cModel> ModelsQueue;
	std::queue<bool> CameraWorldQueue;
};

#endif