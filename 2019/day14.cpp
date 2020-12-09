#include <regex>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <math.h>
#include "../headers/aoc.h"

struct element {

    std::string id;
    long long int base_amount;
    long long int base_ore_cost = 0;
    long long int stored = 0;

    std::map<std::string, long long int> recipe;

    element() { }

    element(std::string _id, long long int _base_amount) {
        id = _id;
        base_amount = _base_amount;
    }
    void store(long long int n) {
        stored += n;
    }
};

void load_elements(std::map<std::string, element>* elements, const std::string& s, const std::regex& r) {
    // temp for storing
    std::vector<element> t;
    // load all matches long long into a vector as elements 
    std::sregex_iterator it(s.begin(), s.end(), r);
    std::sregex_iterator end;
    while(it != end) {
        element e((*it)[2], std::stoi((*it)[1]));
        t.push_back(e);
        ++it;
    }
    element p;
    // loop backwards through recipe
    for(long long int i = t.size() - 1; i >= 0; --i) {
        // if element is the product...
        if(i == t.size() - 1) {
            p = t[i];
            (*elements)[p.id] = p;
        }
        // if element is an ingredient...
        else {
            (*elements)[p.id].recipe[t[i].id] = t[i].base_amount; 
        }
    }
}

long long int part1(std::string start, long long int amount, std::string path) {
    long long int ore_cost = 0;
    std::vector<std::string> queue;
    std::map<std::string, long long int> queue_data;
    std::vector<std::string> lines = util::read_file_by_line(path);
    std::map<std::string, element> elements;
    std::regex r("([0-9]+) ([A-Z]+)");

    for(auto s : lines) { load_elements(&elements, s, r); }

    queue.push_back(start);
    queue_data[start] = amount;


    while(queue.size() > 0) {
        element* e = &elements[queue[0]];

        //std::cout << "Requesting " << queue_data[e->id] << " " << e->id << "\n";
        //std::cout << "    " << e->stored << " " << e->id << " in storage\n";

        if(e->stored >= queue_data[e->id]) {
            e->stored -= queue_data[e->id];
            queue_data[e->id] = 0;
        }
        else if(e->stored < queue_data[e->id]) {
            queue_data[e->id] -= e->stored;
            e->stored = 0;
        }

        //std::cout << "    " << queue_data[e->id] << " " << e->id <<" still needed\n";

        long long int reactions = std::ceil((float)queue_data[e->id] / (float)e->base_amount);
        long long int leftover = (reactions * e->base_amount) - queue_data[e->id];

        //std::cout << "    " << reactions << " reactions will produce " << reactions * e->base_amount << " with " << leftover << " leftover\n";

        e->stored += leftover;

        //std::cout << "    Recipe: ";
        for(std::map<std::string, long long int>::iterator it = e->recipe.begin(); it != e->recipe.end(); ++it) {
            //std::cout << "(" << it->first << " " << it->second << ")";
            if(it->first == "ORE") {
                ore_cost += it->second * reactions;
            }
            else {
                if(!util::contains(queue, it->first)) queue.push_back(it->first);
                if(queue_data.find(it->first) == queue_data.end()) { queue_data[it->first] = (it->second * reactions); }
                else { queue_data[it->first] += (it->second * reactions); }
            }
        }

        //std::cout << "\n    " << "Ore Cost so far: " << ore_cost << "\n";

        queue_data.erase(e->id);
        queue.erase(queue.begin());

        //std::cout << "    Queue [" << queue.size() << "]: ";
        for(std::map<std::string, long long int>::iterator it = queue_data.begin(); it != queue_data.end(); ++it) {
            //std::cout << "(" << it->first << " " << it->second << ")";
        }
        //std::cout << "\n\n";
    }

    return ore_cost;
}

long long int part2(std::string path) {
    std::string start = "FUEL";
    long long int MAX_ORE = 1000000000000;
    long long int upper = 1;
    long long int lower = 0;

    while(1) {
        long long int test = part1("FUEL", upper, path);
        if(test > MAX_ORE) {
            break;
        }
        upper += upper * upper;
    }

    long long int check = upper / 2;
    long long int ore = 0;

    while(check != lower) {
        ore = part1(start, check, path);

        if(ore == MAX_ORE) {
            lower = check;
            break;
        }
        else if(ore > MAX_ORE) {
            upper = check;
        }
        else if(ore < MAX_ORE) {
            lower = check;
        }
        check = lower + ((upper - lower) / 2);
    }
    return lower;
}

void tests() {
    std::cout << "\nRunning tests...\n\n";

    std::cout << "part 1: " << part1("FUEL", 1, "./inputs/day14.txt") << " expecting 362713\n";
    std::cout << "part 1: " << part1("FUEL", 1, "./inputs/day14_t1.txt") << " expecting 31\n";
    std::cout << "part 1: " << part1("FUEL", 1, "./inputs/day14_t2.txt") << " expecting 165\n";
    std::cout << "part 1: " << part1("FUEL", 1, "./inputs/day14_t3.txt") << " expecting 13312\n";
    std::cout << "part 1: " << part1("FUEL", 1, "./inputs/day14_t4.txt") << " expecting 180697\n";
    std::cout << "part 1: " << part1("FUEL", 1, "./inputs/day14_t5.txt") << " expecting 2210736\n";

    std::cout << "\n";

    std::cout << "part 2: " << part2("./inputs/day14.txt") << " expecting 3281820\n"; 
    std::cout << "part 2: " << part2("./inputs/day14_t1.txt") << " expecting \n";
    std::cout << "part 2: " << part2("./inputs/day14_t2.txt") << " expecting \n";
    std::cout << "part 2: " << part2("./inputs/day14_t3.txt") << " expecting 82892753\n";
    std::cout << "part 2: " << part2("./inputs/day14_t4.txt") << " expecting 5586022\n";
    std::cout << "part 2: " << part2("./inputs/day14_t5.txt") << " expecting 460664\n";


    std::cout << "\nSanity Checks...\n\n";

    std::cout << "part 1 using 3281820: " << part1("FUEL", 3281820, "./inputs/day14.txt") << "\n";
    std::cout << "part 1 using 3281821: " << part1("FUEL", 3281821, "./inputs/day14.txt") << "\n";

    std::cout << "\n??? How are both under 100000000000 if 3281821 answer is wrong ???\n\n";
}

void answers() {
    std::cout << "part 1: " << part1("FUEL", 1, "./inputs/day14.txt") << " expecting 362713\n";
    std::cout << "part 2: " << part2("./inputs/day14.txt") << " expecting 3281820\n"; 
}


int main() {
    answers();
    tests();

    return 0;
}
