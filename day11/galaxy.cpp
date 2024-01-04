#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <list>
#include <map>
#include <numeric>

using namespace std;

struct galaxy
{
    int row;
    int col;

    galaxy(int r, int c) : row(r), col(c) {}
};

vector<vector<char>> galaxyMap;
vector<galaxy> galaxiesList;

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

void expand()
{

    bool galaxyRow[galaxyMap.size()];
    bool galaxyCol[galaxyMap.front().size()];

    std::fill_n(galaxyRow, galaxyMap.size(), false);
    std::fill_n(galaxyCol, galaxyMap.front().size(), false);

    int row = 0;
    int col = 0;
    for (const auto &line : galaxyMap)
    {
        col = 0;
        for (const auto &space : line)
        {
            if (space == '#')
            {
                galaxyRow[row] = true;
                galaxyCol[col] = true;
            }

            col++;
        }
        row++;
    }

    vector<char> emptyLine(galaxyMap.size());
    std::fill(emptyLine.begin(), emptyLine.end(), '.');
    std::vector<vector<char>>::iterator it;
    it = galaxyMap.begin();

    for (row = galaxyMap.size() - 1; row >= 0; row--)
    {
        if (!galaxyRow[row])
        {
            cout << "ROW: " << row << " galaxyRow[row]: " << galaxyRow[row] << " " << galaxyMap.size() << endl;
            galaxyMap.insert(it + row, emptyLine);
        }
    }

    for (col = galaxyMap.front().size() - 1; col >= 0; col--)
    {
        if (!galaxyCol[col])
        {
            cout << "col: " << col << " galaxyCol[col]: " << galaxyCol[col] << " " << galaxyMap.size() << endl;
            std::vector<char>::iterator it2;

            for (row = galaxyMap.size() - 1; row >= 0; row--)
            {
                it2 = (galaxyMap[row]).begin();
                galaxyMap[row].insert(it2 + col, '.');
            }
        }
    }
}

void mapGalaxy()
{
    int row = 0;
    int col = 0;
    for (const auto &line : galaxyMap)
    {
        col = 0;
        for (const auto &space : line)
        {
            if (space == '#')
            {
                galaxiesList.push_back(galaxy(row, col));
            }

            col++;
        }
        row++;
    }
}

// ...#...#
// .....#..

int minPathStep(galaxy a, galaxy b)
{
    return abs(b.col - a.col) + abs(b.row - a.row);
}

int sumAllminPath()
{
    long minPathSum = 0;
    for (int i = 0; i < galaxiesList.size(); i++)
    {
        for (int j = i + 1; j < galaxiesList.size(); j++)
        {
            // cout<<i+1
            // <<","
            // <<j+1
            // <<"="
            // <<minPathStep(galaxiesList[i], galaxiesList[j])
            // << endl;
            minPathSum += minPathStep(galaxiesList[i], galaxiesList[j]);
        }
    }

    return minPathSum;
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

    while (getline(inputFile, line))
    {
        vector<char> oneLine(line.begin(), line.end());
        galaxyMap.push_back(oneLine);
    }

    cout << endl
         << galaxyMap << endl;

    expand();

    cout << endl
         << galaxyMap << endl;

    mapGalaxy();

    cout << "SUM: " << sumAllminPath() << endl;
}
