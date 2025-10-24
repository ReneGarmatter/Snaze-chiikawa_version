#include <bits/stdc++.h>
#include "puzzles.h"

  std::vector<std::pair<int, int>>
  /**
   * @brief BFS algorithm, returns a path to the closest apple
   * 
   * @param puzzle 
   * @param start 
   * @param goal 
   */
  puzzle_things::find_path( // treinamento de programaçao serviu rene!! // atarr
       std::vector<std::vector<char>> puzzle, std::pair<int, int> start, char goal) {

    int lines = puzzle.size();
    if (lines == 0)
      return {};
    int cols = puzzle[0].size();

    std::queue<std::pair<int, int>> q;

    // Key: child coordinate, Value: parent coordinate.
    std::map<std::pair<int, int>, std::pair<int, int>> connections_map;

    std::vector<std::vector<bool>> visited(lines,
                                           std::vector<bool>(cols, false));

    q.push(start);
    visited[start.first][start.second] = true;

    std::pair<int, int> end = {-1, -1};

    //search path
    while (!q.empty()) {
      std::pair<int, int> current = q.front();
      q.pop();

      if (puzzle[current.first][current.second] == goal) {
        end = current;
        break;
      }

      std::vector<int> linechange = {-1, 1, 0, 0}; // variations of line
      std::vector<int> colchange = {0, 0, -1, 1};  // variations of colum

      for (int i = 0; i < 4; ++i) {
        std::pair<int, int> neighbor = {current.first + linechange[i],
                                        current.second + colchange[i]};
        if (neighbor.first >= 0 && neighbor.first < lines && // valid line check
            neighbor.second >= 0 && neighbor.second < cols && // valid colum check
            !visited[neighbor.first][neighbor.second] && // tile visited check
            (puzzle[neighbor.first][neighbor.second] == ' ' ||
            puzzle[neighbor.first][neighbor.second] == 'f')){//tail colision check
            
            visited[neighbor.first][neighbor.second] = true; // mark current as visited
            connections_map[neighbor] = current; 
            q.push(neighbor);
        }
      }
    }

    //TODO: try to implement it by making another algorithm wich is triggered when the BFS
    //path finder doesnt find the food because of a tail blocking the way, if that coondition
    //is met the snake will start to search for the closest wall and will travel next by it until
    //the snake body unblocks the way to the food;

    if (end.first != -1) {
      std::vector<std::pair<int, int>> path;
      std::pair<int, int> current = end;

      while (current != start) {
        path.push_back(current);
        current = connections_map[current];
      }
      path.push_back(start);
      std::reverse(path.begin(), path.end());
      return path;
    }
    // PATH NOT FOUND
    return {};
  }

  /**
   * @brief BFS algorithm, returns a path to the farthest wall
   * 
   * @param puzzle 
   * @param start 
   * @param goal 
   * @return std::vector<std::pair<int, int>> 
   */
  std::vector<std::pair<int, int>>
  puzzle_things::find_wall_path( 
       std::vector<std::vector<char>> puzzle, std::pair<int, int> start, char goal) {

    int lines = puzzle.size();
    if (lines == 0)
      return {};
    int cols = puzzle[0].size();

    std::queue<std::pair<int, int>> q;

    // Key: child coordinate, Value: parent coordinate.
    std::map<std::pair<int, int>, std::pair<int, int>> connections_map;

    std::vector<std::vector<bool>> visited(lines,
                                           std::vector<bool>(cols, false));

    q.push(start);
    visited[start.first][start.second] = true;

    std::pair<int, int> end = {-1, -1};

    //search path
    std::pair<int, int> current;
    while (!q.empty()) {
      current = q.front();
      q.pop();

      std::vector<int> linechange = {-1, 1, 0, 0}; // variations of line
      std::vector<int> colchange = {0, 0, -1, 1};  // variations of colum

      for (int i = 0; i < 4; ++i) {
        std::pair<int, int> neighbor = {current.first + linechange[i],
                                        current.second + colchange[i]};
        if (neighbor.first >= 0 && neighbor.first < lines && // valid line check
            neighbor.second >= 0 && neighbor.second < cols && // valid colum check
            !visited[neighbor.first][neighbor.second] && // tile visited check
            (puzzle[neighbor.first][neighbor.second] == ' ' ||
            puzzle[neighbor.first][neighbor.second] == 'f')) {//tail colision check
            
            visited[neighbor.first][neighbor.second] = true; // mark current as visited
            connections_map[neighbor] = current; 
            q.push(neighbor);
        }
      }
    }

    std::vector<std::pair<int, int>> path;
    while (current != start) {
      path.push_back(current);
      current = connections_map[current];
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
    
  }

  bool puzzle_things::is_valid(char cha) {
    if (cha == '#' || cha == 'x') {
      return false;
    }
    return true;
  }
