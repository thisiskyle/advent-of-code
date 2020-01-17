#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <float.h>
#include "./headers/aoc.h"

#define PI 3.14159265

struct Asteroid {
    int x, y;
    float angle;
    Asteroid(int x=0, int y=0) :x(x), y(y) { }

    bool operator==(const Asteroid& b) const {
        return (this->x == b.x && this->y == b.y);
    }
    bool operator!=(const Asteroid& b) const {
        return (this->x != b.x || this->y != b.y);
    }
};

float get_angle(const Asteroid& a, const Asteroid& b) {
    float angle = atan2(b.y - a.y, b.x - a.x) * 180 / PI;
    if(angle < 0) angle += 360;
    return angle;
}

std::vector<float> get_all_angles(const Asteroid& a, std::vector<Asteroid>& asteroids, std::vector<Asteroid>& visible) {
    visible.clear();
    std::vector<float> angles;
    for(auto&& b : asteroids) {
        if(a != b) {
            float angle = get_angle(a, b);
            b.angle = angle;
            if(std::find(angles.begin(), angles.end(), angle) == angles.end()) {
                angles.push_back(angle);
                visible.push_back(b);
            }
        }
    }
    return angles;
}

float distance(const Asteroid& a, const Asteroid& b) {
    int dx = b.x - a.x;
    int dy = b.y - a.y;
    return sqrt((dx * dx) + (dy * dy));
}


int main() {
    std::vector<std::string> map;
    std::vector<Asteroid> asteroids;
    std::vector<Asteroid> visible;
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
        auto t = get_all_angles(a, asteroids, visible);
        if(t.size() > c) {
            c = t.size();
            station = a;
        }
    }
    std::cout << "part 1: " << "Asteroid (" << station.x << ", " << station.y << ") " << "observes " << c << std::endl;

    // part 2
    Asteroid target;
    std::vector<float> angles = get_all_angles(station, asteroids, visible);
    std::sort(angles.begin(), angles.end());
    float closest_angle = 360;
    int index;

    for(int i = 0; i < angles.size(); ++i) {
        if(std::abs(angles[i] - 270) < std::abs(closest_angle - 270)) {
            closest_angle = angles[i];
            index = i;
        }
    }
    // find the 200th element starting from the index
    // wrap index to begining of vector if needed
    if(index + 200 > angles.size() - 1) {
        index = 200 - (angles.size() - index);
    }

    for(auto a : visible) {
        if(a.angle == angles[index - 1]) {
            target = a;
        }
    }

    std::cout << "part 2: " << target.x * 100 + target.y << std::endl;

    return 0;
}



