#include <iostream>
#include <algorithm>
#include <vector>
#include "./headers/Intcode_Computer.h"
#include "./headers/aoc.h"



int main() {

    Intcode_Computer computer("./inputs/day9.txt", {1}, false, true);
    computer.reset();
    computer.run({2});

    return 0;
}
