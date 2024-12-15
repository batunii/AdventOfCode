#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

class Vector2 {
public:
  int i;
  int j;
  Vector2(int i = 0, int j = 0) : i(i), j(j) {};
  std::string toString() { return std::to_string(i) + "," + std::to_string(j); }
  void operator+(const Vector2 &other_vec) {
    i += other_vec.i;
    j += other_vec.j;
  }
};

// Global Vars
unsigned int direction_index = 0;
unsigned int height = 0;
unsigned int widht = 0;
Vector2 go_ahead(-1, 0);
std::vector<Vector2> direction_vects;
std::vector<std::vector<char>> matrix;
long loop_candidates = 0;
std::unordered_set<std::string> visited;
std::unordered_set<std::string> visted_with_directions;

Vector2 add_vectors(const Vector2 &vector1, const Vector2 &vector2) {
  return Vector2(vector1.i + vector2.i, vector1.j + vector2.j);
}

bool is_in_range(const Vector2 &pt, const Vector2 &cust_go_ahead) {
  Vector2 newVector = add_vectors(pt, cust_go_ahead);

  return (newVector.i < height && newVector.i >= 0) &&
  (newVector.j < widht && newVector.j >= 0);
}
bool is_in_range(const Vector2 &pt) {
  Vector2 newVector = add_vectors(pt, go_ahead);

  return (newVector.i < height && newVector.i >= 0) &&
  (newVector.j < widht && newVector.j >= 0);
}
void change_direction() {
  go_ahead + direction_vects[direction_index];
  if (direction_index < 3)
    direction_index++;
  else
    direction_index = 0;
}
bool check_ahead(const Vector2 &ptr) {
  int i = ptr.i + go_ahead.i;
  int j = ptr.j + go_ahead.j;

  return matrix[i][j] != '#';
}

Vector2 move_ahead(Vector2 &ptr) { ptr = add_vectors(ptr, go_ahead);
return ptr; }

void check_loops(Vector2 curr_pos) {
  unsigned int direction_index_local = direction_index;
  Vector2 new_direction_ahead =
      add_vectors(go_ahead, direction_vects[direction_index]);
  while (is_in_range(curr_pos, new_direction_ahead)) {
    if (check_ahead(curr_pos)) {
      curr_pos + new_direction_ahead;
    } else {
      new_direction_ahead + direction_vects[direction_index_local];
      direction_index_local =
          (direction_index_local + 1) % direction_vects.size();
    }
    std::string key =
        curr_pos.toString() + "," + new_direction_ahead.toString();
    if (visted_with_directions.find(key) != visted_with_directions.end()) {
      		std::cout<< key << '\n';
			loop_candidates++;
    }
    break;
  }
}

int main() {
  std::ifstream file("input_exp.txt");
  std::string string_buff;

  while (std::getline(file, string_buff)) {
    std::vector<char> line_buff;
    for (char word : string_buff) {
      line_buff.push_back(word);
    }
    matrix.push_back(line_buff);
  }
  height = matrix.size();
  widht = matrix[0].size();

  // Adding Direction Vectors
  direction_vects.push_back(Vector2(1, 1));
  direction_vects.push_back(Vector2(1, -1));
  direction_vects.push_back(Vector2(-1, -1));
  direction_vects.push_back(Vector2(-1, 1));

  /// Release the engine and go through this maze
  Vector2 start_pt;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < widht; j++) {
      if (matrix[i][j] == '^') {
        start_pt.i = i;
        start_pt.j = j;
        break;
      }
    }
  }
  visited.insert(start_pt.toString()); // starting position
  while (is_in_range(start_pt)) {
    check_loops(start_pt);
    if (check_ahead(start_pt)) // true if no obstacle
    {
      start_pt = move_ahead(start_pt);
      visited.insert(start_pt.toString());
      visted_with_directions.insert(start_pt.toString() + "," + 
      go_ahead.toString());
    } else {
      change_direction();
    }
  }
  std::cout << visited.size() << " " << loop_candidates << std::endl;
}
