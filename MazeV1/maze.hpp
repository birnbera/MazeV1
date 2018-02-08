//
//  maze.hpp
//  MazeV1
//
//  Created by Andrew Birnberg on 2/5/18.
//  Copyright © 2018 Andrew. All rights reserved.
//

#ifndef maze_hpp
#define maze_hpp

#include <iostream>
#include <SDL2/SDL.h>

#include "event.hpp"
#include "map.hpp"
#include "player.hpp"

class Maze : public Event {
    std::auto_ptr<Map> map;
    std::auto_ptr<Player> player;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    bool done;
    bool rerender;
    SDL_Rect viewport;
    float vp_scale;
    void initialize();
    void get_events();
    void get_event(const SDL_Event &e);
    void on_quit();
    void on_key_down(SDL_Keycode sym);
    void update_data();
    void render();
public:
    Maze(std::string file_name);
    ~Maze();
    void run();
};

#endif /* maze_hpp */
