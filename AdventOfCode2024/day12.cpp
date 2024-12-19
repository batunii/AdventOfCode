#include "Vector2.hpp"
#include "splitter.hpp"
#include <queue>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

int size_m;
int size_n;
unordered_set<aoc::Vector2d, aoc::Vector2d::Hashing> visited;

bool can_go(aoc::Vector2d &curr_ele) {
  return (curr_ele.i >= 0 && curr_ele.i < size_m) &&
         (curr_ele.j >= 0 && curr_ele.j < size_n);
}
vector<aoc::Vector2d> direction_vects = aoc::direction4;
pair<vector<aoc::Vector2d>, bool>
elig_neighbors(aoc::Vector2d &curr_ele, vector<vector<string>> matrix) {
  string curr_farm = matrix[curr_ele.i][curr_ele.j];
  bool VERT = false;
  bool HORZ = false;
  vector<aoc::Vector2d> elig_neis;
  for (const auto &dir : direction_vects) {
    aoc::Vector2d result_vec = curr_ele + dir;
    if (can_go(result_vec) && matrix[result_vec.i][result_vec.j] == curr_farm) {
      elig_neis.push_back(result_vec);
      if (dir == direction_vects[0] || dir == direction_vects[2])
        VERT = true;
      if (dir == direction_vects[1] || dir == direction_vects[3])
        HORZ = true;
    }
  }
  return pair<vector<aoc::Vector2d>, bool>({elig_neis, VERT && HORZ});
}

int calc_side_cost(int neighbors, bool vert_horz) {
  int cost = 0;
  switch (neighbors) {
  case 4:
    cost = 0;
    break;
  case 3:
    cost = 2;
    break;
  case 2:
    cost = vert_horz ? 2 : 0;
    break;
  case 1:
    cost = 2;
    break;
  default:
    cost = 4;
    break;
  }
  return cost;
}

int bfs_parse(const aoc::Vector2d &curr_ele,
              const vector<vector<string>> &matrix) {
  if (visited.find(curr_ele) != visited.end())
    return 0;
  queue<aoc::Vector2d> q;
  int perimeter_cost = 0;
  int side_cost = 0;
  int area_counter = 1;
  visited.emplace(curr_ele);
  q.push(curr_ele);
  while (!q.empty()) {
    aoc::Vector2d curr_ele = q.front();
    q.pop();
    pair<vector<aoc::Vector2d>, bool> elig_pair =
        elig_neighbors(curr_ele, matrix);
    vector<aoc::Vector2d> eligible_neighbors = elig_pair.first;
    perimeter_cost += 4 - eligible_neighbors.size();
    // part 2
    side_cost += calc_side_cost(eligible_neighbors.size(), elig_pair.second);
    for (const auto &neighbor : eligible_neighbors) {
      if (visited.find(neighbor) == visited.end()) {
        q.push(neighbor);
        visited.emplace(neighbor);
        area_counter++;
      }
    }
  }
  return side_cost;
}

int main() {
  const vector<vector<string>> matrix = aoc::get_matrix("input_exp.txt");
  int total_cost = 0;
  size_m = matrix.size();
  size_n = matrix[0].size();

  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[i].size(); j++) {
      int cost = bfs_parse(aoc::Vector2d(i, j), matrix);
      cout << "Cost of " << matrix[i][j] << " : " << cost << '\n';
      total_cost += cost;
    }
  }

  cout << "Total cost is -> " << total_cost << endl;
}
