#include <iostream>
#include <algorithm>
#include <vector>
#include <regex>
#include <string>
#include <cstdlib>
#include "./headers/aoc.h"

struct Moon {
    util::Point3 pos;
    util::Point3 velocity;
    
    Moon(std::string s) {
        parse_start_position(s);
    }

    void parse_start_position(std::string s) {
        // @@todo Parse input for starting position using regex match groups
        std::regex r("^<x=(-?[0-9]+), y=(-?[0-9]+), z=(-?[0-9]+)>$");
        std::smatch matches;

        if(std::regex_search(s, matches, r)) {
            pos.x = std::stoi(matches[1]);
            pos.y = std::stoi(matches[2]);
            pos.z = std::stoi(matches[3]);
        }
    }

    void calc_velocity(const Moon& other) {
        // @@todo calc velocity compared to other moons
        if(pos.x != other.pos.x) {
            velocity.x += pos.x < other.pos.x ? 1 : -1;
        }

        if(pos.y != other.pos.y) {
            velocity.y += pos.y < other.pos.y ? 1 : -1;
        }

        if(pos.z != other.pos.z) {
            velocity.z += pos.z < other.pos.z ? 1 : -1;
        }
    }

    void apply_velocity() {
        pos += velocity;
    }
    int energy() {
        return potential_energy() * kinetic_enegery();
    }

    int potential_energy() {
        return std::abs(pos.x) + std::abs(pos.y) + std::abs(pos.z);
    }

    int kinetic_enegery() {
        return std::abs(velocity.x) + std::abs(velocity.y) + std::abs(velocity.z);
    }

    bool operator!=(const Moon& other) const {
        return !(pos == other.pos);
    }

    bool operator==(const Moon& other) const {
        return pos == other.pos;
    }
};


int main() {
    int steps = 1000;

    std::vector<std::string> input = util::read_file_by_line("./inputs/day12.txt");
    std::vector<Moon> moons;

    for(auto l : input) {
        moons.push_back(Moon(l));
    }

    for(int i = 0; i < steps; ++i) {
        for(int j = 0; j < moons.size(); ++j) {
            for(int k = 0; k < moons.size(); ++k) {
                if(j == k) continue;
                moons[j].calc_velocity(moons[k]);
            }
        }
        
        for(int m = 0; m < moons.size(); ++m) {
            moons[m].apply_velocity();
        }
    }

    int total_energy = 0;

    for(int m = 0; m < moons.size(); ++m) {
        total_energy += moons[m].energy();
    }

    std::cout << total_energy << std::endl;
    

    return 0;
}


