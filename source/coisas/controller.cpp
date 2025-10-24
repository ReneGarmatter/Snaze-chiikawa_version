#include <iostream>
#include <vector>
#include <string>

#include <chrono>
#include <thread>
#include <cstdlib>
#include <deque>

#include "puzzles.h"
#include "snake.h"
#include "controller.h"

/**
 * @brief updates game states
 * 
 * @param path_index 
 * @param used_path 
 * @param puzzle 
 */
void controller::update(size_t path_index, std::vector<std::pair<int, int>> used_path, 
                        std::vector<std::vector<char>> puzzle){
    if(grow_tail && tail.empty()){
        tail.push_back(snake_pos);
        grow_tail = false;
    }
    if(tail.empty()){
        running_game_puzzle.puzzle[snake_pos.first][snake_pos.second] = ' ';
        snake_pos = used_path[path_index];
        running_game_puzzle.puzzle[snake_pos.first][snake_pos.second] = 's';
    }
    else{
        if(!grow_tail){
            running_game_puzzle.puzzle[tail.front().first][tail.front().second] = ' ';
            tail.pop_front();
        }
        grow_tail = false;
        tail.push_back(snake_pos);

        for(int i=0; i<tail.size(); i++){
            if(i == tail.size()-1){
                running_game_puzzle.puzzle[tail[i].first][tail[i].second] = 'c';
            }
            else{
                running_game_puzzle.puzzle[tail[i].first][tail[i].second] = 't';
            }
        }
        snake_pos = used_path[path_index];
        running_game_puzzle.puzzle[snake_pos.first][snake_pos.second] = 's';
    }
}

/**
 * @brief renders map
 * 
 */
