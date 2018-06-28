#pragma once
#ifdef __APPLE__
#include "TargetConditionals.h"
#ifdef TARGET_OS_MAC
#include <SDL2_ttf/SDL_ttf.h>
#include "SDL2/SDL.h"
#endif
#elif defined _WIN32 || defined _WIN64
#include <SDL_ttf.h>
#include "SDL.h"
#endif

#include <iostream>
#include <string>

class text
{
public:
	text(const std::string fontPath, int fontSize, const std::string& message, const SDL_Color color);

	static SDL_Texture* loadFont(const std::string fontPath, int fontSize, const std::string& message, const SDL_Color color);

	void displaytext(int x, int y);
	void updateText(const std::string fontPath, int fontSize, const std::string& message, const SDL_Color color);
	~text();

private:
	SDL_Texture* textTexture = nullptr;
	static SDL_Rect textRect;
};

