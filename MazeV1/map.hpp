//
//  map.hpp
//  MazeV1
//
//  Created by Andrew Birnberg on 2/5/18.
//  Copyright © 2018 Andrew. All rights reserved.
//

#ifndef map_hpp
#define map_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>


class Map {
public:
    std::vector<std::vector<uint8_t>> layout;
    uint32_t rows;
    uint32_t columns;
    uint32_t block_size;
    struct initial_position {
        uint32_t x;
        uint32_t y;
    } initial_position;
    Map(std::string filename);
    void print_layout();
};

#endif /* map_hpp */
