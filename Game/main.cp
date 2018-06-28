//
//  main.cpp
//  Game
//
//  Created by Oliver Coe on 27/06/2018.
//
//

#include <stdio.h>


#pragma once
#ifdef __APPLE__
#include "TargetConditionals.h"
#ifdef TARGET_OS_MAC

#include "SDL2/SDL.h"
#endif
#elif defined _WIN32 || defined _WIN64

#include "SDL.h"
#endif
#include "Game.h"
#include <chrono>
#include <iostream>

#undef main

bool running = true;
void mainloop();

Game* game;

int ups = 0;
int fps = 0;

void paint() {
    
    game->paint();
    
    fps += 1;
}

int main(void) {
     game = new Game();
    mainloop();
    if (game) {
        delete game;
         game = nullptr;
      }
    return 0;
}
void mainloop() {
    while (running) {
        Uint32 startTime = SDL_GetTicks();
        Uint32 tickTime = SDL_GetTicks();
        while (running) {
            if(SDL_GetTicks() - startTime > 1000){
                std::cout<<"fps = " << fps <<std::endl;
                startTime = SDL_GetTicks();
                fps = 0;
            }
            if (SDL_GetTicks() - tickTime > 20) {
                 game->update();
                tickTime = SDL_GetTicks();
            }
            paint();
        }
    }
}
