//---------------------------
//------ Luke Monaghan ------
//---------------------------
#if defined(_WIN32)
#include "Common/Managers/SoundManager.h"
#include <iostream>
//--------------------------- Constructor
cSoundManager::cSoundManager(){
	SoundsInstance.clear();
	SoundSources.clear();
	iNextSourceID = 0;
	iNextInstanceID = 0;

}
cSoundManager::~cSoundManager(){
	//empty the memory used by the vector
	SoundsInstance.clear();
	SoundSources.clear();
}
void cSoundManager::Init(){
	//Start the sound engine
	//std::cout << "------------- Starting Irrklang\n";
	SoundEngine = irrklang::createIrrKlangDevice();
	//make sure the sounds vector is empty
	//std::cout << "------------- Irrklang Started\n\n";
}
void cSoundManager::Shutdown(){
	//destroy the sound engine
	SoundEngine->drop(); 
	//make sure the sounds vector is empty
	SoundsInstance.clear();
	SoundSources.clear();
}

//--------------------------- Add/Remove
unsigned int cSoundManager::Add(char* path){
	sSndSource sndsrc;
	sndsrc.iID = iNextSourceID;
	sndsrc.Sndource = SoundEngine->addSoundSourceFromFile(path);
	SoundSources.push_back(sndsrc);
	iNextSourceID++;
	return (sndsrc.iID);
}
void cSoundManager::Remove(unsigned int ID){
	std::vector<sSndSource>::iterator iSnd = SoundSources.begin();
	while (iSnd!=SoundSources.end()) {
		if (iSnd->iID==ID){
			iSnd->Sndource->drop();
			iSnd=SoundSources.erase(iSnd);
			break;
		}else{
			iSnd++;
		}
	}
}
//--------------------------- play pause resume stop
unsigned int cSoundManager::Play(unsigned int ID,bool loop,float volume, float speed){
	sSndInstance sndins;
	sndins.iID = iNextInstanceID;

	std::vector<sSndSource>::iterator iSnd = SoundSources.begin();
	while (iSnd!=SoundSources.end()) {
		if (iSnd->iID==ID){
			sndins.Sound = SoundEngine->play2D(iSnd->Sndource,loop,true);
			sndins.Sound->setIsPaused(false);
			break;
		}else{
			iSnd++;
		}
	}
	if (volume != 1.0f){
		sndins.Sound->setVolume(volume);
	}if (speed != 1.0f){
		sndins.Sound->setPlaybackSpeed(speed);
	}
	SoundsInstance.push_back(sndins);
	iNextInstanceID++;
	return (sndins.iID);
}
void cSoundManager::Pause(unsigned int ID){
	std::vector<sSndInstance>::iterator iSnd = SoundsInstance.begin();
	while (iSnd!=SoundsInstance.end()) {
		if (iSnd->iID==ID){
			iSnd->Sound->setIsPaused(true);
			break;
		}else{
			iSnd++;
		}
	}
}
void cSoundManager::Resume(unsigned int ID){
	std::vector<sSndInstance>::iterator iSnd = SoundsInstance.begin();
	while (iSnd!=SoundsInstance.end()) {
		if (iSnd->iID==ID){
			iSnd->Sound->setIsPaused(false);
			break;
		}else{
			iSnd++;
		}
	}
}
void cSoundManager::Stop(unsigned int ID){
	std::vector<sSndInstance>::iterator iSnd = SoundsInstance.begin();
	while (iSnd!=SoundsInstance.end()) {
		if (iSnd->iID==ID){
			iSnd->Sound->drop();
			iSnd=SoundsInstance.erase(iSnd);
			break;
		}else{
			iSnd++;
		}
	}
}
//--------------------------- Volume Pitch Etc
void cSoundManager::Volume(unsigned int ID,float value){
	std::vector<sSndInstance>::iterator iSnd = SoundsInstance.begin();
	while (iSnd!=SoundsInstance.end()) {
		if (iSnd->iID==ID){
			iSnd->Sound->setVolume(value);
			break;
		}else{
			iSnd++;
		}
	}
}
void cSoundManager::Speed(unsigned int ID,float value){
	std::vector<sSndInstance>::iterator iSnd = SoundsInstance.begin();
	while (iSnd!=SoundsInstance.end()) {
		if (iSnd->iID==ID){
			iSnd->Sound->setPlaybackSpeed(value);
			break;
		}else{
			iSnd++;
		}
	}
}
void cSoundManager::Loop(unsigned int ID){
	std::vector<sSndInstance>::iterator iSnd = SoundsInstance.begin();
	while (iSnd!=SoundsInstance.end()) {
		if (iSnd->iID==ID){
			iSnd->Sound->setIsLooped(true);
			break;
		}else{
			iSnd++;
		}
	}
}
//--------------------------- Advanced features
void cSoundManager::StopAll(){
	SoundEngine->stopAllSounds();
}
void cSoundManager::PauseAll(bool paused){
	SoundEngine->setAllSoundsPaused(paused);
}
//--------------------------- master controls
void cSoundManager::MainVolume(float value){
	SoundEngine->setSoundVolume(value);
}
void cSoundManager::Restart(bool sndmngr){
	if (sndmngr){
		SoundEngine->drop();
		//Start the sound engine
		SoundEngine = irrklang::createIrrKlangDevice();
	}
	//make sure the sounds vector is empty
	SoundsInstance.clear();
	SoundSources.clear();
	iNextSourceID = 0;
	iNextInstanceID = 0;
}
#endif