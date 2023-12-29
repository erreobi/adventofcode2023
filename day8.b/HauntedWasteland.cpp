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

unsigned long LINE_UP = '\033[1A';
unsigned long LINE_CLEAR = '\x1b[2K';

struct NextEl
{
    string left;
    string right;

    NextEl(string l, string r) : left(l), right(r) {}
};

bool operator<(const NextEl &l, const NextEl &r)
{
    return l.left < r.left;
}

bool operator==(const NextEl &l, const NextEl &r)
{
    return l.left < r.left;
}

ostream &operator<<(ostream &strm, const NextEl tt)
{
    return strm << "(" << tt.left << ", " << tt.right << ")";
}

ostream &operator<<(ostream &strm, map<string, NextEl> tt)
{
    map<string, NextEl>::iterator it = tt.begin();
    while (it != tt.end())
    {
        strm << it->first << " = " << it->second << ";" << endl;
        ++it;
    }
    return strm;
}

ostream &operator<<(ostream &strm, map<string, unsigned long> tt)
{
    map<string, unsigned long>::iterator it = tt.begin();
    while (it != tt.end())
    {
        strm << it->first << " = " << it->second << " ";
        ++it;
    }
    return strm;
}

map<string, NextEl> nodes;
string istruction;

unsigned long searchFromOneNome(string instruction, map<string, NextEl> theNodes, string nextSteps)
{

    std::map<string, NextEl>::iterator it;
    unsigned long countSteps = 0;
    unsigned long index = 0;

    do
    {
        it = theNodes.find(nextSteps);

        string key = it->first;

        if (key[(key.length() - 1)] == 'Z')
        {
            return countSteps;
        }
        else
        {
            countSteps++;

            char steps = instruction[index];

            NextEl nextNode = it->second;
            if (steps == 'L')
            {
                nextSteps = nextNode.left;
            }
            else
            {
                nextSteps = nextNode.right;
            }
        }

        index++;
        index = index % (instruction.length());
    } while (it != theNodes.end());

    return 0;
}

unsigned long followInstructionParallel(string instruction, map<string, NextEl> theNodes)
{

    vector<string> listOFPossibleNodes;
    std::map<string, NextEl>::iterator it;

    for (std::map<string, NextEl>::iterator it = theNodes.begin(); it != theNodes.end(); ++it)
    {
        string key = it->first;
        if (key[(key.length() - 1)] == 'A')
        {
            listOFPossibleNodes.push_back(key);
        }
    }

    unsigned long foundAllZs = 0;
    unsigned long indexInstruction = 0;
    unsigned long numberOfStep = 0;

    do
    {
        foundAllZs = 0;
        for (unsigned long indexLpN = 0; indexLpN < listOFPossibleNodes.size(); indexLpN++)
        {
            string posNode = listOFPossibleNodes[indexLpN];

            it = theNodes.find(posNode);
            string key = it->first;
            if (key[(key.length() - 1)] == 'Z')
            {
                foundAllZs++;
            }

            char steps = instruction[indexInstruction];

            NextEl nextNode = it->second;
            if (steps == 'L')
            {
                listOFPossibleNodes[indexLpN] = nextNode.left;
            }
            else
            {
                listOFPossibleNodes[indexLpN] = nextNode.right;
            }
        }

        numberOfStep++;

        indexInstruction++;
        indexInstruction = indexInstruction % (instruction.length());

    } while (foundAllZs != listOFPossibleNodes.size());

    return (numberOfStep - 1); // it counts 1 the first step
}


unsigned long followInstruction(string instruction, map<string, NextEl> theNodes)
{

    vector<string> listOFPossibleNodes;
    std::map<string, NextEl>::iterator it;

    for (std::map<string, NextEl>::iterator it = theNodes.begin(); it != theNodes.end(); ++it)
    {
        string key = it->first;
        if (key[(key.length() - 1)] == 'A')
        {
            listOFPossibleNodes.push_back(key);
        }
    }

    unsigned long lcmNum = 1;

    for (const auto &node : listOFPossibleNodes){

        unsigned long steps = searchFromOneNome(instruction, theNodes, node);
        cout << "Node: " << node << " -> " << steps <<endl;
        lcmNum = std::lcm(lcmNum,steps);
    }

    cout << "LCM: " <<lcmNum << endl;
    
    return lcmNum;
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

    getline(inputFile, istruction);

    string line;
    string uselessChar;
    getline(inputFile, uselessChar);

    while (getline(inputFile, line))
    {
        istringstream iss(line);
        string node;
        string left;
        string right;

        iss >> node >> uselessChar >> left >> right;
        left.erase(std::remove(left.begin(), left.end(), '('), left.end());
        right.erase(std::remove(right.begin(), right.end(), ')'), right.end());
        left.erase(std::remove(left.begin(), left.end(), ','), left.end());

        NextEl nextEl(left, right);

        nodes.insert(pair<string, NextEl>(node, nextEl));
    }

    cout << istruction << endl;
    cout << nodes;

    unsigned long count = followInstruction(istruction, nodes);
    cout << "COUNT: " << count << endl;

    return 0;
}
