//
//  main.cpp
//  MazeV1
//
//  Created by Andrew Birnberg on 2/5/18.
//  Copyright © 2018 Andrew. All rights reserved.
//

#include "maze.hpp"

Maze::Maze(std::string file_name): map (new Map(file_name)), player (new Player(map->initial_position.x, map->initial_position.y, map->block_size)) {}

Maze::~Maze() {
    if (window)
        SDL_DestroyWindow(window);
    if (renderer)
        SDL_DestroyRenderer(renderer);
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
    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create renderer: %s", SDL_GetError());
        throw std::bad_alloc();
    }
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
}

void Maze::get_events() {
    
}

void Maze::render() {
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    float scale = (w/map->columns <= h/map->rows) ? w/map->columns : h/map->rows;
    SDL_Rect viewport;
    viewport.h = scale * map->rows;
    viewport.w = scale * map->columns;
    viewport.x = (w - viewport.w) / 2;
    viewport.y = (h - viewport.h) / 2;
    SDL_RenderSetViewport(renderer, &viewport);
    SDL_RenderSetScale(renderer, scale, scale);
    SDL_SetRenderDrawColor(renderer, 0x4B, 0x4B, 0x4B, 0x00);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0x8F, 0x8F, 0x8F, 0x00);
    for (uint32_t i = 0; i < map->rows; i++) {
        for (uint32_t j = 0; j < map->columns; j++) {
            if (map->layout[i][j] == 0) {
                SDL_Rect block = {int(j), int(i), 1, 1};
                SDL_RenderFillRect(renderer, &block);
            }
            
        }
    }
    SDL_RenderPresent(renderer);
}

void Maze::update_data() {
    
}

void Maze::run() {
    initialize();

    done = false;
//    while (!done) {
//        get_events();
//        update_data();
//        render();
//    }
    render();
    while(true)
        ;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    if (argc != 2)
        exit(EXIT_FAILURE);
    try {
        Maze maze(argv[1]);
        maze.run();
        std::getchar();
        exit(EXIT_SUCCESS);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}
