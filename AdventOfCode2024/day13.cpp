#include "splitter.hpp"
#include <ostream>
#include <string>
#include <vector>

using namespace std;

struct Equation_s {
  long long x1, x2, y1, y2, z1, z2;
  Equation_s(long long x1 = 0, long long x2 = 0, long long y1 = 0,
             long long y2 = 0, long long z1 = 0, long long z2 = 0)
      : x1(x1), x2(x2), y1(y1), y2(y2), z1(z1), z2(z2) {};
  Equation_s make_constants_same() const {
    return Equation_s(x1 * x2, x2 * x1 * (-1), y1 * x2, y2 * x1 * (-1), z1 * x2,
                      z2 * x1 * (-1));
  }
};

ostream &operator<<(ostream &os, const Equation_s &obj) {
  os << obj.x1 << "," << obj.y1 << "=" << obj.z1 << '\n';
  os << obj.x2 << "," << obj.y2 << "=" << obj.z2 << '\n';
  return os;
}
pair<long long, long long> get_inputs(const string &input) {
  string x_buff;
  string y_buff;
  for (size_t i = 0; i < input.length(); i++) {
    if (input.at(i) == 'X') {
      while (i < input.length() && input.at(i) != ',') {
        if (isdigit(input.at(i)))
          x_buff += input.at(i);
        i++;
      }
    }
    if (input.at(i) == 'Y') {
      while (i < input.length() && input.at(i) != ']') {
        if (isdigit(input.at(i)))
          y_buff += input.at(i);
        i++;
      }
    }
  }

  return std::move(make_pair(stoi(x_buff), stoi(y_buff)));
}

vector<Equation_s> parsed_input(vector<vector<string>> &matrix) {

  vector<Equation_s> equations;
  vector<long long> constants;
  constants.reserve(6);
  for (const vector<string> &equation_str : matrix) {
    Equation_s eq;
    if (!equation_str.empty()) {
      pair<long long, long long> x_y_pair = get_inputs(equation_str[0]);
      constants.emplace_back(x_y_pair.first);
      constants.emplace_back(x_y_pair.second);
    } else {
      equations.emplace_back(constants[0], constants[1], constants[2],
                             constants[3], 10000000000000 + constants[4],
                             10000000000000 + constants[5]);
      constants.clear();
    }
  }
  equations.emplace_back(constants[0], constants[1], constants[2], constants[3],
                         10000000000000 + constants[4],
                         10000000000000 + constants[5]);
  constants.clear();
  return equations;
}

pair<long long, long long> solve_equation(const Equation_s &equations) {

  Equation_s same_consts = equations.make_constants_same();
  long long y =
      (same_consts.z1 + same_consts.z2) % (same_consts.y1 + same_consts.y2) == 0
          ? (same_consts.z1 + same_consts.z2) /
                (same_consts.y1 + same_consts.y2)
          : -1;
  long long x =
      y != -1 ? (same_consts.z1 - (same_consts.y1 * y)) / same_consts.x1 : -1;

  return make_pair(x, y);
}

int main() {
  vector<vector<string>> matrix_raw = aoc::get_matrix("input13.txt", "\n");
  vector<Equation_s> equations = parsed_input(matrix_raw);
  long answer_tokens = 0;

  for (const Equation_s &eq : equations) {
    pair<long long, long long> answer = solve_equation(eq);
    answer_tokens +=
        answer.first != -1 ? ((3 * answer.first) + answer.second) : 0;
  }
  cout << "Answer is : " << answer_tokens << endl;
}
