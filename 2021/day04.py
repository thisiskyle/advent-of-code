from modules import aoc_utils
from modules import aoc_api as api

board_w = 5
board_h = 5

def checkBingo(boards, marked_boards):
    # for each board
    for b in range(0, len(marked_boards)):
        # for each index on the board
        for i in range(0, board_w):
            sumRow = 0
            sumRow += marked_boards[b][(i * 5) + 0]
            sumRow += marked_boards[b][(i * 5) + 1]
            sumRow += marked_boards[b][(i * 5) + 2]
            sumRow += marked_boards[b][(i * 5) + 3]
            sumRow += marked_boards[b][(i * 5) + 4]
            if sumRow == 5:
                return b

            sumCol = 0
            sumCol += marked_boards[b][(0 * 5) + i]
            sumCol += marked_boards[b][(1 * 5) + i]
            sumCol += marked_boards[b][(2 * 5) + i]
            sumCol += marked_boards[b][(3 * 5) + i]
            sumCol += marked_boards[b][(4 * 5) + i]
            if sumCol == 5:
                return b

    return None 


def checkMatches(boards, marked_boards, nums):
    # for each number drawn
    for n in nums:
        # for each board
        for b in range(0, len(boards)):
            # for each index on the board
            for i in range(0, len(boards[0])):
                if boards[b][i] == n:
                    marked_boards[b][i] = 1

        winner = checkBingo(boards, marked_boards)

        if winner != None:
            return (winner, n)



def findLoser(boards, marked_boards, nums):
    for n in nums:
        for b in range(0, len(boards)):
            for i in range(0, len(boards[0])):
                if boards[b][i] == n:
                    marked_boards[b][i] = 1

        winner = checkBingo(boards, marked_boards)

        while winner != None:
            if len(boards) == 1:
                return (boards[0], marked_boards[0], n)
            else:
                boards.pop(winner)
                marked_boards.pop(winner)
            winner = checkBingo(boards, marked_boards)




def calcSumOfUnmarked(board, marked_board, lastNum):
    # add up all unmarked numbers
    sum = 0
    for b in range(0, len(board)):
        if marked_board[b] == 0:
            sum += board[b]

    # multiply sum with last number called before bingo
    return sum * lastNum


def solution(inputs):

    board_list = []
    marked_board_list = []
    numbers = []

    for i in inputs:
        if not i:
            inputs.remove(i)

    # take the first line of inputs and put it here
    numbers = [int(n) for n in inputs[0].strip().split(',')]


    # remove the first line
    inputs.pop(0)

    # convert the arrays of strings into a single array of ints
    t = [int(m) for n in inputs for m in n.split()]

    # sort the array of ints into a 1D array for each board
    # and a parallel array for the marked positions
    for i in range(0, len(t), board_w * board_h):
        board_list.append([t[j] for j in range(i, i + 25, 1)])
        marked_board_list.append([0 for x in range(25)])

    winner_info = checkMatches(board_list, marked_board_list, numbers)
    a1 = calcSumOfUnmarked(board_list[winner_info[0]], marked_board_list[winner_info[0]], winner_info[1])

    # reset the marked boards
    marked_board_list = [[0 for x in range(25)] for i in range(len(board_list))]

    loser_info = findLoser(board_list, marked_board_list, numbers)
    a2 = calcSumOfUnmarked(loser_info[0], loser_info[1], loser_info[2])

    return [a1, a2]



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

test_expected = [4512, 1924]


aoc_utils.test_solution(test_input, test_expected, callback=solution, submit_flag=1, day=4, year=2021)
