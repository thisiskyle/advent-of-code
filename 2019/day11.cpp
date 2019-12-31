#include <iostream>
#include <vector>
#include "./headers/aoc.h"
#include "./headers/Intcode_Computer.h"

struct Robot {
    Intcode_Computer brain{"./inputs/day11.txt"};
    std::vector<util::Point> white_panels;
    std::vector<util::Point> black_panels;
    util::Point pos;
    int rotation = 90;

    Robot() {
        pos = util::Point{0, 0};
        visited.push_back(pos);
    }

    void update() {
        long long int out;

        // get current panel color
        // feed it as input
        // handle first output, the new color 0: black 1: white
        // handle second output, rotation 0: left 1: right
    }
    
    // 0: black 1: white
    int get_current_panel() {
        if(util::contains<Point>(white_panels, pos)) {
            return 1;
        }
        if(util::contains<Point>(black_panels, pos)) { 
            return 0;
        }
        return 0;
    }

    void paint_white() {
        // check both color lists for the current panel
        // change color if needed
        // remove from old color and add to new color
        // or just add to color if not found in either

    }

    void paint_black() { 
        // check both color lists for the current panel
        // change color if needed
        // remove from old color and add to new color
        // or just add to color if not found in either
    } 

    void rotateR() {
        rotation -= 90;
        if(rotation < 0) {
            rotation = 360 + rotation;
        }
    }

    void rotateL() {
        rotation += 90;
        if(rotation > 360) {
            rotation -= 360;
        }
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



