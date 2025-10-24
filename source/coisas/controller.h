#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <iostream>
#include <vector>
#include <string>

#include <utility>
#include <deque>

#include "puzzles.h"
#include "snake.h"
#include "food_spawn.h"

/**
 * @brief Controller responsible for the main game loop and state management.
 *
 * The controller coordinates input parsing, spawning food, path finding and
 * rendering. It keeps the current map (puzzle), snake position and tail, and
 * runs the game loop which moves the snake using the path finding utilities.
 *
 * Usage:
 *  - Construct with the default constructor which will prompt for a map and
 *    number of apples (rounds).
 *  - Call `game_start()` to run the game loop.
 */
class controller {
public:
    /**
     * @brief Start the game loop (blocks until game ends or user quits).
     */
    void game_start();

    /**
     * @brief Update internal state moving the snake along a path step.
     * @param path_index index in used_path describing the next position
     * @param used_path vector with the full path to follow
     * @param puzzle current puzzle map (used to update the displayed grid)
     */
    void update(size_t path_index, std::vector<std::pair<int, int>> used_path,
                            std::vector<std::vector<char>> puzzle);

    /**
     * @brief Render the current puzzle state to the terminal.
     */
    void render();

    controller();

    // Index of the selected map file (set by constructor prompt). Default -1
    int file_index = -1;

private:
    // Input parser initialized to look for puzzle files inside `assets/`.
    // Use relative path from the executable working directory. When running
    // from the project root the `assets/` folder is at `./assets`.
    Input input_handler{"assets"};

    // Parsed puzzle files found in the assets folder.
    std::vector<FileInfo> allfiles;

    // Responsible for placing food (apples) on the map.
    spawner food_spawn_handler;

    // Currently running puzzle data and snake position inside it.
    FileInfo running_game_puzzle;
    std::pair<int, int> snake_pos;

    // Path finding utility and the currently computed path.
    puzzle_things path_finder;
    std::vector<std::pair<int, int>> path;

    // Snake tail representation (deque for popping front easily).
    std::deque<std::pair<int, int>> tail;

    // Snake lives and state flags
    size_t snake_lifes = 5;
    bool grow_tail = false;
    bool is_dead = false;

    // How many apples will spawn (selected by user at start)
    int rounds = -1;
};

#endif