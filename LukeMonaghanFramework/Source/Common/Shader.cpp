//---------------------------
//------ Luke Monaghan ------
//---------------------------
#include "Common/Shader.h"
//--------------------------- CMD Window
#include <string>
#include <fstream>
//--------------------------- Constructor
cShader::cShader(char* Filename){
	//printf("------------- Loading Shader. /n");
//Temp Variables
	GLint iPass = 0;
	GLchar cErrorLog[1024] = { 0 };
//create 2 temp chars, adding the .vert and .frag extensions
//vert
	std::string sVert;
	sVert.append(Filename);
	sVert.append(".vert");
	char* vertShad = Filename;
	vertShad = LoadShaderFile(sVert.c_str());
//frag
	std::string sFrag;
	sFrag.append(Filename);
	sFrag.append(".frag");
	char* fragShad = Filename;
	fragShad = LoadShaderFile(sFrag.c_str());
//Create the shader Program
	GLuint ShaderProgram = glCreateProgram();
//check it opened
	if (ShaderProgram == 0){
		printf("Error creating ShaderProgram \n '%i' \n",ShaderProgram);
		iShaderID = -1;
		return;
	}
//apply the shader
	LoadShader(ShaderProgram,GL_VERTEX_SHADER,vertShad);
	LoadShader(ShaderProgram,GL_FRAGMENT_SHADER,fragShad);
//Link the Shader
	glLinkProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram,GL_LINK_STATUS,&iPass);
//Check it is linked
	if (iPass == 0){
		glGetProgramInfoLog(ShaderProgram,sizeof(cErrorLog),NULL,cErrorLog);
		printf("Error while linking ShaderProgram \n '%s' \n",cErrorLog);
		iShaderID = -1;
		return;
	}
//Validate the Shader
	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram,GL_LINK_STATUS,&iPass);
//Check it is Valid
	if (iPass == 0){
		glGetProgramInfoLog(ShaderProgram,sizeof(cErrorLog),NULL,cErrorLog);
		printf("Error while validating ShaderProgram \n '%s' \n",cErrorLog);
		iShaderID = -1;
		return;
	}
	iShaderID = ShaderProgram;
	//printf("------------- Shader Loading finished! \n \n");	
}
void cShader::Delete(){
	glDeleteProgram(iShaderID);
}
void cShader::UseShader(){
	glUseProgram(iShaderID);
}
//--------------------------- Member Variables
void cShader::LoadShader(GLuint ShaderProgram,GLenum ShaderType,const char* File){
//Temp Variables
	GLint iPass = 0;
	GLchar cErrorLog[1024] = { 0 };
	GLint iLength = strlen(File);
//Shader Object
	GLuint ShaderObj = glCreateShader(ShaderType);
//Check it was created
	if (ShaderObj == 0){
		printf("Error with ShaderObj %d\n",ShaderType);
		return;
	}
//Create The shader
	glShaderSource(ShaderObj,1,&File,&iLength);
	glCompileShader(ShaderObj);
//check it was made
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &iPass);
	if (iPass == 0){
		glGetShaderInfoLog(ShaderObj,sizeof(cErrorLog),NULL,cErrorLog);
        printf("Error compiling shader type %d: '%s'\n", ShaderType, cErrorLog);
		return;
	}
//Finally after all the checks, Attatch it to the shaders Index
	glAttachShader(ShaderProgram,ShaderObj);
}
char* cShader::LoadShaderFile(const char* File){
	//Open file
	std::ifstream is(File,std::ifstream::binary);
	//Check it opened else fail
	if (!is){
		return 0;
	}
	//get the length of the file
	is.seekg(0,is.end);
	int length = (int)is.tellg();
	is.seekg(0,is.beg);
	//create the Return char
	char* cReturn = new char[length];
	//read the entire file into the char
	is.read(cReturn,length);
	//set the end to '\0'
	cReturn[length] = 0;
	//return the new char*
	//printf("Shader Loaded! '%s' \n",File);
	return (cReturn);
}