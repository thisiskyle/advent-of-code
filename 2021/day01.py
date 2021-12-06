from modules import aoc_utils


def solution(inputs):
    a1 = 0
    a2 = 0

    # convert to ints
    for i in range(len(inputs)):
        inputs[i] = int(inputs[i])


    # init the prev variable
    prev = inputs[0]

    # loop and check
    for num in range(1, len(inputs)):
        if(inputs[num] > prev):
            a1 += 1
        prev = inputs[num]

    # init the prev variable
    prev_window = (inputs[0] + inputs[1] + inputs[2])

    # loop and check
    for i in range(1, len(inputs) - 2):
        window = (inputs[i] + inputs[i+1] + inputs[i+2])
        if(window > prev_window):
            a2 += 1
        prev_window = window

    # return answers
    return [a1, a2]



input_test = [199, 200, 208, 210, 200, 207, 240, 269, 260, 263]

aoc_utils.test_and_submit(1, 2021, input_test, [7, 5], solution)
