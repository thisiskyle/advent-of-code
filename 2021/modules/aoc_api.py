import requests
import os.path



base_URL = "https://adventofcode.com/"

session_file = open("./session_id")
cookie = {'session': session_file.readline()}
session_file.close()



def get_input(day, year):

    if not (os.path.exists("./inputs/" + str(day) + ".txt")):
        print("Requesting input")
        URL = base_URL + str(year) + "/day/" + str(day) + "/input"
        r = requests.get(URL, cookies=cookie)
        file = open(f"./inputs/{str(day)}.txt", "w")
        file.write(r.text)
        file.close()

    inputs = []

    file = open(f"./inputs/{str(day)}.txt")

    for line in file:
        inputs.append(line)

    file.close()
    return inputs




def submit(day, year, level, answer):
    URL = base_URL + str(year) + "/day/" + str(day) + "/answer"

    d={'level': level, 'answer': answer}

    r = requests.post(URL, data=d, cookies=cookie)

    if (r.text.find("That's the right answer!")):
        print(f"Level {level}: {answer} is correct")

    elif (r.text.find("That's not the right answer.")):
        print(f"Level {level}: {answer} is incorrect")

