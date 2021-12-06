

def run_test(input, expected, level, callback):
    ans = callback(input)
    if(expected == ans[level - 1]):
       print(f"Test {level} Passed! Expected: {str(expected)} Actual: {str(ans[level - 1])}")
       return True
    else:
       print(f"Test {level} failed! Expected: {str(expected)} Actual: {str(ans[level - 1])}")
       return False


