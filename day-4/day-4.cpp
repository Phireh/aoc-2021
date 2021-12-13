#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <array>
#include <string.h>
#include <deque>


void part_1()
{
    std::deque<int> nums;
    std::vector<int*> boards;
    std::vector<bool*> points;

    std::string line;
    std::ifstream input_file("input");

    // Get the list of numbers on the first line
    std::getline(input_file, line);

    // Separate numbers
    char *pch = strtok(line.data(), ",");
    nums.push_back(atoi(pch));

    while ((pch = strtok(nullptr, ",")) != nullptr)
    {
        nums.push_back(atoi(pch));
    }

    int col = 0;
    int row = 0;
    int *arr;
    // Get bingo boards
    while (std::getline(input_file,line))
    {
        if (line.size())
        {
            row = 0;
            // Separate numbers
            char *pch = strtok(line.data(), " ");
            arr[(col * 5) + row++] = atoi(pch);

            while ((pch = strtok(nullptr, " ")) != nullptr)
            {
                arr[(col * 5) + row++] = atoi(pch);
            }
            ++col;
        }
        else
        {
            arr = (int*) calloc(1, sizeof(int) * 5 * 5);
            boards.push_back(arr);
            col = 0;
            row = 0;
        }
    }


}

int main(int argc, char *argv[])
{
    part_1();
}
