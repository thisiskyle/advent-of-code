from modules import aoc_utils
import re

day = 3
year = 2023
input = aoc_utils.get_input(day, year)

test_input1 = [
    '467..114..',
    '...%......',
    '..35..633.',
    '......#...',
    '617-......',
    '.....+.58.',
    '..592.....',
    '......755.',
    '.../.*....',
    '.664.598..'
]

test_input2 = [
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


# turns an array of indexes into the actual number they represent
def indexes2num(input, indexes):
    start = indexes[0]
    end = start + len(indexes)
    return int(input[start:end:1])

# checks if a given index is adjacent to  a symbol
def is_touching_symbol(index, cols, input):
    adj = [ 
        index + 1, 
        index - 1, 
        index + cols, 
        index - cols, 
        index + cols - 1, 
        index - cols - 1, 
        index + cols + 1,
        index - cols + 1
    ]

    for a in adj:
        if(a >= 0 and a < len(input)):
            if (re.search('[^0-9|\.]', input[a])):
                return True

    return False

# checks if the gear index is touching two numbers
# then return those two numbers
def gear_is_touching_two(index, cols, input, numbers):
    adj = [ 
        index + 1, 
        index - 1, 
        index + cols, 
        index - cols, 
        index + cols - 1, 
        index - cols - 1, 
        index + cols + 1,
        index - cols + 1
    ]

    numbers_touched = []

    for a in adj:
        if(a >= 0 and a < len(input)):
            if (re.search('[0-9]', input[a])):
                num_indexes = get_number_at_index(numbers, a)
                num = indexes2num(input, num_indexes)
                if (num not in numbers_touched):
                    numbers_touched.append(num)

    if len(numbers_touched) == 2:
        return numbers_touched

    return []


# return the array of indexes, representing a number on the grid that contains the given index
# this lets us reason out the whole number no matter which "digit" we start with
def get_number_at_index(numbers, index):
    for n in numbers:
        if index in n:
            return n

    return []



# this function returns an array of arrays of indexes that represent
# the numbers on the input
# example: '432....56..' would be returned as [[0, 1, 2], [7, 8]]
def get_number_indexes(input, cols):
    number_indexes = []

    i = 0
    while(i < len(input)):
        num = []
        current_row = int(i / cols)

        while(re.search('[0-9]', input[i])):
            num.append(i)

            # handle the break at a wrap
            if(int((i + 1) / cols) != current_row):
                break
            else:
                i += 1

        if(len(num) > 0):
            number_indexes.append(num)

        i += 1

    return number_indexes



def part1(inputs):
    a = 0
    cols = len(inputs[0])

    joined_input = ''.join(inputs)
    number_indexes = get_number_indexes(joined_input, cols)

    for n in number_indexes:
        for d in n:
            if(is_touching_symbol(d, cols, joined_input)):
                x = (indexes2num(joined_input, n))
                a += x
                break

    return a


def part2(inputs):
    a = 0
    cols = len(inputs[0])
    gear_indexes = []

    joined_input = ''.join(inputs)
    number_indexes = get_number_indexes(joined_input, cols)

    for i in range(0, len(joined_input)):
        if (joined_input[i] == '*'):
            gear_indexes.append(i)

    for g in gear_indexes:
        res = gear_is_touching_two(g, cols, joined_input, number_indexes)
        if len(res) == 2:
            a += res[0] * res[1]

    return a


aoc_utils.test(input, expected=84495585, callback=part2)

#aoc_utils.submit(day, year, level=1, callback=part1)
#aoc_utils.submit(day, year, level=2, callback=part2)
