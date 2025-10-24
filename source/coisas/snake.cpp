
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "snake.h"

namespace fs = std::filesystem;

/**
 * @brief reads and adds file to files list
 * 
 * @param entry 
 */
void Input::parseFile(const fs::directory_entry &entry) {
  FileInfo currentFile;
  currentFile.name = entry.path().filename().string();

  std::ifstream fileStream(entry.path());
  if (!fileStream.is_open()) {
    std::cerr << "could not open file " << std::endl;
    return;
  }

  std::string line;
  int lines, columns;
  // get the dimensions from the file
  std::getline(fileStream, line);
  std::stringstream dimensions(line);
  dimensions >> lines >> columns;
  
  // now to actually read the file correctly
  for (int i = 0; i < lines; ++i) {
    std::getline(fileStream, line);
    
    std::vector<char> aux_line;
    aux_line.clear();
    bool jump = false;
    for(auto element:line){
      if(element == '#' ||
        element == ' ' ||
        element == '.'||
        element == '&'){
          aux_line.push_back(element);
        }
        else{
          aux_line.push_back(element);
      }
    }
    currentFile.puzzle.push_back(aux_line);
  }

  for(size_t i=0; i<currentFile.puzzle.size(); i++){
    for(size_t j=0; j<currentFile.puzzle[i].size(); j++){
      if(currentFile.puzzle[i][j] == '&'){
        currentFile.start = std::make_pair(i, j);
      }
    }
  }

  if(currentFile.start.first == -1){
    std::cout << "file " << currentFile.name << " missing spawnpoint";
    throw std::runtime_error("missing spawn");
  }

  allFiles.push_back(currentFile);
  std::cout << "Successfully processed " << currentFile.name << std::endl;
}

Input::Input(const std::string &directoryPath) {
  fs::path path(directoryPath);

  if (!fs::exists(path) || !fs::is_directory(path)) {
    throw std::runtime_error("directory not found");
  }

  for (const auto &entry : fs::directory_iterator(path)) {
    if (entry.is_regular_file()) {
      parseFile(entry);
    }
  }
}

/**
 * @brief returns allfiles
 * 
 * @return std::vector<FileInfo> 
 */
std::vector<FileInfo> Input::getFiles(){
  return allFiles;
}
