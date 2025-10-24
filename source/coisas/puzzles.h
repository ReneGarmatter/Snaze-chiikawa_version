
#ifndef PUZZLE_THINGS_HPP
#define PUZZLE_THINGS_HPP

#include <utility>
#include <vector>

/**
 * @class puzzle_things
 * @brief A class to find the shortest path in a 2D grid using GRAPHS.
 * point to a goal character ('&').
 */
class puzzle_things {
public:
  /**
   * @brief Finds the shortest path from a start point to the goal ('&').
   * @param puzzle A constant reference to a 2D vector of characters
   * representing the grid.
   * @param start A pair of integers {lines, col} for the starting position.
   * @return A vector of coordinate pairs for the shortest path. Returns an
   * empty vector if no path exists.
   */
  std::vector<std::pair<int, int>>
  find_path( std::vector<std::vector<char>> puzzle,
            std::pair<int, int> start, char goal);
  std::vector<std::pair<int, int>>
  find_wall_path(std::vector<std::vector<char>> puzzle,
             std::pair<int, int> start, char goal);

    private:
    bool is_valid(char cha);
};
#endif // PUZZLE_THINGS_HPP
