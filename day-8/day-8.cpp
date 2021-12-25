#include <string>
#include <fstream>
#include <iostream>
#include <string.h>
#include <vector>
#include <math.h>

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
            {
                // We read either a '2', a '3' or a '5'
                char missing_segments[2] = {};

                int idx = 0;
                for (char c : "abcdefg")
                {
                    if (!strchr(n.c_str(), c))
                        missing_segments[idx++] = c;
                }

                bool could_be_2 = ((std::find(bv.begin(), bv.end(), missing_segments[0]) != bv.end()) && (std::find(fv.begin(), fv.end(), missing_segments[1]) != fv.end())) ||
                    ((std::find(bv.begin(), bv.end(), missing_segments[1]) != bv.end()) && (std::find(fv.begin(), fv.end(), missing_segments[0]) != fv.end()));

                bool could_be_3 = ((std::find(bv.begin(), bv.end(), missing_segments[0]) != bv.end()) && (std::find(ev.begin(), ev.end(), missing_segments[1]) != ev.end())) ||
                    ((std::find(bv.begin(), bv.end(), missing_segments[1]) != bv.end()) && (std::find(ev.begin(), ev.end(), missing_segments[0]) != ev.end()));

                bool could_be_5 = ((std::find(cv.begin(), cv.end(), missing_segments[0]) != cv.end()) && (std::find(ev.begin(), ev.end(), missing_segments[1]) != ev.end())) ||
                    ((std::find(cv.begin(), cv.end(), missing_segments[1]) != cv.end()) && (std::find(ev.begin(), ev.end(), missing_segments[0]) != ev.end()));


                if (could_be_2 && !could_be_3 && !could_be_5)
                {
                    // It's a '2'
                    std::erase_if(av, [missing_segments](char x) { return x == missing_segments[0] || x == missing_segments[1]; });
                    std::erase_if(bv, [missing_segments](char x) { return !(x == missing_segments[0] || x == missing_segments[1]); });
                    std::erase_if(cv, [missing_segments](char x) { return x == missing_segments[0] || x == missing_segments[1]; });
                    std::erase_if(dv, [missing_segments](char x) { return x == missing_segments[0] || x == missing_segments[1]; });
                    std::erase_if(ev, [missing_segments](char x) { return x == missing_segments[0] || x == missing_segments[1]; });
                    std::erase_if(fv, [missing_segments](char x) { return !(x == missing_segments[0] || x == missing_segments[1]); });
                    std::erase_if(gv, [missing_segments](char x) { return x == missing_segments[0] || x == missing_segments[1]; });
                }
                if (!could_be_2 && could_be_3 && !could_be_5)
                {
                    // It's a '3'
                    std::erase_if(av, [missing_segments](char x) { return x == missing_segments[0] || x == missing_segments[1]; });
                    std::erase_if(bv, [missing_segments](char x) { return !(x == missing_segments[0] || x == missing_segments[1]); });
                    std::erase_if(cv, [missing_segments](char x) { return x == missing_segments[0] || x == missing_segments[1]; });
                    std::erase_if(dv, [missing_segments](char x) { return x == missing_segments[0] || x == missing_segments[1]; });
                    std::erase_if(ev, [missing_segments](char x) { return !(x == missing_segments[0] || x == missing_segments[1]); });
                    std::erase_if(fv, [missing_segments](char x) { return x == missing_segments[0] || x == missing_segments[1]; });
                    std::erase_if(gv, [missing_segments](char x) { return x == missing_segments[0] || x == missing_segments[1]; });
                }
                if (!could_be_2 && !could_be_3 && could_be_5)
                {
                    // It's a '5'
                    std::erase_if(av, [missing_segments](char x) { return x == missing_segments[0] || x == missing_segments[1]; });
                    std::erase_if(bv, [missing_segments](char x) { return x == missing_segments[0] || x == missing_segments[1]; });
                    std::erase_if(cv, [missing_segments](char x) { return !(x == missing_segments[0] || x == missing_segments[1]); });
                    std::erase_if(dv, [missing_segments](char x) { return x == missing_segments[0] || x == missing_segments[1]; });
                    std::erase_if(ev, [missing_segments](char x) { return !(x == missing_segments[0] || x == missing_segments[1]); });
                    std::erase_if(fv, [missing_segments](char x) { return x == missing_segments[0] || x == missing_segments[1]; });
                    std::erase_if(gv, [missing_segments](char x) { return x == missing_segments[0] || x == missing_segments[1]; });
                }



            } break;
            case 6:
            {
                // We read either a '6', a '0' or a '9'

                // Since our number is only missing one segment, we try to use it to determine which number it is
                char missing_segment;
                if (!strchr(n.c_str(), 'a'))
                    missing_segment = 'a';
                else if (!strchr(n.c_str(), 'b'))
                    missing_segment = 'b';
                else if (!strchr(n.c_str(), 'c'))
                    missing_segment = 'c';
                else if (!strchr(n.c_str(), 'd'))
                    missing_segment = 'd';
                else if (!strchr(n.c_str(), 'e'))
                    missing_segment = 'e';
                else if (!strchr(n.c_str(), 'f'))
                    missing_segment = 'f';
                else if (!strchr(n.c_str(), 'g'))
                    missing_segment = 'g';

                bool missing_segment_could_be_c = (std::find(cv.begin(), cv.end(), missing_segment) != cv.end());
                bool missing_segment_could_be_d = (std::find(dv.begin(), dv.end(), missing_segment) != dv.end());
                bool missing_segment_could_be_e = (std::find(ev.begin(), ev.end(), missing_segment) != ev.end());

                if (missing_segment_could_be_c && !missing_segment_could_be_d && !missing_segment_could_be_e)
                {
                    // The number is a '6'
                    std::erase(av, missing_segment);
                    std::erase(bv, missing_segment);
                    std::erase_if(cv, [missing_segment](char x) { return !(x == missing_segment); });
                    std::erase(dv, missing_segment);
                    std::erase(ev, missing_segment);
                    std::erase(fv, missing_segment);
                    std::erase(gv, missing_segment);
                }
                if (!missing_segment_could_be_c && missing_segment_could_be_d && !missing_segment_could_be_e)
                {
                    // The number is a '0'
                    std::erase(av, missing_segment);
                    std::erase(bv, missing_segment);
                    std::erase(cv, missing_segment);
                    std::erase_if(dv, [missing_segment](char x) { return !(x == missing_segment); });
                    std::erase(ev, missing_segment);
                    std::erase(fv, missing_segment);
                    std::erase(gv, missing_segment);
                }
                if (!missing_segment_could_be_c && !missing_segment_could_be_d && missing_segment_could_be_e)
                {
                    // The number is a '9'
                    std::erase(av, missing_segment);
                    std::erase(bv, missing_segment);
                    std::erase(cv, missing_segment);
                    std::erase(dv, missing_segment);
                    std::erase_if(ev, [missing_segment](char x) { return !(x == missing_segment); });
                    std::erase(fv, missing_segment);
                    std::erase(gv, missing_segment);
                }
            } break;



            case 7:
                // We read a '8', which gives us no useful information about the wiring
                ;
                break;
            }
        }
    }
    printf("Line deciphered. Coding is:\n");
    printf("\tav = ");
    for (char c : av)
    {
        printf("%c", c);
    }
    printf("\n");

    printf("\tbv = ");
    for (char c : bv)
    {
        printf("%c", c);
    }
    printf("\n");

    printf("\tcv = ");
    for (char c : cv)
    {
        printf("%c", c);
    }
    printf("\n");

    printf("\tdv = ");
    for (char c : dv)
    {
        printf("%c", c);
    }
    printf("\n");

    printf("\tev = ");
    for (char c : ev)
    {
        printf("%c", c);
    }
    printf("\n");

    printf("\tfv = ");
    for (char c : fv)
    {
        printf("%c", c);
    }
    printf("\n");

    printf("\tgv = ");
    for (char c : gv)
    {
        printf("%c", c);
    }
    printf("\n");

    int idx = 4;
    auto it = number_encodings.end() - idx;
    int final_number = 0;

    while (it < number_encodings.end())
    {
        std::string encoding = *it;
        int digit;
        switch(encoding.size())
        {
        case 7:
            digit = 8;
            break;
        case 6:
            if (std::find(encoding.begin(), encoding.end(), cv[0]) == encoding.end())
                digit = 6;
            if (std::find(encoding.begin(), encoding.end(), dv[0]) == encoding.end())
                digit = 0;
            if (std::find(encoding.begin(), encoding.end(), ev[0]) == encoding.end())
                digit = 9;
            break;
        case 5:
            if ((std::find(encoding.begin(), encoding.end(), bv[0]) == encoding.end()) &&  (std::find(encoding.begin(), encoding.end(), fv[0]) == encoding.end()))
                digit = 2;
            if ((std::find(encoding.begin(), encoding.end(), bv[0]) == encoding.end()) &&  (std::find(encoding.begin(), encoding.end(), ev[0]) == encoding.end()))
                digit = 3;
            if ((std::find(encoding.begin(), encoding.end(), cv[0]) == encoding.end()) &&  (std::find(encoding.begin(), encoding.end(), ev[0]) == encoding.end()))
                digit = 5;
            break;
        case 4:
            digit = 4;
            break;
        case 3:
            digit = 7;
            break;
        case 2:
            digit = 1;
            break;
        }
        final_number += digit * pow(10, --idx);

        printf("%s is %d\n", encoding.c_str(), digit);
        ++it;
    }
    printf("\nFinal number: %d\n", final_number);


    return final_number;
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
