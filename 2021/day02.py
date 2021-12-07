from modules import aoc_utils



def solution(inputs):
    x = 0
    y = 0
    y2 = 0
    aim = 0

    # parse the input
    for i in range(len(inputs)):
        instruction = inputs[i].split()
        
        if instruction[0] == "forward":
            x += int(instruction[1])
            y2 += (aim * int(instruction[1]))
        elif instruction[0] == "up":
            y -= int(instruction[1])
            aim -= int(instruction[1])
        elif instruction[0] == "down":
            y += int(instruction[1])
            aim += int(instruction[1])


    a1 = x * y

    a2 = x * y2

    return [a1, a2]




test_input = [ "forward 5", "down 5", "forward 8", "up 3", "down 8", "forward 2" ]
test_expected = [150, 900]

aoc_utils.test_solution(test_input, test_expected, callback=solution, submit_flag=0, day=2, year=2021)


