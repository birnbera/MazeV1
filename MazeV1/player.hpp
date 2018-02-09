#ifndef player_hpp
#define player_hpp

#include "map.hpp"
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <cstdlib>

class Player {
public:
    double x;
    double y;
    double angle;
    double fov;
    Player(uint32_t x, uint32_t y, uint32_t block_size);
    void move_along(int8_t direction, const std::vector<std::vector<uint8_t>> &layout, const uint32_t block_size);
    void move_strafe(int8_t direction, const std::vector<std::vector<uint8_t>> &layout, const uint32_t block_size);
    void update_angle(int8_t direction);
};

double check_angle(double angle);

#endif /* player_hpp */
