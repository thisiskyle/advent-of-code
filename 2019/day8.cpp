#include <iostream>
#include <algorithm>
#include <vector>
#include "../headers/aoc.h"

int w = 25;
int h = 6;
int zeroes = -1;
int ones = 0;
int twos = 0;
std::vector<int> final_image;


int main() {
    // get the input
    std::vector<std::string> lines;
    util::read_file_by_line("./inputs/day8.txt", &lines);
    // put input into a container
    std::vector<int> raw_image_data;
    for(auto c : lines[0]) {
        raw_image_data.push_back(c - 48);
    }

    int layer_length = w * h;
    int layer_count = raw_image_data.size() / layer_length;

    // for each layer...
    for(int i = 0; i < layer_count; ++i) {
        int t_zeroes = 0;
        int t_ones = 0;
        int t_twos = 0;
        // for each pixel in layer...
        for(int j = 0; j < layer_length; ++j) {

            // get the index and track the pixel count
            int index = i * layer_length + j;
            if(raw_image_data[index] == 0) ++t_zeroes;
            else if(raw_image_data[index] == 1) ++t_ones;
            else if(raw_image_data[index] == 2) ++t_twos;

            // get the right pixels for final image
            // if first layer, fill final image with pixels from first layer
            if(i == 0) { final_image.push_back(raw_image_data[index]); }
            // if the final image pixel is transparent (2), replace it with a pixel from the current layer
            else if(final_image[j] == 2) { final_image[j] = raw_image_data[index]; }
        }
        // store the pixels counts for part 1
        if(zeroes == -1 || t_zeroes < zeroes) {
            zeroes = t_zeroes;
            ones = t_ones;
            twos = t_twos;
        }
    }
    std::cout << "part 1: " << ones * twos << std::endl;

    std::cout << "part 2: " << std::endl;

    // render final image
    for(int y = 0; y < h; ++y) {
        for(int x = 0; x < w; ++x) {
            int index = (y * w) + x;
            std::string s = final_image[index] ? "#" : " ";
            std::cout << s;
        }
        std::cout << "\n";
    }
}
