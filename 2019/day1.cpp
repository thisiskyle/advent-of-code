#include <fstream>
#include <iostream>
#include <cmath>

int main() {
    int answer1 = 0;
    int answer2 = 0;
    int input;
    std::ifstream input_file;
    input_file.open("./inputs/day1.txt");

    while(input_file >> input) {
        input = std::floor(input / 3) - 2;
        answer1 += input;
        while(input > 0) {
            answer2 += input;
            input = std::floor(input / 3) - 2;
        }
    }

    std::cout << "part 1: " << answer1 << std::endl;
    std::cout << "part 2: " << answer2 << std::endl;

    return 0;
}
