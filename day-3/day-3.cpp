#include <string>
#include <fstream>
#include <iostream>
#include <vector>

int gamma_rate = 0; // we use the 12 lsb
int epsilon_rate = 0;

/* frequencies[0]: count of 0s for each position
   frequencies[1]: count of 1s for each position */
int frequencies[2][12] = {};

std::vector<std::pair<bool,int>> nums;


void part_1()
{
    FILE *fp = fopen("input", "r");

    char line[13]; // 12 bits + newline

    while (fread(&line, 1, sizeof(line), fp) == sizeof(line))
    {
        int num = 0;
        for (int i = 0; i < sizeof(line)-1; ++i)
        {
            bool bit = line[i] - '0';
            ++frequencies[bit][i];
            num |= ((bit) << (sizeof(line) - 2 - i));
        }

        nums.push_back(std::pair<bool,int>(true,num));
    }

    for (int i = 0; i < sizeof(line)-1; ++i)
        if (frequencies[1][i] > frequencies[0][i])
            gamma_rate |= (1 << (sizeof(line) - 2 - i));

    epsilon_rate = (~gamma_rate) & 0xFFF;

    std::cout << "Part 1: " << gamma_rate * epsilon_rate << std::endl;
}

void part_2()
{
    int valid_nums = 2;
    int last_valid_num = 0;
    int idx = 0;

    int oxygen_generator_rating = 0;
    int co2_scrubber_rating = 0;


    while (valid_nums > 1 && idx < 12)
    {
        for (int i = 0; i < 12; ++i)
        {
            frequencies[0][i] = 0;
            frequencies[1][i] = 0;
        }

        for (auto num : nums)
        {
            if (num.first)
            {
                int value = num.second;
                bool bit = (value >> (11 - idx) & 1);
                ++frequencies[bit][idx];
            }
        }

        valid_nums = 0;
        for (auto &num : nums)
        {
            if (num.first)
            {
                int value = num.second;
                bool bit = (value >> (11 - idx) & 1);
                bool most_common_bit = frequencies[1][idx] >= frequencies[0][idx] ? 1 : 0;

                if (most_common_bit == bit)
                {
                    ++valid_nums;
                    last_valid_num = value;
                }
                else
                {
                    num.first = false;
                }
            }
        }
        ++idx;
    }

    oxygen_generator_rating = last_valid_num;


    // Reset bools
    for (auto &num : nums)
        num.first = true;

    // Look again, this time for the co2 rating
    idx = 0;
    valid_nums = 2;

    while (valid_nums > 1 && idx < 12)
    {
        for (int i = 0; i < 12; ++i)
        {
            frequencies[0][i] = 0;
            frequencies[1][i] = 0;
        }

        for (auto num : nums)
        {
            if (num.first)
            {
                int value = num.second;
                bool bit = (value >> (11 - idx) & 1);
                ++frequencies[bit][idx];
            }
        }

        valid_nums = 0;
        for (auto &num : nums)
        {
            if (num.first)
            {
                int value = num.second;
                bool bit = (value >> (11 - idx) & 1);
                bool least_common_bit = frequencies[0][idx] <= frequencies[1][idx] ? 0 : 1;

                if (bit == least_common_bit)
                {
                    ++valid_nums;
                    last_valid_num = value;
                }
                else
                {
                    num.first = false;
                }
            }
        }
        ++idx;
    }

    co2_scrubber_rating = last_valid_num;

    printf("oxygen rating: %d(0x%x)\nco2 scrubber rating: %d(0x%x)\n", oxygen_generator_rating, oxygen_generator_rating, co2_scrubber_rating, co2_scrubber_rating);
    std::cout << "Part 2: " << co2_scrubber_rating * oxygen_generator_rating << std::endl;

}

int main(int argc, char *argv[])
{
    part_1();
    part_2();
}
