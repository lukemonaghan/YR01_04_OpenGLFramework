//---------------------------
//------ Luke Monaghan ------
//---------------------------
#ifndef MODEL_H_
#define MODEL_H_
//---------------------------
#include "renderable.h" 
//---------------------------
#include "MATH/Vector2.h"
#include "MATH/Vector3.h"
//---------------------------
struct sModelInformation{
	Vector3 Size;
	Vector2 UV;
};
//---------------------------
class cModel : public cRenderable {
public:
	cModel();
	cModel(const char* path);
	void Delete();
	void UpdateVerts();
	void DrawModel(int uLocation,cFramework *FW);
	bool loadOBJ(const char* path);
protected:
	sModelInformation* Verticies;
	unsigned int VAO,VBO,IBO;
	unsigned int SizeOfModel;
};

#endif