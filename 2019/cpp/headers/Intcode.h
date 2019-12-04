#ifndef INTCODE_H
#define INTCODE_H


#include <vector>
#include <iostream>

class Intcode {
public:
    std::vector<int> memory;

    Intcode(std::vector<int>mem, int noun, int verb) {
        memory = mem;
        memory[1] = noun;
        memory[2] = verb;
    }
    void run() {
        // initialize instruction pointer
        int ins_pointer = 0;

        // execute instructions
        while(memory[ins_pointer] != 99) {
            switch(memory[ins_pointer]) {
                case 1:
                    memory[memory[ins_pointer + 3]] = memory[memory[ins_pointer + 1]] + memory[memory[ins_pointer + 2]];
                    ins_pointer += 4;
                    break;
                case 2:
                    memory[memory[ins_pointer + 3]] = memory[memory[ins_pointer + 1]] * memory[memory[ins_pointer + 2]];
                    ins_pointer += 4;
                    break;
                default:
                    std::cout << "Error: Opcode invalid" << std::endl;
                    break;
            }
        }
    }
    int get_output() {
        return memory[0];
    }
};

#endif
