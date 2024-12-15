from io import TextIOWrapper
from typing import List

file = open(r"input4.txt", "r")
final_ans: int = 0


def convert_to_array(input_str: str | TextIOWrapper) -> List[List[str]]:
    words_array: List[List[str]] = list()
    for line in input_str:
        word_array: List[str] = list()
        for letter in line:
            if letter == "\n":
                break
            else:
                word_array.append(letter)
        words_array.append(word_array)
    return words_array


# check to make sure we can go up
def can_go_up(i: int) -> bool:
    return i - 3 >= 0


# check to make sure we can go up
def can_go_down(i: int, matrix: List[List[str]]) -> bool:
    return i + 3 < len(matrix)


# check to make sure we can go right
def can_go_right(i: int, j: int, matrix: List[List[str]]) -> bool:
    return j + 3 < len(matrix[i])


# check to make sure we can go left
def can_go_left(j: int) -> bool:
    return j - 3 >= 0


# lets see if there is anything vertically present
def check_vertical(i: int, j: int, matrix: List[List[str]]) -> int:
    count: int = 0
    if can_go_up(i):
        if (
            matrix[i - 1][j] == "M"
            and matrix[i - 2][j] == "A"
            and matrix[i - 3][j] == "S"
        ):
            count += 1
            print(f"VU i = {i}, j= {j}")
    if can_go_down(i, matrix):
        if (
            matrix[i + 1][j] == "M"
            and matrix[i + 2][j] == "A"
            and matrix[i + 3][j] == "S"
        ):
            count += 1
            print(f"VD i = {i}, j= {j}")
    return count


# lets see if there is anything horizontally
def check_horizontal(i: int, j: int, matrix: List[List[str]]) -> int:
    count: int = 0
    if can_go_right(i, j, matrix):
        if (
            matrix[i][j + 1] == "M"
            and matrix[i][j + 2] == "A"
            and matrix[i][j + 3] == "S"
        ):
            count += 1
            print(f"HR i = {i}, j = {j}")
    if can_go_left(j):
        if (
            matrix[i][j - 1] == "M"
            and matrix[i][j - 2] == "A"
            and matrix[i][j - 3] == "S"
        ):
            count += 1
            print(f"HL i = {i}, j = {j}")
    return count


# lets check up-left and down-right now
def check_ul_dr(i: int, j: int, matrix: List[List[str]]) -> int:
    count: int = 0
    if i - 3 >= 0 and j - 3 >= 0:
        if (
            matrix[i - 1][j - 1] == "M"
            and matrix[i - 2][j - 2] == "A"
            and matrix[i - 3][j - 3] == "S"
        ):
            count += 1
            print(f"UL i = {i}, j = {j}")

    if i + 3 < len(matrix) and j + 3 < len(matrix[i]):
        if (
            matrix[i + 1][j + 1] == "M"
            and matrix[i + 2][j + 2] == "A"
            and matrix[i + 3][j + 3] == "S"
        ):
            count += 1
            print(f"DR i = {i}, j = {j}")
    return count


# check up-right down-left now
def check_ur_dl(i: int, j: int, matrix: List[List[str]]) -> int:
    count: int = 0
    if i - 3 >= 0 and j + 3 < len(matrix[i]):
        if (
            matrix[i - 1][j + 1] == "M"
            and matrix[i - 2][j + 2] == "A"
            and matrix[i - 3][j + 3] == "S"
        ):
            count += 1
            print(f"UR i = {i}, j = {j}")
    if i + 3 < len(matrix) and j - 3 >= 0:
        if (
            matrix[i + 1][j - 1] == "M"
            and matrix[i + 2][j - 2] == "A"
            and matrix[i + 3][j - 3] == "S"
        ):

            count += 1
            print(f"DL i = {i}, j = {j}")
    return count


# lets test if its x now
def get_xmas_count(matrix: List[List[str]]) -> int:
    total_num: int = 0
    for i in range(len(matrix)):
        for j in range(len(matrix[i])):
            if matrix[i][j] == "X":
                total_num += (
                    check_vertical(i, j, matrix)
                    + check_horizontal(i, j, matrix)
                    + check_ul_dr(i, j, matrix)
                    + check_ur_dl(i, j, matrix)
                )

    return total_num


input_matrix: List[List[str]] = convert_to_array(file)

# so that module doesn't run always

if __name__ == '__main__':
    print(get_xmas_count(input_matrix))
