//
//  player.cpp
//  MazeV1
//
//  Created by Andrew Birnberg on 2/5/18.
//  Copyright © 2018 Andrew. All rights reserved.
//

#include "player.hpp"

Player::Player(uint32_t x, uint32_t y, uint32_t block_size): x((block_size * x) + (block_size / 2.0)), y((block_size * y) + (block_size / 2.0)) {
    angle = 0;
    fov = M_PI / 3.0;
}

void Player::move_along(int8_t direction, const std::vector<std::vector<uint8_t>> &layout, const uint32_t block_size) {
    double dx = 10 * cos(angle) * direction;
    double ux = 0;
    double dy = 10 * -sin(angle) * direction;
    double uy = 0;
    if (layout[floor(y / block_size)][floor((x + dx)/ block_size)] == 0)
        ux = dx;
    if (layout[floor((y + dy) / block_size)][floor(x / block_size)] == 0)
        uy = dy;
    x += ux;
    y += uy;
}

void Player::move_strafe(int8_t direction, const std::vector<std::vector<uint8_t>> &layout, const uint32_t block_size) {
    double dx = 10 * -sin(angle) * direction;
    double dy = 10 * -cos(angle) * direction;
    double ux = 0;
    double uy = 0;
    if (layout[floor(y / block_size)][floor((x + dx)/ block_size)] == 0)
        ux = dx;
    if (layout[floor((y + dy) / block_size)][floor(x / block_size)] == 0)
        uy = dy;
    x += ux;
    y += uy;
}

void Player::update_angle(int8_t direction, double dtheta) {
    angle -= 10 * dtheta * direction;
    angle = fmod(fmod(angle, 2 * M_PI) + 2 * M_PI, 2 * M_PI);
}
