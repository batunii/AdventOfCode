from io import TextIOWrapper
from typing import List

file: TextIOWrapper = open(r"input7.txt", "r")
sum_list: List[int] = list()
vals_list: List[List[int]] = list()
for index, line in enumerate(file):
    line.strip()
    sum, val = line.split(":")
    sum_list.append(int(sum))
    vals: List[int] = list(map(int, val.split()))
    vals_list.append(vals)


def recursion(array: List[int], result: int, final_result: int) -> bool:
    if len(array) == 0:
        return result == final_result
    else:
        val1 = array[0]
        new_array = array[1:]
        # 2 paths now
        add_val = val1 + result
        mul_val = val1 * (1 if result == 0 else result)
        # 3rd path
        conc_val = int(f"{'' if result==0 else result}{val1}")
        return (
            recursion(new_array, add_val, final_result)
            or recursion(new_array, mul_val, final_result)
            or recursion(new_array, conc_val, final_result)
        )


def call_recursion(sum_vals: List[int], vals: List[List[int]]) -> int:
    final_answer = 0
    for i in range(len(sum_vals)):
        if recursion(vals[i], 0, sum_vals[i]):
            final_answer += sum_vals[i]

    return final_answer


print(call_recursion(sum_list, vals_list))
