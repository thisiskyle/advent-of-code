from modules import aoc_utils
from modules import aoc_api as api


board_w = 5
board_h = 5
board_list = []
marked_board_list = []
numbers = []

# access the index of the board via coords
def getIndex(x, y):
    return (y * board_w) + x


def checkBingo(boards, marked_boards):
    # for each board
    for b in range(0, len(marked_boards)):

        # for each index on the board
        for i in range(0, board_w - 1):
            sumRow = marked_boards[b][i] + marked_boards[b][i + 1] + marked_boards[b][i + 2] + marked_boards[b][i + 3] + marked_boards[b][i + 4]
            sumCol = marked_boards[b][i] + marked_boards[b][i + (5 * 1)] + marked_boards[b][i + (5 * 2)] + marked_boards[b][i + (5 * 3)] + marked_boards[b][i + (5 * 4)]

            if sumRow == 5 or sumCol == 5:
                return b
    return -1


def checkMatches(boards, marked_boards, nums):

    # for each number drawn
    for n in range(0, len(numbers)):

        # for each board
        for b in range(0, len(boards)):

            # for each index on the board
            for i in range(0, len(boards[0])):
                if boards[b][i] == numbers[n]:
                    marked_boards[b][i] = 1


        winner = checkBingo(boards, marked_boards)
        if winner >= 0:
            return (winner, numbers[n])

def calcSumOfUnmarked(board, marked_board, lastNum):
    # add up all unmarked numbers
    sum = 0
    for b in range(0, len(board)):
        if not marked_board[b]:
            sum += board[b]

    # multiply sum with last number called before bingo
    return sum * lastNum


def solution(inputs):

    # take the first line of inputs and put it here
    for n in inputs[0].split(","):
        numbers.append(int(n))

    # turn the rest of the input into something useful
    t = []
    for j in range(1, len(inputs)):
        if not inputs[j]:
            continue
        for k in inputs[j].split(" "):
            if not k == '':
                t.append(int(k))



    # load the input into boards
    # a 1D array for each board
    for i in range(0, len(t), board_w * board_h):
        temp = []
        temp_marked = []
        for j in range(i, i + 25, 1):
            temp.append(t[j])
            temp_marked.append(0)


        board_list.append(temp)
        marked_board_list.append(temp_marked)

    winner_info = checkMatches(board_list, marked_board_list, numbers)

    a1 = calcSumOfUnmarked(board_list[winner_info[0]], marked_board_list[winner_info[0]], winner_info[1])

    return [a1]


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

test_expected = [4512]

aoc_utils.test_solution(test_input, test_expected, callback=solution, submit_flag=0, day=4, year=2021)
#aoc_utils.test_with_real_inputs(4, 2021, callback=solution)
