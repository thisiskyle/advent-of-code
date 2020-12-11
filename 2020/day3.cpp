#include <fstream>
#include <iostream>
#include <vector>
#include "../headers/aoc.h"


int main() {

    // open the input file
    std::vector<std::string> inputs = util::read_file_by_line("./inputs/day3.txt");

    int a1 = 0;
    long long a2 = 1;
    int height = inputs.size();
    int width = inputs[0].length();

    // store the slope data
    std::vector<util::Point> slopes;
    slopes.push_back(util::Point(1,1));
    slopes.push_back(util::Point(3,1));
    slopes.push_back(util::Point(5,1));
    slopes.push_back(util::Point(7,1));
    slopes.push_back(util::Point(1,2));


    // loop through all the slopes and do the stuff
    for(int i = 0; i < slopes.size(); ++i) {
        int t = 0;
        int x = 0;

        // traverse map based on slope and count trees
        for(int y = slopes[i].y; y < inputs.size(); y += slopes[i].y) {
            x = (x + slopes[i].x) % width;
            t += inputs[y][x] == '#';
        }

        if(i == 1) a1 = t;
        a2 *= t;
    }

    std::cout << "part 1: " << a1 << "\n";
    std::cout << "part 2: " << a2 << "\n";
    return 0;
}
