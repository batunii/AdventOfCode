#include <cstring>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

class Pair {
public:
  int i;
  int j;
  Pair(int i = 0, int j = 0) : i(i), j(j) {}
  Pair operator+(const Pair &OtherPair) {
    return Pair(i + OtherPair.i, j + OtherPair.j);
  };
  Pair *operator/(const Pair &OtherPair) {
    this->i += OtherPair.i;
    this->j += OtherPair.j;
    return this;
  }
  string toString() { return to_string(i) + "," + to_string(j); }
};

int global_index = 0;
vector<Pair> change_direction_vec;
Pair ahead_direction_vec(-1, 0);
long max_path = 0;

vector<char> split(const string &input) {
  char word;
  vector<char> input_vector;
  // cout<<input<<endl;
  for (char word : input) {
    input_vector.push_back(word);
  }
  return input_vector;
}

bool canGo(int i, int j, vector<vector<char>> matrix) {
  Pair result = Pair(i, j) + ahead_direction_vec;
  return (result.i >= 0 && result.i < matrix.size()) &&
         (result.j >= 0 && result.j < matrix[i].size());
}

bool loop_possible(Pair str_ptr, const vector<vector<char>> &matrix,
                   const unordered_set<string> &visited) {

  int direction_index_copy = global_index;
  Pair ahead_direction_copy(ahead_direction_vec);
  ahead_direction_copy / change_direction_vec[direction_index_copy];
  while (canGo(str_ptr.i, str_ptr.j, matrix)) {
    str_ptr / ahead_direction_copy;
    string key = to_string(str_ptr.i) + "," + to_string(str_ptr.j);
    if (visited.find(key) != visited.end()) {
      max_path++;
      if (max_path >= matrix.size())
        return true;
      else
        return loop_possible(str_ptr, matrix, visited);
    } else {
      return loop_possible(str_ptr, matrix, visited);
    }
  }
  return false;
}

int main(int argc, char *argv[]) {

  ifstream file("input_exp.txt");
  string *str_buff = new string();
  char *found;
  vector<string> input;
  vector<vector<char>> input_vector;
  while (getline(file, *str_buff, '\n')) {
    // cout<<*str_buff<<endl;
    input.push_back(*str_buff);
  }
  for (string line : input) {
    vector<char> word = split(line);
    input_vector.push_back(word);
  }

  Pair start_ptr;

  for (int i = 0; i < input_vector.size(); i++) {
    for (int j = 0; j < input_vector[i].size(); j++) {
      if (input_vector[i][j] == '^') {
        start_ptr.i = i;
        start_ptr.j = j;
      }
    }
  }

  change_direction_vec.push_back(Pair(1, 1));
  change_direction_vec.push_back(Pair(1, -1));
  change_direction_vec.push_back(Pair(-1, -1));
  change_direction_vec.push_back(Pair(-1, 1));

  int answer = 1;
  int loop = 0;
  // auto cut_cmp = [](Pair a, Pair b) { return (a.i != b.i) && (a.j != b.j); };
  unordered_set<string> visitedSet;
  while (canGo(start_ptr.i, start_ptr.j, input_vector)) {

    /* tracing the path */
    cout << start_ptr.i << "," << start_ptr.j << endl;

    Pair new_ptr = start_ptr + ahead_direction_vec;
    if (input_vector[new_ptr.i][new_ptr.j] == '#') {
      cout << " We have hit a trouble at " << new_ptr.i << " , " << new_ptr.j
           << endl;
      ahead_direction_vec / change_direction_vec[global_index];
      if (global_index < 3)
        global_index++;
      else
        global_index = 0;
    } else {
      string key = to_string(start_ptr.i) + "," + to_string(start_ptr.j);
      if (loop_possible(start_ptr, input_vector, visitedSet)) {
        loop++;
        cout << " loop possible at " << start_ptr.toString() << '\n';
      }
      if (visitedSet.find(key) == visitedSet.end()) {
        cout << answer++ << " ans increased " << endl;
        visitedSet.insert(key);
      }
      start_ptr / ahead_direction_vec;
    }
  }
  cout << loop << endl;
}
