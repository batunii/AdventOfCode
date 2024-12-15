#include "splitter.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

void printM(vector<string> &vecs) {

  for (const auto &ele : vecs) {
    cout << ele << " ";
  }
  cout << '\n';
}

void swap_elements(int ptr1, int ptr1_2, int ptr2, int ptr2_2,
                   vector<string> &disk_map) {
  int chg_ptr1 = ptr1;
  int chg_ptr2 = ptr2;
  while (chg_ptr2 >= ptr2_2) {
    swap(disk_map[chg_ptr2], disk_map[chg_ptr1]);
    chg_ptr2--;
    chg_ptr1++;
  }
}

int main() {
  vector<vector<string>> input = aoc::get_matrix("input9.txt");
  vector<string> input_disk = input[0];
  vector<string> disk_map;
  bool is_file = true;
  int id = 0;
  for (const auto &str : input_disk) {
    //   cout << str << "";
    if (is_file) {
      for (int i = 0; i < stoi(str); i++) {
        disk_map.push_back(to_string(id));
      }
      id++;
      is_file = false;
    } else {
      for (int i = 0; i < stoi(str); i++) {
        disk_map.push_back(".");
      }
      is_file = true;
    }
  }
  //  cout << endl;
  //  for (const auto &ele : disk_map) {
  //    cout << ele;
  //  }
  //  cout << endl;

  vector<string> disk_map_copy(disk_map);

  int ptr1 = 0, ptr2 = disk_map.size() - 1;
  while (ptr1 < ptr2) {

    if (disk_map[ptr1] == ".") {
      if (disk_map[ptr2] != ".") {
        swap(disk_map[ptr1], disk_map[ptr2]);
        ptr1++;
        ptr2--;
      } else {
        ptr2--;
      }
    } else {
      ptr1++;
    }
  }

  //  for (const auto &ele : disk_map_copy) {
  //    cout << ele;
  //  }
  cout << endl;

  ptr1 = 0;
  int ptr1_2 = 0;
  ptr2 = disk_map_copy.size() - 1;
  int ptr2_2 = ptr2;

  // loop1 to detect the number of ele at back

  while (ptr2 > 0) {
    if (disk_map_copy[ptr2] != ".") {
      string curr_ele = disk_map_copy[ptr2];
      ptr2_2 = ptr2;
      while (ptr2_2 >= 0 && curr_ele == disk_map_copy[ptr2_2]) {
        ptr2_2--;
      }

      ptr1 = 0;

      while (ptr1 < disk_map_copy.size() && ptr1 < ptr2) {
        if (disk_map_copy[ptr1] != ".") {
          ptr1++;
          continue;
        } else {
          ptr1_2 = ptr1;
          while (ptr1_2 < disk_map_copy.size() &&
                 disk_map_copy[ptr1_2] == ".") {
            ptr1_2++;
          }
        }
        int space_avl = ptr1_2 - ptr1;
        int space_rqd = ptr2 - ptr2_2;
        if (space_avl >= space_rqd) {
          //      cout << " Avialble space for " << curr_ele << " : " <<
          //      space_avl
          //          << " reqd " << space_rqd << '\n';
          int change_ptr1 = ptr1;
          int change_ptr2 = ptr2;
          while (change_ptr2 > ptr2_2 && change_ptr1 < change_ptr2) {
            swap(disk_map_copy[change_ptr1], disk_map_copy[change_ptr2]);
            change_ptr1++;
            change_ptr2--;
            //          printM(disk_map_copy);
          }
          break;
        } else {
          ptr1 = ptr1_2;
        }
      }
      // cout << ptr2 - ptr2_2 << " " << curr_ele << "s" << '\n';
      ptr2 = ptr2_2;
    } else
      ptr2--;
  }

  // printM(disk_map_copy);
  long answer = 0;
  for (int i = 0; i < disk_map_copy.size(); i++) {
    if (disk_map_copy[i] != ".")
      answer += stoi(disk_map_copy[i]) * i;
  }
  cout << answer << endl;
}
