#include <fstream>
#include <vector>
#include "../headers/Intcode_Computer.h"
#include "../headers/aoc.h"

int main() {
    // part 1
    Intcode_Computer computer("./inputs/day5.txt");
    computer.add_input(1);
    computer.run();

    // part 2
    computer.reset();
    computer.add_input(5);
    computer.run();
    return 0;
}
