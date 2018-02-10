#include "maze.hpp"

double Maze::get_vertical_intersection(double angle) {
    double Ix, Iy;
    double initial_intersection, dx, dy, correction;
    
    if (double(90) > angle || angle > double(270)) {
        initial_intersection = map->block_size;
        correction = 0;
        dx = double(map->block_size);
    } else {
        initial_intersection = 0;
        correction = 1;
        dx = - double(map->block_size);
    }
    dy = fabs(double(map->block_size) * tan(angle * M_PI / 180));
    if (double(0) < angle && angle < double(180))
        dy *= -1;
    
    Ix = floor(player->x / double(map->block_size)) * double(map->block_size) + initial_intersection;
    Iy = player->y + (player->x-Ix) * tan(angle * M_PI / 180);
    
    int32_t x = floor(Ix / double(map->block_size)) - correction;
    int32_t y = floor(Iy / double(map->block_size));
    if (!(0 <= x && x< map->columns && 0 <= y && y < map->rows))
        return INFINITY;
    while(0 <= x && x< map->columns && 0 <= y && y < map->rows && !map->layout[y][x])
    {
        Ix += dx;
        x = floor(Ix / double(map->block_size)) - correction;
        Iy += dy;
        y = floor(Iy / double(map->block_size));
        if (!(0 <= x && x< map->columns && 0 <= y && y < map->rows))
            return INFINITY;
    }
    if ((45 > angle || angle > 315) || (135 < angle && angle < 225))
        return ((Ix - player->x) / cos(angle * M_PI / 180));
    else
        return ((player->y - Iy) / sin(angle * M_PI / 180));
}

double Maze::get_horizontal_intersection(double angle) {
    double Ix, Iy;
    double initial_intersection, dx, dy, correction;
    
    if (double(0) < angle && angle < double(180)) {
        initial_intersection = 0;
        correction = 1;
        dy = - double(map->block_size);
    } else {
        initial_intersection = double(map->block_size);
        correction = 0;
        dy = double(map->block_size);
    }
    dx = fabs(double(map->block_size) / tan(angle * M_PI / 180));
    if (double(90) < angle && angle < double(270))
        dx *= -1;
    
    Iy = floor(player->y / double(map->block_size)) * double(map->block_size) + initial_intersection;
    Ix = player->x + (player->y-Iy)/tan(angle * M_PI / 180);
    
    int32_t x = floor(Ix / map->block_size);
    int32_t y = floor(Iy / map->block_size) - correction;
    if (!(0 <= x && x< map->columns && 0 <= y && y < map->rows))
        return INFINITY;
    while(!map->layout[y][x])
    {
        Ix += dx;
        x = floor(Ix / map->block_size);
        Iy += dy;
        y = floor(Iy / map->block_size) - correction;
        if (!(0 <= x && x< map->columns && 0 <= y && y < map->rows))
            return INFINITY;
    }
    if ((45 > angle || angle > 315) || (135 < angle && angle < 225))
        return ((Ix - player->x) / cos(angle * M_PI / 180));
    else
        return ((player->y - Iy) / sin(angle * M_PI / 180));
}

double Maze::get_wall_height(double distance_to_slice) {
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    double distance_to_projection_plane = double(w) / (2 * tan(player->fov * M_PI / 360));
    double wall_height = map->block_size * distance_to_projection_plane / distance_to_slice;
    return (wall_height);
}

void Maze::render_wall(double slice_height, int window_height, int position, int wall_side) {
    int y1 = (window_height - slice_height) / 2;
    int y2 = y1 + slice_height;
    if (wall_side)
        SDL_SetRenderDrawColor(renderer, 0x8F, 0x8F, 0x8F, 0x00);
    else
        SDL_SetRenderDrawColor(renderer, 0x4B, 0x4B, 0x4B, 0x00);
    SDL_RenderDrawLine(renderer, position, y1, position, y2);
}

void Maze::render3d() {
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0x00);
    SDL_RenderClear(renderer);
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    SDL_Rect bottom_half = {0, h/2, w, h/2};
    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x00);
    SDL_RenderFillRect(renderer, &bottom_half);
    double angle, angle_step = player->fov / double(w);
    int position;
    for (position = 0, angle = player->angle + (player->fov / 2); position < w; angle -= angle_step, position++) {
        double distance;
        int wall_side;
        double checked_angle = check_angle(angle);
        if (checked_angle == double(0) || checked_angle == double(180)) {
            distance = get_vertical_intersection(checked_angle) * cos((angle - player->angle) * M_PI / 180);
            wall_side = 0;
        } else if (checked_angle == double(90) || checked_angle == double(270)) {
            double pd = get_horizontal_intersection(checked_angle);
            distance = pd * cos((angle - player->angle) * M_PI / 180);
            wall_side = 1;
        } else {
            double dh = get_horizontal_intersection(checked_angle);
            double dv = get_vertical_intersection(checked_angle);
            if (dh <= dv){
                distance = dh * cos((angle - player->angle) * M_PI / 180);
                wall_side = 1;
            } else {
                distance = dv * cos((angle - player->angle) * M_PI / 180);
                wall_side = 0;
            }
        }
        render_wall(get_wall_height(distance), h, position, wall_side);
    }
    SDL_RenderPresent(renderer);
}
