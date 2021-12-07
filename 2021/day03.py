from modules import aoc_utils
from modules import aoc_api as api



def solution(inputs):

    gamma = 0
    epsilon = 0
    oxygen = inputs.copy()
    c02 = inputs.copy()

    # for each bit
    for i in range(len(inputs[0])):
        ones = 0
        zeroes = 0

        # for each input
        for j in range(len(inputs)):

            if (int(inputs[j], 2) & 1 << (len(inputs[0]) - 1 - i)):
                ones += 1
            else:
                zeroes += 1


        if (ones >= zeroes):
            gamma = gamma | 1 << (len(inputs[0]) - 1 - i)

            if not (len(oxygen) == 1):
                for o in range(len(oxygen) - 1, -1, -1):
                    if not (oxygen[o][i] == "1"):
                        if(len(oxygen) > 1):
                            oxygen.pop(o)

            if not (len(c02) == 1):
                for c in range(len(c02) - 1, -1, -1):
                    if not (c02[c][i] == "0"):
                        if (len(c02) > 1):
                            c02.pop(c)

        else:

            if not (len(oxygen) == 1):
                for o in range(len(oxygen) - 1, -1, -1):
                    if not (oxygen[o][i] == "0"):
                        if(len(oxygen) > 1):
                            oxygen.pop(o)

            if not (len(c02) == 1):
                for c in range(len(c02) - 1, -1, -1):
                    if not (c02[c][i] == "1"):
                        if (len(c02) > 1):
                            c02.pop(c)


    #print(oxygen)
    #print(c02)

    epsilon = int((str("1") * len(inputs[0])), 2) - gamma

    return [(gamma * epsilon), (int(oxygen[0], 2) * int(c02[0], 2))]



test_input = [
    "00100",
    "11110",
    "10110",
    "10111",
    "10101",
    "01111",
    "00111",
    "11100",
    "10000",
    "11001",
    "00010",
    "01010"
]

test_expected = [198, 230]

aoc_utils.test_solution(test_input, test_expected, callback=solution, submit_flag=0, day=3, year=2021)
