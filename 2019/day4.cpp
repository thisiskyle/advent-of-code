#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "./headers/aoc.h"


bool check_doubles(const std::string &s) {
    char prev;
    for(auto c : s) {
        if(!prev) { prev = c; continue; }
        if(c == prev) return true;
        prev = c;
    }
    return false;
}

bool check_group(const std::string &s) {
    char prev;
    for(int i = 0; i < s.size(); i++) {
        if(!prev) { prev = s[i]; continue; }
        if(s[i] == prev) {
            int t = i + 1;
            int count = 2;
            while(s[t] == prev) {
                count++;
                t++;
            }
            if(count == 2) return true;
            else { i = t - 1; }
        }
        prev = s[i];
    }
    return false;
}

bool check_ascending(const std::string &s) {
    char prev;
    for(auto c : s) {
        if(!prev) { prev = c; continue; }
        if(util::ctoi(c) < util::ctoi(prev)) {
            return false;
        }
        prev = c;
    }
    return true;
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::string> input;
    std::vector<std::string> min_and_max;

    util::read_file_by_line("./inputs/day4.txt", &input);
    util::split_string(input[0], '-', &min_and_max);

    int count = 0;
    int count2 = 0;

    for(int i = std::stoi(min_and_max[0]) + 1; i < std::stoi(min_and_max[1]); i++) {
        std::string s = std::to_string(i);
        if(check_doubles(s) && check_ascending(s)) {
            count++;
            if(check_group(s)) count2++;
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto run_time = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout << "1: " << count << " 2: " << count2 << std::endl;
    std::cout << run_time.count() << "ms" << std::endl;
    return 0;
}
