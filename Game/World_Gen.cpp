#include "World_Gen.h"
#include "Game.h"


World_Gen::World_Gen()
{
}
vector<int>* World_Gen::Load_world(std::string filename) {
	m_Texture = nullptr;
	m_Surface = nullptr;

	m_Renderer = Game::m_Renderer;
	m_Surface = SDL_LoadBMP(filename.c_str());
	if (!m_Surface) {
		printf("failed to load surface");
	}
	else {
		m_Texture = SDL_CreateTextureFromSurface(m_Renderer, m_Surface);
		if (!m_Texture) {
			printf("failed to load texture");
		}
	}
	vector<int> * res = new vector<int>;
	for (int y = 0; y < m_Surface->h; y++) {
		for (int x = 0; x < m_Surface->w; x++) {
			res->push_back(get_Blue(getpixel(m_Surface, x, y)));
			//cout << "tile ID:::: " << get_Blue(getpixel(m_Surface, x, y));
			//cout << endl;
		}
	}
	level_width = m_Surface->w;
	my_level = res;
	return res;
}
vector<int>* World_Gen::Load_objects(std::string filename) {
	m_Texture = nullptr;
	m_Surface = nullptr;

	m_Renderer = Game::m_Renderer;
	m_Surface = SDL_LoadBMP(filename.c_str());
	if (!m_Surface) {
		printf("failed to load surface");
	}
	else {
		m_Texture = SDL_CreateTextureFromSurface(m_Renderer, m_Surface);
		if (!m_Texture) {
			printf("failed to load texture");
		}
	}
	vector<int> * res = new vector<int>;
	for (int y = 0; y < m_Surface->h; y++) {
		for (int x = 0; x < m_Surface->w; x++) {
			res->push_back(get_Blue(getpixel(m_Surface, x, y)));
			//cout << "tile ID:::: " << get_Blue(getpixel(m_Surface, x, y));
			//cout << endl;
		}
	}
	level_width = m_Surface->w;
	my_level = res;
	return res;
}

vector<World_Gen::area>* World_Gen::get_tiles(std::string filename) {
	m_Texture = nullptr;
	m_Surface = nullptr;
	m_Renderer = Game::m_Renderer;
	m_Surface = SDL_LoadBMP(filename.c_str());
	if (!m_Surface) {
		printf("failed to load surface");
	}
	else {
		m_Texture = SDL_CreateTextureFromSurface(m_Renderer, m_Surface);
		if (!m_Texture) {
			printf("failed to load texture");
		}
	}
	Uint32 point_color = SDL_MapRGB(m_Surface->format, 255, 0, 226);
	int width = 1;
	for (int y = 0; y < m_Surface->h; y += width) {
		for (int x = 0; x < m_Surface->w; x+=width) {
			if (getpixel(m_Surface, x, y) == point_color) {
				for (int i = 1; i < max_sprite_size; i++) {
					if (getpixel(m_Surface, x + i, y) == point_color) {
						width = i;
						area temp;
						temp.x = x+1;
						temp.y = y+1;
						temp.endx = x + i-1;
						temp.endy = y + i-1;
						tiles->push_back(temp);
						break;
					}
				}
				
			}
		}
	}
	cout << tiles->size() << "   tile_size   " << endl;
	return tiles;
}
vector<World_Gen::area>* World_Gen::get_objects(std::string filename) {
	m_Texture = nullptr;
	m_Surface = nullptr;
	m_Renderer = Game::m_Renderer;
	m_Surface = SDL_LoadBMP(filename.c_str());
	if (!m_Surface) {
		printf("failed to load surface");
	}
	else {
		m_Texture = SDL_CreateTextureFromSurface(m_Renderer, m_Surface);
		if (!m_Texture) {
			printf("failed to load texture");
		}
	}
	Uint32 point_color = SDL_MapRGB(m_Surface->format, 255, 0, 226);
	int width = 1;
	for (int y = 0; y < m_Surface->h; y += width) {
		for (int x = 0; x < m_Surface->w; x += width) {
			if (getpixel(m_Surface, x, y) == point_color) {
				for (int i = 1; i < max_sprite_size; i++) {
					if (getpixel(m_Surface, x + i, y) == point_color) {
						//width = i;
						area temp;
						temp.x = x + 1;
						temp.endx = x + i - 1;
						for (int j = 1; j < max_sprite_size; j++) {
						
							if (getpixel(m_Surface, x+i, y+j) == point_color) {
								temp.y = y + 1;
								temp.endy = y + j - 1;
								objects->push_back(temp);
								break;
							}
						}
						break;
					}
				}

			}
		}
	}
	cout << objects->size() << "   object_size   " << endl;
	return objects;
}
int World_Gen::get_width() {
	return level_width;
}
World_Gen::~World_Gen()
{
}

int World_Gen::get_Red(Uint32 color)
{
	int a =(int)(color >> 16);
	return a;
}
int World_Gen::get_Blue(Uint32 color)
{
	int b = (int)(color >> 0);
	return b;
}
int World_Gen::get_Green(Uint32 color)
{
	int g = (int)(color >> 8);
	return g;
}

Uint32 World_Gen::getpixel(SDL_Surface *surface, int x, int y)
{
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to retrieve */
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp) {
	case 1:
		return *p;
		break;

	case 2:
		return *(Uint16 *)p;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;
		break;

	case 4:
		return *(Uint32 *)p;
		break;

	default:
		return 0;
	}
}