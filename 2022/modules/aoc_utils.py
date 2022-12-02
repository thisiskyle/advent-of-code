from modules import aoc_api as api


def test_solution(input, expected, callback, day=0, year=0):
    test_results = []
    test_answers = callback(input)
    to_return = True

    print("\n--- Running tests with test data--- \n")

    for n in range(len(test_answers)):
       test_results.append(expected[n] == test_answers[n])
       if(test_results[n] == False):
           to_return = False
       print(f"Testing level {n + 1}: [{test_results[n]}] Expected: {str(expected[n])} Actual: {str(test_answers[n])}")

    print("")

    return to_return



def test_with_real_inputs(day, year, callback):
    print("\n--- Running tests with real data ---\n")

    answers = callback(api.get_input(day, year))

    print("")
    for a in range(len(answers)):
        print(f"Answer {a + 1}: {answers[a]}")
    print("")


def submit_solution(day, year, callback):
    if (day == 0) or (year == 0):
        print("\nCannot submit without a day or year")
        return

    answers = callback(api.get_input(day, year))

    for a in range(len(answers)):
        print(f"\nSubmitting answer {a + 1}: {answers[a]}\n")
        api.submit(day, year, (a + 1), answers[a])
