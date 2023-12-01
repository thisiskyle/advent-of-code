from modules import aoc_utils

day = 1
year = 2023


def part1(inputs):
    a = 0
    for e in inputs:
        numbers = []
        for ch in e:
            if (ch.isnumeric()):
                numbers.append(ch)

        a += int(numbers[0] + numbers[len(numbers) - 1])

    return a


def part2(inputs):
    a = 0
    son = ['one', 'two', 'three', "four", "five", "six", "seven", "eight", "nine"]
    nums = ['1', '2', '3', '4', '5', '6', '7', '8', '9']

    for s in inputs:
        numbers = []
        for si in range(0, len(s)):
            if (s[si].isnumeric()):
                numbers.append(s[si])
            else:
                for i in range(0, len(son)):
                    if(s[si] == son[i][0]):
                        if(s[si:si + len(son[i])] == son[i]):
                            numbers.append(nums[i])


        a += int(numbers[0] + numbers[len(numbers) - 1])

    return a


#input = aoc_utils.get_input(day, year)
#input = ['two1nine', 'eightwothree', 'abcone2threexyz', 'xtwone3four', '4nineeightseven2', 'zoneight234', '7pqrstsixteen']
#aoc_utils.test(input, 281, callback=part2)

aoc_utils.submit(day, year, 2, callback=part2)
