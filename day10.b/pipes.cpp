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

#define NO_DIR direction(-1, -1, -1);

bool operator==(const direction lhs, const direction rhs)
{
    return lhs.col == rhs.col && lhs.row == rhs.row && lhs.toward == rhs.toward;
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

vector<vector<char>> wall;
long DIR_S_START;
long DIR_S_END;
direction dirS(-1, -1, -1);

void init()
{
    for (long row = 0; row < wall.size(); row++)
    {
        for (long col = 0; col < wall[row].size(); col++)
        {
            wall[row][col] = '0';
        }
    }
}

// ostream &operator<<(ostream &strm, vector<vector<char>> tt)
// {
//     for (const auto &line : tt)
//     {
//         for (const auto &pipe : line)
//         {
//             strm << pipe;
//         }
//         strm << endl;
//     }
//     return strm;
// }

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
            return direction(dir.row - 1, dir.col, UP);
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
            return direction(dir.row + 1, dir.col, DOWN);
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
            return direction(dir.row, dir.col + 1, RIGHT);
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
int findLoop(vector<vector<char>> theMap, direction nextStep, int steps)
{
    if (nextStep.row < 0 || nextStep.row >= theMap.size())
        return -1;

    if (nextStep.col < 0 || nextStep.col >= theMap[nextStep.row].size())
        return -1;

    if (theMap[nextStep.row][nextStep.col] == 'S')
    {
        DIR_S_END = nextStep.toward;
        return steps;
    }
    direction newDiction = nextIndexFromPipe(theMap[nextStep.row][nextStep.col], nextStep);
    if (newDiction == direction(-1, -1, -1))
    {
        return -1;
    }

    wall[nextStep.row][nextStep.col] = theMap[nextStep.row][nextStep.col];

    return findLoop(theMap, newDiction, steps + 1);
}

void changeS()
{
    cout << "DIR_S_END: " << DIR_S_END << endl;
    cout << "DIR_S_START: " << DIR_S_START << endl;
    /*
        END -> direction of the flow ...

         END is left becase the flow is coming from left
          v
         F-
         |

        END ->  START
       * UP - UP ->   |
       * UP - LEFT -> 7
       * UP - RIGTH -> F

       * DOWN - LEFT -> J
       * DOWN - RIGHT -> L
       * DOWN - DOWN -> |

        *LEFT - LEFT -> -
       * LEFT - UP -> L
       * LEFT - DOWN -> F

        *RIGTH - RIGTH -> -
        *RIGTH - UP -> J
        *RIGTH - DOWN -> 7

    */
    if ((DIR_S_START == UP && DIR_S_END == UP) || (DIR_S_START == DOWN && DIR_S_END == DOWN))
    {
        wall[dirS.row][dirS.col] = '|';
    }

    if ((DIR_S_START == RIGHT && DIR_S_END == DOWN) || (DIR_S_START == UP && DIR_S_END == LEFT))
    {
        wall[dirS.row][dirS.col] = 'L';
    }

    if ((DIR_S_START == UP && DIR_S_END == RIGHT) || (DIR_S_START == LEFT && DIR_S_END == DOWN))
    {
        wall[dirS.row][dirS.col] = 'J';
    }

    if ((DIR_S_START == DOWN && DIR_S_END == LEFT) || (DIR_S_START == RIGHT && DIR_S_END == UP))
    {
        wall[dirS.row][dirS.col] = 'F';
    }

    if ((DIR_S_START == DOWN && DIR_S_END == RIGHT) || (DIR_S_START == LEFT && DIR_S_END == UP))
    {
        wall[dirS.row][dirS.col] = '7';
    }

    if ((DIR_S_START == LEFT && DIR_S_END == LEFT) || (DIR_S_START == RIGHT && DIR_S_END == RIGHT))
    {
        wall[dirS.row][dirS.col] = '-';
    }
}

int findLoop(vector<vector<char>> theMap)
{

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

    if (dirS == direction(-1, -1, -1))
    {
        return -1;
    }

    cout << "S: [" << dirS.row << ", " << dirS.col << "]" << endl;

    direction newDirection = dirS;
    int steps;
    wall = std::vector<std::vector<char>>(theMap.size(),
                                          std::vector<char>(theMap[0].size()));

    // 4 direction
    // UP
    init();
    wall[dirS.row][dirS.col] = 'S';
    newDirection.toward = UP;
    newDirection.row--;
    steps = findLoop(theMap, newDirection, 1);
    DIR_S_START = UP;

    if (steps > 0)
        return steps;

    // DOWN
    init();
    wall[dirS.row][dirS.col] = 'S';
    newDirection = dirS;
    newDirection.toward = DOWN;
    newDirection.row++;
    steps = findLoop(theMap, newDirection, 1);
    DIR_S_START = DOWN;

    if (steps > 0)
        return steps;

    // RIGHT
    init();
    wall[dirS.row][dirS.col] = 'S';
    newDirection = dirS;
    newDirection.toward = RIGHT;
    newDirection.col++;
    steps = findLoop(theMap, newDirection, 1);
    DIR_S_START = LEFT;

    if (steps > 0)
        return steps;

    // LEFT --> NO needed ...  check 3 of 4 direction is enough

    return -1;
}

int howmanywalls(direction dir)
{
    if (dir.row < 0 || dir.row >= wall.size())
        return 0;

    if (dir.col < 0 || dir.col >= wall[dir.row].size())
        return 0;

    direction newDir = dir;

    switch (dir.toward)
    {
    case UP:
        newDir.row--;
        break;
    case DOWN:
        newDir.row++;
        break;
    case RIGHT:
        newDir.col++;
        break;
    case LEFT:
        newDir.col--;
        break;

    default:
        break;
    }

    if (wall[dir.row][dir.col] != '0' && wall[dir.row][dir.col] != 'I' && wall[dir.row][dir.col] != '.')
    {
        // if it is horinzontal, the horizontal wall shouldn not count
        switch (dir.toward)
        {
        case RIGHT:
        case LEFT:
            if (wall[dir.row][dir.col] == '-')
            {
                return howmanywalls(newDir);
            }

        default:
            return 1 + howmanywalls(newDir);
        }
    }
    else
    {
        return howmanywalls(newDir);
    }
}

void markExternals()
{

    for (long row = 0; row < wall.size(); row++)
    {
        for (long col = 0; col < wall[row].size(); col++)
        {
            if (wall[row][col] == '0')
            {
                int numbWallUP = howmanywalls(direction(row, col, UP));
                int numbWallDOWN = howmanywalls(direction(row, col, DOWN));
                int numbWallLEFT = howmanywalls(direction(row, col, LEFT));
                int numbWallRIGT = howmanywalls(direction(row, col, RIGHT));

                if (numbWallUP == 0 || numbWallDOWN == 0 || numbWallLEFT == 0 || numbWallRIGT == 0)
                {
                    wall[row][col] = '.';
                }
                else
                {
                    numbWallRIGT = 0;
                    bool findF = false;
                    bool findL = false;

                    // check right
                    /*
                    FJ
                    F7

                    */
                    for (long index = col + 1; index < wall[row].size(); index++)
                    {
                        if (wall[row][index] == '|')
                        {
                            numbWallRIGT++;
                        }
                        else if (wall[row][index] == 'F')
                        {
                            findF = true;
                        }
                        else if (wall[row][index] == 'J')
                        {
                            if (findF)
                            {
                                numbWallRIGT++;
                                findF = false;
                            }
                            if (findL)
                                findL = false;
                        }
                        else if (wall[row][index] == '7')
                        {
                            if (findL)
                            {
                                numbWallRIGT++;
                                findL = false;
                            }
                            if (findF)
                                findF=false;
                        }
                        else if (wall[row][index] == 'L')
                        {
                            findL = true;
                        }
                    }

                    numbWallLEFT = 0;
                    bool findJ = false;
                    bool find7 = false;
                    for (long index = col - 1; index >= 0; index--)
                    {
                        if (wall[row][index] == '|')
                        {
                            numbWallLEFT++;
                        }
                        else if (wall[row][index] == 'F')
                        {
                            if (findJ)
                            {
                                numbWallLEFT++;
                                findJ = false;
                            }
                            if (find7)
                                find7 = false;
                        }
                        else if (wall[row][index] == 'J')
                        {
                            findJ = true;
                        }
                        else if (wall[row][index] == '7')
                        {
                            find7 = true;
                        }
                        else if (wall[row][index] == 'L')
                        {
                            if (find7)
                            {
                                numbWallLEFT++;
                                find7 = false;
                            }

                            if (findJ)
                                findJ = false;
                        }
                    }

                    // cout << "wall[" << row << "][" << col << "]=" << wall[row][col]
                    //      << " -> numbWallLEFT: " << numbWallLEFT
                    //      << "  numbWallRIGT: " << numbWallRIGT
                    //      << endl;

                    if (numbWallLEFT > 0 && numbWallRIGT > 0)
                    {
                        if ((numbWallLEFT % 2) != 0 && (numbWallRIGT % 2) != 0)
                        {
                            wall[row][col] = 'I';
                        }
                    }
                }
            }
        }
    }
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

    cout << endl
         << theMap << endl;

    int steps = findLoop(theMap);

    cout << "STEP: " << steps << endl;
    cout << steps / 2 << endl;

    cout << endl
         << wall << endl;
    changeS();
    cout << endl
         << wall << endl;
    markExternals();
    cout << endl
         << wall << endl;

    long totI = 0;
    for (long row = 0; row < wall.size(); row++)
    {
        for (long col = 0; col < wall[row].size(); col++)
        {
            if (wall[row][col] == 'I')
            {
                totI++;
            }
        }
    }

    cout << endl
         << "TOT: " << totI << endl;

    return 0;
}
