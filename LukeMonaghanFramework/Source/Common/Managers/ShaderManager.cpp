//---------------------------
//------ Luke Monaghan ------
//---------------------------
#include "Common/Managers/ShaderManager.h"
//--------------------------- Functions
int  cShaderManager::Create(char* path){
	Shaders.push_back(cShader(path));
	return (Shaders.back().ID());
}
void cShaderManager::Use(int ShaderID){
	std::vector<cShader>::iterator iShd = Shaders.begin();
	while (iShd!=Shaders.end()) {
		if (iShd->ID()==ShaderID){
			iShd->UseShader();
			break;
		}else{
			iShd++;
		}
	}
}
void cShaderManager::Remove(int ShaderID){
	std::vector<cShader>::iterator iShd = Shaders.begin();
	while (iShd!=Shaders.end()) {
		if (iShd->ID()==ShaderID){
			iShd=Shaders.erase(iShd);
			break;
		}else{
			iShd++;
		}
	}
}
