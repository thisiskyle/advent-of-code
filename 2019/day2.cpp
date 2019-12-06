#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include "./headers/Intcode_Computer.h"

int main() {
    // reading input file
    std::ifstream input_file;
    input_file.open("./inputs/day2.txt");

    std::string temp;
    std::vector<int> input;
    while(getline(input_file, temp, ',')) {
        input.push_back(std::stoi(temp));
    }

    Intcode_Computer intcode(input);
    intcode.run(12, 2);
    std::cout << "part 1: " << intcode.get_output() << std::endl;

    int noun;
    int verb;

    for(noun = 0; noun < 100; noun++) {
        for(verb = 0; verb < 100; verb++) {
            intcode.reset_memory();
            intcode.run(noun, verb);
            if(intcode.get_output() == 19690720 ) {
                goto loop_break;
            }
        }
    }
    loop_break:

    std::cout << "part 2: " << (100 * noun) + verb << std::endl;

    return 0;
}
