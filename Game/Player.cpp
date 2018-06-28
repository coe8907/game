#include <stdio.h>
#include "Player.h"
#include<iostream>


int max_speed = 5;
int drag_speed_x = 2;
int drag_speed_y = 2;
float acc_x = 0.5f;
float acc_y = 0.5f;

Player::Player(bitmap * passed_bitmap,bool p_solid,int id ):Object(passed_bitmap,p_solid), Controller(id) {
    xspeed = 0.0f;
    yspeed = 0.0f;
}
Player::~Player(){
    
}


void Player::update(int xoffset, int yoffset) {
    m_bitmap->set_xoffset(xoffset);
    m_bitmap->set_yoffset(yoffset);
    
    
    
    c_update();
    if (abs((int)xspeed) > max_speed) {
        if (xspeed > 0) {
            xspeed = max_speed;
        }
        else {
            xspeed = -max_speed;
        }
    }
    if (abs((int)yspeed) > max_speed) {
        if (yspeed > 0) {
            yspeed = max_speed;
        }
        else {
            yspeed = -max_speed;
        }
    }
    
    xspeed += acc_x;
    if (xspeed >= 2) { xspeed -= drag_speed_x; }else if(xspeed > 0 && drag_speed_x != 0)(xspeed = 0);
    if (xspeed <= -2) { xspeed += drag_speed_x; }else if (xspeed < 0&&drag_speed_x != 0)(xspeed = 0);
    
    yspeed += acc_y;
    if (yspeed >= 2) { yspeed -= drag_speed_y; }
    else if (yspeed > 0 && drag_speed_y != 0)(yspeed = 0);
    if (yspeed <= -2) { yspeed += drag_speed_y; }
    else if (yspeed < 0 && drag_speed_y != 0)(yspeed = 0);
    
    
    if (!coll) {
        lastx = get_x();
        lasty = get_y();
        m_bitmap->move_Draw_Position(xspeed, yspeed);
    }
    else {
        xspeed = 0;
        yspeed = 0;
        m_bitmap->set_Draw_Position(lastx, lasty);
        ///xspeed = -xspeed*2;
        ///yspeed = -yspeed*2;
        coll = false;
    }
};
void Player::colision(Object * target){
    coll = true;
}

void Player::left()
{
}

void Player::right()
{
}

void Player::up()
{
}

void Player::down()
{
}

void Player::left_stick_x(int x_value)
{
    
}

void Player::left_stick_y(int y_value)
{
    
}

void Player::right_stick_x(int x_value)
{if (abs(x_value) < 4000) {
    drag_speed_x = 2;
    acc_x = 0;
}
else {
    drag_speed_x = 0;
    float i = 0.5f;
    if (x_value > 0) {
        acc_x = i;
    }
    else {
        acc_x = -i;
    }
}
}

void Player::right_stick_y(int y_value)
{if (abs(y_value) < 4000) {
    drag_speed_y = 2;
    acc_y = 0;
}
else {
    drag_speed_y = 0;
    float i = 0.5f;
    if (y_value > 0) {
        acc_y = i;
    }
    else {
        acc_y = -i;
    }
}
}

void Player::button_1()
{
}

void Player::button_2()
{
}

void Player::button_3()
{
}

void Player::button_4()
{
}
