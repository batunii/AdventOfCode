#include "splitter.hpp"
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

template <typename T, typename V> void printM(unordered_map<T, V> &matrix) {
  for (const auto [key, value] : matrix) {
    cout << key << " : " << value << endl;
  }
  cout << endl;
}
void add_to_dict(unordered_map<long, long> &map, long val,
                 long exist_freq = 1) {
  if (map.find(val) != map.end())
    map[val] = map[val]+exist_freq;
  else
    map[val] = exist_freq;
}

vector<long> calc_new_val(long old_val) {
  if (old_val == 0)
    return vector<long>({1});
  else if (to_string(old_val).length() % 2 == 0) {
    int length = to_string(old_val).length();
    long val1 = stol(to_string(old_val).substr(0, length / 2));
    long val2 = stol(to_string(old_val).substr(length / 2));
    return vector<long>({val1, val2});
  } else
    return vector<long>({old_val * 2024});
}

unordered_map<long, long> &blink_once(unordered_map<long, long> &curr_map) {
  unordered_map<long, long> *new_map = new unordered_map<long, long>();
  for (const auto [key, freq] : curr_map) {
    vector<long> values = calc_new_val(key);
    for (const long &value : values) {
      add_to_dict(*new_map, value, freq);
    }
  }
  return *new_map;
}

int main() {
  vector<vector<string>> temp_matrix = aoc::get_matrix("input11.txt", " ");
  vector<string> matrix = temp_matrix[0];
  unordered_map<long, long> freq_map;
  for (const auto &matrix_val : matrix) {
    add_to_dict(freq_map, stol(matrix_val));
  }
  for (int i = 0; i < 75; i++) {
    freq_map = blink_once(freq_map);
  }
  long answer = 0;
  for (const auto [key, value] : freq_map) {
    answer += value;
  }
  cout << answer << endl;
}
