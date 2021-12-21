#include <string>
#include <fstream>
#include <iostream>
#include <string.h>
#include <vector>

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

int decipher_line(std::string line)
{
    /* Possible wirings for each desired output segment. As we process the line,
       we delete possible candidates.

       For example, if we read 'fg', we know that the number is '1' and that 'fg'
       are the only possible wirings to 'a' and 'b'. We can delete every other possibility
       from ab, bv and delete 'f' and 'g' from every other vector.
     */
    std::vector<char> av = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    std::vector<char> bv = av, cv = av, dv = av, ev = av, fv = av, gv = av;

    // We're going to need to process numbers multiple times, so tokenize them in advance
    std::vector<std::string> number_encodings;
    
    char *pch = strtok(line.data(), "| ");
    do
    {
        number_encodings.push_back(pch);
    } while ((pch = strtok(nullptr, "| ")) != nullptr);

    // Decipher wiring
    while (av.size() > 1 || bv.size() > 1 || cv.size() > 1 || dv.size() > 1 ||
           ev.size() > 1 || fv.size() > 1 || gv.size() > 1)
    {
        for (auto n : number_encodings)
        {
            switch(segments(n.c_str()))
            {
            case 2:
                // we read a '1'. It should we written with 'a' and 'b'
                av = {};
                bv = {};
                for (char c : n)
                {
                    av.push_back(c);
                    bv.push_back(c);
                    std::erase();
                }
                break;
            }
        }
    }
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

void part_2()
{
    std::string line;
    std::ifstream input_file("input");

    int output_value = 0;

    while (std::getline(input_file, line))
    {
        output_value += decipher_line(line);
    }

    printf("Part 2: %d\n", output_value);
}

int main()
{
    part_1();
    part_2();
}
