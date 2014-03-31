//---------------------------
//------ Luke Monaghan ------
//---------------------------
#include "Common/Managers/FontManager.h"
//--------------------------- OpenGL
#include "GL/glew.h"
//--------------------------- Functions
cFontManager::cFontManager(){}
void cFontManager::Initialise(){
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
void cFontManager::Shutdown(){
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers     (1, &VBO);
	glDeleteBuffers     (1, &IBO);
	while(FontsMap.size()>0){
		Remove(FontsMap.begin()->second.ID());
	}
	FontsMap.clear();
}

int cFontManager::Draw(int uLocation,cFramework *FW){
	int returnamount = LettersQueue.size();
	if ( returnamount > 0){
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER,VBO);
		for (int id = 0; id < returnamount; id++ ){
			LettersQueue.front().UpdateVerts();
			LettersQueue.front().Draw(uLocation,FW,CameraWorldQueue.front());
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			CameraWorldQueue.pop();
			LettersQueue.pop();
		}
		LettersQueue.empty();
		glBindBuffer(GL_ARRAY_BUFFER,0);
		glBindVertexArray(0);
		return returnamount;
	}
	return 0;
}
void cFontManager::Colour(int FontID, float f_Red, float f_Green, float f_Blue, float f_Alpha){
	FontsMapIt = FontsMap.find(FontID);
	FontsMapIt->second.SetColour(f_Red,f_Green,f_Blue,f_Alpha);
}

//--------------------------- Int String
void cFontManager::String(int FontID,char* string,float x, float y,float depth,bool center,bool Camera0_world1){
	FontsMapIt = FontsMap.find(FontID);
	if (FontsMapIt != FontsMap.end()){
		TempWordLettersQueue = FontsMapIt->second.DrawString(string,x,y,depth,center);
		int TempSize = TempWordLettersQueue.size();
		for (int i = 0; i < TempSize; i++){
			LettersQueue.push(TempWordLettersQueue.front());
			CameraWorldQueue.push(Camera0_world1);
			TempWordLettersQueue.pop();
		}
	}
	TempWordLettersQueue.empty();
}
void cFontManager::Int(int FontID,int Value,float x, float y,float depth,bool center,bool Camera0_world1){
	FontsMapIt = FontsMap.find(FontID);
	if (FontsMapIt != FontsMap.end()){
		TempWordLettersQueue = FontsMapIt->second.DrawInt(Value,x,y,depth,center);
		int TempSize = TempWordLettersQueue.size();
		for (int i = 0; i < TempSize; i++){
			LettersQueue.push(TempWordLettersQueue.front());
			CameraWorldQueue.push(Camera0_world1);
			TempWordLettersQueue.pop();
		}
	}
	TempWordLettersQueue.empty();
}

void cFontManager::Float(int FontID,float Value ,float x, float y,float depth,bool center,bool Camera0_world1){
	FontsMapIt = FontsMap.find(FontID);
	if (FontsMapIt != FontsMap.end()){
		TempWordLettersQueue = FontsMapIt->second.DrawFloat(Value,x,y,depth,center);
		int TempSize = TempWordLettersQueue.size();
		for (int i = 0; i < TempSize; i++){
			LettersQueue.push(TempWordLettersQueue.front());
			CameraWorldQueue.push(Camera0_world1);
			TempWordLettersQueue.pop();
		}
	}
	TempWordLettersQueue.empty();
}

//--------------------------- Create Remove
int cFontManager::Create(char* path){
	cFont tFnt(path);
	FontsMap.insert(std::pair<unsigned int,cFont>(tFnt.ID(),tFnt));
	return (tFnt.ID());
}
void cFontManager::Remove(int FontID){
	FontsMapIt = FontsMap.find(FontID);
	if (FontsMapIt != FontsMap.end()){
		FontsMapIt->second.Delete();
		FontsMap.erase(FontID);
	}
}
