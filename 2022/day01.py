from modules import aoc_utils


def solution(inputs):
    a1 = 0
    a2 = 0

    calories = 0
    i = 0
    top_three = [0, 0, 0]

    while(True):
        if(i >= len(inputs)):
            if(calories > a1):
                a1 = calories

            if(top_three[0] < calories):
                top_three[0] = calories

            break

        if(inputs[i] == ''):
            if(calories > a1):
                a1 = calories

            if(top_three[0] < calories):
                top_three[0] = calories

            calories = 0

        else:
            calories += int(inputs[i])

        top_three.sort()
        i += 1


    for a in top_three:
        a2 += a

    return [a1, a2]



test_input = ['1000', '2000', '3000', '', '4000', '', '5000', '6000', '', '7000', '8000', '9000', '', '10000']
test_expected = [24000, 45000] 

#aoc_utils.test_solution(test_input, test_expected, callback=solution, day=1, year=2022)
#aoc_utils.test_with_real_inputs(1, 2022, callback=solution)
aoc_utils.submit_solution(1, 2022, callback=solution)
