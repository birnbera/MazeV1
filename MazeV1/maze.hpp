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
#include "player.hpp"

class Maze {
    std::auto_ptr<Map> map;
    std::auto_ptr<Player> player;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    bool done;
    void initialize();
    void get_events();
    void update_data();
    void render();
public:
    Maze(std::string file_name);
    ~Maze();
    void run();
};

#endif /* maze_hpp */
