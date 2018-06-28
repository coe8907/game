#include "text.h"
#include "Game.h"

SDL_Rect text::textRect;

text::text(const std::string fontPath, int fontSize, const std::string& message, const SDL_Color color)
{
	textTexture = loadFont(fontPath.c_str(), fontSize, message.c_str(), color);
	SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);
}


SDL_Texture* text::loadFont(const std::string fontPath, int fontSize, const std::string& message, const SDL_Color color)
{
	TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);

	if (!font)
	{
		std::cerr << "Failed to load font";
	}

	SDL_Surface* textSurface = TTF_RenderText_Solid(font, message.c_str(), color);

	if (!textSurface)
	{
		std::cerr << "Failed to load text surface";
	}

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Game::m_Renderer, textSurface);

	if (!textTexture)
	{
		std::cerr << "Failed to load text texture";
	}
	SDL_FreeSurface(textSurface);
	
	

	return textTexture;
}

void text::displaytext(int x, int y)
{
	textRect.x = x;
	textRect.y = y;

	
	SDL_RenderCopy(Game::m_Renderer, textTexture, nullptr, &textRect);
}

void text::updateText(const std::string fontPath, int fontSize, const std::string& message, const SDL_Color color)
{
	textTexture = loadFont(fontPath.c_str(), fontSize, message.c_str(), color);
	SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);
}

text::~text()
{
}
