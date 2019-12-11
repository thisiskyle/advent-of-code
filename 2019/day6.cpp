#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <map>
#include "./headers/aoc.h"

std::vector<std::string> map_the_path(const std::map<std::string, std::string>& map_from, std::string _key) {
    std::string key = _key;
    std::vector<std::string> map_to;
    while(key != "COM") {
        key = map_from.find(key)->second;
        map_to.push_back(key);
    }
    return map_to;
}


int main() {
    int total_orbits = 0;
    std::vector<std::string> lines;
    std::map<std::string, std::string> orbit_map; // key is orbiting value

    util::read_file_by_line("./inputs/day6.txt", &lines);

    // put input file into a map
    for(auto l : lines) {
        std::vector<std::string> orbit_pairs; // [1] is orbiting [0]
        util::split_string(l, ')', &orbit_pairs);
        orbit_map[orbit_pairs[1]] = orbit_pairs[0];
    }
    // loop through the map and trace every planets orbit back to COM
    for (std::map<std::string, std::string>::iterator it = orbit_map.begin(); it != orbit_map.end(); ++it)
    {
        std::string parent = it->second;
        while(1) {
            if(parent != "COM") {
                ++total_orbits;
                parent = orbit_map[parent];
            }
            else {
                ++total_orbits;
                break;
            }
        }
    }
    std::cout << "part 1: " << total_orbits << std::endl;

    int total_steps = 0;

    std::vector<std::string> YOU_orbits = map_the_path(orbit_map, "YOU");
    std::vector<std::string> SAN_orbits = map_the_path(orbit_map, "SAN");

    for(int i = 0; i < YOU_orbits.size(); ++i) {
        for(int j = 0; j < SAN_orbits.size(); ++j) {
            if(YOU_orbits[i] == SAN_orbits[j]) {
                total_steps = i + j;
                goto end;
            }
        }
    }
    end:
    std::cout << "part 2: " << total_steps << std::endl;

    return 0;
}
