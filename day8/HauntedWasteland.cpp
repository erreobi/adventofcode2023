#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <list>
#include <map>

using namespace std;

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

map<string, NextEl> nodes;
string istruction;

int followInstruction(string instruction, map<string, NextEl> theNodes){
    
    std::map<string, NextEl>::iterator it;
    int countSteps = 0;
    int index = 0;
    string nextSteps = "AAA"; 

    do{
        it = theNodes.find(nextSteps); 

        if (it->first == "ZZZ"){
            return countSteps;
        }else{
            countSteps++;
            
            char steps = instruction[index];

            NextEl nextNode = it->second;
            if (steps == 'L')
            {
                nextSteps = nextNode.left;
            }else{
                nextSteps = nextNode.right;
            }
    
        }

        index++;
        index = index % (instruction.length());
    }while (it != theNodes.end());

    return 0;
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

    int count = followInstruction(istruction, nodes);
    cout<<"COUNT: "<<count<<endl;

    return 0;
}
