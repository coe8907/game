#ifndef Player_h
#define Player_h
#include "Object.h"
#include "Controller.h"
#include <cstdlib>
#include <cstdint>

using namespace std;
class Player: public Object, public Controller{
private:
    bool coll = false;
    float bounds = 800;
    
    void left();
    void right();
    void up();
    void down();
    
    void left_stick_x(int x_value);
    void left_stick_y(int y_value);
    
    void right_stick_x(int x_value);
    void right_stick_y(int y_value);
    
    void button_1();
    void button_2();
    void button_3();
    void button_4();
    int lastx;
    int lasty;
public:
    void colision(Object * target);
    
    Player(bitmap * passed_bitmap, bool p_solid, int id);
    
    void update(int xoffset, int yoffset);
    ~Player();
};

#endif /* Player_h */
