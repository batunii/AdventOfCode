import re
from typing import List

file = open(r"input3.txt", "r")
input_text = file.read()
text_input = "xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))"
text_input_ex2 = "xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))"


def identify_muls(input_string: str) -> int:
    pattern = re.compile(r"mul\([0-9]+,[0-9]+\)", re.IGNORECASE)
    result: List[str] = pattern.findall(input_string)
    answer: int = 0
    number_pattern = re.compile(r"[0-9]+,[0-9]+", re.NOFLAG)
    for muls in result:
        numbers: str = number_pattern.search(muls).group()
        num1, num2 = map(int, numbers.split(","))
        answer += num1 * num2
    return answer

print(identify_muls(input_text))


def remove_donts(input_string: str) -> int:
    new_ans: int = 0
    dont_do_pattern = re.compile(r"mul\(\d{1,3},\d{1,3}\)|do\(\)|don't\(\)", re.NOFLAG)
    matches = dont_do_pattern.findall(input_string)
    flag:bool = True
    for match in matches:
        if match == "don't()":
            flag = False
        elif match == "do()":
            flag = True
        else:
            if flag:
                num1, num2 = map(int, match[4:-1].split(","))
                new_ans+=num1*num2
    return new_ans

print(remove_donts(input_text))
