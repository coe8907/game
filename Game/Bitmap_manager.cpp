#include "Bitmap_manager.h"
#include <map>
using namespace std;

struct bitmap_info {
	
	SDL_Texture*	m_Texture;
	vector<bool> * colision_mask;
    bitmap * master_bitmap;
};
std::map<string, bitmap_info> loaded;


Bitmap_manager::Bitmap_manager()
{
}
bitmap* Bitmap_manager::create_bitmap(std::string filename, int xpos, int ypos, bool usingtrans){
    bitmap_info * temp = new bitmap_info;
    if (loaded.find(filename) != loaded.end()) {
        temp->colision_mask = loaded.at(filename).colision_mask;
        temp->m_Texture = loaded.at(filename).m_Texture;
        temp->master_bitmap= loaded.at(filename).master_bitmap;
        if (temp->colision_mask != nullptr) {
            int xsize = temp->master_bitmap->get_loadwidth();
            int ysize = temp->master_bitmap->get_loadheight();
            return new bitmap(temp->m_Texture,  temp->colision_mask, xpos, ypos, xsize, ysize);
        }
        if (temp->colision_mask == nullptr) {
            return new bitmap(temp->m_Texture,  xpos, ypos);
        }
    }
    
    bitmap * t = new bitmap(filename, xpos, ypos, usingtrans);
    temp->master_bitmap = t;
    temp->colision_mask = t->get_master_mask();;
    temp->m_Texture = t->get_Texture();
    
    loaded[filename] = *temp;
    
    return t;
    
}

Bitmap_manager::~Bitmap_manager()
{
    for(std::map<std::string, bitmap_info>::iterator itr = loaded.begin(); itr != loaded.end(); itr++)
    {
        SDL_DestroyTexture( itr->second.m_Texture);
        delete itr->second.colision_mask;
    }
}
