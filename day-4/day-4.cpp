#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <array>
#include <string.h>
#include <deque>


void part_1()
{
    std::deque<int> nums;
    std::vector<int*> boards;
    std::vector<bool*> points;

    std::string line;
    std::ifstream input_file("input");

    // Get the list of numbers on the first line
    std::getline(input_file, line);

    // Separate numbers
    char *pch = strtok(line.data(), ",");
    nums.push_back(atoi(pch));

    while ((pch = strtok(nullptr, ",")) != nullptr)
    {
        nums.push_back(atoi(pch));
    }

    int col = 0;
    int row = 0;
    int *arr;
    // Get bingo boards
    while (std::getline(input_file,line))
    {
        if (line.size())
        {
            row = 0;
            // Separate numbers
            char *pch = strtok(line.data(), " ");
            arr[(col * 5) + row++] = atoi(pch);

            while ((pch = strtok(nullptr, " ")) != nullptr)
            {
                arr[(col * 5) + row++] = atoi(pch);
            }
            ++col;
        }
        else
        {
            arr = (int*) calloc(1, sizeof(int) * 5 * 5);
            boards.push_back(arr);
            col = 0;
            row = 0;
        }
    }

    for (uint i = 0; i < boards.size(); ++i)
        points.push_back((bool*)calloc(1, sizeof(bool) * 5 * 5));

    int winner_score = 0;
    
    while (!winner_score && !nums.empty())
    {
        int n = nums.at(0);
        nums.pop_front();

        auto itb = boards.begin();
        auto itp = points.begin();

        // Record points in all boards with that number
        for (; itb < boards.end() && itp < points.end(); ++itb, ++itp)
        {
            int *board = *itb;
            bool *point_table = *itp;
            for (int i = 0; i < 25; ++i)
            {
                if (board[i] == n)
                {
                    point_table[i] = true;
                }
            }
        }

        int *winner = nullptr;
        
        // Check for winners
        for (itb = boards.begin(), itp = points.begin();
             itb < boards.end() && itp < points.end();
             ++itb, ++itp)
        {
            int *board = *itb;
            bool *point_table = *itp;


            // Check rows
            if (point_table[0] && point_table[1] && point_table[2] && point_table[3] && point_table[4])
                winner = board;
            else if (point_table[5] && point_table[6] && point_table[7] && point_table[8] && point_table[9])
                winner = board;
            else if (point_table[10] && point_table[11] && point_table[12] && point_table[13] && point_table[14])
                winner = board;
            else if (point_table[15] && point_table[16] && point_table[17] && point_table[18] && point_table[19])
                winner = board;
            else if (point_table[20] && point_table[21] && point_table[22] && point_table[23] && point_table[24])
                winner = board;

            // Check columns
            else if (point_table[0] && point_table[5] && point_table[10] && point_table[15] && point_table[20])
                winner = board;
            else if (point_table[1] && point_table[6] && point_table[11] && point_table[16] && point_table[21])
                winner = board;
            else if (point_table[2] && point_table[7] && point_table[12] && point_table[17] && point_table[22])
                winner = board;
            else if (point_table[3] && point_table[8] && point_table[13] && point_table[18] && point_table[23])
                winner = board;
            else if (point_table[4] && point_table[9] && point_table[14] && point_table[19] && point_table[24])
                winner = board;

            if (winner)
            {
                // Count all unmarked numbers
                for (int i = 0; i < 25; ++i)
                {
                    if (!point_table[i]) winner_score += winner[i];
                }
                // Multiply score by last called number
                winner_score *= n;
                break;
            }
        }
    }
    printf("Part 1: %d\n", winner_score);
}

void part_2()
{
    std::deque<int> nums;
    std::vector<int*> boards;
    std::vector<bool*> points;

    std::string line;
    std::ifstream input_file("input");

    // Get the list of numbers on the first line
    std::getline(input_file, line);

    // Separate numbers
    char *pch = strtok(line.data(), ",");
    nums.push_back(atoi(pch));

    while ((pch = strtok(nullptr, ",")) != nullptr)
    {
        nums.push_back(atoi(pch));
    }

    int col = 0;
    int row = 0;
    int *arr;
    // Get bingo boards
    while (std::getline(input_file,line))
    {
        if (line.size())
        {
            row = 0;
            // Separate numbers
            char *pch = strtok(line.data(), " ");
            arr[(col * 5) + row++] = atoi(pch);

            while ((pch = strtok(nullptr, " ")) != nullptr)
            {
                arr[(col * 5) + row++] = atoi(pch);
            }
            ++col;
        }
        else
        {
            arr = (int*) calloc(1, sizeof(int) * 5 * 5);
            boards.push_back(arr);
            col = 0;
            row = 0;
        }
    }

    for (uint i = 0; i < boards.size(); ++i)
        points.push_back((bool*)calloc(1, sizeof(bool) * 5 * 5));

    int winner_score = 0;
    
    while (!winner_score && !nums.empty())
    {
        int n = nums.at(0);
        nums.pop_front();

        auto itb = boards.begin();
        auto itp = points.begin();

        // Record points in all boards with that number
        for (; itb < boards.end() && itp < points.end(); ++itb, ++itp)
        {
            int *board = *itb;
            bool *point_table = *itp;
            for (int i = 0; i < 25; ++i)
            {
                if (board[i] == n)
                {
                    point_table[i] = true;
                }
            }
        }

        // Check for winners
        for (itb = boards.begin(), itp = points.begin();
             itb < boards.end() && itp < points.end() && !winner_score;)
             
        {
            int *board = *itb;
            bool *point_table = *itp;
            int *winner = nullptr;


            // Check rows
            if (point_table[0] && point_table[1] && point_table[2] && point_table[3] && point_table[4])
                winner = board;
            else if (point_table[5] && point_table[6] && point_table[7] && point_table[8] && point_table[9])
                winner = board;
            else if (point_table[10] && point_table[11] && point_table[12] && point_table[13] && point_table[14])
                winner = board;
            else if (point_table[15] && point_table[16] && point_table[17] && point_table[18] && point_table[19])
                winner = board;
            else if (point_table[20] && point_table[21] && point_table[22] && point_table[23] && point_table[24])
                winner = board;

            // Check columns
            else if (point_table[0] && point_table[5] && point_table[10] && point_table[15] && point_table[20])
                winner = board;
            else if (point_table[1] && point_table[6] && point_table[11] && point_table[16] && point_table[21])
                winner = board;
            else if (point_table[2] && point_table[7] && point_table[12] && point_table[17] && point_table[22])
                winner = board;
            else if (point_table[3] && point_table[8] && point_table[13] && point_table[18] && point_table[23])
                winner = board;
            else if (point_table[4] && point_table[9] && point_table[14] && point_table[19] && point_table[24])
                winner = board;


            if (winner)
            {
                // If this isn't the last winner board, remove it
                if (boards.size() > 1)
                {
                    itb = boards.erase(itb);
                    itp = points.erase(itp);
                }
                else
                {
                    // Count all unmarked numbers
                    for (int i = 0; i < 25; ++i)
                    {
                        if (!point_table[i]) winner_score += winner[i];
                    }
                    // Multiply score by last called number
                    winner_score *= n;
                }
            }
            else
            {
                // This wasn't the winner, keep looking
                ++itb;
                ++itp;
            }
        }
    }
    printf("Part 2: %d\n", winner_score);
}

int main(int argc, char *argv[])
{
    part_1();
    part_2();
}
