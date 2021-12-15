#include <string>
#include <fstream>
#include <iostream>
#include <array>
#include <string.h>

/* Get next iteration of lanternfish at t+1 */
void iterate(std::array<uint64_t,9> &arr)
{
    uint64_t new_lanternfish = arr[0];

    for (uint i = 1; i < arr.size(); ++i)
        arr[i-1] = arr[i];

    arr[6] += new_lanternfish;
    arr[8] = new_lanternfish;
}

void part_1()
{

    std::array<uint64_t,9> lanternfish{0};

    std::string line;
    std::ifstream input_file("input");

    std::getline(input_file, line);

    // input only has a single line
    char *pch = strtok(line.data(), ",");

    do
    {
        ++lanternfish[atoi(pch)];
    } while ((pch = strtok(nullptr, ",")) != nullptr);

    printf("Initial state: ");
    for (uint64_t l : lanternfish)
        printf("%lu ", l);
    printf("\n");

    for (int i = 1; i <= 80; ++i)
    {
        iterate(lanternfish);
        printf("After %d days: ", i);
        for (uint64_t l : lanternfish)
            printf("%lu ", l);
        printf("\n");
    }

    uint64_t count = 0;

    for (uint64_t l : lanternfish)
    {
        count += l;
    }

    printf("Part 1: %lu\n", count);

}

void part_2()
{
    std::array<uint64_t,9> lanternfish{0};

    std::string line;
    std::ifstream input_file("input");

    std::getline(input_file, line);

    // input only has a single line
    char *pch = strtok(line.data(), ",");

    do
    {
        ++lanternfish[atoi(pch)];
    } while ((pch = strtok(nullptr, ",")) != nullptr);

    printf("Initial state: ");
    for (uint l : lanternfish)
        printf("%d ", l);
    printf("\n");

    for (int i = 1; i <= 256; ++i)
    {
        iterate(lanternfish);
        printf("After %d days: ", i);
        for (uint64_t l : lanternfish)
            printf("%lu ", l);
        printf("\n");
    }

    uint64_t count = 0;

    for (uint64_t l : lanternfish)
    {
        count += l;
    }

    printf("Part 2: %lu\n", count);
}

int main()
{
    part_1();
    part_2();
}
