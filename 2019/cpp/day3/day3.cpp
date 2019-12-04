#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include <cstdlib>

class Point {
    public:
        int x = 0;
        int y = 0;

        int manhattanDistance() {
             return std::abs(x) + std::abs(y);
        }

        bool operator==(const Point &other) const {
            return x == other.x && y == other.y;
        }
        bool operator!=(const Point &other) const {
            return !(x == other.x && y == other.y);
        }
};

class Wire {
    public:
        Point pos;
        std::vector<Point> path;

        Wire(std::vector<std::string> route) {
            plot_path(route);
        }

        void move_up(int n) {
            for(int i = 1; i <= n; i++) {
                pos.y++;
                path.push_back(pos);
            }
        }
        void move_down(int n) {
            for(int i = 1; i <= n; i++) {
                pos.y--;
                path.push_back(pos);
            }
        }
        void move_right(int n) {
            for(int i = 1; i <= n; i++) {
                pos.x++;
                path.push_back(pos);
            }
        }
        void move_left(int n) {
            for(int i = 1; i <= n; i++) {
                pos.x--;
                path.push_back(pos);
            }
        }
        void plot_path(std::vector<std::string> route) {
            for(int i = 0; i < route.size(); i++) {
                std::string direction = route[i].substr(0,1);
                int distance = std::stoi(route[i].substr(1));
                
                if(direction == "U") { move_up(distance); }
                else if(direction == "D") { move_down(distance); }
                else if(direction == "L") { move_left(distance); }
                else if(direction == "R") { move_right(distance); }
            }
        }
};

std::vector<std::string> input;

void read_input() {
    // reading input file and put it into a vector
    std::ifstream input_file;
    std::string temp;
    input_file.open("./input.txt");
    while(getline(input_file, temp, '\n')) {
        input.push_back(temp);
    }
}



int main() {

    read_input();

    std::vector<std::string> wire1_route;
    std::vector<std::string> wire2_route;

    std::stringstream s1(input[0]);
    std::stringstream s2(input[1]);

    std::string temp;

    while(getline(s1, temp, ',')) { wire1_route.push_back(temp); }
    while(getline(s2, temp, ',')) { wire2_route.push_back(temp); }

    Wire wire1(wire1_route);
    Wire wire2(wire2_route);

    std::vector<Point> intersections;
    std::vector<Point>::iterator it;


    std::cout << wire1.path.size() << std::endl;
    std::cout << wire2.path.size() << std::endl;

    int min_dis = INT_MAX;
    for(auto point : wire1.path) {
        if(std::find(wire2.path.begin(), wire2.path.end(), point) != wire2.path.end()) {
            //intersections.push_back(point);
            if(point.manhattanDistance() < min_dis) {
                min_dis = point.manhattanDistance();
            }
        }
    }
    std::cout << "part 1: " << min_dis << std::endl;



    return 0;
}
