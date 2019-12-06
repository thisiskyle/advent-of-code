#ifndef INTCODE_H
#define INTCODE_H

#include <vector>
#include <iostream>

class Intcode_Computer {

public:
    std::vector<int> static_memory;
    std::vector<int> dynamic_memory;

    Intcode_Computer(const std::vector<int>& memory) {
        set_static_memory(memory);
        reset_memory();
    }

    void run(int noun, int verb) {
        dynamic_memory[1] = noun;
        dynamic_memory[2] = verb;
        run();
    }

    void run() {
        int instruction_pointer = 0;

        while(dynamic_memory[instruction_pointer] != 99 && instruction_pointer < dynamic_memory.size()) {

            int opcode;
            std::vector<int> parameter_modes;
            parse_instructions(dynamic_memory[instruction_pointer], opcode, parameter_modes);
            
            switch(opcode) {
                case 1: 
                case 2:
                    opcode1_2(opcode, instruction_pointer, parameter_modes);
                    break;
                case 3:
                    opcode3(instruction_pointer);
                    break;
                case 4:
                    opcode4(instruction_pointer);
                    break;
                case 5:
                    opcode5(instruction_pointer, parameter_modes);
                    break;
                case 6:
                    opcode6(instruction_pointer, parameter_modes);
                    break;
                case 7:
                    opcode7(instruction_pointer, parameter_modes);
                    break;
                case 8:
                    opcode8(instruction_pointer, parameter_modes);
                    break;
                default:
                    std::cout << "Error: Opcode " << opcode << " invalid" << std::endl;
                    break;
            }
        }
    }

    void opcode1_2(const int& opcode, int& instruction_pointer, const std::vector<int>& parameter_modes) {
        int address1 = dynamic_memory[instruction_pointer + 1];
        int address2 = dynamic_memory[instruction_pointer + 2];
        int addressOut = dynamic_memory[instruction_pointer + 3];
        int value1;
        int value2;

        if(parameter_modes[0] == 0) {
            value1 = dynamic_memory[address1];
        }
        else if(parameter_modes[0] == 1) {
            value1 = address1;
        }
        if(parameter_modes[1] == 0) {
            value2 = dynamic_memory[address2];
        }
        else if(parameter_modes[1] == 1) {
            value2 = address2;
        }

        if(opcode == 1) dynamic_memory[addressOut] = value1 + value2;
        else if(opcode == 2) dynamic_memory[addressOut] = value1 * value2;

        instruction_pointer += 4;
    }
    void opcode3(int& instruction_pointer) {
        // get user input
        int input;
        std::cout << "Please Provide System ID: ";
        std::cin >> input;

        // store the input
        int address = dynamic_memory[instruction_pointer + 1];
        dynamic_memory[address] = input;

        instruction_pointer += 2;
    }
    void opcode4(int& instruction_pointer) {
        int address = dynamic_memory[instruction_pointer + 1];
        std::cout << dynamic_memory[address] << std::endl;

        instruction_pointer += 2;
    }
    void opcode5(int& instruction_pointer, const std::vector<int>& parameter_modes) {

    }
    void opcode6(int& instruction_pointer, const std::vector<int>& parameter_modes) {

    }
    void opcode7(int& instruction_pointer, const std::vector<int>& parameter_modes) {

    }
    void opcode8(int& instruction_pointer, const std::vector<int>& parameter_modes) {

    }

    void reset_memory() {
        dynamic_memory = static_memory;
    }

    void set_static_memory(const std::vector<int> &memory) {
        static_memory = memory;
    }

    int get_output() {
        return dynamic_memory[0];
    }

    void parse_instructions(int instruction, int& opcode, std::vector<int>& parameter_modes) {
        int temp = instruction;
        std::vector<int> temp_list;
        for(int i = 0; i < 5; i++) {
            int n = temp % 10;
            temp_list.push_back(n);
            temp = temp / 10;
        }
        opcode = temp_list[0] + (temp_list[1] * 10);
        temp_list.erase(temp_list.begin(), temp_list.begin() + 2);
        parameter_modes = temp_list;
    }
};

#endif
