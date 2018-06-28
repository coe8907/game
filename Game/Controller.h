#pragma once
#ifdef __APPLE__
#include "TargetConditionals.h"
#ifdef TARGET_OS_MAC

#include "SDL2/SDL.h"
#endif
#elif defined _WIN32 || defined _WIN64

#include "SDL.h"
#endif

#include <iostream>
#include <vector>
using namespace std;
class Controller
{
protected:
    SDL_Joystick* my_controller = NULL;
    int id = 0;
public:
    Controller();
    virtual void left() {};
    virtual void right() {};
    virtual void up() {};
    virtual void down() {};
    
    virtual void left_stick_x(int x_value) {};
    virtual void left_stick_y(int y_value) {};
    
    virtual void right_stick_x(int x_value) {};
    virtual void right_stick_y(int y_value) {};
    
    virtual void button_1() {};
    virtual void button_2() {};
    virtual void button_3() {};
    virtual void button_4() {};
    
    Controller(int id);
    
    void c_update();
    ~Controller();
};


