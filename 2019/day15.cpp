#include <iostream>
#include <vector>
#include <map>
#include "./headers/aoc.h"
#include "./headers/Intcode_Computer.h"


int minx = 0;
int miny = 0;
int maxx = 0;
int maxy = 0;

struct direction {
    static util::Point up;
    static util::Point down;
    static util::Point left;
    static util::Point right;
};

util::Point direction::up = util::Point(0, 1);
util::Point direction::down = util::Point(0, -1);
util::Point direction::left = util::Point(-1, 0);
util::Point direction::right = util::Point(1, 0);

struct tile {
    bool visited = false;
    int type;

    tile() { type = 0; }
    tile(int t) { type = t; }

    std::string graphic() {
        switch(type) {
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
    int last_command;
    int maxx, maxy, minx, miny;
    long long int* memory;

    droid(long long int* out) {
        pos = util::Point();
        memory = out;
    }

    void update(int d) {
        brain.add_input_clean(d);
        brain.run(1, memory);
    }

    void move(int d) {
        switch(d) {
            case 0: pos += direction::up; break;
            case 1: pos += direction::down; break;
            case 2: pos += direction::left; break;
            case 3: pos += direction::right; break;
        }
    }

    void repeat() {
        update(last_command);
    }
};

void HandleWall(int* next_command, std::map<util::Point, tile>* grid) {
    // @todo update the grid
    
    ++(*next_command);
    *next_command = *next_command > 4 ? 0 : *next_command;
}

void HandleOpen(int* next_command, droid* d, std::map<util::Point, tile>* grid) {
    d->move(*next_command);
    // @todo update the grid
}

void render(const std::map<util::Point, tile>& grid) {
    for(int i = maxy; i >= miny; --i) {
        for(int j = minx; i <= maxx; ++i) {

            // @bug This doesnt work because grid.find() doesnt work with util::Point
            std::map<util::Point, tile>::iterator it = grid.find(util::Point(j, i));

            if(it != grid.end()) {
                std::cout << it->second.graphic();
            }
            else {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
}

int main() {
    long long int out;
    int next_command = 0;
    std::map<util::Point, tile> grid;

    droid d(&out);

    while(1) {
        // read output and do something with it
        // decide on a new input direction
        // update the grid
        d.update(next_command);

        switch(out) {
            case 0:
                HandleWall(&next_command, &grid);
                break;
            case 1:
                HandleOpen(&next_command, &d, &grid);
                break;
            case 2:
                std::cout << "Oxygen tank found\n";
                break;
        }


    }

    return 0;
}
