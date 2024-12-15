from io import TextIOWrapper
from typing import List

from day4 import convert_to_array 

file: TextIOWrapper = open("input4.txt")
input_matrix: List[List[str]] = convert_to_array(file)


# testing if we can make an X
def can_make_X(i: int, j: int, matrix: List[List[str]]) -> bool:
    return i - 1 >= 0 and i + 1 < len(matrix) and j - 1 >= 0 and j + 1 < len(matrix[i])


# case 1 when M is at top
def top_M(i: int, j: int, matrix: List[List[str]]) -> bool:
    if can_make_X(i, j, matrix):
        if (
            matrix[i - 1][j - 1] == "M"
            and matrix[i - 1][j + 1] == "M"
            and matrix[i + 1][j - 1] == "S"
            and matrix[i + 1][j + 1] == "S"
        ):
            return True
    return False


# case 2 when M is at down
def down_M(i: int, j: int, matrix: List[List[str]]) -> bool:
    if can_make_X(i, j, matrix):
        if (
            matrix[i - 1][j - 1] == "S"
            and matrix[i - 1][j + 1] == "S"
            and matrix[i + 1][j - 1] == "M"
            and matrix[i + 1][j + 1] == "M"
        ):
            return True
    return False


# case 3 when M is at right
def right_M(i: int, j: int, matrix: List[List[str]]) -> bool:
    if can_make_X(i, j, matrix):
        if (
            matrix[i - 1][j - 1] == "S"
            and matrix[i - 1][j + 1] == "M"
            and matrix[i + 1][j - 1] == "S"
            and matrix[i + 1][j + 1] == "M"
        ):
            return True
    return False


# case 4 when M is at left
def left_M(i: int, j: int, matrix: List[List[str]]) -> bool:
    if can_make_X(i, j, matrix):
        if (
            matrix[i - 1][j - 1] == "M"
            and matrix[i - 1][j + 1] == "S"
            and matrix[i + 1][j - 1] == "M"
            and matrix[i + 1][j + 1] == "S"
        ):
            return True
    return False


# this time we will keep an eye for A
def get_X_MAS_count(matrix: List[List[str]]) -> int:
    count: int = 0
    for i in range(len(matrix)):
        for j in range(len(matrix[i])):
            if matrix[i][j] == "A":
                if (
                    top_M(i, j, matrix)
                    or down_M(i, j, matrix)
                    or left_M(i, j, matrix)
                    or right_M(i, j, matrix)
                ):
                    count += 1
    return count

print(get_X_MAS_count(input_matrix))
