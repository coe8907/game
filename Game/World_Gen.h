#pragma once
#ifdef __APPLE__
#include "TargetConditionals.h"
#ifdef TARGET_OS_MAC
#include "SDL2/SDL.h"
#endif
#elif defined _WIN32 || defined _WIN64
#include "SDL.h"
#endif

#include <string>
#include <vector>

using namespace std;

class World_Gen
{
public:
	struct area {
	int x = 0;
	int y = 0;
	int endx = 0;
	int endy = 0;
	};
private:
	
	const int max_sprite_size = 50;
	
	
	SDL_Renderer*	m_Renderer;
	SDL_Surface*	m_Surface;
	SDL_Texture*	m_Texture;
	vector<int> * my_level;
	vector<area> * tiles = new vector<area>;
	vector<area> * objects = new vector<area>;
	int level_width;
	int get_Red(Uint32 color);
	int get_Blue(Uint32 color);
	int get_Green(Uint32 color);
	Uint32 getpixel(SDL_Surface * surface, int x, int y);
public:
	World_Gen();
	vector<int>* Load_world(std::string filename);
	vector<int>* Load_objects(std::string filename);
	vector<area>* fine_me();
	vector<area>* get_tiles(std::string filename);
	vector<World_Gen::area>* get_objects(std::string filename);
	int get_width();
	~World_Gen();
	
};

