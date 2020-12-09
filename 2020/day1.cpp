#include <fstream>
#include <iostream>
#include <vector>

int main() {

    int a1;
    int a2;

    int in;
    std::vector<int> inputs;


    // open the input file
    std::ifstream input_file;
    input_file.open("./inputs/day1.txt");

    // add them all to an array first
    while(input_file >> in) {
        inputs.push_back(in);
    }

    // then we can loop through with an index 
    // and a nested loop withou repeating numbers
    for(int i = 0; i < inputs.size(); ++i) {
        for(int j = i + 1; j < inputs.size(); ++j) {

            int a = inputs[i];
            int b = inputs[j];

            int sum = a + b;
            
            if(sum == 2020) {
                a1 = a * b;
                break;
            }
        }
    }

    // output answer 1
    std::cout << "part 1: " << a1 << std::endl;

    for(int i = 0; i < inputs.size(); ++i) {
        for(int j = i + 1; j < inputs.size(); ++j) {
            for(int k = j + 1; k < inputs.size(); ++k) {

                int a = inputs[i];
                int b = inputs[j];
                int c = inputs[k];

                int sum = a + b + c;
                
                if(sum == 2020) {
                    a2 = a * b * c;
                    break;
                }
            }
        }
    }

    // output answer 2
    std::cout << "part 2: " << a2 << std::endl;

    return 0;
}
