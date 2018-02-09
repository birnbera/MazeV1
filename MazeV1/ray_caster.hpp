//
//  ray_caster.hpp
//  MazeV1
//
//  Created by Andrew Birnberg on 2/7/18.
//  Copyright © 2018 Andrew. All rights reserved.
//

#ifndef ray_caster_hpp
#define ray_caster_hpp
#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include "map.hpp"
#include "player.hpp"

class RayCaster {
public:
    RayCaster(SDL_Renderer *renderer, Player &player, Map &map);
    ~RayCaster();
    void render2d();
    void render3d();
private:
    SDL_Renderer *renderer;
    Player player;
    Map map;
    double find_intersect_v(double px, double py, double angle, Map &map, SDL_Point &wall_coord);
    double find_intersect_h(double px, double py, double angle, Map &map, SDL_Point &wall_coord);
    void draw_wall(double dist, int column, int vh);
    
};

#endif /* ray_caster_hpp */
