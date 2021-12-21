from modules import aoc_utils
from modules import aoc_api as api


board_w = 5
board_h = 5
board_list = []
numbers = []

# access the index of the board via coords
def getIndex(x, y):
    return (y * board_w) + x


def solution(inputs):

    # take the first line of inputs and put it here
    for n in inputs[0].split(","):
        numbers.append(int(n))

    # turn the rest of the input into something useful
    t = []
    for j in range(1, len(inputs)):
        for k in inputs[j].split(" "):
            if not k == '':
                t.append(int(k))


    # load the input into boards
    # a 1D array for each board
    for i in range(0, len(t) - 1, board_w * board_h):
        temp = []
        for j in range(i, i + 24, 1):
            temp.append(t[j])


        board_list.append(temp)

    print(board_list[0][getIndex(0,4)])

    return [0]


test_input = [ 
    "7,4,9,5,11,17,23,2,0,14,21,24,10,16,13,6,15,25,12,22,18,20,8,19,3,26,1",
    "22 13 17 11  0",
    " 8  2 23  4 24",
    "21  9 14 16  7",
    " 6 10  3 18  5",
    " 1 12 20 15 19",
    " 3 15  0  2 22",
    " 9 18 13 17  5",
    "19  8  7 25 23",
    "20 11 10 24  4",
    "14 21 16 12  6",
    "14 21 17 24  4",
    "10 16 15  9 19",
    "18  8 23 26 20",
    "22 11 13  6  5",
    " 2  0 12  3  7"
]

test_expected = [0]

aoc_utils.test_solution(test_input, test_expected, callback=solution, submit_flag=0, day=4, year=2021)
