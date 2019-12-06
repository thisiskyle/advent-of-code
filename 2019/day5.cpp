#include <fstream>
#include <vector>
#include "./headers/Intcode_Computer.h"
#include "./headers/aoc.h"


int main() {

    std::vector<std::string> lines;
    std::vector<std::string> split;
    std::vector<int> input;

    util::read_file_by_line("./inputs/day5.txt", &lines);
    util::split_string(lines[0], ',', &split);
    util::v_stoi(split, &input);
    
    Intcode_Computer computer(input);
    computer.run();

    return 0;
}
