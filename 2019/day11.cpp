#include <iostream>
#include <vector>
#include "./headers/aoc.h"
#include "./headers/Intcode_Computer.h"

struct Robot {
    Intcode_Computer brain{"./inputs/day11.txt"};
    std::vector<util::Point> white_panels;
    std::vector<util::Point> visited;
    util::Point pos;

    Robot() {
        pos = util::Point{0, 0};
        visited.push_back(pos);
    }

    void update() {
        long long int out;

        // get current panel color
        int current_panel;
        if(util::find_index_of<util::Point>(white_panels, pos) == -1) {
            current_panel = 0;
        }
        else current_panel = 1;

        brain.add_input(current_panel);

        // handle first output, the new color
        // 0: black
        // 1: white
        brain.run(true, &out);
        if(out == 1) {
            if(util::find_index_of<util::Point>(white_panels, pos) == -1) {
                white_panels.push_back(pos);
            }
        }
        else {
            int i = util::find_index_of<util::Point>(white_panels, pos);
            if( i != -1) {
                white_panels.erase(white_panels.begin() + i);
            }
        }

        // handle second output, rotation
        // 0: left
        // 1: right
        brain.step(&out);
        if(out == 0) rotateL();
        else rotateR();
    }

    int rotation = 90;

    void rotateR() {
        rotation -= 90;
        if(rotation < 0) {
            rotation = 360 + rotation;
        }
        move();
    }
    void rotateL() {
        rotation += 90;
        if(rotation > 360) {
            rotation -= 360;
        }
        move();
    }
    void move() {
        switch(rotation) {
            case 90:
                ++pos.y;
                break;
            case 180:
                --pos.x;
                break;
            case 270:
                --pos.y;
                break;
            case 0:
                ++pos.x;
                break;
        }
        if(util::find_index_of<util::Point>(visited, pos) == -1) {
            visited.push_back(pos);
        }
    }
    bool is_done() {
        return brain.is_halted();
    }
};



int main() {
    Robot robot;


    while(!robot.is_done()) {
        robot.update();
    }
    std::cout << robot.visited.size() << std::endl;

    return 0;
}



