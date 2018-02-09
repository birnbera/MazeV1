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

#include "map.hpp"
#include "event.hpp"
#include "player.hpp"
#include "ray_caster.hpp"

class Maze : public Event {
    Map *map = NULL;
    Player *player = NULL;
    RayCaster *raycaster = NULL;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Rect viewport;
    bool done;
    bool rerender;
    float vp_scale;
    void initialize();

    void get_events();
    void get_event(const SDL_Event &e);
    void on_quit();
    void on_key_down(SDL_Keycode sym);
    void update_data();
public:
    Maze(std::string file_name);
    ~Maze();
    void run();
};

#endif /* maze_hpp */
