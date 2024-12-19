#include <string>
#include <vector>

namespace aoc {
class Vector2d {
public:
  int i;
  int j;
  Vector2d(int i = 0, int j = 0) : i(i), j(j) {}

  std::string toString() const {
    return std::to_string(i) + "," + std::to_string(j);
  }

  // functor/ Operator

  bool operator==(const Vector2d &Other) const {
    return (i == Other.i) && (j == Other.j);
  }
  Vector2d &operator+(const Vector2d &Other) {
    Vector2d *new_vector = new Vector2d(i + Other.i, j + Other.j);
    return *new_vector;
  }
  Vector2d &operator-(const Vector2d &Other) {
    Vector2d *new_vector = new Vector2d(i - Other.i, j - Other.j);
    return *new_vector;
  }
  Vector2d &operator*(const int multiplier) {
    Vector2d *new_vector = new Vector2d(i * multiplier, j * multiplier);
    return *new_vector;
  }
  struct Hashing {
    size_t operator()(const Vector2d &vec2d) const {
      return std::hash<size_t>()(std::hash<int>()(vec2d.i) ^
                                 std::hash<int>()(vec2d.j));
    }
  };
};

std::ostream &operator<<(std::ostream &os, const Vector2d &vec_obj) {
  os << vec_obj.toString();
  return os;
}

const std::vector<Vector2d> direction4 = {Vector2d(1, 0), Vector2d(0, 1),
                                          Vector2d(-1, 0), Vector2d(0, -1)};

} // namespace aoc
