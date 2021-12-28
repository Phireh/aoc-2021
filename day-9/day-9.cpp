#include <string>
#include <fstream>
#include <iostream>
#include <string.h>
#include <stdio.h>

void part_1()
{
    const int maxx = 100;
    const int maxy = 100;
    int heightmap[maxx][maxy] = {};

    FILE *mapfile = fopen("input", "r");

    char c;
    int *p = &heightmap[0][0];
    while (fread(&c, sizeof(char), 1, mapfile))
    {
        if (c == '\n')
            continue;

        *(p++) = c - '0';
    }

    int risk_level = 0;
    for (int i = 0; i < maxx; ++i)
        for (int j = 0; j < maxy; ++j)
        {
            int point = heightmap[i][j];
            bool is_low_point;

            // Check that none of the adjacent coordinates are lower or equal than the current point
            is_low_point = !(((i-1 >= 0) && (heightmap[i-1][j] <= point))   ||  // up
                             ((i+1 < maxx) && (heightmap[i+1][j] <= point)) ||  // down
                             ((j-1 >= 0) && (heightmap[i][j-1] <= point))   ||  // left
                             ((j+1 < maxy) && (heightmap[i][j+1] <= point)));   // right

            if (is_low_point)
                risk_level += point+1;
        }

    printf("Part 1: %d\n", risk_level);
}

int main()
{
    part_1();
}
