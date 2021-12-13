#include <string>
#include <fstream>
#include <iostream>

int xpos;
int ypos; // aka 'depth'
int aim;

void move(std::string command)
{
    /* Last character is \n */
    /* Second-to-last character is a char between 1 and 9 */
    char c = command[command.length()-1];

    int offset = c - '0';

    if (command.find("forward") != std::string::npos)
        xpos += offset;
    else if (command.find("up") != std::string::npos)
        ypos -= offset;
    else if (command.find("down") != std::string::npos)
        ypos += offset;
}

void move_with_aim(std::string command)
{
    /* Last character is a char between 1 and 9 */
    char c = command[command.length()-1];

    int offset = c - '0';

    if (command.find("forward") != std::string::npos)
    {
        xpos += offset;
        ypos += aim * offset;
    }
    else if (command.find("up") != std::string::npos)
        aim -= offset;
    else if (command.find("down") != std::string::npos)
        aim += offset;
}

void part_1()
{
    xpos = 0;
    ypos = 0;

    std::string line;
    std::ifstream input_file("input");


    while (std::getline(input_file, line))
    {
        move(line);
    }
    std::cout << "Part 1: " << xpos * ypos << std::endl;
}

void part_2()
{
    xpos = 0;
    ypos = 0;
    aim = 0;

    std::string line;
    std::ifstream input_file("input");


    while (std::getline(input_file, line))
    {
        move_with_aim(line);

    }

    std::cout << "Part 2: " << xpos * ypos << std::endl;



}

int main(int argc, char *argv[])
{
    part_1();
    part_2();
}
