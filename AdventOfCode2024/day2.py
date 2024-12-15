from typing import List

programs: List[str] = []
file = open(r"input2.txt", "r")
for line in file:
    programs.append(line)

file.close()

final_pro: List[List[int]] = list()
for _ in range(len(programs)):
    program: List[int] = list(map(int, programs.pop().strip().split(" ")))
    final_pro.append(program)


def is_sorted(list: List[int]) -> bool:
    asc: bool = all(list[i] <= list[i + 1] for i in range(len(list) - 1))
    dsc: bool = all(list[i] >= list[i + 1] for i in range(len(list) - 1))
    return asc or dsc


def diff_5(list: List[int]) -> bool:
    return all(abs(list[i] - list[i + 1]) <= 3 and abs(list[i] - list[i + 1]) > 0 for i in range(len(list) - 1))


def is_safe(program: List[int]) -> bool:
     return is_sorted(program) and diff_5(program)


safe: int = 0
for pro in final_pro:
    if is_safe(pro):
        print(pro)
        safe = safe + 1

print(safe)

new_safe: int = 0

def remove_one(list_var: List[int], index: int) -> List[int] :
    new_list: List[int] = list()
    for x in range(len(list_var)):
        if x!=index :
            new_list.append(list_var[x])
    return new_list

for pro in final_pro : 
    if is_safe(pro) : 
        new_safe += 1
    else:
        for x in range(len(pro)) :
            new_list = remove_one(pro, x)
            if is_safe(new_list) :
                new_safe += 1
                break

print(new_safe)
