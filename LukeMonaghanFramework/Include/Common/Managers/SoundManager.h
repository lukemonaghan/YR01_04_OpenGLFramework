//---------------------------
//------ Luke Monaghan ------
//---------------------------
#if defined(_WIN32)
#ifndef SOUNDMANAGER_H_
#define SOUNDMANAGER_H_
//--------------------------- Vector STL
#include <vector>
//--------------------------- irrKlang
#include "IK/irrKlang.h"
//--------------------------- Structs
struct sSndSource{
	unsigned int iID;
	irrklang::ISoundSource* Sndource;
};
struct sSndInstance{
	unsigned int iID;
	irrklang::ISound* Sound;
};
//--------------------------- ManagerClass
class cSoundManager{
public:
	cSoundManager();
	~cSoundManager();
	void Init();
	//add remove
	unsigned int Add(char* path);
	void Remove(unsigned int ID);
	//pause stop
	unsigned int Play(unsigned int ID,bool loop,float volume, float speed);
	void Pause(unsigned int ID);
	void Resume(unsigned int ID);
	void Stop(unsigned int ID);
	//Volume Pitch Etc
	void Volume(unsigned int ID,float value);
	void Speed (unsigned int ID,float value);
	void Loop(unsigned int ID);
	//Advanced features
	void StopAll();
	void PauseAll(bool paused);
	//master controls
	void MainVolume(float value);
	void Restart(bool sndmngr = false);
	void Shutdown();
private:
	int iNextSourceID;
	int iNextInstanceID;
	irrklang::ISoundEngine*   SoundEngine;
	std::vector<sSndInstance> SoundsInstance;
	std::vector<sSndSource>   SoundSources;
};
#endif
#endif