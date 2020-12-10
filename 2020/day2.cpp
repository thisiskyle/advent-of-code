#include <fstream>
#include <iostream>
#include <vector>
#include "../headers/aoc.h"

int main() {

    int a1 = 0;
    int a2 = 0;

    // open the input file
    std::vector<std::string> inputs = util::read_file_by_line("./inputs/day2.txt");

    // loop through all of the inputs
    for(int i = 0; i < inputs.size(); ++i) {

        // parse the input string
        std::vector<std::string> split = util::split_string(inputs[i], ':');
        std::vector<std::string> rules = util::split_string(split[0], ' ');
        std::vector<std::string> counts = util::split_string(rules[0], '-');
        std::string password = split[1].substr(1, split[1].size() - 1);
        
        // convert rules to int
        int rule1 = std::stoi(counts[0]);
        int rule2 = std::stoi(counts[1]);

        // convert string to char
        char rule_char = rules[1][0];

        int count = 0;

        // count the number of occurances of rule_char
        for(int c = 0; c < password.length(); ++c) {
            if(password[c] == rule_char) {
                ++count;
            }
        }

        // if valid password according to part 1 rules, increment the part 1 answer by 1
        if(count >= rule1 && count <= rule2) {
            ++a1;
        }

        // if valid password according to part 2 rules, increment the part 2answer by 1
        if(((password[rule1 - 1] == rule_char) + (password[rule2 - 1] == rule_char)) == 1) {
            ++a2;
        }
    }

    util::print_answers(a1, a2);
    return 0;
}
