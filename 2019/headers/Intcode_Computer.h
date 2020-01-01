#ifndef INTCODE_H
#define INTCODE_H

#include <vector>
#include <string>
#include <iostream>
#include "./aoc.h"

class Intcode_Computer {

public:

    Intcode_Computer(const std::string& program_path, const std::vector<long long int>& _inputs = std::vector<long long int>()) {
        std::vector<std::string> lines = util::read_file_by_line(program_path);
        std::vector<std::string> split = util::split_string(lines[0], ',');
        add_input(_inputs);
        util::v_stolli(split, &program);
        memory = program;
    }

    void run(bool _pause_on_out = false, long long int* _out = NULL) {
        if(paused) resume();
        pause_on_out = _pause_on_out;
        out = _out;
        while(!halted && !paused) { step(); }
    }
    

    void step(long long int* _out = NULL) {
        if(halted) { return; }

        allocate_memory(instruction_pointer);

        int opcode;
        std::vector<int> parameter_modes = parse_instructions(memory[instruction_pointer], opcode);

        long long int param1 = memory[get_parameter_address(parameter_modes[0], 1)];
        long long int param2 = memory[get_parameter_address(parameter_modes[1], 2)];
        long long int param3 = get_parameter_address(parameter_modes[2], 3);


        switch(opcode) {
            case 1: 
                memory[param3] = param1 + param2;
                instruction_pointer += 4;
                break;

            case 2:
                memory[param3] = param1 * param2;
                instruction_pointer += 4;
                break;

            case 3:
                if(input_buffer.size() > 0) {
                    memory[get_parameter_address(parameter_modes[0], 1)] = input_buffer[0];
                    input_buffer.erase(input_buffer.begin());
                }
                else {
                    std::cout << "Error: no inputs in buffer" << std::endl;
                }
                instruction_pointer += 2;
                break;

            case 4:
                if(out == NULL) { std::cout << "OUT: " << param1 << std::endl; }
                else { *out = param1; }

                instruction_pointer += 2;
                if(pause_on_out) pause();
                break;

            case 5:
                instruction_pointer = param1 != 0 ? param2 : (instruction_pointer + 3);
                break;

            case 6:
                instruction_pointer = param1 == 0 ? param2 : (instruction_pointer + 3);
                break;

            case 7:
                memory[param3] = (param1 < param2);
                instruction_pointer += 4;
                break;

            case 8:
                memory[param3] = (param1 == param2);
                instruction_pointer += 4;
                break;

            case 9:
                relative_base += param1;
                instruction_pointer += 2;
                break;

            default:
                std::cout << "Error: Opcode " << opcode << " invalid" << std::endl;
                std::cout << "Instruction: " << memory[instruction_pointer] << std::endl;
                return;
        }

        if(memory[instruction_pointer] == 99) {
            halt();
        }
    }

    void reset() {
        memory = program;
        instruction_pointer = 0;
        halted = false;
        paused = false;
        relative_base = 0;
        input_buffer.clear();
    }

    // specific for use with day 2
    int get_output() {
        return memory[0];
    }
    // specific for use with day 2
    void insert_noun_and_verb(long long int noun, long long int verb) {
        memory[1] = noun;
        memory[2] = verb;
    }

    bool is_halted() {
        return halted;
    }
    bool is_paused() {
        return paused;
    }
    void add_input(long long int input) {
        input_buffer.push_back(input);
    }
    void add_input(std::vector<long long int> input) {
        for(auto i : input) {
            input_buffer.push_back(i);
        }
    }

private:
    std::vector<long long int> program;
    std::vector<long long int> memory;

    std::vector<long long int> input_buffer;

    long long int instruction_pointer = 0;
    long long int relative_base = 0;

    long long int* out;

    bool halted = false;
    bool paused = false;
    bool pause_on_out = false;

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

    int get_parameter_address(const int& mode, int offset) {
        int address = 0;
        switch(mode) {
            case 0:
                address = memory[instruction_pointer + offset];
                break;
            case 1:
                address = instruction_pointer + offset;
                break;
            case 2:
                address = relative_base + memory[instruction_pointer + offset];
                break;
            default:
                std::cout << "Invalid parameter mode " << mode << std::endl;
                break;
        }
        allocate_memory(address);
        return address;
    }

    void pause() {
        paused = true;
    }
    void resume() {
        paused = false;
    }
    void halt() {
        halted = true;
    }

    void allocate_memory(int a) {
        if(a > memory.size()) {
            int temp = a - memory.size();
            for(int i = 0; i < temp; ++i) {
                memory.push_back(0);
            }
        }
    }

};
#endif
