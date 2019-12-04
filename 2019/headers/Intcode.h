#ifndef INTCODE_H
#define INTCODE_H


#include <vector>
#include <iostream>

class Intcode {
public:
    static int run(std::vector<int> memory, int noun, int verb) {

        memory[1] = noun;
        memory[2] = verb;

        // initialize instruction pointer
        int instruction_pointer = 0;

        // execute instructions
        while(memory[instruction_pointer] != 99 && instruction_pointer < memory.size()) {

            int address_1 = memory[instruction_pointer + 1]; 
            int address_2 = memory[instruction_pointer + 2]; 
            int address_out = memory[instruction_pointer + 3]; 

            switch(memory[instruction_pointer]) {
                case 1:
                    memory[address_out] = memory[address_1] + memory[address_2];
                    instruction_pointer += 4;
                    break;
                case 2:
                    memory[address_out] = memory[address_1] * memory[address_2];
                    instruction_pointer += 4;
                    break;
                default:
                    std::cout << "Error: Opcode invalid" << std::endl;
                    break;
            }
        }
        return memory[0];
    }
};

#endif
