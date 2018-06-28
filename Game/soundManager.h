#pragma once
#ifdef __APPLE__
#include "TargetConditionals.h"
#ifdef TARGET_OS_MAC
#include <SDL2_mixer/SDL_mixer.h>
#endif
#elif defined _WIN32 || defined _WIN64
#include <SDL_mixer.h>
#endif

#include <iostream>
#include <map>

class soundManager
{
public:
	soundManager();
	~soundManager();

	Mix_Music* loadMusic(const char* filename);
	Mix_Chunk* loadSound(const char* filename);

	void playMusic(const char* filename);
	void playSound(const char* filename);

private:
	std::map<const char*, Mix_Music*> musicFiles;
	std::map<const char*, Mix_Chunk*> soundFiles;

	
	
};

