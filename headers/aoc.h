#ifndef AOC_H
#define AOC_H

#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

namespace util {

    void clear_screen() {
        std::cout << std::string(100, '\n');
    }

    int sum_of_digits(int n) {
        int sum = 0;

        while(n > 0) {
            int m = n % 10;
            sum += m;
            n /= 10;
        }

        return sum;
    }

    // shouldnt use these
    void print_answers(int a1, int a2) {
        std::cout << "part 1: " << a1 << std::endl;
        std::cout << "part 2: " << a2 << std::endl;
    }

    // shouldnt use these
    void print_answers(std::string a1, std::string a2) {
        std::cout << "part 1: " << a1 << std::endl;
        std::cout << "part 2: " << a2 << std::endl;
    }

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

    // turns a vector or strings into a vector of ints
    void v_stoi(std::vector<std::string> s, std::vector<int>* out) {
        for(auto i : s) {
            out->push_back(std::stoi(i));
        }
    }

    // turns a vector or strings into a vector of ints
    std::vector<int> v_stoi(std::vector<std::string> s) {
        std::vector<int> out;
        for(auto i : s) {
            out.push_back(std::stoi(i));
        }
        return out;
    }

    // vector of strings to long ints
    void v_stoli(std::vector<std::string> s, std::vector<long int>* out) {
        for(auto i : s) {
            out->push_back(std::stol(i));
        }
    }
    std::vector<long int> v_stoli(std::vector<std::string> s) {
        std::vector<long int> out;
        for(auto i : s) {
            out.push_back(std::stol(i));
        }
        return out;
    }
    void v_stolli(std::vector<std::string> s, std::vector<long long int>* out) {
        for(auto i : s) {
            out->push_back(std::stoll(i));
        }
    }
    std::vector<long long int> v_stolli(std::vector<std::string> s) {
        std::vector<long long int> out;
        for(auto i : s) {
            out.push_back(std::stoll(i));
        }
        return out;
    }

    int ctoi(char c) {
        return c - '0';
    }

    template <typename T>
    int find_index_of(const std::vector<T>& v, const T& element) {
        auto it = std::find(v.begin(), v.end(), element);
        if (it != v.end())
        {
            return distance(v.begin(), it);
        }
        return -1;
    }
    template <typename T>
    int contains(const std::vector<T>& v, const T& element) {
        auto it = std::find(v.begin(), v.end(), element);
        return it != v.end();
    }
    template <typename T>
    void remove_element(std::vector<T>& v, const T& element) {
        int index = find_index_of(v, element);
        if(index == -1) return;
        v.erase(v.begin() + index);
    }
    long long int gcd(long long int a, long long int b) {
        if (b == 0) return a; 
        return gcd(b, a % b);
    }

    long long int lcm(long long int a, long long int b) {
        return (a * b) / gcd(a, b);
    }
    int gcd(int a, int b) {
        if (b == 0) return a; 
        return gcd(b, a % b);
    }

    int lcm(int a, int b) {
        return (a * b) / gcd(a, b);
    }

    double delta_time(int fps) {
        return (1000 / fps);
    }

    struct Point {
        int x, y;

        Point() {  
            this->x = 0;
            this->y = 0;
        }
        Point(int x, int y) {
            this->x = x;
            this->y = y;
        }

        bool operator==(const Point& other) const {
            return x == other.x && y == other.y;
        }
        bool operator!=(const Point& other) const {
            return !(x == other.x && y == other.y);
        }
        Point operator+(const Point& other) const {
            Point p(x + other.x, y + other.y);
            return p;
        }
        Point operator-(const Point& other) const {
            Point p(x - other.x, y - other.y);
            return p;
        }
        Point& operator+=(const Point& other) {
            this->x += other.x;
            this->y += other.y;
            return *this;
        }
        Point& operator-=(const Point& other) {
            this->x -= other.x;
            this->y -= other.y;
            return *this;
        }
    };
    struct Point3 {
        int x, y, z;

        Point3() {
            this->x = 0;
            this->y = 0;
            this->z = 0;

        } 
        Point3(int x, int y, int z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        bool operator==(const Point3& other) const {
            return x == other.x && y == other.y && z == other.z;
        }
        bool operator!=(const Point3& other) const {
            return !(x == other.x && y == other.y && z == other.z);
        }
        Point3 operator+(const Point3& other) const {
            Point3 p(x + other.x, y + other.y, z + other.z);
            return p;
        }
        Point3 operator-(const Point3& other) const {
            Point3 p(x - other.x, y - other.y, z - other.z);
            return p;
        }
        Point3& operator+=(const Point3& other) {
            this->x += other.x;
            this->y += other.y;
            this->z += other.z;
            return *this;
        }
    };
}

#endif
