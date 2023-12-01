from modules import aoc_utils


def solution(inputs):
    a1 = 0
    a2 = 0

    win = 6
    draw = 3
    lose = 0

    #          R    P    S      R    P    S
    items = [["A", "B", "C"], ["X", "Y", "Z"]]
    item_points = [1, 2, 3]

    for round in inputs:
        selections = round.split()
        opponent = items[0].index(selections[0])
        me = items[1].index(selections[1])

        # draw
        if(me == opponent):
            a1 += draw + item_points[me]
        # win
        elif(me == (opponent + 1) % len(items[0])):
            a1 += win + item_points[me]
        # lose
        else:
            a1 += lose + item_points[me]

        # lose
        if(selections[1] == "X"):
            a2 += item_points[(opponent + 2) % len(items[0])]
        # draw
        elif(selections[1] == "Y"):
            a2 += draw + item_points[opponent]
        # win
        elif(selections[1] == "Z"):
            a2 += win + item_points[(opponent + 1) % len(items[0])]
        else:
            print("something is wrong")

    return [a1, a2]


test_input = ["A Y", "B X", "C Z"]
test_expected = [15, 12] 

aoc_utils.test_solution(test_input, test_expected, callback=solution)
#aoc_utils.test_with_real_inputs(2, 2022, callback=solution)
#aoc_utils.submit_solution(2, 2022, callback=solution)
