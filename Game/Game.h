#pragma once
#ifdef __APPLE__
#include "TargetConditionals.h"
#ifdef TARGET_OS_MAC
#include "SDL2/SDL.h"
#endif
#elif defined _WIN32 || defined _WIN64
#include "SDL.h"
#endif

#include "text.h"
#include "soundManager.h"
#include "World.h"
class Game
{
private:
	SDL_Window * m_Window;
	text* Text;
	soundManager* sound;
public:
	Game();
	~Game();
	void paint();
	void update();
	void SetDisplayColor(void);
	static SDL_Renderer * m_Renderer;
	World * world;

};

