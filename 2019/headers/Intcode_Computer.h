#ifndef INTCODE_H
#define INTCODE_H

#include <vector>
#include <string>
#include <iostream>
#include "./aoc.h"

class Intcode_Computer {

public:

    Intcode_Computer(const std::vector<long long int>& memory, bool pauses = false, bool run_now = false, long long int* _out = NULL) {
        static_memory = memory;
        reset_dynamic_memory();
        out = _out;
        pause_after_output = pauses;
        if(run_now) run();
    }
    Intcode_Computer(const std::vector<long long int>& memory, std::vector<long long int> _inputs, bool pauses = false, bool run_now = false, long long int* _out = NULL) {
        static_memory = memory;
        reset_dynamic_memory();
        inputs = _inputs;
        out = _out;
        pause_after_output = pauses;
        if(run_now) run();
    }

    Intcode_Computer(std::string initial_state_path, bool pauses = false, bool run_now = false, long long int* _out = NULL) {
        std::vector<std::string> lines = util::read_file_by_line(initial_state_path);
        std::vector<std::string> split = util::split_string(lines[0], ',');
        util::v_stolli(split, &static_memory);
        out = _out;
        pause_after_output = pauses;
        reset_dynamic_memory();
        if(run_now) run();
    }
    Intcode_Computer(std::string initial_state_path, std::vector<long long int> _inputs, bool pauses = false, bool run_now = false, long long int* _out = NULL) {
        std::vector<std::string> lines = util::read_file_by_line(initial_state_path);
        std::vector<std::string> split = util::split_string(lines[0], ',');
        inputs = _inputs;
        out = _out;
        pause_after_output = pauses;
        util::v_stolli(split, &static_memory);
        reset_dynamic_memory();
        if(run_now) run();
    }
    
    void run(long long int noun, long long int verb) {
        dynamic_memory[1] = noun;
        dynamic_memory[2] = verb;
        run();
    }

    void run(std::vector<long long int> _inputs, long long int* _out = NULL) {
        inputs = _inputs;
        out = _out;
        run();
    }

    // general use run function
    void run() {
        running = true;
        while(running && !halted && dynamic_memory[instruction_pointer] != 99) {
            int opcode;
            allocate_memory(instruction_pointer);

            std::vector<int> parameter_modes = parse_instructions(dynamic_memory[instruction_pointer], opcode);

            long long int param1 = dynamic_memory[get_parameter_address(parameter_modes[0], 1)];
            long long int param2 = dynamic_memory[get_parameter_address(parameter_modes[1], 2)];
            long long int param3 = get_parameter_address(parameter_modes[2], 3);


            switch(opcode) {
                case 1: 
                    dynamic_memory[param3] = param1 + param2;
                    instruction_pointer += 4;
                    break;
                case 2:
                    dynamic_memory[param3] = param1 * param2;
                    instruction_pointer += 4;
                    break;
                case 3:
                    long long int input;
                    if(inputs.size() > input_index) {
                        input = inputs[input_index];
                        ++input_index;
                    } else { // get user input
                        std::cout << "Please provide a system ID: ";
                        std::cin >> input;
                    }
                    dynamic_memory[get_parameter_address(parameter_modes[0], 1)] = input;
                    instruction_pointer += 2;
                    break;
                case 4:
                    if(out == NULL) { std::cout << param1 << std::endl; }
                    else { *out = param1; }
                    if(pause_after_output) pause();
                    instruction_pointer += 2;
                    break;
                case 5:
                    instruction_pointer = param1 != 0 ? param2 : (instruction_pointer + 3);
                    break;
                case 6:
                    instruction_pointer = param1 == 0 ? param2 : (instruction_pointer + 3);
                    break;
                case 7:
                    dynamic_memory[param3] = (param1 < param2);
                    instruction_pointer += 4;
                    break;
                case 8:
                    dynamic_memory[param3] = (param1 == param2);
                    instruction_pointer += 4;
                    break;
                case 9:
                    relative_base += param1;
                    instruction_pointer += 2;
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

    void reset() {
        reset_dynamic_memory();
        instruction_pointer = 0;
        halted = false;
        relative_base = 0;
    }

    // specific for use with day 2
    int get_output() {
        return dynamic_memory[0];
    }

    bool is_halted() {
        return halted;
    }

private:
    std::vector<long long int> static_memory;
    std::vector<long long int> dynamic_memory;
    std::vector<long long int> inputs;
    long long int instruction_pointer = 0;
    long long int input_index = 0;
    long long int relative_base = 0;
    long long int* out;
    bool running = false;
    bool halted = false;
    bool pause_after_output = false;

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

    int get_parameter_address(const int& mode, int offset) {
        int address = 0;
        switch(mode) {
            case 0:
                address = dynamic_memory[instruction_pointer + offset];
                break;
            case 1:
                address = instruction_pointer + offset;
                break;
            case 2:
                address = relative_base + dynamic_memory[instruction_pointer + offset];
                break;
            default:
                std::cout << "Invalid parameter mode " << mode << std::endl;
                break;
        }
        allocate_memory(address);
        return address;
    }

    void pause() {
        running = false;
        input_index = 0;
    }

    void halt() {
        input_index = 0;
        running = false;
        halted = true;
    }

    void allocate_memory(int a) {
        if(a > dynamic_memory.size()) {
            int temp = a - dynamic_memory.size();
            for(int i = 0; i < temp; ++i) {
                dynamic_memory.push_back(0);
            }
        }
    }
};
#endif
