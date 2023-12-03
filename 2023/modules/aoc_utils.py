from modules import aoc_api as api


def test(input, expected, callback):
    print("\n--- Running Test --- \n")
    test_answer = callback(input)
    to_return = (expected == test_answer)
    print(f"Testing Solution: [{to_return}]\n    Expected: {str(expected)}\n    Actual: {str(test_answer)}")
    print("")
    return to_return


def submit(day, year, level, callback):
    if (day == 0) or (year == 0):
        print("\nCannot submit without a day or year")
        return

    answer = callback(api.get_input(day, year))
    print(f"\nSubmitting {year} day {day}, part {level}: {answer}\n")
    api.submit(day, year, level, answer)


def get_input(day, year):
    if (day == 0) or (year == 0):
        print("\nCannot get input without a day or year")
        return

    return api.get_input(day, year)
