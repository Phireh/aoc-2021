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
       are the only possible wirings to 'c' and 'f'. We can delete every other possibility
       from ab, bv and delete 'c' and 'f' from every other vector.
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
            switch(segments((char*)n.c_str()))
            {
            case 2:
                // we read a '1'. It should we written with 'c' and 'f'
                std::erase_if(cv, [n](char x) { return x != n[0] && x != n[1]; });
                std::erase_if(fv, [n](char x) { return x != n[0] && x != n[1]; });
                for (char c : n)
                {
                    std::erase(av, c);
                    std::erase(bv, c);
                    std::erase(dv, c);
                    std::erase(ev, c);
                    std::erase(gv, c);
                }
                break;

            case 3:
                // we read a '7'. It should be written with 'a', 'c', and 'f'
                std::erase_if(av, [n](char x) { return x != n[0] && x != n[1] && x != n[2]; });
                std::erase_if(cv, [n](char x) { return x != n[0] && x != n[1] && x != n[2]; });
                std::erase_if(fv, [n](char x) { return x != n[0] && x != n[1] && x != n[2]; });
                for (char c : n)
                {
                    std::erase(bv, c);
                    std::erase(dv, c);
                    std::erase(ev, c);
                    std::erase(gv, c);
                }
                break;

            case 4:
                // we read a 4. It should be written with 'b', 'c', 'd', and 'f'
                std::erase_if(bv, [n](char x) { return x != n[0] && x != n[1] && x != n[2] && x != n[3]; });
                std::erase_if(cv, [n](char x) { return x != n[0] && x != n[1] && x != n[2] && x != n[3]; });
                std::erase_if(dv, [n](char x) { return x != n[0] && x != n[1] && x != n[2] && x != n[3]; });
                std::erase_if(fv, [n](char x) { return x != n[0] && x != n[1] && x != n[2] && x != n[3]; });
                for (char c : n)
                {
                    std::erase(av, c);
                    std::erase(ev, c);
                    std::erase(gv, c);
                }
                break;

            case 5:
                // We read either a '2', a '3' or a '5'
                break;
            case 6:
                // We read either a '6', a '0' or a '9'
            case 7:
                // We read a '8', which gives us no useful information about the wiring
                break;
            }
        }
    }
    return 0;
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
