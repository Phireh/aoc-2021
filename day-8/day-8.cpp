#include <string>
#include <fstream>
#include <iostream>
#include <string.h>

/* For part 1 we are only asked about the "easy digits". 
   Those are the nonambiguous ones; 
   i.e the digits which don't have another digit that is displayed using the same amount of segments 
   
   0 -> 6 segments, ambiguous
   1 -> 2 segments, unambiguous
   2 -> 5 segments, ambiguous
   3 -> 5 segments, ambiguous
   4 -> 4 segments, unambiguous
   5 -> 5 segments, ambiguous
   6 -> 6 segments, ambiguous
   7 -> 3 segments, unambiguous
   8 -> 7 segments, unambiguous
   9 -> 6 segments, ambiguous
   
   Therefore, we're being asked about the number of 1s, 4s, 7s and 8s in the output portion of the input
*/

int segments(char *str)
{
    bool present[7] = {};

    char *p = str;
    char c;

    while ((c = *p++))
    {
        present[c - 'a'] = true;
    }

    int n = 0;
    for (bool p : present)
    {
        if (p) ++n;
    }
    return n;
}

void part_1()
{
    std::string line;
    std::ifstream input_file("input");

    int ndigits = 0;

    while (std::getline(input_file, line))
    {
        char *pch = strtok(line.data(), "|");

        for (int i = 0; i < 4; ++i)
        {
            pch = strtok(nullptr, " ");

            switch(segments(pch))
            {
            case 2:
            case 3:
            case 4:
            case 7:
                // unambiguous
                ++ndigits;
                break;
            default:
                // other digits
                break;
            }
        }
    }

    printf("Part 1: %d\n", ndigits);
}

int main()
{
    part_1();
}
