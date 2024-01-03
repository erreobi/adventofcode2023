#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <list>
#include <map>
#include <numeric>

#define UP 2
#define DOWN 8
#define LEFT 4
#define RIGHT 6

struct direction
{
    long row;
    long col;
    long toward;

    direction(long r, long c, long d) : row(r), col(c), toward(d) {}
};

#define NO_DIR direction(-1,-1,-1);

bool operator==(const direction lhs, const direction rhs){
    return lhs.col==rhs.col && lhs.row==rhs.row && lhs.toward==rhs.toward;
}

using namespace std;

ostream &operator<<(ostream &strm, vector<vector<char>> tt)
{
    for (const auto &line : tt)
    {
        for (const auto &pipe : line)
        {
            strm << pipe;
        }
        strm << endl;
    }
    return strm;
}

// It can tell you the next direction to take. 
direction nextIndexFromPipe(char pipe, direction dir)
{

    switch (pipe)
    {
    case '|': // is a vertical pipe connecting north and south.
        switch (dir.toward)
        {
        case UP:
            return direction(dir.row - 1, dir.col, UP);
        case DOWN:
            return direction(dir.row + 1, dir.col, DOWN);
        default:
            return direction(-1, -1, -1);
        }
        break;

    case '-': // is a horizontal pipe connecting east and west.
        switch (dir.toward)
        {
        case LEFT:
            return direction(dir.row, dir.col - 1, LEFT);
        case RIGHT:
            return direction(dir.row, dir.col + 1, RIGHT);
        default:
            return direction(-1, -1, -1);
        }
        break;
    case 'L': // is a 90-degree bend connecting north and east.
        switch (dir.toward)
        {
        case LEFT:
            return direction(dir.row - 1, dir.col, UP);
        case DOWN:
            return direction(dir.row, dir.col + 1, RIGHT);
        default:
            return direction(-1, -1, -1);
        }
        break;
    case 'J': // is a 90-degree bend connecting north and west.
        switch (dir.toward)
        {
        case RIGHT:
            return direction(dir.row - 1 , dir.col, UP);
        case DOWN:
            return direction(dir.row, dir.col - 1, LEFT);
        default:
            return direction(-1, -1, -1);
        }
        break;
    case '7': // is a 90-degree bend connecting south and west.
        switch (dir.toward)
        {
        case RIGHT:
            return direction(dir.row + 1 , dir.col, DOWN);
        case UP:
            return direction(dir.row, dir.col - 1, LEFT);
        default:
            return direction(-1, -1, -1);
        }
        break;
    case 'F': // is a 90-degree bend connecting south and east.
        switch (dir.toward)
        {
        case UP:
            return direction(dir.row , dir.col+1, RIGHT);
        case LEFT:
            return direction(dir.row + 1, dir.col, DOWN);
        default:
            return direction(-1, -1, -1);
        }
        break;
    case '.': // is ground; there is no pipe in this tile.
        return direction(-1, -1, -1);
    case 'S': // s the starting position of the animal; there is a pipe on this tile, but your sketch doesn't show what shape the pipe has
        return direction(-1, -1, -1);
    default:
        return direction(-1, -1, -1);
        break;
    }
    return direction(-1, -1, -1);
}

// return -1 if it doesn't fidn a loop
int findLoop (vector<vector<char>> theMap, direction nextStep, int steps)
{
    if (nextStep.row < 0 || nextStep.row >= theMap.size())
        return -1;
    
    if (nextStep.col < 0 || nextStep.col >= theMap[nextStep.row].size())
        return -1;

    if (theMap[nextStep.row][nextStep.col] == 'S'){
        return steps;
    }
    direction newDiction = nextIndexFromPipe (theMap[nextStep.row][nextStep.col],nextStep);
    if (newDiction == direction (-1,-1,-1))
    {
        return -1;
    }
    return findLoop (theMap, newDiction, steps+1);
}

int findLoop (vector<vector<char>> theMap)
{
    direction dirS (-1,-1,-1);

    for (long row = 0; row < theMap.size(); row++)
    {
        for (long col = 0; col < theMap[row].size(); col++)
        {
            if (theMap[row][col] == 'S')
            {
                dirS.col = col;
                dirS.row = row;
                break;
            }
        }
    }
    
    if (dirS == direction(-1,-1,-1))
    {
        return -1;
    }

    cout << "S: [" << dirS.row << ", "<<dirS.col << "]"<<endl;

    direction newDirection = dirS;
    int steps;

    //4 direction
    //UP
    newDirection.toward = UP;
    newDirection.row--;
    steps = findLoop(theMap, newDirection, 1);
    if (steps > 0)
        return steps;
    
    //DOWN
    newDirection = dirS;
    newDirection.toward = DOWN;
    newDirection.row++;
    steps = findLoop(theMap, newDirection, 1);
    if (steps > 0)
        return steps;

    //RIGHT
    newDirection = dirS;
    newDirection.toward = RIGHT;
    newDirection.col++;
    steps = findLoop(theMap, newDirection, 1);
    if (steps > 0)
        return steps;

     //LEFT --> NO needed ...  check 3 of 4 direction is enough

    return -1;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "You need to pass the file in input";
        return -1;
    }

    ifstream inputFile(argv[1]);
    if (!inputFile.is_open())
    {
        std::cerr << "Unable to open the file. " << argv[1] << std::endl;
        return -1;
    }

    string line;
    string uselessChar;
    vector<vector<char>> theMap;

    while (getline(inputFile, line))
    {
        vector<char> oneLine(line.begin(), line.end());
        theMap.push_back(oneLine);
    }

    cout << endl << theMap << endl;

    int steps = findLoop(theMap);

    cout << steps << endl;
    cout << steps/2 << endl;


    return 0;
}
