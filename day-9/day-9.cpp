#include <string>
#include <fstream>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <functional>

const int maxx = 100;
const int maxy = 100;
int heightmap[maxx][maxy] = {};

struct p2d
{
    int x;
    int y;
};

/* Recursively find size of basin starting from its lowest member */
uint32_t basin_size(int i, int j)
{
    static bool visited[maxx][maxy] = {};
    uint32_t size = 0;

    if (heightmap[i][j] < 9)
    {
        if (!visited[i][j])
        {
            visited[i][j] = true;
            ++size;
        }

        /* East cell */
        if (i < maxx-1 && !visited[i+1][j])
            size += basin_size(i+1, j);

        /* South cell */
        if (j < maxy-1 && !visited[i][j+1])
            size += basin_size(i, j+1);

        /* West cell */
        if (i > 0 && !visited[i-1][j])
            size += basin_size(i-1, j);

        /* North cell */
        if (j > 0 && !visited[i][j-1])
            size += basin_size(i, j-1);
    }
    return size;
}


void part_1()
{
    FILE *mapfile = fopen("input", "r");

    char c;
    int *p = &heightmap[0][0];
    while (fread(&c, sizeof(char), 1, mapfile))
    {
        if (c == '\n' || c == '\r')
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

void part_2()
{
    FILE *mapfile = fopen("input", "r");

    char c;
    int *p = &heightmap[0][0];
    while (fread(&c, sizeof(char), 1, mapfile))
    {
        if (c == '\n' || c == '\r')
            continue;

        *(p++) = c - '0';
    }

    /* Since every low point has a basin, finding them before is the easiest method to get the basins */
    std::vector<p2d> low_points;
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
            {
                p2d p = { i, j };
                low_points.push_back(p);
            }

        }

    std::vector<uint32_t> sizes;
    for (p2d p : low_points)
    {
        sizes.push_back(basin_size(p.x, p.y));
    }

    std::sort(sizes.begin(), sizes.end(), std::greater<uint32_t>());

    uint32_t result = sizes[0] * sizes[1] * sizes[2];

    printf("Part 2: %d\n", result);
}

int main()
{
    part_1();
    part_2();
}
