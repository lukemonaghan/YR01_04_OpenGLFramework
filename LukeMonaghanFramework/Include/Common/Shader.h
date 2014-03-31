//---------------------------
//------ Luke Monaghan ------
//---------------------------
#ifndef SHADER_H_
#define SHADER_H_
//--------------------------- OpenGL
#include "GL/glew.h"
//--------------------------- Shader Class
class cShader{
public:
	cShader(char* Filename);
	void Delete();
	void LoadShader(GLuint ShaderProgram,GLenum ShaderType,const char* File);// TODO add uniform uniforms.
	char* LoadShaderFile(const char* File);
	void UseShader();
	int ID(){return iShaderID;}
private:
	cShader(){};
	int iShaderID;
};

#endif