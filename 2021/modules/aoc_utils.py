from modules import aoc_api as api


def test_solution(input, expected, callback, submit_flag=0, day=0, year=0):
    test_results = []
    test_answers = callback(input)

    print("\nRunning tests\n")

    for n in range(len(test_answers)):
       test_results.append(expected[n] == test_answers[n])
       print(f"Testing level {n + 1}: [{test_results[n]}] Expected: {str(expected[n])} Actual: {str(test_answers[n])}")

    print("")

    if (submit_flag):
        if (day == 0) or (year == 0):
            print("\nCannot submit without a day or year")
            return

        answers = callback(api.get_input(day, year))
        print(f"\nAnswers: {answers}")

        print("\nSubmitting answers\n")
        for r in range(len(test_results)):
            if test_results[r]:
                api.submit(day, year, (r + 1), answers[r])
            else:
                print(f"Test for level {r + 1} failed. No answer submitted")

        print("")


def test_with_real_inputs(day, year, callback):
        answers = callback(api.get_input(day, year))
        for i in answers:
            print(i)
