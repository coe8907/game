#include "soundManager.h"



soundManager::soundManager()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		
	}
}


soundManager::~soundManager()
{
	//Quit SDL_mixer
	Mix_CloseAudio();
}


Mix_Music * soundManager::loadMusic(const char * filename)
{
	if (!musicFiles.count(filename))
	{
		Mix_Music* music = Mix_LoadMUS(filename);

		if (music == NULL)
		{
			std::cout << "Error: " << Mix_GetError();
		}
		musicFiles.insert(musicFiles.begin(), std::pair<const char*, Mix_Music*>(filename, music));
	}

	return musicFiles.at(filename);
}

Mix_Chunk * soundManager::loadSound(const char * filename)
{
	if (!soundFiles.count(filename))
	{
		Mix_Chunk* sound = Mix_LoadWAV(filename);
		soundFiles.insert(soundFiles.begin(), std::pair<const char*, Mix_Chunk*>(filename, sound));
	}

	return soundFiles.at(filename);
}

void soundManager::playMusic(const char * filename)
{
	if(musicFiles.count(filename))
	{
		Mix_PlayMusic(musicFiles.at(filename), -1);
	}
	else
	{
		Mix_PlayMusic(loadMusic(filename), -1);
	}
}

void soundManager::playSound(const char * filename)
{
	if (soundFiles.count(filename))
	{
		Mix_PlayChannel(-1, soundFiles.at(filename), 0);
	}
	else
	{
		
		Mix_PlayChannel(-1, loadSound(filename), 0);
	}
}
