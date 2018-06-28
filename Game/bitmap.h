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

struct positions {
	int x =0;
	int y= 0;
	int w= 0;
	int h= 0;
};

class bitmap
{
private :
    int loadwidth = 0;
    int loadheight = 0;
    vector<int> * submask;
	positions load_pos;
	positions draw_pos;
	bool pixel_perfect;
	vector<bool> * colision_mask;
	void checkPixels();
	void create_Colision_Mask();
	Uint32 getpixel(SDL_Surface * surface, int x, int y);
	float scale = 1;
	int x_offset = 0;
	int y_offset = 0;
	bool is_trans = false;
protected:
	SDL_Renderer*	m_Renderer;
	SDL_Surface*	m_Surface;
	SDL_Texture*	m_Texture;
	

public:
    
	
    
    
    int get_loadwidth(){return loadwidth;}
    int get_loadheight(){return loadheight;}
	bool get_trans() { return is_trans; }
	void set_xoffset(int newx) { x_offset = newx; };
	void set_yoffset(int newy) { y_offset = newy; };

	void move_xoffset(int newx) { x_offset += newx; };
	void move_yoffset(int newy) { y_offset += newy; };

	bitmap(std::string filename, int xpos, int ypos, bool usingtrans);
	bitmap(SDL_Texture * m_Texture_temp, vector<bool>* colision_mask_temp, int xpos, int ypos,int b,int a);
	bitmap(SDL_Texture * m_Texture_temp, int xpos, int ypos);
	
	
	/*GETs*/
	vector<int> * get_colision_mask();
	vector<bool> * get_master_mask() { return colision_mask; }
	SDL_Surface*	get_Surface();
	SDL_Texture*	get_Texture();

	int getxpos();

	int getypos();

	int getwidth();

	int getheight();


	/*SETs*/
	void set_Load_Position(int x, int y, int w, int h);
	void set_Load_Position(positions temp_Pos);

	void set_Draw_Position(int x, int y);

	void move_Draw_Position(int x, int y);

	void set_Scale(float newscale);

	void set_Draw_Dimensions(int width, int height);


	void draw();
	~bitmap();
};

