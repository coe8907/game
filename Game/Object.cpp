#include "Object.h"
#include <iostream>

Object::Object(){
    
}
Object::Object(bitmap * passed_bitmap,bool p_solid)
{
	m_bitmap = passed_bitmap;
	solid = p_solid;
}
bitmap* Object::get_bitmap() {
	return m_bitmap;
}


void Object::colision(Object * target) {
    //cout<<"Object : colision " << endl;
	
}

void Object::update(int xoffset,int yoffset) {
	m_bitmap->set_xoffset(xoffset);
	m_bitmap->set_yoffset(yoffset);
}
void Object::update() {
	
}
void Object::draw() {
	m_bitmap->draw();
}
Object::~Object()
{
    delete m_bitmap;
	m_bitmap = nullptr;
}
