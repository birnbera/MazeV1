//
//  main.cpp
//  MazeV1
//
//  Created by Andrew Birnberg on 2/5/18.
//  Copyright © 2018 Andrew. All rights reserved.
//

#include "maze.hpp"

Maze::Maze(std::string file_name) {
    this->map = new Map(file_name);
    this->player = new Player(map->initial_position.x, map->initial_position.y, map->block_size);
}

Maze::~Maze() {
    delete this->map;
    delete this->player;
    if (this->window)
        SDL_DestroyWindow(this->window);
    if (this->renderer)
        SDL_DestroyRenderer(this->renderer);
}

void Maze::initialize() {
    atexit(SDL_Quit);
    if (SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize video system: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    this->window = SDL_CreateWindow("Maze v1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 320, 0);
    if (!this->window) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create window: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    if (!this->renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create renderer: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

void Maze::get_events() {
    
}

void Maze::render() {
    
}

void Maze::update_data() {
    
}

void Maze::run() {
    this->initialize();

    this->done = false;
    while (!this->done) {
        this->get_events();
        this->update_data();
        this->render();
    }
}


int main(int argc, const char * argv[]) {
    // insert code here...
    if (argc != 2)
        exit(EXIT_FAILURE);
    Maze maze(argv[1]);
    maze.run();
    return 0;
}
