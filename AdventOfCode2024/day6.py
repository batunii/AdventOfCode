from typing import List, Tuple
from itertools import cycle
from graphs import Grid, GridPoint, add_points, parse_grid

file = open(r"input6.txt", "r")
matrix:List[List[str]] = list()
init_dir: Tuple = (1,1)
for line in file:
    array: List[str] = []
    for char in line:
        if char!='\n':
            array.append(char)
        else:
            break
    matrix.append(array)


def track_guard(grid: Grid) -> tuple[bool, set[GridPoint]]:
    OFFSETS = cycle([(-1, 0), (0, 1), (1, 0), (0, -1)])
    offset = next(OFFSETS)

    loc = next(k for k, v in grid.items() if v == "^")
    visited: set[tuple[GridPoint, GridPoint]] = {(loc, offset)}

    while True:
        next_loc = add_points(loc, offset)
        if next_loc not in grid:
            break

        if grid[next_loc] == "#":
            offset = next(OFFSETS)
            visited.add((loc, offset))
        else:
            to_add = next_loc, offset
            if to_add in visited:
                # loop!
                return False, set()

            visited.add(to_add)
            loc = next_loc

    return True, {l for l, _ in visited}

def solve() -> tuple[int, int]:
        grid = parse_grid(matrix)

        exited, path = track_guard(grid)
        assert exited
        initial_path_size = len(path)

        possible_obstacle_locations = 0
        for loc in path:
            # can't drop a barrel on his head
            if grid[loc] != ".":
                continue

            grid[loc] = "#"
            exited, _ = track_guard(grid)
            if not exited:
                possible_obstacle_locations += 1
            grid[loc] = "."

        return initial_path_size, possible_obstacle_locations
print(solve())
