#ifndef AOC_H
#define AOC_H

#include <fstream>
#include <vector>
#include <sstream>
#include <string>

namespace util {

    std::ifstream read_file(std::string input_path) {
        std::ifstream input_file;
        input_file.open(input_path);
        return input_file;
    }

    void read_file_by_line(std::string input_path, std::vector<std::string> *input) {
        std::string temp;
        std::ifstream input_file;
        input_file.open(input_path);
        while(getline(input_file, temp)) {
            input->push_back(temp);
        }
    }
    void split_string(std::string s, char delim, std::vector<std::string> *string_list) {
        std::string temp;
        std::stringstream ss(s);
        while(getline(ss, temp, delim)) {
            string_list->push_back(temp);
        }
    }

    int ctoi(char c) {
        return c - '0';
    }
}


#endif
