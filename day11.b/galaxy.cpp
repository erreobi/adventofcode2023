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
    unsigned long row;
    unsigned long col;

    galaxy(unsigned long r, unsigned long c) : row(r), col(c) {}
};

vector<vector<char>> galaxyMap;
vector<galaxy> galaxiesList;
vector<bool> galaxyRow;
vector<bool> galaxyCol;

ostream &operator<<(ostream &strm,galaxy tt)
{
    return strm<<"["<<tt.row<<"]"<<"["<<tt.col<<"]";
}

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
    galaxyRow.resize(galaxyMap.size());
    galaxyCol.resize(galaxyMap.front().size());

    std::fill(galaxyRow.begin(), galaxyRow.end(), false);
    std::fill(galaxyCol.begin(), galaxyCol.end(), false);

    unsigned long row = 0;
    unsigned long col = 0;
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
}

void mapGalaxy()
{
    unsigned long row = 0;
    unsigned long col = 0;
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
//                              1000000
unsigned long exmpationFactor = 999999;

unsigned long calcuateExpantion(galaxy A, galaxy B)
{
    unsigned long expantion = 0;
    unsigned long minRow = min(A.row, B.row);
    unsigned long maxRow = max(A.row, B.row);
    unsigned long minCol = min(A.col, B.col);
    unsigned long maxCol = max(A.col, B.col);

    // cout << "\t"<<"A: "<<A<<" B:"<<B<<";"<<endl;

    for (unsigned long index = minRow; index < maxRow; index++)
    {
        if (!galaxyRow[index])
        {   
            // cout << "\tgalaxyRow["<<index<<"];";
            expantion += exmpationFactor;
        }
    }
    // cout << "\texpantion: "<<expantion<<";"<<endl;

    for (unsigned long index = minCol; index < maxCol; index++)
    {
        if (!galaxyCol[index])
        {
            // cout << "\tgalaxyCol["<<index<<"];";
            expantion += exmpationFactor;
        }
    }
    // cout << "\texpantion: "<<expantion<<";"<<endl;

    // cout << endl;

    return expantion;
}
unsigned long  minPathStep(galaxy a, galaxy b)
{
    unsigned long col;
    unsigned long row;

    if (b.col > a.col){
        col = b.col - a.col;
    }else{
        col = a.col - b.col;
    }

    if (b.row > a.row){
        row = b.row - a.row;
    }else{
        row = a.row - b.row;
    }

    return col + row + calcuateExpantion(a, b);
}

unsigned long sumAllminPath()
{
    unsigned long minPathSum = 0;
    for (unsigned long i = 0; i < galaxiesList.size(); i++)
    {
        for (unsigned long j = i + 1; j < galaxiesList.size(); j++)
        {
            // cout << i + 1
            //      << ","
            //      << j + 1
            //      << "="
            //      << minPathStep(galaxiesList[i], galaxiesList[j])
            //      << endl;
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

    unsigned long SUM = sumAllminPath() ;
    cout << "SUM: " <<SUM << endl;
}
