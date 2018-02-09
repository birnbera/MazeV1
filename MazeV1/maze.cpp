//
//  main.cpp
//  MazeV1
//
//  Created by Andrew Birnberg on 2/5/18.
//  Copyright © 2018 Andrew. All rights reserved.
//

#include "maze.hpp"

Maze::Maze(std::string file_name): map (new Map(file_name)) {
    player = new Player(map->initial_position.x, map->initial_position.y, map->block_size);
}

Maze::~Maze() {
    if (window)
        SDL_DestroyWindow(window);
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (map)
        delete map;
    if (player)
        delete player;
    
}

void Maze::initialize() {
    atexit(SDL_Quit);
    if (SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize video system: %s", SDL_GetError());
        throw std::bad_alloc();
    }
    window = SDL_CreateWindow("Maze v1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 320, 0);
    if (!window) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create window: %s", SDL_GetError());
        throw std::bad_alloc();
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create renderer: %s", SDL_GetError());
        throw std::bad_alloc();
    }
    raycaster = new RayCaster(renderer, player, map);
}

void Maze::get_events() {
    SDL_Event e;
    rerender = false;
    while (SDL_PollEvent(&e))
        get_event(e);
}

void Maze::get_event(const SDL_Event &e) {
    Event::get_event(e);
}

void Maze::on_quit() {
    done = true;
}

void Maze::on_key_down(SDL_Keycode sym) {
    rerender = true;
    SDL_Rect vp;
    SDL_RenderGetViewport(renderer, &vp);
    double dtheta = player->fov / vp.w;
    switch (sym) {
        case SDLK_q:
            on_quit();
            rerender = false;
            break;
        case SDLK_UP:
            player->move_along(1, map->layout, map->block_size);
            break;
        case SDLK_DOWN:
            player->move_along(-1, map->layout, map->block_size);
            break;
        case SDLK_LEFT:
            player->update_angle(1, dtheta);
            break;
        case SDLK_RIGHT:
            player->update_angle(-1, dtheta);
            break;
        case SDLK_a:
            player->move_strafe(1, map->layout, map->block_size);
            break;
        case SDLK_d:
            player->move_strafe(-1, map->layout, map->block_size);
            break;
        default:
            break;
    }
}

void Maze::update_data() {
    
}

void Maze::run() {
    initialize();
    raycaster->render3d();
    done = false;
    while (!done) {
        get_events();
        update_data();
        if (rerender)
            raycaster->render3d();
    }
}


int main(int argc, const char * argv[]) {
    if (argc != 2)
        exit(EXIT_FAILURE);
    try {
        Maze maze(argv[1]);
        maze.run();
        exit(EXIT_SUCCESS);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}
