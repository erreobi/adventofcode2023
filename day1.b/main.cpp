#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const string number2Letters[] = {"on", "tw", "th", "fo", "fi", "si", "se", "ei", "ni"};
const string numberStrings[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
const int numberStrignsValue[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

int searchIn2Letter(string first2Letters)
{

    int index = 0;
    while (index < 9)
    {
        if (first2Letters.compare(number2Letters[index]) == 0)
        {
            return index;
        }
        index++;
    }
    return -1;
}

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

            while (leftIndex <= rightIndex && (leftDigit < 0 || rightDigit < 0))
            {
                if (isdigit(line[leftIndex]))
                {
                    leftDigit = int(line[leftIndex] - '0');
                }
                else if ((leftIndex + 1) < line.length())
                {
                    string possible2LetterNumber = line.substr(leftIndex, 2);
                    int possibleIndexValue = searchIn2Letter(possible2LetterNumber);
                    if (possibleIndexValue >= 0)
                    {
                        string possibleValue = numberStrings[possibleIndexValue];
                        string subString = line.substr(leftIndex, possibleValue.length());
                        if (subString.compare(possibleValue) == 0)
                        {
                            leftDigit = numberStrignsValue[possibleIndexValue];
                        }
                        else
                        {
                            leftIndex++;
                        }
                    }
                    else
                    {
                        leftIndex++;
                    }
                }
                else
                {
                    leftIndex++;
                }

                // cout << "rightIndex:" << rightIndex << '\n';
                // cout << "\t line[rightIndex]: " << line[rightIndex] << '\n';

                if (isdigit(line[rightIndex]))
                {
                    rightDigit = int(line[rightIndex] - '0');
                }
                else if ((rightIndex + 1) < line.length())
                {
                    string possible2LetterNumber = line.substr(rightIndex, 2);
                    // cout << "\t possible2LetterNumber: " << possible2LetterNumber << '\n';
                    int possibleIndexValue = searchIn2Letter(possible2LetterNumber);
                    // cout << "\t possibleIndexValue: " << possibleIndexValue << '\n';
                    if (possibleIndexValue >= 0)
                    {
                        string possibleValue = numberStrings[possibleIndexValue];
                        // cout << "\t possibleValue: " << possibleValue << '\n';
                        string subString = line.substr(rightIndex, possibleValue.length());
                        // cout << "\t subString: " << subString << '\n';
                        if (subString.compare(possibleValue) == 0)
                        {
                            rightDigit = numberStrignsValue[possibleIndexValue];
                            // cout << "\t rightDigit: " << rightDigit << '\n';
                        }
                        else
                        {
                            rightIndex--;
                        }
                    }
                    else
                    {
                        rightIndex--;
                    }
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
