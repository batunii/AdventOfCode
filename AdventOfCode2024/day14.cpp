#include "Vector2.hpp"
#include "splitter.hpp"
#include <regex>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
using vec = aoc::Vector2d;

size_t size_x = 101;
size_t size_y = 103;

pair<vec, vec> pos_vel_pair(const string &input) {
  regex regex_pattern(R"(\p=(\d+),(\d+) v=(-?\d+),(-?\d+))");
  smatch match;
  regex_search(input, match, regex_pattern);
  return make_pair(vec(stoi(match[1]), stoi(match[2])),
                   vec(stoi(match[3]), stoi(match[4])));
}

pair<vec, vec> speed_run(pair<vec, vec> &bot, int time = 100) {
  for (int i = 0; i < time; i++) {
    bot.first = bot.first + bot.second;
    bot.first.i = bot.first.i < 0 ? size_x + bot.first.i : bot.first.i % size_x;
    bot.first.j = bot.first.j < 0 ? size_y + bot.first.j : bot.first.j % size_y;
  }
  return bot;
}

void print_xmas(unordered_set<vec, vec::Hashing> &position) {
  for (int i = 0; i < size_y; i++) {
    for (int j = 0; j < size_x; j++) {
      if (position.find(vec(j, i)) != position.end()) {
        printf("#");
      } else
        printf(".");
    }
    printf("\n");
  }
}

void print_xmas_tree(vector<pair<vec, vec>> bots) {
  unordered_set<vec, aoc::Vector2d::Hashing> position;
  size_t total_size = bots.size();
  for (int i = 0; i < 20'000; i++) {
    for (pair<vec, vec> &bot : bots) {
      bot = speed_run(bot, 1);
      position.emplace(bot.first.i, bot.first.j);
    }
    if (total_size == position.size()) {
      cout << "Iteration " << i << " is the first\n";
      print_xmas(position);
    }
    position.clear();
  }
}

int main() {
  vector<vector<string>> matrix_raw = aoc::get_matrix("input14.txt", "\n");
  // aoc::print_matrix<string>();
  vector<pair<vec, vec>> bots;
  for (const vector<string> &bot : matrix_raw) {
    bots.emplace_back(pos_vel_pair(bot[0]));
  }

  print_xmas_tree(bots);
  long answer = 0;
  int q1 = 0, q2 = 0, q3 = 0, q4 = 0;
  for (pair<vec, vec> bot_vecs : bots) {
    // cout << "Position : " << bot_vecs.first
    //      << " Velocities : " << bot_vecs.second << '\n';
    speed_run(bot_vecs);
    // cout << "Position After : " << bot_vecs.first
    //     << " Velocities : " << bot_vecs.second << '\n';
    if (bot_vecs.first.i < size_x / 2 && bot_vecs.first.j < size_y / 2) {
      // cout << " In quad 1 \n";
      q1++;
    } else if (bot_vecs.first.i > size_x / 2 && bot_vecs.first.j < size_y / 2) {
      //  cout << "In quad 2 \n";
      q2++;
    } else if (bot_vecs.first.i < size_x / 2 && bot_vecs.first.j > size_y / 2) {
      //  cout << "In quad 3 \n";
      q3++;
    } else if (bot_vecs.first.i > size_x / 2 && bot_vecs.first.j > size_y / 2) {
      //  cout << "In quad 4 \n";
      q4++;
    }
  }

  answer = q1 * q2 * q3 * q4;
  cout << " Answer is : " << answer << endl;
}
