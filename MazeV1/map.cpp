//
//  map.cpp
//  MazeV1
//
//  Created by Andrew Birnberg on 2/5/18.
//  Copyright © 2018 Andrew. All rights reserved.
//

#include "map.hpp"

Map::Map(std::string filename) {
    std::string line;
    std::ifstream map_file(filename);
    if (map_file.is_open()) {
        this->rows = 0;
        this->columns = 0;
        bool start_exists = false;
        while (std::getline(map_file, line)) {
            this->rows++;
            std::vector<uint8_t> row;
            uint32_t i;
            for (i = 0; line[i] != '\n' && line[i] != '\0'; i++) {
                if (!start_exists && line[i] == '0') {
                    this->initial_position.y = this->rows;
                    this->initial_position.x = i;
                    start_exists = true;
                }
                if (line[i] == 'x') {
                    start_exists = true;
                    this->initial_position.y = this->rows;
                    this->initial_position.x = i;
                }
                if (!std::isdigit(line[i])) {
                    line[i] = '0';
                }
                row.push_back(line[i] - '0');
            }
            if (i > this->columns)
                this->columns = i;
            this->layout.push_back(row);
        }
        map_file.close();
        if (!start_exists) {
            std::cout << "No valid start location possible! Check your map!!" << std::endl;
            exit(EXIT_FAILURE);
        }
        for (uint32_t i = 0; i < this->rows; i++) {
            this->layout[i].resize(this->columns, 0);
            this->layout[i].insert(this->layout[i].begin(), 1);
            this->layout[i].push_back(1);
        }
        this->rows += 2;
        this->columns += 2;
        this->initial_position.x += 1;
        this->initial_position.y += 1;
        this->layout.insert(this->layout.begin(), std::vector<uint8_t>(this->columns, 1));
        this->layout.push_back(std::vector<uint8_t>(this->columns, 1));
    } else {
        std::cout << "Could not open file: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Map::print_layout() {
    for (uint8_t i = 0; i < this->rows; i++)
    {
        for (uint8_t j = 0; j < this->columns; j++) {
            if (j) {
                std::cout <<  " ";
            }
            std::cout << int(this->layout[i][j]);
        }
        std::cout << std::endl;
    }
}
