//
//  ray_caster.cpp
//  MazeV1
//
//  Created by Andrew Birnberg on 2/7/18.
//  Copyright © 2018 Andrew. All rights reserved.
//

#include "ray_caster.hpp"

double get_dist(double angle, double px, double py, double Ax, double Ay) {
    int octant;
    remquo(angle - M_PI / 8, M_PI_4, &octant);
    octant %= 8;
    switch (octant) {
        case 1: case -7: case 2: case -6: case 5: case -3: case 6: case -2:
            return fabs((py - Ay) / sin(angle));
            break;
        default:
            return fabs((px - Ax) / cos(angle));
            break;
    }
}

RayCaster::RayCaster(SDL_Renderer *renderer, Player *player, Map *map): renderer(renderer), player(player), map(map) {}

void RayCaster::render3d() {
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0x00);
    SDL_RenderClear(renderer);
    SDL_Rect vp;
    SDL_RenderGetViewport(renderer, &vp);
    SDL_Rect bottom_half = {0, vp.h / 2, vp.w, vp.h / 2};
    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x00);
    SDL_RenderFillRect(renderer, &bottom_half);
    SDL_Point vblock, hblock;
    double vDist, hDist, dtheta;
    dtheta = player->fov / vp.w;
    std::cout << player->x << ' ' << player->y << ' ' << player->angle << std::endl;
    for (double a = -player->fov / 2; a < player->fov / 2; a += dtheta) {
        vDist = find_intersect_v(player->x, player->y, player->angle + a, *map, vblock);
        hDist = find_intersect_h(player->x, player->y, player->angle + a, *map, hblock);
        if (hDist < vDist) {
            SDL_SetRenderDrawColor(renderer, 0x60, 0x60, 0x60, 0x00);
            draw_wall(hDist * cos(a), (a + player->fov / 2) * vp.w, vp.h);
        }
        else if (hDist > vDist) {
            SDL_SetRenderDrawColor(renderer, 0x70, 0x70, 0x70, 0x00);
            draw_wall(vDist * cos(a), (a + player->fov / 2) * vp.w, vp.h);
        }
    }
    SDL_RenderPresent(renderer);
}

void RayCaster::draw_wall(double dist, int column, int vh) {
    int lh = (vh * map->block_size) / (4 * dist * tan(player->fov / 2));
    SDL_RenderDrawLine(renderer, column, (vh - lh) / 2, column, (vh + lh) / 2);
}

double RayCaster::find_intersect_h(double px, double py, double angle, Map &map, SDL_Point &wall_coord) {
    SDL_Point A;
    uint32_t Xa, Ya;
    if (fmod(angle, M_PI) == 0)
        return INFINITY;

    int octant;
    remquo(angle - M_PI / 8, M_PI_4, &octant);
    octant %= 8;
    switch (octant) {
        case 0: case 1: case 2: case 3: case -7: case -6: case -5:
        {
            A.y = round(py/map.block_size) * map.block_size - 1;
            Ya = map.block_size;
            break;
        }
        default:
        {
            A.y = round(py/map.block_size) * map.block_size + map.block_size;
            Ya = -map.block_size;
            break;
        }
    }
    A.x = px + (py - A.y)/tan(angle);
    Xa = map.block_size/tan(angle);
    if (A.x / map.block_size > map.columns - 1 || A.y / map.block_size > map.rows - 1)
        return INFINITY;
    while (!map.layout[A.y/map.block_size][A.x/map.block_size]) {
        A.x += Xa;
        A.y += Ya;
        if (A.x < 0 || A.x/map.block_size > map.columns - 1 || A.y < 0 || A.y/map.block_size > map.rows - 1)
            return INFINITY;
    }
    return get_dist(angle, px, py, A.x, A.y);
}

double RayCaster::find_intersect_v(double px, double py, double angle, Map &map, SDL_Point &wall_coord) {
    SDL_Point A;
    uint32_t Xa, Ya;
    if (fmod(angle - M_PI_2, M_PI) == 0)
        return INFINITY;

    int octant;
    remquo(angle - M_PI / 8, M_PI_4, &octant);
    octant %= 8;
    switch (octant) {
        case 6: case -2: case 7: case -1: case 0: case 1: case -7:
        {
            A.x = round(px/map.block_size) * map.block_size - 1;
            Xa = map.block_size;
            break;
        }
        default:
        {
            A.x = round(px/map.block_size) * map.block_size + map.block_size;
            Xa = -map.block_size;
            break;
        }
    }
    A.y = py + (px - A.x)/tan(angle);
    Ya = map.block_size/tan(angle);
    if (A.y / map.block_size > map.rows - 1 || A.x / map.block_size > map.columns - 1)
        return INFINITY;
    while (!(map.layout[A.y/map.block_size][A.x/map.block_size])) {
        A.x += Xa;
        A.y += Ya;
        if (A.x < 0 || A.x/map.block_size > map.columns - 1 || A.y < 0 || A.y/map.block_size > map.rows - 1)
            return INFINITY;
    }
    return get_dist(angle, px, py, A.x, A.y);
}

void RayCaster::render2d() {
    SDL_Rect vp;
    SDL_RenderGetViewport(renderer, &vp);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0x4B, 0x4B, 0x4B, 0x00);
    SDL_RenderSetViewport(renderer, NULL);
    SDL_RenderSetScale(renderer, 1, 1);
    
    SDL_Rect win;
    SDL_RenderGetViewport(renderer, &win);
    double vp_scale = (float(win.w)/map->columns <= float(win.h)/map->rows) ? float(win.w)/map->columns : float(win.h)/map->rows;
    vp.h = vp_scale * map->rows;
    vp.w = vp_scale * map->columns;
    vp.x = (win.w - vp.w) / 2;
    vp.y = (win.h - vp.h) / 2;
    SDL_RenderFillRect(renderer, &vp);
    SDL_RenderSetViewport(renderer, &vp);
    SDL_RenderSetScale(renderer, vp_scale, vp_scale);
    SDL_SetRenderDrawColor(renderer, 0x8F, 0x8F, 0x8F, 0x00);
    for (uint32_t i = 0; i < map->rows; i++) {
        for (uint32_t j = 0; j < map->columns; j++) {
            if (map->layout[i][j] == 0) {
                SDL_Rect block = {int(j), int(i), 1, 1};
                SDL_RenderFillRect(renderer, &block);
            }
        }
    }
    SDL_RenderSetScale(renderer, vp_scale / 10, vp_scale / 10);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
    SDL_RenderDrawPoint(renderer, int(player->x * 10 / map->block_size), int(player->y * 10 / map->block_size));
    SDL_RenderPresent(renderer);
}
