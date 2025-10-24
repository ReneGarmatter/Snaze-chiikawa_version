#include <iostream>
#include <vector>
#include <string>

#include <utility>
#include <random>

#include "food_spawn.h"

void spawner::spawn_food(std::vector<std::vector<char>> &puzzle){
    std::vector<std::pair<int, int>> valid_spawn_position;
    
    for(size_t i=0; i<puzzle.size(); i++){
        for(size_t j=0; j<puzzle[i].size(); j++){
            if(puzzle[i][j] == ' '){
                valid_spawn_position.push_back(std::make_pair(i, j));
            }
        }
    }

    if(valid_spawn_position.empty()){
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, valid_spawn_position.size()-1);
    int idx = distrib(gen);

    puzzle[valid_spawn_position[idx].first][valid_spawn_position[idx].second] = 'f';
}