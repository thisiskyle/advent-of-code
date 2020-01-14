#include <iostream>
#include <vector>
#include <map>
#include "./headers/aoc.h"
#include "./headers/Intcode_Computer.h"

enum dir {
    up = 1,
    down,
    left,
    right
};

enum tile_type {
    wall,
    walkable,
    tank,
    robot,
    empty
};

struct tile {
    bool visited = false;
    tile_type type;

    tile() { type = empty; }
    tile(tile_type t) { type = t; }
    tile(int t) { type = (tile_type)t; }

    std::string graphic() {
        switch((int)type) {
            case 0: return "#";
            case 1: return ".";
            case 2: return "O";
            case 3: return "@";
        }
        return " ";
    }
};

struct droid {
    Intcode_Computer brain{"./inputs/day15.txt"};
    util::Point pos;
    int maxx, maxy, minx, miny;
    long long int* memory;

    droid(long long int* out) {
        memory = out;
    }

    void update(dir d) {
        switch(d) {
            case up: move_up(); break;
            case down: move_down(); break;
            case left: move_left(); break;
            case right: move_right(); break;
        }
        brain.run(1, memory);
    }

    void move_up() {
        ++pos.y;
        brain.add_input_clean(up);
    }
    void move_down() {
        --pos.y;
        brain.add_input_clean(down);
    }
    void move_left() {
        --pos.x;
        brain.add_input_clean(left);
    }
    void move_right() {
        ++pos.x;
        brain.add_input_clean(right);
    }
};

int main() {
    int in;
    int out;
    std::map<util::Point, tile> grid;
    droid d(&out);

    // initialize with and up command
    d.update(up);
    while(1) {

        // read out

        // do some logic

        // decide on a new input direction

        // d.update(new input)

        // update the grid
    }

    return 0;
}
