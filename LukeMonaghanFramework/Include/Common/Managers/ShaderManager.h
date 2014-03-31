//---------------------------
//------ Luke Monaghan ------
//---------------------------
#ifndef SHADERMANAGER_H_
#define SHADERMANAGER_H_
//--------------------------- Includes
#include <vector>
#include "Common/Shader.h"
//--------------------------- Class
class cShaderManager{
public:
//--------------------------- De/Constructor
	cShaderManager(){};
	~cShaderManager(){
		Shaders.clear();
	};
//--------------------------- Create Remove
	int  Create(char* path);
	void Remove(int ShaderID);
	void Use(int ShaderID);
private:
	std::vector<cShader> Shaders;
	GLuint VAO,VBO,IBO;
};

#endif