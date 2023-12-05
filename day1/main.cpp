#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        cerr << "You need to pass the file in input";
        return -1;
    }

    ifstream testFile(argv[1]);
    string line;
    int sum = 0;

    if (testFile.is_open())
    {
        while (getline(testFile, line))
        {
            int leftDigit = -1;
            int rightDigit = -1;
            int leftIndex = 0, rightIndex = line.length() - 1;

            // // cout << "leftIndex: " << leftIndex << " rightIndex: "<< rightIndex<<'\n';
            // cout << "leftIndex <= rightIndex = [" << (leftIndex <= rightIndex)<<"]\n";

            while (leftIndex <= rightIndex && (leftDigit < 0 || rightDigit < 0) && line.length())
            {
                //cout << "leftIndex:" << leftIndex<<'\n';
                // cout << "\t line[leftIndex]: " << line[leftIndex]<<'\n';
                if (isdigit(line[leftIndex]))
                {
                    leftDigit = int(line[leftIndex] - '0');
                    // cout << "\t FOUND leftDigit: " << leftDigit<<'\n';
                }
                else
                {
                    leftIndex++;
                }

            //    cout << "rightIndex:" << rightIndex<<'\n';
            //    cout << "\t line[rightIndex]" << line[rightIndex]<<'\n';

                if (isdigit(line[rightIndex]))
                {
                    rightDigit = int(line[rightIndex] - '0');
                    // cout << "\t FOUND rightDigit: " << rightDigit<<'\n';
                }
                else
                {
                    rightIndex--;
                }
            }

            int calibration = leftDigit * 10 + rightDigit;
            sum += calibration;

            cout << line << " -> " << calibration << '\n';
        }
        testFile.close();
    }
    else
    {
        cerr << "Unable to open file";
        return -1;
    }

    cout << sum << '\n';

    return 0;
}
