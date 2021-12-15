#include <string>
#include <fstream>
#include <iostream>
#include <array>
#include <string.h>
#include <vector>
#include <bits/stdc++.h>

void part_1()
{
    std::string line;
    std::ifstream input_file("input");
    std::vector<int> nums;

    // input is in one single line
    std::getline(input_file, line);

    int max = 0;
    int min = INT_MAX;
    char *pch = strtok(line.data(), ",");
    do
    {
        int n = atoi(pch);
        max = max > n ? max : n;
        min = min < n ? min : n;

        nums.push_back(n);
    } while ((pch = strtok(nullptr, ",")));

    int best_fuel = INT_MAX; // less is better
    int best_pivot;

    for (int i = min; i <= max; ++i)
    {
        int fuel = 0;
        for (int n : nums)
        {
            fuel += std::abs(n - i);
            if (fuel > best_fuel)
                break;
        }
        if (fuel < best_fuel)
        {
            best_fuel = fuel;
            best_pivot = i;
        }
    }

    printf("Part 1: Best position: %d; fuel cost: %d\n", best_pivot, best_fuel);
}

// Use formula of integer sum to efficiently compute the fuel cost
int fuel_consumption(int from, int to)
{
    int n = std::abs(to - from);
    return (n * (n+1)) / 2;
}

void part_2()
{
    std::string line;
    std::ifstream input_file("input");
    std::vector<int> nums;

    // input is in one single line
    std::getline(input_file, line);

    int max = 0;
    int min = INT_MAX;
    char *pch = strtok(line.data(), ",");
    do
    {
        int n = atoi(pch);
        max = max > n ? max : n;
        min = min < n ? min : n;

        nums.push_back(n);
    } while ((pch = strtok(nullptr, ",")));

    int best_fuel = INT_MAX; // less is better
    int best_pivot;

    for (int i = min; i <= max; ++i)
    {
        int fuel = 0;
        for (int n : nums)
        {
            fuel += fuel_consumption(n, i);
            if (fuel > best_fuel)
                break;
        }
        if (fuel < best_fuel)
        {
            best_fuel = fuel;
            best_pivot = i;
        }
    }

    printf("Part 2: Best position: %d; fuel cost: %d\n", best_pivot, best_fuel);
}


int main()
{
    part_1();
    part_2();
}
