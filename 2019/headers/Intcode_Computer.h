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
        int count = 0;

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
                    std::cout << "Instruction: " << dynamic_memory[instruction_pointer] << std::endl;
                    return;
            }
        }
    }

    void opcode1_2(const int& opcode, int& instruction_pointer, const std::vector<int>& parameter_modes) {
        int param1 = get_parameter(parameter_modes[0], instruction_pointer, 1);
        int param2 = get_parameter(parameter_modes[1], instruction_pointer, 2);
        int write_address = dynamic_memory[instruction_pointer + 3];

        if(opcode == 1) dynamic_memory[write_address] = param1 + param2;
        else if(opcode == 2) dynamic_memory[write_address] = param1 * param2;
        instruction_pointer += 4;
    }

    void opcode3(int& instruction_pointer) {
        // get user input
        int input;
        std::cout << "Please provide a system ID: ";
        std::cin >> input;
        // store the input
        int write_address = dynamic_memory[instruction_pointer + 1];
        dynamic_memory[write_address] = input;
        instruction_pointer += 2;
    }

    void opcode4(int& instruction_pointer) {
        int address = dynamic_memory[instruction_pointer + 1];
        std::cout << dynamic_memory[address] << std::endl;
        instruction_pointer += 2;
    }

    void opcode5(int& instruction_pointer, const std::vector<int>& parameter_modes) {
        int param1 = get_parameter(parameter_modes[0], instruction_pointer, 1);
        int param2 = get_parameter(parameter_modes[1], instruction_pointer, 2);
        instruction_pointer = param1 != 0 ? param2 : (instruction_pointer + 3);
    }

    void opcode6(int& instruction_pointer, const std::vector<int>& parameter_modes) {
        int param1 = get_parameter(parameter_modes[0], instruction_pointer, 1);
        int param2 = get_parameter(parameter_modes[1], instruction_pointer, 2);
        instruction_pointer = param1 == 0 ? param2 : (instruction_pointer + 3);
    }

    void opcode7(int& instruction_pointer, const std::vector<int>& parameter_modes) {
        int param1 = get_parameter(parameter_modes[0], instruction_pointer, 1);
        int param2 = get_parameter(parameter_modes[1], instruction_pointer, 2);
        int write_address = dynamic_memory[instruction_pointer + 3];
        dynamic_memory[write_address] = (param1 < param2);
        instruction_pointer += 4;
    }

    void opcode8(int& instruction_pointer, const std::vector<int>& parameter_modes) {
        int param1 = get_parameter(parameter_modes[0], instruction_pointer, 1);
        int param2 = get_parameter(parameter_modes[1], instruction_pointer, 2);
        int write_address = dynamic_memory[instruction_pointer + 3];
        dynamic_memory[write_address] = (param1 == param2);
        instruction_pointer += 4;
    }

    void reset_memory() {
        dynamic_memory = static_memory;
    }

    void set_static_memory(const std::vector<int> &memory) {
        static_memory = memory;
    }

    // for use with day 2
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

    int get_parameter(const int& mode, const int& instruction_pointer, int offset) {
        return mode == 0 ? dynamic_memory[dynamic_memory[instruction_pointer + offset]] : dynamic_memory[instruction_pointer + offset];
    }
};
#endif
