#pragma once
#pragma once
#include "bitmap.h"
class Bitmap_manager

{
public:
	Bitmap_manager();
	bitmap * create_bitmap(std::string filename, int xpos, int ypos, bool usingtrans);
	~Bitmap_manager();
};

