#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include "./headers/Intcode_Computer.h"

int main() {

    Intcode_Computer computer("./inputs/day2.txt");
    computer.insert_noun_and_verb(12, 2);
    computer.run();


    std::cout << "part 1: " << computer.get_output() << std::endl;


    int noun, verb;
    for(noun = 0; noun < 100; noun++) {
        for(verb = 0; verb < 100; verb++) {

            computer.reset();
            computer.insert_noun_and_verb(noun, verb);
            computer.run();

            if(computer.get_output() == 19690720 ) { goto loop_break; }
        }
    }
    loop_break:

    std::cout << "part 2: " << (100 * noun) + verb << std::endl;

    return 0;
}
