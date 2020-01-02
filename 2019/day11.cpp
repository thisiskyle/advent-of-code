#include <iostream>
#include <algorithm>
#include <vector>
#include "./headers/aoc.h"
#include "./headers/Intcode_Computer.h"

struct Robot {
    Intcode_Computer brain{"./inputs/day11.txt"};
    std::vector<util::Point> white;
    std::vector<util::Point> black;
    std::vector<util::Point> painted;
    util::Point pos;
    int rotation = 90;
    int min_x = 0;
    int max_x = 0;
    int min_y = 0;
    int max_y = 0;

    Robot(int part) {
        pos = util::Point{0, 0};
        if(part == 2) white.push_back(pos);
    }

    void update() {
        long long int new_color;
        long long int new_rotation;
        int current_panel = get_current_panel();

        brain.add_input(current_panel);
        brain.run(true, &new_color);
        brain.run(true, &new_rotation);

        handle_new_color(new_color);
        handle_rotation(new_rotation);
    }
    
    // 0: black 1: white
    int get_current_panel() {
        if(util::contains<util::Point>(white, pos)) {
            return 1;
        }
        else if(util::contains<util::Point>(black, pos)) {
            return 0;
        }
        return 0;
    }

    // handle first output, the new color 0: black 1: white
    void handle_new_color(const int& new_color) {

        if(new_color == 0) {
            if(util::contains<util::Point>(white, pos)) {
                util::remove_element<util::Point>(white, pos);
                black.push_back(pos);
            }
            else if(!util::contains<util::Point>(black, pos)) {
                painted.push_back(pos);
                black.push_back(pos);
            }
        }
        else if(new_color == 1) {
            if(util::contains<util::Point>(black, pos)) {
                util::remove_element<util::Point>(black, pos);
                white.push_back(pos);
            }
            else if(!util::contains<util::Point>(white, pos)) {
                painted.push_back(pos);
                white.push_back(pos);
            }

        }
    }

    // handle second output, rotation 0: left 1: right
    void handle_rotation(const int& new_rot) {
        if(new_rot == 0)  rotateL();
        else if(new_rot == 1)  rotateR();
        move();
    }

    void rotateR() {
        rotation -= 90;
        if(rotation < 0) {
            rotation = 360 + rotation;
        }
    }

    void rotateL() {
        rotation += 90;
        if(rotation >= 360) {
            rotation -= 360;
        }
    }

    void move() {
        switch(rotation) {
            case 90:
                ++pos.y;
                max_y = pos.y > max_y ? pos.y : max_y;
                break;
            case 180:
                --pos.x;
                min_x = pos.x < min_x ? pos.x : min_x;
                break;
            case 270:
                --pos.y;
                min_y = pos.y < min_y ? pos.y : min_y;
                break;
            case 0:
                ++pos.x;
                max_x = pos.x > max_x ? pos.x : max_x;
                break;
        }

    }

    bool is_done() {
        return brain.is_halted();
    }

    void render() {
        for(int y = max_y; y >= min_y; --y) {
            for(int x = min_x; x <= max_x; ++x) {
                if(util::contains(white, util::Point(x,y))) {
                    std::cout << "1";
                }
                else {
                    std::cout << " ";
                }
            }
            std::cout << "\n";
        }
    }
};

int main() {
    Robot robot(1);
    while(!robot.is_done()) {
        robot.update();
    }
    std::cout << "part 1: " << robot.painted.size() << std::endl;
    std::cout << "part 2: " << std::endl;
    Robot robot2(2);
    while(!robot2.is_done()) {
        robot2.update();
    }
    robot2.render();
    return 0;
}


