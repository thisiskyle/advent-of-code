#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include "../headers/Intcode.h"

int main() {
    // reading input file
    std::ifstream input_file;
    input_file.open("./input.txt");

    // copy input into initial memory
    std::string input;
    std::vector<int> initial_memory_state;
    while(getline(input_file, input, ',')) {
        initial_memory_state.push_back(std::stoi(input));
    }

    Intcode intcode(initial_memory_state, 12, 2);
    intcode.run();

    std::cout << "part 1: " << intcode.get_output() << std::endl;

    int noun;
    int verb;

    for(noun = 0; noun < 100; noun++) {
        for(verb = 0; verb < 100; verb++) {
            Intcode intcode(initial_memory_state, noun, verb);
            intcode.run();
            if(intcode.get_output() == 19690720 ) {
                goto loop_break;
            }
        }
    }
    loop_break:

    std::cout << "part 2: " << (100 * noun) + verb << std::endl;

    return 0;
}
