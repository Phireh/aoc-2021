#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

void part_1()
{
    // The amount of times that the next number read is larger than the previous
    int ntimes = 0;
    
    int curr, prev;
    std::ifstream input_file("input");
    std::string line;

    // Initialize first number
    std::getline(input_file, line);
    curr = stoi(line);
    
    while(std::getline(input_file, line))
    {
        prev = curr;
        curr = stoi(line);

        if (prev < curr)
            ++ntimes;        
    }
    std::cout << "Part 1: " << ntimes << std::endl;
}

void part_2()
{
    // The amount of times that the next (3 element) sliding window sum is larger than the previous
    int ntimes = 0;
    const int window_size = 4;

    // Vector representing our sliding windows
    // window[0..2] is the first, window[1..3] is the second
    std::vector window(window_size, 0);

    std::ifstream input_file("input");
    std::string line;

    // Initialize first window
    std::getline(input_file, line);
    window[3] = stoi(line);
    std::getline(input_file, line);
    window[2] = stoi(line);
    std::getline(input_file, line);
    window[1] = stoi(line);
    std::getline(input_file, line);

    int idx = 0;

    do {
        window[idx] = stoi(line);
        
        int curr_window = window[idx%window_size] + window[(idx+1)%window_size] + window[(idx+2)%window_size];
        int last_window = window[(idx+1)%window_size] + window[(idx+2)%window_size] + window[(idx+3)%window_size];

        if (curr_window > last_window)
            ++ntimes;

        idx = idx == 0 ? window_size - 1 : idx - 1;

    } while (std::getline(input_file, line));
    
        std::cout << "Part 2: " << ntimes << std::endl;
}


int main(int argc, char *argv[])
{
    part_1();
    part_2();
}