void controller::render(){
    //clear terminal
    std::system("clear");

    //render lifes
    std::cout << "Lifes: ";
    for(size_t i=0; i<snake_lifes; i++){
        std::cout << "🤍";
    }
    std::cout << std::endl;

    //render game
    for(auto line:running_game_puzzle.puzzle){
        for(auto element:line){
            switch(element){
                case '#':
                    std::cout << "█"; break;
                case 's':
                    std::cout << "●"; break;
                case 't':
                    std::cout << "◯"; break;
                case 'c':
                    std::cout << "◯"; break;
                case ' ':
                    std::cout << ' '; break;
                case 'f':
                    std::cout << "@"; break;
                case '.':
                    std::cout << ' '; break;
                default:
                    std::cout << "█"; break;
            }
        }
        std::cout << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

/**
 * @brief starts a game round
 * 
 */
void controller::game_start(){    
    snake_pos = running_game_puzzle.start;
    running_game_puzzle = allfiles[file_index];

    size_t round_counter = rounds;
    while(round_counter--){
        food_spawn_handler.spawn_food(running_game_puzzle.puzzle);
        //initial render
        render();
        
        //calling the find path method
        path = path_finder.find_path(running_game_puzzle.puzzle, snake_pos, 'f');
        
        //TODO: snake death
        std::vector<std::pair<int, int>> path_to_wall;
        if(path.empty() && !is_dead){
            //search for the farthest wall
            path_to_wall = path_finder.find_wall_path(running_game_puzzle.puzzle, snake_pos, '#');
    
            int i=1;
            while(path.empty()){
                if(i == path_to_wall.size()){
                    path_to_wall = path_finder.find_wall_path(running_game_puzzle.puzzle, snake_pos, '#');
                    i=1;
                }

                if(running_game_puzzle.puzzle[path_to_wall[i].first][path_to_wall[i].second] == '#' ||
                    running_game_puzzle.puzzle[path_to_wall[i].first][path_to_wall[i].second] == 'c' ||
                    running_game_puzzle.puzzle[path_to_wall[i].first][path_to_wall[i].second] == 's' ||
                    running_game_puzzle.puzzle[path_to_wall[i].first][path_to_wall[i].second] == 't'){
                        is_dead = true;
                        std::cout << "snake is dead!" << std::endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                        break;
                    }

                update(i, path_to_wall, running_game_puzzle.puzzle);
                render();

                path = path_finder.find_path(running_game_puzzle.puzzle, snake_pos, 'f');
                i++;
            }
            
        }
        //updates snake position on the puzzle and renders until it reaches the food
        if(is_dead){
            snake_lifes--;
            if(snake_lifes == 0){
                std::cout   << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣠⡀⠀" << std::endl
                            << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣤⠀⠀⠀⢀⣴⣿⡶⠀⣾⣿⣿⡿⠟⠛⠁"<< std::endl
                            << "⠀⠀⠀⠀⠀⠀⣀⣀⣄⣀⠀⠀⠀⠀⣶⣶⣦⠀⠀⠀⠀⣼⣿⣿⡇⠀⣠⣿⣿⣿⠇⣸⣿⣿⣧⣤⠀⠀⠀"<< std::endl
                            << "⠀⠀⢀⣴⣾⣿⡿⠿⠿⠿⠇⠀⠀⣸⣿⣿⣿⡆⠀⠀⢰⣿⣿⣿⣷⣼⣿⣿⣿⡿⢀⣿⣿⡿⠟⠛⠁⠀⠀"<< std::endl
                            << "⠀⣴⣿⡿⠋⠁⠀⠀⠀⠀⠀⠀⢠⣿⣿⣹⣿⣿⣿⣿⣿⣿⡏⢻⣿⣿⢿⣿⣿⠃⣼⣿⣯⣤⣴⣶⣿⡤⠀"<< std::endl
                            << "⣼⣿⠏⠀⣀⣠⣤⣶⣾⣷⠄⣰⣿⣿⡿⠿⠻⣿⣯⣸⣿⡿⠀⠀⠀⠁⣾⣿⡏⢠⣿⣿⠿⠛⠋⠉⠀⠀⠀"<< std::endl
                            << "⣿⣿⠲⢿⣿⣿⣿⣿⡿⠋⢰⣿⣿⠋⠀⠀⠀⢻⣿⣿⣿⠇⠀⠀⠀⠀⠙⠛⠀⠀⠉⠁⠀⠀⠀⠀⠀⠀⠀"<< std::endl
                            << "⠹⢿⣷⣶⣿⣿⠿⠋⠀⠀⠈⠙⠃⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"<< std::endl
                            << "⠀⠀⠈⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣤⣴⣶⣦⣤⡀⠀"<< std::endl
                            << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡀⠀⠀⠀⠀⠀⠀⠀⣠⡇⢰⣶⣶⣾⡿⠷⣿⣿⣿⡟⠛⣉⣿⣿⣿⠆"<< std::endl
                            <<"⠀⠀⠀⠀⠀⠀⢀⣤⣶⣿⣿⡎⣿⣿⣦⠀⠀⠀⢀⣤⣾⠟⢀⣿⣿⡟⣁⠀⠀⣸⣿⣿⣤⣾⣿⡿⠛⠁⠀"<< std::endl
                            <<"⠀⠀⠀⠀⣠⣾⣿⡿⠛⠉⢿⣦⠘⣿⣿⡆⠀⢠⣾⣿⠋⠀⣼⣿⣿⣿⠿⠷⢠⣿⣿⣿⠿⢻⣿⣧⠀⠀⠀"<< std::endl
                            <<"⠀⠀⠀⣴⣿⣿⠋⠀⠀⠀⢸⣿⣇⢹⣿⣷⣰⣿⣿⠃⠀⢠⣿⣿⢃⣀⣤⣤⣾⣿⡟⠀⠀⠀⢻⣿⣆⠀⠀"<< std::endl
                            <<"⠀⠀⠀⣿⣿⡇⠀⠀⢀⣴⣿⣿⡟⠀⣿⣿⣿⣿⠃⠀⠀⣾⣿⣿⡿⠿⠛⢛⣿⡟⠀⠀⠀⠀⠀⠻⠿⠀⠀"<< std::endl
                            <<"⠀⠀⠀⠹⣿⣿⣶⣾⣿⣿⣿⠟⠁⠀⠸⢿⣿⠇⠀⠀⠀⠛⠛⠁⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀"<< std::endl
                            <<"⠀⠀⠀⠀⠈⠙⠛⠛⠛⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"<< std::endl;
                            return;
            }
            is_dead = false;
            tail.clear();
            path.clear();
            game_start();
            return;
        }
        else{
            for(size_t i=0; i<path.size(); i++){
                update(i, path, running_game_puzzle.puzzle);
                render();
            }
        }
        grow_tail = true;

    }   

    std::cout << "All apples have been eaten" << std::endl;
}

/**
 * @brief Construct a new controller::controller object
 * 
 */
controller::controller(){

    allfiles = input_handler.getFiles();
    while(!(file_index >= 0 && file_index < allfiles.size())){
        std::system("clear");
        std::cout << "Choose game map:" << std::endl;
        for(int i=0; i<allfiles.size(); i++){
            std::cout << i+1 << " - " << allfiles[i].name << std::endl;
        }
        std::cin >> file_index;
        file_index--;
    }
    running_game_puzzle = allfiles[file_index];

    while(rounds < 0){
        std::system("clear");
        std::cout << "Choose how many apples will spawn:" << std::endl;
        std::cin >> rounds;
    }
    
}