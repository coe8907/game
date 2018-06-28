#include "bitmap.h"
#include <string>
#include "Game.h"

bitmap::bitmap(std::string filename, int xpos, int ypos, bool usingtrans)
{
	is_trans = usingtrans;
	m_Texture = nullptr;
	m_Surface = nullptr;

	m_Renderer = Game::m_Renderer;
	m_Surface = SDL_LoadBMP(filename.c_str());
	if (!m_Surface) {
		printf("failed to load surface");
	}
	else {
		if (usingtrans) {
			Uint32 colourKey = SDL_MapRGB(m_Surface->format, 255, 0, 255);
			SDL_SetColorKey(m_Surface, SDL_TRUE, colourKey);
		}
		m_Texture = SDL_CreateTextureFromSurface(m_Renderer, m_Surface);
		if (!m_Texture) {
			printf("failed to load texture");
		}
	}
    loadheight = m_Surface->h;
    loadwidth = m_Surface->w;
    draw_pos.x = 0;
    draw_pos.y = 0;
	draw_pos.w = m_Surface->w;
	draw_pos.h = m_Surface->h;

	set_Load_Position(draw_pos);

	draw_pos.x = xpos;
	draw_pos.y = ypos;
	if (usingtrans) {
		colision_mask = new vector<bool>;
		create_Colision_Mask();
		pixel_perfect = true;
	}
	else {
		pixel_perfect = false;
	}
    //SDL_FreeSurface(m_Surface);

}

bitmap::bitmap(SDL_Texture* m_Texture_temp, vector<bool> * colision_mask_temp, int xpos, int ypos,int t_loadheight, int t_loadwidth)
{
	m_Texture = nullptr;
	m_Surface = nullptr;
    loadwidth = t_loadwidth;
    loadheight = t_loadheight;
	m_Texture = m_Texture_temp;
	

	m_Renderer = Game::m_Renderer;
    draw_pos.x = 0;
    draw_pos.y = 0;
	draw_pos.w = 100;
	draw_pos.h = 100;

	set_Load_Position(draw_pos);

	draw_pos.x = xpos;
	draw_pos.y = ypos;
	is_trans = true;
	colision_mask = colision_mask_temp;
	pixel_perfect = true;

    //SDL_FreeSurface(m_Surface);


}

bitmap::bitmap(SDL_Texture* m_Texture_temp, int xpos, int ypos)
{
	m_Texture = nullptr;
	m_Surface = nullptr;

	m_Texture = m_Texture_temp;
	

	m_Renderer = Game::m_Renderer;

    draw_pos.x = 0;
    draw_pos.y = 0;
	draw_pos.w = 100;
	draw_pos.h = 100;

	set_Load_Position(draw_pos);

	draw_pos.x = xpos;
	draw_pos.y = ypos;
    is_trans = false;
	pixel_perfect = false;
    //SDL_FreeSurface(m_Surface);

}

vector<int>* bitmap::get_colision_mask()
{
    if(submask == nullptr){
        if (colision_mask == nullptr) {
            for (int y = 0; y < Max_image_size; y++) {
                for (int x = 0; x < Max_image_size; x++) {
                    submask->push_back(1);
                }
            }
        }
        else {
            submask = new vector<int>;
            float xscale = (float)load_pos.w / Max_image_size;
            float yscale = (float)load_pos.h / Max_image_size;
            for (int y = 0; y < Max_image_size; y++) {
                for (int x = 0; x < Max_image_size; x++) {
                    int realx = x*xscale + load_pos.x;
                    int realy = y*yscale * loadwidth;
                    if (colision_mask->at(realx + realy)) {
                        submask->push_back(1);
                    }
                    else {
                        submask->push_back(0);
                    }
                }
            }
        }
    }
    return submask;
}

SDL_Texture * bitmap::get_Texture()
{
	return m_Texture;
}


int bitmap::getxpos() {
	return draw_pos.x;
}
int bitmap::getypos() {
	return draw_pos.y;
}
int bitmap::getwidth() {
	return draw_pos.w;
}
int bitmap::getheight() {
	return draw_pos.h;
}



void bitmap::set_Load_Position(int x, int y,int w,int h) {
	load_pos.x = x;
	load_pos.y = y;
	load_pos.w = w;
	load_pos.h = h;
}

void bitmap::set_Load_Position(positions temp_Pos) {
	load_pos = temp_Pos;
}

void bitmap::set_Draw_Position(int x, int y) {
	draw_pos.x = x;
	draw_pos.y = y;
}
void bitmap::move_Draw_Position(int x, int y) {
	draw_pos.x += x;
	draw_pos.y += y;
}

void bitmap::set_Scale(float newscale) {
	scale = newscale;
}

void bitmap::set_Draw_Dimensions(int width,int height) {
	draw_pos.w = width;
	draw_pos.h = height;
}

void bitmap::create_Colision_Mask()
{
	colision_mask->clear();
	if (!m_Surface) {
		return;
	}
	Uint32 transcolor = SDL_MapRGB(m_Surface->format, 255, 0, 255);


	for (int y = 0; y < m_Surface->h; y++) {

		for (int x = 0; x < m_Surface->w; x++) {

			if (getpixel(m_Surface, x, y) == transcolor) {
				colision_mask->push_back(false);

			}
			else {
				colision_mask->push_back(true);

			}
		}
	}

	SDL_UnlockTexture(m_Texture);
}

Uint32 bitmap::getpixel(SDL_Surface *surface, int x, int y)
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

void bitmap::draw() {
	if (m_Texture) {
		SDL_Rect destRect;
		destRect = {draw_pos.x + x_offset,draw_pos.y + y_offset ,(int)(draw_pos.w*scale),(int)(draw_pos.h*scale)};
		SDL_Rect loadRect;
		loadRect = { load_pos.x,load_pos.y ,load_pos.w,load_pos.h };

		SDL_RenderCopy(m_Renderer, m_Texture, &loadRect, &destRect);
    
         //  SDL_RenderPresent(m_Renderer);
	}
}

bitmap::~bitmap()
{
	if (m_Texture != nullptr) {
		m_Texture = nullptr;
	}
	if (m_Surface != nullptr) {
		m_Surface = nullptr;
	}
	if (colision_mask != nullptr) {
		colision_mask = nullptr;
	}
	if (m_Renderer) {
		m_Renderer = nullptr;
	}
}
