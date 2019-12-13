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

    void read_file_by_line(std::string input_path, std::vector<std::string>* input) {
        std::string temp;
        std::ifstream input_file;
        input_file.open(input_path);
        while(getline(input_file, temp)) {
            input->push_back(temp);
        }
    }

    std::vector<std::string> read_file_by_line(std::string input_path) {
        std::string temp;
        std::vector<std::string> input;
        std::ifstream input_file;
        input_file.open(input_path);
        while(getline(input_file, temp)) {
            input.push_back(temp);
        }
        return input;
    }

    void split_string(std::string s, char delim, std::vector<std::string>* string_list) {
        std::string temp;
        std::stringstream ss(s);
        while(getline(ss, temp, delim)) {
            string_list->push_back(temp);
        }
    }
    std::vector<std::string> split_string(std::string s, char delim) {
        std::string temp;
        std::vector<std::string> string_list;
        std::stringstream ss(s);
        while(getline(ss, temp, delim)) {
            string_list.push_back(temp);
        }
        return string_list;
    }

    void v_stoi(std::vector<std::string> s, std::vector<int>* out) {
        for(auto i : s) {
            out->push_back(std::stoi(i));
        }
    }
    std::vector<int> v_stoi(std::vector<std::string> s) {
        std::vector<int> out;
        for(auto i : s) {
            out.push_back(std::stoi(i));
        }
        return out;
    }
    void v_stoli(std::vector<std::string> s, std::vector<long int>* out) {
        for(auto i : s) {
            out->push_back(std::stoi(i));
        }
    }
    std::vector<long int> v_stoli(std::vector<std::string> s) {
        std::vector<long int> out;
        for(auto i : s) {
            out.push_back(std::stoi(i));
        }
        return out;
    }

    int ctoi(char c) {
        return c - '0';
    }
}


#endif
