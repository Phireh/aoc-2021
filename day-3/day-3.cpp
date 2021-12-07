#include <string>
#include <fstream>
#include <iostream>

int gamma_rate = 0; // we use the 12 lsb

/* frequencies[0]: count of 0s for each position
   frequencies[1]: count of 1s for each position */
bool frequencies[2][12] = {};

int main(int argc, char *argv[])
{
    FILE *fp = fopen("input", "r");

    char line[13]; // 12 bits + newline

    while (fread(&line, 1, sizeof(line), fp) != sizeof(line))
    {
        printf("%s", line);
    }
}
