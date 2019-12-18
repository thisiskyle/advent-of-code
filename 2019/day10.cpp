#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include "./headers/aoc.h"

#define PI 3.14159265

struct Asteroid {
    int x, y;
    Asteroid(int x=0, int y=0) :x(x), y(y) { }

    bool operator==(const Asteroid& b) const {
        return (this->x == b.x && this->y == b.y);
    }
    bool operator!=(const Asteroid& b) const {
        return (this->x != b.x || this->y != b.y);
    }
};

double get_angle(const Asteroid& a, const Asteroid& b) {
    return atan2(b.y - a.y, b.x - a.x) * 180 / PI;
}

std::vector<double> get_all_angles(const Asteroid& a, const std::vector<Asteroid>& asteroids) {
    int count = 0;
    std::vector<double> angles;
    for(auto b : asteroids) {
        if(a != b) {
            double angle = get_angle(a, b);
            if(std::find(angles.begin(), angles.end(), angle) == angles.end()) {
                angles.push_back(angle);
            }
        }
    }
    return angles;
}


int main() {
    std::vector<std::string> map;
    std::vector<Asteroid> asteroids;
    Asteroid station;
    int c = 0;

    util::read_file_by_line("./inputs/day10.txt", &map);

    // grab the asteroids
    for(int y = 0; y < map.size(); ++y) {
        for(int x = 0; x < map[0].size(); ++x) {
            if(map[y][x] == '#') { asteroids.push_back(Asteroid(x, y)); }
        }
    }

    for(auto a : asteroids) {
        auto t = get_all_angles(a, asteroids);
        if(t.size() > c) {
            c = t.size();
            station = a;
        }
    }
    std::cout << "part 1: " << "Asteroid (" << station.x << ", " << station.y << ") " << "oberves " << c << std::endl;

    // part 2
    std::vector<double> angles = get_all_angles(station, asteroids);
    std::sort(angles.begin(), angles.end());
    double target_angle = angles[200];

    // @@todo this doesnt work...
    for(auto a : asteroids) {
        double test = get_angle(station, a);
        if(test == target_angle) {
            std::cout << a.x * 100 + a.y << std::endl;
        }
    }
    return 0;
}
