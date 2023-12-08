#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

vector<vector<char>> schematic;
char eraseChar='.';

int extractNumber(int row, int col, bool erase)
{
    //find the first number
    int index = col;

    for (; index < schematic[row].size() && isdigit(schematic[row][index]); index++);
    
    index--;//return beack of one to point to the right number

    int tenPow = 0;
    int number = 0;
    for (;index >= 0 && isdigit(schematic[row][index]); index--){
        int digit = int (schematic[row][index]-'0');
        number += digit * pow(10, tenPow); 
        tenPow++;
        if (erase)
        {
            schematic[row][index]='.';
        }
    }

    return number;
}



int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        std::cerr << "You need to pass the file in input";
        return -1;
    }

    ifstream inputFile(argv[1]); // Replace with the actual file name

    if (!inputFile.is_open()) {
        std::cerr << "Unable to open the file." << std::endl;
        return -1;
    }

    string line;
    while (getline(inputFile, line)) {

        vector<char> tempV; 
        for (int j = 0; j < line.length(); j++) { 
            tempV.push_back(line[j]); 
        } 
        schematic.push_back(tempV); 

    }

    //print the matrix 
    for (int i = 0; i < schematic.size(); i++) { 
        for (int j = 0; j < schematic[i].size(); j++) 
            cout << schematic[i][j] << " "; 
        cout << endl; 
    } 

    const int newRowArray[] = {-1, -1, -1,  0, 0,  1, 1, 1};
    const int newColArray[] = {-1,  0,  1, -1, +1, -1, 0, 1};
    int sum = 0;

    for (int r = 0; r < schematic.size(); r++) 
    { 
        for (int c = 0; c < schematic[r].size(); c++) 
        {
            if (schematic[r][c] == '*')
            {
                cout << "-------------------"<<endl;
                cout << "\t schematic["<< r <<"]["<<c<<"]: "<< schematic[r][c] << endl;
                /*
                   r-1,c-1|r-1,c|r-1,c+1
                   r,c-1  |r,c  |r,c+1
                   r+1,c-1|r+1,c|r+1,c+1
                */
               int foundCount = 0;
               long ratio = 1;
                for (int newIndex = 0; newIndex < 8; newIndex++)
                {
                    int newRow = r+newRowArray[newIndex];
                    int newCol = c+newColArray[newIndex];

                    cout << "\t schematic["<< newRow <<"]["<<newCol<<"]: "<< schematic[newRow][newCol] << endl;

                    if (newRow >= 0 && newRow < schematic.size())
                    {
                        if (newCol >= 0 && newCol < schematic[r].size())
                        {
                            if (isdigit(schematic[newRow][newCol])){
                                int theNumber = extractNumber(newRow, newCol, true);
                                cout << "\t" << theNumber << endl;
                                
                                foundCount++;
                                ratio *= theNumber;
                            }
                        }
                    }
                }
                if (foundCount == 2){
                    sum += ratio;
                }
                cout << "-------------------"<<endl;
            }
            
        }
    } 

    cout << endl; 
    cout << endl; 

    //print the matrix 
    for (int i = 0; i < schematic.size(); i++) { 
        for (int j = 0; j < schematic[i].size(); j++) 
            cout << schematic[i][j]; 
        cout << endl; 
    }

    cout<<"SUM: "<<sum<<endl;

}