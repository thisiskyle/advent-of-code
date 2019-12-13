#include <algorithm>
#include <vector>
#include "./headers/Intcode_Computer.h"
#include "./headers/aoc.h"

class Amp {
public:
    Intcode_Computer computer{"./inputs/day7.txt", true};
    int phase;
    long int output;
    bool first_run;

    Amp() { 
    }
    ~Amp() {
    }

    void run(int in) {
        std::vector<long int> input;
        if(first_run) {
            input.push_back(phase);
            first_run = false;
        }
        input.push_back(in);
        computer.run(input, &output);
    }

    int get_output() {
        return output;
    }
    bool is_computer_halted() {
        return computer.is_halted();
    }
    void reset() {
        output = 0;
        first_run = true;
        computer.reset();
    }
};

int main() {
    Intcode_Computer computer("./inputs/day7.txt");
    int largest = 0;

    std::vector<int> phase_settings{0,1,2,3,4}; // a b c d e
    do {
        long int output = 0;
        for(int i = 0; i < 5; ++i) {
            std::vector<long int> input{ phase_settings[i], output };
            computer.reset();
            computer.run(input, &output);
            if(output > largest) {
                largest = output;
            }
        }
    } while(std::next_permutation(phase_settings.begin(), phase_settings.end()));

    std::cout << "part 1: " << largest << std::endl;


    // ---------------- part 2
    std::vector<int> phase_settings2{5,6,7,8,9}; // a b c d e
    largest = 0;
    Amp amp1, amp2, amp3, amp4, amp5;
    int output = 0;

    do {
        output = 0;
        amp1.reset();
        amp2.reset();
        amp3.reset();
        amp4.reset();
        amp5.reset();

        amp1.phase = phase_settings2[0];
        amp2.phase = phase_settings2[1];
        amp3.phase = phase_settings2[2];
        amp4.phase = phase_settings2[3];
        amp5.phase = phase_settings2[4];

        while(!amp5.is_computer_halted()) {
            amp1.run(output);
            amp2.run(amp1.get_output());
            amp3.run(amp2.get_output());
            amp4.run(amp3.get_output());
            amp5.run(amp4.get_output());
            output = amp5.get_output();
        }

        if(output > largest) {
            largest = output;
        }


    } while(std::next_permutation(phase_settings2.begin(), phase_settings2.end()));

    std::cout << "part 2: " << largest << std::endl;

    return 0;
}
