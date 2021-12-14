#include <string>
#include <fstream>
#include <iostream>
#include <array>
#include <string.h>

/* Get next iteration of lanternfish at t+1 */
void iterate(std::array<uint,9> &arr)
{
    uint new_lanternfish = arr[0];

    for (uint i = 1; i < arr.size(); ++i)
        arr[i-1] = arr[i];

    arr[6] += new_lanternfish;
    arr[8] += new_lanternfish;
}

void part_1()
{

    std::array<uint,9> lanternfish{0};
    
    std::string line;
    std::ifstream input_file("input");

    std::getline(input_file, line);

    // input only has a single line
    char *pch = strtok(line.data(), ",");

    do
    {
        ++lanternfish[atoi(pch)];
    } while ((pch = strtok(nullptr, ",")) != nullptr);

    for (int i = 0; i < 80; ++i)
        iterate(lanternfish);

    uint64_t count = 0;

    for (uint l : lanternfish)
    {
        count += l;
    }

    printf("Part 1: %lu\n", count);
    
}

int main()
{
    part_1();
}
