#pragma once
#include "bitmap.h"
class Object
{
private:
	bool solid = false;
	
    
protected:
    bitmap * m_bitmap;
public:
    char name = 'O';
	int get_x() { return m_bitmap->getxpos(); }
	int get_y() { return m_bitmap->getypos(); }
	int get_width() { return m_bitmap->getwidth(); }
	int get_height() { return m_bitmap->getheight(); }
	bitmap* get_bitmap();
    virtual void colision(Object * target);
    Object();
	Object(bitmap * m_bitmap, int xpos, int ypos, bool colision);
	Object(bitmap * passed_bitmap, bool p_solid);
	float xspeed = 0;
	float yspeed = 0;
	virtual void update();
	virtual void update(int xoffset, int yoffset);
	void draw();
	bool is_solid() {
		return solid;
	}
	~Object();
};

