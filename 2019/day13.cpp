#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include "../headers/aoc.h"
#include "../headers/Intcode_Computer.h"

std::string get_tile(int n) {
    switch(n) {
        case 0: return " ";
        case 1: return "#";
        case 2: return "x";
        case 3: return "_";
        case 4: return "o";
    }
    return " ";
}

void draw(std::vector<std::vector<int>>& screen, int score) {
    util::clear_screen();
    std::string display = "";
    for(int i = 0; i < screen.size(); ++i) {
        for(int j = 0; j < screen[i].size(); ++j) {
            display.append(get_tile(screen[i][j]));
        }
        display.append("\n");
    }
    std::cout << display;
    std::cout << "Score: " << score << "\n";
    usleep(5 * 1000);
}

int main() {

    long long int x, y, t;
    int block_count = 0;
    int score = 0;

    util::Point paddle;
    util::Point ball;

    std::vector<std::vector<int>> screen;
    Intcode_Computer computer("./inputs/day13.txt");
    computer.set_memory_position(0, 2);

    // intcode loop
    while(!computer.is_halted()) {
        computer.run(true, &x);
        computer.run(true, &y);
        computer.run(true, &t);

        if(x == -1 && y == 0) {
            score = t;
        }
        else {
            if(t == 2) {
                ++block_count;
            }
            else if(t == 3) { 
                paddle.x = x; 
                paddle.y = y;
            }
            else if(t == 4) {
                ball.x = x; 
                ball.y = y;
            }

            // build grid 
            if(y == screen.size()) { 
                screen.push_back(std::vector<int>());
            }
            if(x == screen[y].size()) {
                screen[y].push_back(0);
            }

            // add tile to screen
            screen[y][x] = t;
        }

        // move paddle
        if(ball.x > paddle.x) {
            computer.add_input_clean(1);
        }
        else if(ball.x < paddle.x) {
            computer.add_input_clean(-1);
        }
        else {
            computer.add_input_clean(0);
        }

        // uncomment to visualize
        draw(screen, score);
    }

    std::cout << "part 1: " << block_count << "\n";
    std::cout << "part 2: " << score << "\n";


    return 0;
}


