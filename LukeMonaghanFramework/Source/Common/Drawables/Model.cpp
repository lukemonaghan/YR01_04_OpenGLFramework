//---------------------------
//------ Luke Monaghan ------
//---------------------------
#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
//---------------------------
#include "Common/Drawables/Model.h"
//--------------------------- OpenGL
#include "GL/glew.h"
#include <iostream>
//---------------------------
cModel::cModel(){}
cModel::cModel(const char* path){
	//loadOBJ(path);
	//uiSpriteID = 1;
}
void cModel::Delete(){
	//delete Verticies;
	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers     (1, &VBO);
	//glDeleteBuffers     (1, &IBO);
}
void cModel::UpdateVerts(){
	//glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(Verticies),Verticies);
}
void cModel::DrawModel(int uLocation,cFramework *FW){
	//glBindVertexArray(VAO);
	//glBindBuffer(GL_ARRAY_BUFFER,VBO);
	//
	//Draw(uLocation,FW);
	//glDrawElements(GL_TRIANGLES, SizeOfModel, GL_UNSIGNED_INT, 0);
	//
	//glBindBuffer(GL_ARRAY_BUFFER,0);
	//glBindVertexArray(0);
}


bool cModel::loadOBJ(const char* path){
	//std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	//std::vector<Vector3> temp_vertices; 
	//std::vector<Vector2> temp_uvs;
	//std::vector<Vector3> temp_normals;
	//
	//FILE * file = fopen(path, "r");
	//if( file == NULL ){
	//	printf("Cannot open file of path '%s' please check it exists. \n",path);
	//	return false;
	//}else{
	//	printf("Found file of path '%s' Loading now. \n",path);
	//}
	//while( 1 ){
	//	char lineHeader[128];
	//	// read the first word of the line
	//	int res = fscanf(file, "%s", lineHeader);
	//
	//	if (res == EOF){
	//		break; // EOF = End Of File. Quit the loop.		
	//	}
	//
	//	if ( strcmp( lineHeader, "v" ) == 0 ){
	//		Vector3 vertex;
	//		fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
	//		temp_vertices.push_back(vertex);
	//	}else if ( strcmp( lineHeader, "vt" ) == 0 ){
	//		Vector2 uv;
	//		fscanf(file, "%f %f\n", &uv.x, &uv.y );
	//		temp_uvs.push_back(uv);
	//	}else if ( strcmp( lineHeader, "vn" ) == 0 ){
	//		Vector3 normal;
	//		fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
	//		temp_normals.push_back(normal);
	//	}else if ( strcmp( lineHeader, "f" ) == 0 ){
	//		std::string vertex1, vertex2, vertex3;
	//		unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
	//		int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
	//		if (matches != 9){
	//			printf("File can't be read on line %i. Either to advanced, or broken.\n",lineHeader);
	//			return false;
	//		}
	//		vertexIndices.push_back(vertexIndex[0]);
	//		vertexIndices.push_back(vertexIndex[1]);
	//		vertexIndices.push_back(vertexIndex[2]);
	//		uvIndices    .push_back(uvIndex[0]);
	//		uvIndices    .push_back(uvIndex[1]);
	//		uvIndices    .push_back(uvIndex[2]);
	//		normalIndices.push_back(normalIndex[0]);
	//		normalIndices.push_back(normalIndex[1]);
	//		normalIndices.push_back(normalIndex[2]);
	//	}else{
	//		// Probably a comment, eat up the rest of the line
	//		char stupidBuffer[1000];
	//		fgets(stupidBuffer, 1000, file);
	//	}
	//
	//}
	//SizeOfModel = vertexIndices.size();
	//Verticies = new sModelInformation[SizeOfModel];
	//
	////For each vertex of each triangle
	//for( unsigned int i=0; i < SizeOfModel; i++ ){		
	//	// Put the attributes in buffers
	//	Verticies[i].Size   = temp_vertices[ vertexIndices[i]-1 ];
	//	Verticies[i].UV     = temp_uvs     [ uvIndices    [i]-1 ];
	//	//Verticies[i].Normal = temp_normals [ normalIndices[i]-1 ];
	//}
	//
	//glGenBuffers     (1, &VBO);
	//glGenVertexArrays(1, &VAO);
	//
	//glBindVertexArray(VAO);
	//glBindBuffer(GL_ARRAY_BUFFER,VBO);
	//
	//glBufferData(GL_ARRAY_BUFFER          ,sizeof(sModelInformation)*SizeOfModel,&Verticies,GL_STATIC_DRAW);
	//
	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	//
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(sModelInformation), (void*)0);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE , sizeof(sModelInformation), (void*)12);
	//
	//glBindBuffer(GL_ARRAY_BUFFER,0);
	//glBindVertexArray(0);
	return true;
}