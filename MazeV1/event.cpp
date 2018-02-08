//
//  event.cpp
//  MazeV1
//
//  Created by Andrew Birnberg on 2/7/18.
//  Copyright © 2018 Andrew. All rights reserved.
//

#include "event.hpp"

Event::Event() {}

Event::~Event() {}

void Event::get_event(const SDL_Event &e) {
    switch (e.type) {
        case SDL_QUIT:
            on_quit();
            break;
        case SDL_KEYDOWN:
            on_key_down(e.key.keysym.sym);
            break;
        case SDL_KEYUP:
            on_key_up(e.key.keysym.sym);
            break;
        case SDL_MOUSEMOTION:
            on_mouse_move(e.motion.x, e.motion.y, e.motion.xrel, e.motion.yrel);
            break;
        default:
            break;
    }
}

void Event::on_quit() {}

void Event::on_key_down(SDL_Keycode sym) {}

void Event::on_key_up(SDL_Keycode sym) {}

void Event::on_mouse_move(int x, int y, int xrel, int yrel) {};
