from modules import aoc_utils
from modules import aoc_api as api



def solution(inputs):

    gamma = 0
    epsilon = 0

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

    epsilon = int((str("1") * len(inputs[0])), 2) - gamma

    return [(gamma * epsilon), (calc_oxygen(inputs.copy()) * calc_c02(inputs.copy()))] 



def calc_oxygen(bins):
    # for each bit
    for i in range(len(bins[0])):
        ones = 0
        zeroes = 0
        # loop through list
        for j in range(len(bins)):
            if (int(bins[j], 2) & 1 << (len(bins[0]) - 1 - i)):
                ones += 1
            else:
                zeroes += 1

        if (ones >= zeroes):

            if not (len(bins) == 1):
                for o in range(len(bins) - 1, -1, -1):
                    if not (bins[o][i] == "1"):
                        if(len(bins) > 1):
                            bins.pop(o)
        else:

            if not (len(bins) == 1):
                for o in range(len(bins) - 1, -1, -1):
                    if not (bins[o][i] == "0"):
                        if(len(bins) > 1):
                            bins.pop(o)

    return int(bins[0], 2)

def calc_c02(bins):
    # for each bit
    for i in range(len(bins[0])):
        ones = 0
        zeroes = 0
        # loop through list
        for j in range(len(bins)):
            if (int(bins[j], 2) & 1 << (len(bins[0]) - 1 - i)):
                ones += 1
            else:
                zeroes += 1

        if (ones >= zeroes):

            if not (len(bins) == 1):
                for o in range(len(bins) - 1, -1, -1):
                    if not (bins[o][i] == "0"):
                        if(len(bins) > 1):
                            bins.pop(o)
        else:

            if not (len(bins) == 1):
                for o in range(len(bins) - 1, -1, -1):
                    if not (bins[o][i] == "1"):
                        if(len(bins) > 1):
                            bins.pop(o)

    return int(bins[0], 2)




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

aoc_utils.test_solution(test_input, test_expected, callback=solution, submit_flag=1, day=3, year=2021)
