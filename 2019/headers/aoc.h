#ifndef AOC_H
#define AOC_H

#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <windows.h>
#include <algorithm>

namespace util {

    void clear_screen() {
        HANDLE                     hStdOut;
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        DWORD                      count;
        DWORD                      cellCount;
        COORD                      homeCoords = { 0, 0 };

        hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
        if (hStdOut == INVALID_HANDLE_VALUE) return;

        /* Get the number of cells in the current buffer */
        if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
        cellCount = csbi.dwSize.X *csbi.dwSize.Y;

        /* Fill the entire buffer with spaces */
        if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR) ' ',
        cellCount,
        homeCoords,
        &count
        )) return;

        /* Fill the entire buffer with the current colors and attributes */
        if (!FillConsoleOutputAttribute(
        hStdOut,
        csbi.wAttributes,
        cellCount,
        homeCoords,
        &count
        )) return;

        /* Move the cursor home */
        SetConsoleCursorPosition( hStdOut, homeCoords );
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
