#include <string>
#include <fstream>
#include <iostream>
#include <array>
#include <string.h>


void part_1()
{
    int *nums = (int*) calloc(1, sizeof(int) * 1000 * 1000);

    std::string line;
    std::ifstream input_file("input");

    while (std::getline(input_file, line))
    {
        // Extract our four numbers
        int x1, x2, y1, y2;

        // read first coord
        char *pch = strtok(line.data(), ",");
        x1 = atoi(pch);

        pch = strtok(nullptr, " ");
        y1 = atoi(pch);

        // get rid of '->'
        pch = strtok(nullptr, " ");

        // read second coord
        pch = strtok(nullptr, ",");
        x2 = atoi(pch);

        pch = strtok(nullptr, "");
        y2 = atoi(pch);

        // only consider horizontal and vertical lines
        if (x1 == x2 || y1 == y2)
        {
            int xoffset = 0;
            int yoffset = 0;

            if (x1 < x2)
                xoffset = 1;
            if (x2 < x1)
                xoffset = -1;

            if (y1 < y2)
                yoffset = 1;
            if (y2 < y1)
                yoffset = -1;

            int x = x1;
            int y = y1;
            while (x != x2 || y != y2)
            {
                ++nums[y * 1000 + x];
                x += xoffset, y += yoffset;
            }
            ++nums[y * 1000 + x]; // last iteration
        }
    }

    int result = 0;
    for (int i = 0; i < 1000 * 1000; ++i)
        if (nums[i] > 1)
            ++result;

    printf("Part 1: %d\n", result);
}

void part_2()
{
        int *nums = (int*) calloc(1, sizeof(int) * 1000 * 1000);

    std::string line;
    std::ifstream input_file("input");

    while (std::getline(input_file, line))
    {
        // Extract our four numbers
        int x1, x2, y1, y2;

        // read first coord
        char *pch = strtok(line.data(), ",");
        x1 = atoi(pch);

        pch = strtok(nullptr, " ");
        y1 = atoi(pch);

        // get rid of '->'
        pch = strtok(nullptr, " ");

        // read second coord
        pch = strtok(nullptr, ",");
        x2 = atoi(pch);

        pch = strtok(nullptr, "");
        y2 = atoi(pch);



        int xoffset = 0;
        int yoffset = 0;

        if (x1 < x2)
            xoffset = 1;
        if (x2 < x1)
            xoffset = -1;

        if (y1 < y2)
            yoffset = 1;
        if (y2 < y1)
            yoffset = -1;

        int x = x1;
        int y = y1;
        while (x != x2 || y != y2)
        {
            ++nums[y * 1000 + x];
            x += xoffset, y += yoffset;
        }
        ++nums[y * 1000 + x]; // last iteration
    }

    int result = 0;
    for (int i = 0; i < 1000 * 1000; ++i)
        if (nums[i] > 1)
            ++result;

    printf("Part 2: %d\n", result);

}

int main()
{
    part_1();
    part_2();
}
