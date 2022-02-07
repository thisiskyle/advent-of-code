import requests
import os.path



base_URL = "https://adventofcode.com/"

session_file = open("./session_id")
cookie = {'session': session_file.readline()}
session_file.close()



def get_input(day, year):

    print("\nSearching for input")

    if not (os.path.exists("./inputs/" + str(day) + ".txt")):
        print("Requesting input")
        URL = base_URL + str(year) + "/day/" + str(day) + "/input"
        r = requests.get(URL, cookies=cookie)
        file = open(f"./inputs/{str(day)}.txt", "w")
        file.write(r.text)
        file.close()
    else:
        print("Input found")

    inputs = []

    file = open(f"./inputs/{str(day)}.txt")

    for line in file:
        inputs.append(line.rstrip('\n'))

    file.close()
    return inputs




def submit(day, year, level, answer):


    URL = base_URL + str(year) + "/day/" + str(day) + "/answer"

    d={'level': level, 'answer': answer}

    r = requests.post(URL, data=d, cookies=cookie)

    if (r.text.find("That's the right answer") != -1):
        print(f"Day {day} level {level}: {answer} is correct")
    elif (r.text.find("That's not the right answer") != -1):
        print(f"Day {day} level {level}: {answer} is incorrect")
    elif (r.text.find("answer too recently") != -1):
        print(f"Day {day} level {level}: Answered too recently, please wait")
    elif (r.text.find("Did you already complete it") != -1):
        print(f"Day {day} level {level}: Already Solved")
    else:
        print(f"Day {day} level {level}: Something went wrong when submitting")


