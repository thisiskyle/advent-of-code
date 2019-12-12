#ifndef INTCODE_H
#define INTCODE_H

#include <vector>
#include <string>
#include <iostream>
#include "./aoc.h"

class Intcode_Computer {

public:
    std::vector<int> static_memory;
    std::vector<int> dynamic_memory;
    std::vector<int> inputs;
    int instruction_pointer = 0;
    int input_index = 0;
    int* out;
    bool running = false;
    bool halted = false;
    bool pause_on_4 = false;



    Intcode_Computer(const std::vector<int>& memory, bool run_now = false, int* _out = NULL) {
        static_memory = memory;
        reset_dynamic_memory();
        out = _out;
        if(run_now) run();
    }
    Intcode_Computer(const std::vector<int>& memory, std::vector<int> _inputs, bool run_now = false, int* _out = NULL) {
        static_memory = memory;
        reset_dynamic_memory();
        inputs = _inputs;
        out = _out;
        if(run_now) run();
    }

    Intcode_Computer(std::string initial_state_path, bool pauses = false, bool run_now = false, int* _out = NULL) {
        std::vector<std::string> lines = util::read_file_by_line(initial_state_path);
        std::vector<std::string> split = util::split_string(lines[0], ',');
        util::v_stoi(split, &static_memory);
        out = _out;
        pause_on_4 = pauses;
        reset_dynamic_memory();
        if(run_now) run();
    }
    Intcode_Computer(std::string initial_state_path, std::vector<int> _inputs, bool run_now = false, int* _out = NULL) {
        std::vector<std::string> lines = util::read_file_by_line(initial_state_path);
        std::vector<std::string> split = util::split_string(lines[0], ',');
        inputs = _inputs;
        out = _out;
        util::v_stoi(split, &static_memory);
        reset_dynamic_memory();
        if(run_now) run();
    }
    
    // specific for use with day 2
    void run(int noun, int verb) {
        dynamic_memory[1] = noun;
        dynamic_memory[2] = verb;
        run();
    }

    void run(std::vector<int> _inputs, int* _out = NULL) {
        inputs = _inputs;
        out = _out;
        run();
    }

    // general use run function
    void run() {
        input_index = 0;
        running = true;
        halted = false;
        while(running && dynamic_memory[instruction_pointer] != 99 && instruction_pointer < dynamic_memory.size()) {
            int opcode;
            std::vector<int> parameter_modes = parse_instructions(dynamic_memory[instruction_pointer], opcode);
            switch(opcode) {
                case 1: 
                    opcode1(opcode, parameter_modes);
                    break;
                case 2:
                    opcode2(opcode, parameter_modes);
                    break;
                case 3:
                    opcode3();
                    break;
                case 4:
                    opcode4();
                    break;
                case 5:
                    opcode5(parameter_modes);
                    break;
                case 6:
                    opcode6(parameter_modes);
                    break;
                case 7:
                    opcode7(parameter_modes);
                    break;
                case 8:
                    opcode8(parameter_modes);
                    break;
                default:
                    std::cout << "Error: Opcode " << opcode << " invalid" << std::endl;
                    std::cout << "Instruction: " << dynamic_memory[instruction_pointer] << std::endl;
                    return;
            }
        }
        if(dynamic_memory[instruction_pointer] == 99) {
            halt();
        }
    }

    void opcode1(const int& opcode, const std::vector<int>& parameter_modes) {
        int param1 = get_parameter(parameter_modes[0], instruction_pointer, 1);
        int param2 = get_parameter(parameter_modes[1], instruction_pointer, 2);
        int write_address = dynamic_memory[instruction_pointer + 3];
        dynamic_memory[write_address] = param1 + param2;
        instruction_pointer += 4;
    }
    void opcode2(const int& opcode, const std::vector<int>& parameter_modes) {
        int param1 = get_parameter(parameter_modes[0], instruction_pointer, 1);
        int param2 = get_parameter(parameter_modes[1], instruction_pointer, 2);
        int write_address = dynamic_memory[instruction_pointer + 3];
        dynamic_memory[write_address] = param1 * param2;
        instruction_pointer += 4;
    }
    void opcode3() {
        int input;
        if(inputs.size() > input_index) {
            input = inputs[input_index];
            ++input_index;
        }
        else { // get user input
            std::cout << "Please provide a system ID: ";
            std::cin >> input;
        }
        // store the input
        int write_address = dynamic_memory[instruction_pointer + 1];
        dynamic_memory[write_address] = input;
        instruction_pointer += 2;
    }
    void opcode4() {
        int address = dynamic_memory[instruction_pointer + 1];
        if(out == NULL) { std::cout << dynamic_memory[address] << std::endl; }
        else { *out = dynamic_memory[address]; }
        if(pause_on_4) pause();
        instruction_pointer += 2;
    }
    void opcode5(const std::vector<int>& parameter_modes) {
        int param1 = get_parameter(parameter_modes[0], instruction_pointer, 1);
        int param2 = get_parameter(parameter_modes[1], instruction_pointer, 2);
        instruction_pointer = param1 != 0 ? param2 : (instruction_pointer + 3);
    }
    void opcode6(const std::vector<int>& parameter_modes) {
        int param1 = get_parameter(parameter_modes[0], instruction_pointer, 1);
        int param2 = get_parameter(parameter_modes[1], instruction_pointer, 2);
        instruction_pointer = param1 == 0 ? param2 : (instruction_pointer + 3);
    }
    void opcode7(const std::vector<int>& parameter_modes) {
        int param1 = get_parameter(parameter_modes[0], instruction_pointer, 1);
        int param2 = get_parameter(parameter_modes[1], instruction_pointer, 2);
        int write_address = dynamic_memory[instruction_pointer + 3];
        dynamic_memory[write_address] = (param1 < param2);
        instruction_pointer += 4;
    }
    void opcode8(const std::vector<int>& parameter_modes) {
        int param1 = get_parameter(parameter_modes[0], instruction_pointer, 1);
        int param2 = get_parameter(parameter_modes[1], instruction_pointer, 2);
        int write_address = dynamic_memory[instruction_pointer + 3];
        dynamic_memory[write_address] = (param1 == param2);
        instruction_pointer += 4;
    }
    void reset() {
        reset_dynamic_memory();
        instruction_pointer = 0;
        halted = false;
    }
    // specific for use with day 2
    int get_output() {
        return dynamic_memory[0];
    }

private:
    std::vector<int> parse_instructions(int instruction, int& opcode) {
        int temp = instruction;
        std::vector<int> temp_list;
        for(int i = 0; i < 5; i++) {
            int n = temp % 10;
            temp_list.push_back(n);
            temp = temp / 10;
        }
        opcode = temp_list[0] + (temp_list[1] * 10);
        temp_list.erase(temp_list.begin(), temp_list.begin() + 2);
        return temp_list;
    }
    void reset_dynamic_memory() {
        dynamic_memory = static_memory;
    }

    int get_parameter(const int& mode, const int& instruction_pointer, int offset) {
        return mode == 0 ? dynamic_memory[dynamic_memory[instruction_pointer + offset]] : dynamic_memory[instruction_pointer + offset];
    }

    void pause() {
        running = false;
    }

    void halt() {
        running = false;
        halted = true;
    }
};
#endif
