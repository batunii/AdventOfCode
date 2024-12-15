#include "splitter.hpp"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <ostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

class Vec {
public:
  int i;
  int j;

  Vec(int i = 0, int j = 0) : i(i), j(j) {}

  Vec operator-(const Vec &OtherObj) const {
    return Vec(i - OtherObj.i, j - OtherObj.j);
  }
  Vec operator+(const Vec &OtherObj) const {
    return Vec(i + OtherObj.i, j + OtherObj.j);
  }
  Vec operator*(const int multiplier) const {
    return Vec(i * multiplier, j * multiplier);
  }
  bool operator==(const Vec &OtherObj) const {
    return (i == OtherObj.i) && (j == OtherObj.j);
  }

  struct HashVec {
    size_t operator()(const Vec &Obj) const {

      return hash<size_t>()(hash<int>()(Obj.i) ^ hash<int>()(Obj.j));
    }
  };
  friend ostream &operator<<(ostream &os, const Vec &Obj);
};
ostream &operator<<(ostream &os, const Vec &Obj) {
  os << Obj.i << "," << Obj.j;
  return os;
}

vector<vector<string>> matrix_present;

bool in_range(const Vec point,
              const vector<vector<std::string>> matrix = matrix_present) {
  return point.i < matrix.size() && point.j < matrix[point.i].size() &&
         point.i >= 0 && point.j >= 0;
}
// problem 1
vector<Vec> &calc_network_points(Vec vec1, Vec vec2) {
  vector<Vec> *valid_pts = new vector<Vec>();
  Vec diff_vec = vec1 - vec2;
  Vec pt_1 = vec1 + diff_vec;
  Vec pt_2 = vec1 - (diff_vec * 2);
  if (in_range(pt_1))
    valid_pts->push_back(pt_1);
  if (in_range(pt_2))
    valid_pts->push_back(pt_2);
  return *valid_pts;
}
// problem 2
vector<Vec> &calc_network_points_grids(Vec vec1, Vec vec2) {
  vector<Vec> *valid_pts = new vector<Vec>;
  Vec diff_vec = vec1 - vec2;
  Vec up_pts = vec1 + diff_vec;
  int multiplier = 1;
  // up points

  while (in_range(up_pts)) {
    valid_pts->push_back(up_pts);
    up_pts = vec1 + (diff_vec * multiplier);
    multiplier++;
  }
  multiplier = 2;
  Vec down_pts = vec1 - (diff_vec * multiplier);
  while (in_range(down_pts)) {
    valid_pts->push_back(down_pts);
    multiplier++;
    down_pts = vec1 - (diff_vec * multiplier);
  }
  return *valid_pts;
}

void print_matrix(size_t m, size_t n, unordered_set<Vec, Vec::HashVec> set) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (set.find(Vec(i, j)) != set.end()) {
        cout << "#";
      } else
        cout << ".";
    }
    cout << endl;
  }
}

int main() {
  matrix_present = aoc::get_matrix("input8.txt");
  cout << " Size of Matrix is : " << matrix_present.size() << " , "
       << matrix_present[0].size() << '\n';
  aoc::print_matrix<string>();
  unordered_map<string, vector<Vec>> signal_map;
  unordered_set<Vec, Vec::HashVec> unique_net_locs;
  for (int i = 0; i < matrix_present.size(); i++) {
    for (int j = 0; j < matrix_present[i].size(); j++) {
      if (matrix_present[i][j] != ".") {
        // element already present
        unique_net_locs.emplace(Vec(i, j));
        if (signal_map.find(matrix_present[i][j]) != signal_map.end()) {
          vector<Vec> new_vec = signal_map[matrix_present[i][j]];
          new_vec.push_back(Vec(i, j));
          signal_map[matrix_present[i][j]] = new_vec;
        } else {
          vector<Vec> new_vec;
          new_vec.push_back(Vec(i, j));
          signal_map[matrix_present[i][j]] = new_vec;
        }
      }
    }
  }

  for (const auto &pair : signal_map) {
    cout << pair.first << ":" << '\n';
    for (int i = 0; i < pair.second.size(); i++) {
      for (int j = i + 1; j < pair.second.size(); j++) {
        vector<Vec> network_list =
            calc_network_points_grids(pair.second[i], pair.second[j]);
        for (Vec potential_nets : network_list) {
          unique_net_locs.emplace(potential_nets);
          cout << "Potential Pts -> " << potential_nets << '\n';
        }
      }
    }
  }

  cout << "Potential network points -> " << unique_net_locs.size() << '\n';
  // print_matrix(matrix_present.size(), matrix_present[0].size(),
  //             unique_net_locs);
}
