from modules import aoc_utils
import re

day = 4
year = 2023
input = aoc_utils.get_input(day, year)

test_input = [
    'Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53',
    'Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19',
    'Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1',
    'Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83',
    'Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36',
    'Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11'
]


def part1(inputs):
    a = 0

    card_win_count = []
    card_numbers_win = []
    card_numbers_own = []

    # organize the input and card numbers
    for i in range(0, len(inputs)):
        numbers = inputs[i].replace("  ", " ").split(': ')[1].split(' | ')
        card_numbers_win.append(numbers[0].split(" "))
        card_numbers_own.append(numbers[1].split(" "))
        card_win_count.append(0)

    # calculate wins for each card
    for j in range(0, len(inputs)):
        for n in card_numbers_own[j]:
            if n in card_numbers_win[j]:
                card_win_count[j] += 1

    # calculate result
    for c in card_win_count:
        if(c > 0):
            a += 2**(c - 1)

    return a


def part2(inputs):
    a = 0

    card_win_count = []
    card_instances = []
    card_numbers_win = []
    card_numbers_own = []

    # organize the input and card numbers
    for i in range(0, len(inputs)):
        numbers = inputs[i].replace("  ", " ").split(': ')[1].split(' | ')
        card_numbers_win.append(numbers[0].split(" "))
        card_numbers_own.append(numbers[1].split(" "))
        card_win_count.append(0)
        card_instances.append(1)

    # calculate wins for each card
    for j in range(0, len(inputs)):
        for n in card_numbers_own[j]:
            if n in card_numbers_win[j]:
                card_win_count[j] += 1

    # distribute wins
    for c in range(0, len(inputs)):
        for n in range(0, card_win_count[c]):
            card_instances[c + n + 1] += card_instances[c]

    # count the cards
    for c in card_instances:
        a += c


    return a

aoc_utils.test(test_input, expected=30, callback=part2)
#aoc_utils.submit(day, year, level=1, callback=part1)
aoc_utils.submit(day, year, level=2, callback=part2)
