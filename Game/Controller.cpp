#include "Controller.h"



Controller::Controller(int t_id)
{
    id = t_id;
    if (SDL_NumJoysticks() > 0) {
        // Open joystick
        if (SDL_NumJoysticks() >= id) {
            my_controller = SDL_JoystickOpen(id);
            cout << "Number of joy sticks " << SDL_NumJoysticks() << endl;
            cout << SDL_JoystickNumAxes(my_controller) << endl;
        }
        else {
            cout << "  JOY STICKS ID not found " << endl;
        }
    }
    else {
        cout << " NO JOY STICKS " << endl;
    }
}


void Controller::c_update()
{
    SDL_Event e;
    vector<SDL_Event> a;
    while (SDL_PollEvent(&e) != 0)
    {
        
        if (e.type == SDL_JOYAXISMOTION) {
            if (e.jaxis.which == id) {
                if (e.jaxis.axis == 0) {
                    //cout << "0" << endl;
                    //	left_stick_x(e.jaxis.value);
                }
                if (e.jaxis.axis == 1) {
                    //cout << "1" << endl;
                    //left_stick_y(e.jaxis.value);
                }
                if (e.jaxis.axis == 2) {
                    //cout << "2" << endl;
                    //
                }
                if (e.jaxis.axis == 3) {
                    //cout << "3" << endl;
                    right_stick_x(e.jaxis.value);
                }
                if (e.jaxis.axis == 4) {
                    //cout << "4" << endl;
                    right_stick_y(e.jaxis.value);
                    
                }
            }
            else { 
                a.push_back(e);
                //int i = SDL_PushEvent(&e); 
                //	cout << i << endl;
            }
        }
    }
    for (int i = 0; i < a.size(); i++) {
        SDL_PushEvent(&a.at(i));
    }
    
    //Sint16 x_move = SDL_JoystickGetAxis(my_controller, 0);
    //Sint16 y_move = SDL_JoystickGetAxis(my_controller, 1);
    //cout << "xmove = " << x_move << endl;
    //cout << "ymove = " << y_move << endl;
    
}

Controller::~Controller()
{
}
