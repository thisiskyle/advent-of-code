#include <iostream>
#include <algorithm>
#include <vector>
#include <regex>
#include <string>
#include <cstdlib>
#include <numeric>
#include "./headers/aoc.h"


struct Moon {
    util::Point3 pos, start_pos, velocity;
    
    Moon(std::string s) { parse_start_position(s); }

    void parse_start_position(std::string s) {
        std::regex r("^<x=(-?[0-9]+), y=(-?[0-9]+), z=(-?[0-9]+)>$");
        std::smatch matches;
        if(std::regex_search(s, matches, r)) {
            pos.x = std::stoi(matches[1]);
            pos.y = std::stoi(matches[2]);
            pos.z = std::stoi(matches[3]);
        }
        start_pos = pos;
    }

    void calc_velocity(const Moon& other) {
        if(pos.x != other.pos.x) { velocity.x += pos.x < other.pos.x ? 1 : -1; }
        if(pos.y != other.pos.y) { velocity.y += pos.y < other.pos.y ? 1 : -1; }
        if(pos.z != other.pos.z) { velocity.z += pos.z < other.pos.z ? 1 : -1; }
    }

    void apply_velocity() {
        pos += velocity;
    }

    int energy() {
        int potential = std::abs(pos.x) + std::abs(pos.y) + std::abs(pos.z);
        int kinetic = std::abs(velocity.x) + std::abs(velocity.y) + std::abs(velocity.z);
        return potential * kinetic;
    }
    bool operator!=(const Moon& other) const { return !(pos == other.pos); }
    bool operator==(const Moon& other) const { return pos == other.pos; }

    void reset() {
        pos = start_pos;
        velocity = util::Point3(0,0,0);
    }
};

std::vector<int> getaxis(const std::vector<Moon>& moons, std::string axis) {
    if(axis == "x") { return { moons[0].pos.x, moons[1].pos.x, moons[2].pos.x, moons[3].pos.x}; }
    else if(axis == "y") { return { moons[0].pos.y, moons[1].pos.y, moons[2].pos.y, moons[3].pos.y}; }
    else if(axis == "z"){ return { moons[0].pos.z, moons[1].pos.z, moons[2].pos.z, moons[3].pos.z}; }
    return { };
}

void update_velocity(std::vector<Moon>* moons) {
    for(int j = 0; j < moons->size(); ++j) {
        for(int k = 0; k < moons->size(); ++k) {
            if(j == k) continue;
            moons->at(j).calc_velocity(moons->at(k));
        }
    }
}
void update_position(std::vector<Moon>* moons) {
    for(int m = 0; m < moons->size(); ++m) {
        moons->at(m).apply_velocity();
    }
}
void update_moons(std::vector<Moon>* moons) {
    update_velocity(moons);
    update_position(moons);
}

void part1(std::vector<Moon>* moons) {
    long long int steps = 1000;
    int total_energy = 0;

    for(int i = 0; i < steps; ++i) { update_moons(moons); }

    for(int m = 0; m < moons->size(); ++m) {
        total_energy += moons->at(m).energy();
    }

    std::cout << "part 1: " << total_energy << std::endl;
}

void part2(std::vector<Moon>* moons) {
    long long int x_steps = 0, y_steps = 0, z_steps = 0, steps = 0;

    std::vector<int> xi, yi, zi;
    for(int m = 0; m < moons->size(); ++m) {
        moons->at(m).reset();
        xi.push_back(moons->at(m).pos.x);
        yi.push_back(moons->at(m).pos.y);
        zi.push_back(moons->at(m).pos.z);
    }

    while(!x_steps || !y_steps || !z_steps) {
        ++steps;
        update_moons(moons);

        if(!x_steps && xi == getaxis(*moons, "x")) x_steps = steps + 1;
        if(!y_steps && yi == getaxis(*moons, "y")) y_steps = steps + 1;
        if(!z_steps && zi == getaxis(*moons, "z")) z_steps = steps + 1;
    }

    long long int a = util::lcm(z_steps, util::lcm(x_steps, y_steps));
    std::cout << "part 2: " << a << std::endl;
}


int main() {
    std::vector<std::string> input = util::read_file_by_line("./inputs/day12.txt");
    std::vector<Moon> moons;
    for(auto l : input) { moons.push_back(Moon(l)); }
    part1(&moons);
    part2(&moons);
    return 0;
}


