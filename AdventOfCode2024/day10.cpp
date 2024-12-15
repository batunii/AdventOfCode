#include "splitter.hpp"
#include <cstddef>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

class Vec {
public:
  int i, j;
  Vec(int i = 0, int j = 0) : i(i), j(j) {}

public:
  string out() { return "[" + to_string(i) + "," + to_string(j) + "]->"; }
  Vec *operator+(const Vec &Other) const {
    return new Vec(i + Other.i, j + Other.j);
  }
  bool operator==(const Vec &Other) const {
    return (i == Other.i) && (j == Other.j);
  }
  struct Hashing {
    size_t operator()(const Vec &Other) const {
      return hash<size_t>()(hash<int>()(Other.i) ^ hash<int>()(Other.j));
    }
  };
  friend ostream &operator<<(ostream &os, const Vec &Other);
};
ostream &operator<<(ostream &os, const Vec &Other) {
  os << Other.i << "," << Other.j;
  return os;
}

const vector<Vec> direction_vec = {Vec(1, 0), Vec(0, -1), Vec(-1, 0),
                                   Vec(0, 1)};
int size_m = 0;
int size_n = 0;

unordered_set<string> path_id_set;

bool can_go(Vec &vec) {

  return (vec.i < size_m && vec.i >= 0) && (vec.j < size_n && vec.j >= 0);
}

bool is_plus_1(const Vec &curr_vec, const Vec &other_vec,
               const vector<vector<string>> &matrix) {
  return stoi(matrix[curr_vec.i][curr_vec.j]) + 1 ==
         stoi(matrix[other_vec.i][other_vec.j]);
}

void calculate_trail_dfs(Vec &curr_ele, const vector<vector<string>> &matrix,
                         string &&path_id) {
  if (stoi(matrix[curr_ele.i][curr_ele.j]) == 9) {
    path_id_set.emplace(path_id + "*");
  } else {
    for (const auto &neighbors : direction_vec) {
      Vec *neigbor_vec = curr_ele + neighbors;
      if (can_go(*neigbor_vec) && is_plus_1(curr_ele, *neigbor_vec, matrix)) {
        calculate_trail_dfs(*neigbor_vec, matrix, path_id + neigbor_vec->out());
      }
    }
  }
}

int calculate_trail_paths(const Vec &start_pt,
                          const vector<vector<string>> &matrix) {
  queue<Vec> q;
  int total_paths = 1;
  q.emplace(start_pt);

  while (!q.empty()) {
    total_paths += q.size() - 1;
    Vec curr_ele = q.front();
    q.pop();

    if (matrix[curr_ele.i][curr_ele.j] == "9")
      continue;

    for (const Vec &neighbors : direction_vec) {
      Vec *neighbor_vec = curr_ele + neighbors;
      if (can_go(*neighbor_vec) && is_plus_1(curr_ele, *neighbor_vec, matrix)) {
        cout << "Adding " << *neighbor_vec << " as potential for " << curr_ele
             << '\n';
        q.emplace(*neighbor_vec);
      }
    }
  }
  return total_paths;
}

int main() {
  const vector<vector<string>> matrix = aoc::get_matrix("input10.txt");
  unordered_set<Vec, Vec::Hashing> set_vec;
  vector<Vec> trail_points;
  size_m = matrix.size();
  size_n = matrix[0].size();
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[i].size(); j++) {
      if (stoi(matrix[i][j]) == 0)
        trail_points.push_back(Vec(i, j));
    }
  }

  uint answer = 0;

  for (Vec &trails : trail_points) {
    calculate_trail_dfs(trails, matrix, trails.out());
  }
  // for (const string &paths : path_id_set) {
  //   cout << paths << '\n';
  // }
  cout << "Answer is: " << path_id_set.size() << endl;
}
