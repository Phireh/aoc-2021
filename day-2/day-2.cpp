#include <string>
#include <fstream>
#include <iostream>


int xpos = 0;
int ypos = 0;

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

int main(int argc, char *argv[])
{
    std::string line;    
    std::ifstream input_file("input");


    while (std::getline(input_file, line))
    {
        move(line);
        
    }
    std::cout << "Part 1: " << xpos * ypos << std::endl;
}
