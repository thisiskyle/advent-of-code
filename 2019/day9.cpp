#include <iostream>
#include <algorithm>
#include <vector>
#include "../headers/Intcode_Computer.h"
#include "../headers/aoc.h"



int main() {

    // part 1
    Intcode_Computer computer("./inputs/day9.txt", {1});
    computer.run();

    // part 2
    computer.reset();
    computer.add_input(2);
    computer.run();

    return 0;
}
