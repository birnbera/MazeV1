#include "map.hpp"

Map::Map(std::string filename) {
    std::string line;
    std::ifstream map_file(filename);
    if (map_file.is_open()) {
        rows = 0;
        columns = 0;
        bool start_exists = false;
        while (std::getline(map_file, line)) {
            rows++;
            std::vector<uint8_t> row;
            uint32_t i;
            for (i = 0; line[i] != '\n' && line[i] != '\0'; i++) {
                if (!start_exists && line[i] == '0') {
                    initial_position.y = rows - 1;
                    initial_position.x = i;
                    start_exists = true;
                }
                if (line[i] == 'x') {
                    start_exists = true;
                    initial_position.y = rows - 1;
                    initial_position.x = i;
                }
                if (!std::isdigit(line[i])) {
                    line[i] = '0';
                }
                row.push_back(line[i] - '0');
            }
            if (i > columns)
                columns = i;
            layout.push_back(row);
        }
        map_file.close();
        if (!start_exists) {
            std::cout << "No valid start location possible! Check your map!!" << std::endl;
            exit(EXIT_FAILURE);
        }
        for (uint32_t i = 0; i < this->rows; i++) {
            layout[i].resize(columns, 0);
            layout[i].insert(layout[i].begin(), 1);
            layout[i].push_back(1);
        }
        rows += 2;
        columns += 2;
        initial_position.x += 1;
        initial_position.y += 1;
        layout.insert(layout.begin(), std::vector<uint8_t>(columns, 1));
        layout.push_back(std::vector<uint8_t>(columns, 1));
    } else {
        std::cout << "Could not open file: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Map::print_layout() {
    for (uint8_t i = 0; i < rows; i++)
    {
        for (uint8_t j = 0; j < columns; j++) {
            if (j) {
                std::cout <<  " ";
            }
            std::cout << int(layout[i][j]);
        }
        std::cout << std::endl;
    }
}
