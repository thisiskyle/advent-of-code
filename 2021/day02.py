from modules import tester
from modules import aocapi as aoc


day = 2
year = 2021

input_actual = aoc.get_input(day, year)

input_test = [
    "forward 5",
    "down 5",
    "forward 8",
    "up 3",
    "down 8",
    "forward 2"
]

def test_and_submit(submit_flag=0):
    if(tester.run_test(input_test, 150, 1, callback=run)):
        answer = run(input_actual)

        if(submit_flag): 
            aoc.submit(day, year, 1, answer[0])
        else:
            print(f"part 1: {answer[0]}")

        if(tester.run_test(input_test, 900, 2, callback=run)):

            if(submit_flag): 
                aoc.submit(day, year, 1, answer[1])
            else:
                print(f"part 2: {answer[1]}")



def run(inputs):
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



test_and_submit()




