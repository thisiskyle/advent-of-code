from modules import aoc_utils

day = 2
year = 2023


def part1(inputs):
    a = 0
    colors = ['red', 'green', 'blue']
    max = [12, 13, 14]

    for i in inputs:
        t1 = i.split(': ')
        game_id = t1[0][5::]
        rounds = t1[1].split('; ')
        possible = True

        for r in rounds:
            if not possible:
                break

            in_hand = r.split(', ')

            for m in in_hand:
                color_count = m.split(' ')
                count = int(color_count[0])
                color = color_count[1]

                if (count > max[colors.index(color)]):
                    possible = False
                    break


        if (possible):
            a += int(game_id)

    return a


def part2(inputs):
    a = 0

    for i in inputs:
        t1 = i.split(': ')
        game_id = t1[0][5::]
        rounds = t1[1].split('; ')
        colors = ['red', 'green', 'blue']
        max_found = [0, 0, 0]


        for r in rounds:
            in_hand = r.split(', ')

            for m in in_hand:
                color_count = m.split(' ')
                count = int(color_count[0])
                color = color_count[1]

                if (count > max_found[colors.index(color)]):
                    max_found[colors.index(color)] = count


        a += (max_found[0] * max_found[1] * max_found[2])

    return a


# input = aoc_utils.get_input(day, year)
input = [
    'Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green',
    'Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue',
    'Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red',
    'Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red',
    'Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green'
]

aoc_utils.test(input, expected=2286, callback=part2)

aoc_utils.submit(day, year, level=2, callback=part2)
