#include <regex>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <math.h>
#include "./headers/aoc.h"

struct element {

    std::string id;
    int base_amount;
    int base_ore_cost = 0;
    int stored = 0;

    std::map<std::string, int> recipe;

    element() { }

    element(std::string _id, int _base_amount) {
        id = _id;
        base_amount = _base_amount;
    }
    void store(int n) {
        stored += n;
    }


    int get_ore_cost(int amount_requested, std::map<std::string, element>* elements) {
        int amount_needed = 0;
        int reactions = 0;
        int overbuild = 0;
        int cost_to_produce = 0;

        std::cout << "Requesting " << amount_requested << " " << id << " with " << stored << " in storage\n";

        if(stored != 0) {
            if(amount_requested > stored){
                amount_needed = amount_requested - stored;
                stored = 0;
            }
            else if(stored > amount_requested) {
                stored -= amount_requested;
            }
        }
        else amount_needed = amount_requested;

        if(amount_needed > 0) {
            reactions = std::ceil((float)amount_needed / (float)base_amount);
            overbuild = base_amount * reactions - amount_needed;
        }

        std::cout << amount_needed << " " << id << " still needed\n";
        std::cout << reactions << " reactions will produce " << base_amount * reactions << " " << id << " with " << overbuild << " leftover\n";
        store(overbuild);

        for(std::map<std::string, int>::iterator it = recipe.begin(); it != recipe.end(); ++it) {
            if(it->first == "ORE") {
                base_ore_cost = it->second;
            }
            else {
                base_ore_cost += (*elements)[it->first].get_ore_cost(it->second, elements);
            }
        }

        return cost_to_produce * reactions;
    }
};


void load_elements(std::map<std::string, element>* elements, const std::string& s, const std::regex& r) {
    // temp for storing
    std::vector<element> t;
    // load all matches into a vector as elements 
    std::sregex_iterator it(s.begin(), s.end(), r);
    std::sregex_iterator end;
    while(it != end) {
        element e((*it)[2], std::stoi((*it)[1]));
        t.push_back(e);
        ++it;
    }
    element p;
    // loop backwards through recipe
    for(int i = t.size() - 1; i >= 0; --i) {
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

void part1(std::string path) {
    std::vector<std::string> lines = util::read_file_by_line(path);
    std::map<std::string, element> elements;
    std::regex r("([0-9]+) ([A-Z]+)");
    // load element data
    for(auto s : lines) { load_elements(&elements, s, r); }

    std::cout << elements["FUEL"].get_ore_cost(1, &elements) << std::endl;
}


int main() {
    //part1("./inputs/day14.txt");
    
    //part1("./inputs/day14_t1.txt");
    part1("./inputs/day14_t2.txt");
    //part1("./inputs/day14_t3.txt");

    return 0;
}
