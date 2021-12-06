from modules import aoc_tester as tester
from modules import aoc_api as api


def run_test(day, year, test_inputs, outputs, callback):
    test_results = []

    for n in range(len(outputs)):
        test_results.append(tester.run_test(test_inputs, outputs[n], (n + 1), callback=callback))

    return test_results



def solve_and_submit(day, year, callback):

        input_actual = api.get_input(day, year)
        answer = callback(input_actual)

        for i in range(len(answer)):
            api.submit(day, year, (i + 1), answer[i])



def test_and_submit(day, year, test_inputs, outputs, callback):

    test_results = run_test(day, year, test_inputs, outputs, callback)

    for r in test_results:
        if not r:
            return


    solve_and_submit(day, year, callback)





