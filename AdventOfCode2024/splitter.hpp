#include <fstream>
#include <iostream>
#include <string>
#include <vector>
namespace aoc {

template <typename T> std::vector<std::vector<T>> this_matrix;

inline std::vector<std::string> split(std::string line, std::string deli = "") {
  std::vector<std::string> elements;
  std::string string_buf;
  for (int i = 0; i < line.size(); i++) {
    if (deli == "") {
      elements.push_back(line.substr(i, 1));
    } else {
      if (line.substr(i, 1) == deli) {
        elements.push_back(string_buf);
        string_buf = "";
      } else {
        string_buf.push_back(line.at(i));
      }
    }
  }
  if (string_buf != "") {
    elements.push_back(string_buf);
    string_buf = "";
  }
  return elements;
}
template <typename T>
inline void print_matrix(std::vector<std::vector<T>> matrix = this_matrix<T>) {
  for (int i = 0; i < matrix.size(); i++) {
    std::cout << "[";
    for (int j = 0; j < matrix[i].size(); j++) {
      std::cout << matrix[i][j];
      if (j != matrix[i].size() - 1)
        std::cout << " , ";
    }
    std::cout << "] \n";
  }
}
inline std::vector<std::vector<std::string>> get_matrix(std::string file_name,
                                                        std::string deli = "") {
  std::ifstream input_file(file_name);
  std::string line_buf;
  std::vector<std::vector<std::string>> matrix;
  while (getline(input_file, line_buf)) {
    std::vector<std::string> line_arr = split(line_buf, deli);
    matrix.push_back(line_arr);
  }
  this_matrix<std::string> = matrix;
  return matrix;
}
} // namespace aoc
