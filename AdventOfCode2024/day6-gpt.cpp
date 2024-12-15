#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <tuple>

struct Vector2 {
    int i, j;
    Vector2(int i = 0, int j = 0) : i(i), j(j) {}
    Vector2 operator+(const Vector2& other) const {
        return Vector2(i + other.i, j + other.j);
    }
    std::string toString() const {
        return std::to_string(i) + "," + std::to_string(j);
    }
};

class GuardSimulation {
private:
    std::vector<std::vector<char>> grid;
    int height, width;
    Vector2 start_pos;
    unsigned int start_dir;
    Vector2 directions[4] = {Vector2(-1, 0), Vector2(0, 1), Vector2(1, 0), Vector2(0, -1)};

public:
    // Constructor: Load grid from file
    GuardSimulation(const std::string& filename) {
        std::ifstream file(filename);
        std::string line;
        while (std::getline(file, line)) {
            grid.push_back(std::vector<char>(line.begin(), line.end()));
        }
        height = grid.size();
        width = grid[0].size();
        locateStart();
    }

    // Locate the guard's starting position and direction
    void locateStart() {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (grid[i][j] == '^') {
                    start_pos = Vector2(i, j);
                    start_dir = 0;
                    grid[i][j] = '.'; // Replace guard's starting position with empty space
                    return;
                }
                if (grid[i][j] == '>') {
                    start_pos = Vector2(i, j);
                    start_dir = 1;
                    grid[i][j] = '.';
                    return;
                }
                if (grid[i][j] == 'v') {
                    start_pos = Vector2(i, j);
                    start_dir = 2;
                    grid[i][j] = '.';
                    return;
                }
                if (grid[i][j] == '<') {
                    start_pos = Vector2(i, j);
                    start_dir = 3;
                    grid[i][j] = '.';
                    return;
                }
            }
        }
    }

    // Simulate the guard's movement and check for loops
    bool simulate(Vector2 pos, unsigned int dir) {
        std::unordered_set<std::string> visited_states;
        while (true) {
            std::string state_key = pos.toString() + "," + std::to_string(dir);
            if (!visited_states.insert(state_key).second) {
                return true; // Loop detected
            }

            // Move forward or turn if blocked
            Vector2 next_pos = pos + directions[dir];
            if (next_pos.i < 0 || next_pos.i >= height || next_pos.j < 0 || next_pos.j >= width ||
                grid[next_pos.i][next_pos.j] == '#') {
                dir = (dir + 1) % 4; // Turn right
            } else {
                pos = next_pos; // Move forward
            }

            // Guard leaves the grid
            if (pos.i < 0 || pos.i >= height || pos.j < 0 || pos.j >= width) {
                return false; // No loop
            }
        }
    }

    // Test all possible positions for the obstruction
    int countLoopingObstructions() {
        int valid_positions = 0;
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (grid[i][j] == '.' && !(i == start_pos.i && j == start_pos.j)) {
                    // Place a temporary obstruction
                    grid[i][j] = '#';

                    // Check if it causes a loop
                    if (simulate(start_pos, start_dir)) {
                        valid_positions++;
                    }

                    // Remove the obstruction
                    grid[i][j] = '.';
                }
            }
        }
        return valid_positions;
    }
};

int main() {
    GuardSimulation simulation("input_exp.txt");
    int result = simulation.countLoopingObstructions();
    std::cout << "Number of valid positions for obstruction: " << result << std::endl;
    return 0;
}

