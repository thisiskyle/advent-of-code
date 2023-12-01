import requests
import os.path
import os


base_URL = "https://adventofcode.com/"
session_file = open("./session_id")
cookie = {'session': session_file.readline().rstrip('\n')}
session_file.close()


def get_input(day, year):
    if not (os.path.exists("./inputs/")):
        print("\nCreating input directory")
        os.mkdir("./inputs/")

    if not (os.path.exists("./inputs/" + str(day) + ".txt")):
        print(f"\nRequesting day {day} input")
        URL = base_URL + str(year) + "/day/" + str(day) + "/input"
        r = requests.get(URL, cookies=cookie)
        file = open(f"./inputs/{str(day)}.txt", "w")
        file.write(r.text)
        file.close()
    else:
        print(f"Day {day} input file found")

    inputs = []
    file = open(f"./inputs/{str(day)}.txt")

    for line in file:
        inputs.append(line.rstrip('\n'))

    file.close()
    return inputs


def submit(day, year, level, answer):
    URL = base_URL + str(year) + "/day/" + str(day) + "/answer"
    d = {'level': level, 'answer': answer}
    r = requests.post(URL, data=d, cookies=cookie)

    # pass
    if (r.text.find("That's the right answer") != -1):
        print(f"Day {day} level {level}: {answer} is correct")
    # fail
    elif (r.text.find("That's not the right answer") != -1):
        print(f"Day {day} level {level}: {answer} is incorrect")
    # already solved
    elif (r.text.find("Did you already complete it") != -1):
        print(f"Day {day} level {level}: Already Solved")
    # ???
    else:
        print(r.text)
