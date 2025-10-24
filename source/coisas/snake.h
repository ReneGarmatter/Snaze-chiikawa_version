
#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <filesystem>
#include <string>
#include <utility>
#include <vector>

// Filesystem alias for convenience
namespace fs = std::filesystem;

/**
   * @struct FileInfo
   * @brief Stores the parsed data for a single puzzle file.
   */
struct FileInfo {
    std::string name;
    std::vector<std::vector<char>> puzzle;
    std::pair<int, int> start = {-1, -1};
  };

/**
 * This class handles reading puzzle files from a specified directory.
 * It parses the dimensions and character grid of each puzzle,
 * storing the results for later use.
 */
class Input {
public:
  /**
   * @brief Constructs the InputHandler and immediately parses files.
   * @param directoryPath The path to the directory containing puzzle files.
   */
  Input(const std::string &directoryPath);

  /**
   * @brief A const getter to safely access the parsed puzzle data.
   * @return A constant reference to the vector of FileInfo objects.
   */
  std::vector<FileInfo> getFiles();
  std::vector<FileInfo> allFiles;

private:
  // A vector to store the parsed information from all files.

  /**
   * @brief A private helper function to parse a single file.
   * @param entry A directory entry representing the file to parse.
   */
  void parseFile(const fs::directory_entry &entry);
};
#endif
