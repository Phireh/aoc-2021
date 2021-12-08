#include <string>
#include <fstream>
#include <iostream>

int gamma_rate = 0; // we use the 12 lsb
int epsilon_rate = 0;

/* frequencies[0]: count of 0s for each position
   frequencies[1]: count of 1s for each position */
int frequencies[2][12] = {};

int main(int argc, char *argv[])
{
    FILE *fp = fopen("input", "r");

    char line[13]; // 12 bits + newline

    while (fread(&line, 1, sizeof(line), fp) == sizeof(line))
    {
        for (int i = 0; i < sizeof(line)-1; ++i)
        {
            ++frequencies[line[i] - '0'][i];
        }
    }

    for (int i = 0; i < sizeof(line)-1; ++i)
        if (frequencies[1][i] > frequencies[0][i])
            gamma_rate |= (1 << (sizeof(line) - 2 - i));

    epsilon_rate = (~gamma_rate) & 0xFFF;

    std::cout << "Part 1: " << gamma_rate * epsilon_rate << std::endl;
}
