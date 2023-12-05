from modules import aoc_utils

day = 3
year = 2023


def part1(inputs):
    a = 0
    regex = r'[^0-9|\.]'
    cols = len(inputs[0])
    rows = len(inputs)

    numbers = []

    for i in inputs:
        a += 0

    return a


def part2(inputs):
    a = 0

    for i in inputs:
        a += 0

    return a

# -11, -10, -9, -1, +1, +11, +10, +9
# 1, cols - 1, cols + 1, cols 

# input = aoc_utils.get_input(day, year)
input = [
    '467..114..',
    '...*......',
    '..35..633.',
    '......#...',
    '617*......',
    '.....+.58.',
    '..592.....',
    '......755.',
    '...$.*....',
    '.664.598..'
]

aoc_utils.test(input, expected=4361, callback=part1)
#aoc_utils.submit(day, year, level=2, callback=part1)
