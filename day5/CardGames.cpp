#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// 12 red cubes, 13 green cubes, and 14 blue cubes?
const int MAX_BLUE = 14;
const int MAX_RED = 12;
const int MAX_GREEN = 13;

struct Card
{
    int cardNumber;
    int quantity = 1;
    std::vector<int> winningNumbers;
    std::vector<int> yourNumber;
};

std::vector<Card> populate(char *filename)
{
    std::ifstream inputFile(filename); // Replace with the actual file name
    std::vector<Card> games;           // Store information about each game

    if (!inputFile.is_open())
    {
        std::cerr << "Unable to open the file." << std::endl;
        return games;
    }

    std::string line;
    while (std::getline(inputFile, line))
    {

        std::cout << "Line: " << line << "\n";
        std::string token;
        std::stringstream lineStream(line);

        // GAME Part:
        std::getline(lineStream, token, ':');
        std::cout << "\t token: " << token << "\n";

        std::istringstream iss(token);

        Card currentCard;
        // Read "Game 1:" and extracts 1
        iss >> token >> currentCard.cardNumber; // Read "Game", game number, ":"

        //.. it takes the second token
        std::getline(lineStream, token, ':');
        std::cout << "\t token: " << token << "\n";

        // number part
        std::stringstream tokenStream(token);
        string subToken;

        int whichNumber = 0;
        while (std::getline(tokenStream, subToken, '|'))
        {
            std::cout << "\t\t sub token: " << subToken << "\n";
            // string number;

            std::stringstream subTokenStream(subToken);
            // while (getline(subTokenStream,number,' '))
            // {
            //     std::cout << "\t\t\t number ["<< number<<"]\n";
            // }

            int number = 0;
            while (subTokenStream >> number)
            {
                if (whichNumber == 0)
                {
                    currentCard.winningNumbers.push_back(number);
                }
                else
                {
                    currentCard.yourNumber.push_back(number);
                }
                std::cout << "\t\t\t number [" << number << "]\n";
            }

            whichNumber++;
        }

        games.push_back(currentCard);
    }

    inputFile.close();

    // Display the extracted information
    for (const auto &game : games)
    {
        cout << "Card: " << game.cardNumber << " ";
        for (const auto &winNum : game.winningNumbers)
        {
            cout << "" << winNum << " ";
        }
        cout << "| ";
        for (const auto &yourNum : game.yourNumber)
        {
            cout << "" << yourNum << " ";
        }
        cout<<endl;
    }
cout<<endl;
    return games;
}

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        std::cerr << "You need to pass the file in input";
        return -1;
    }

    std::vector<Card> games = populate(argv[1]);

    int sum = games.size();
    
    for (const auto &game : games)
    {   
        // double winning = 0.5;
        int howManyMatchning = 0;
        for (const auto &yourNum : game.yourNumber)
        {
            for (const auto &winNum : game.winningNumbers)
            {
                if (yourNum == winNum)
                {
                   // cout << "" << yourNum << " ";
                    // winning *= 2;
                    howManyMatchning++;
                }
            }
        }

        cout<< "Card " << game.cardNumber << " has generated "<<howManyMatchning<<" card"<<endl;
        cout<< "\tit is "<<game.quantity<<" duplicate so it generates "<<game.quantity<<" each cards"<<endl;

        sum += game.quantity*howManyMatchning;
        
        int indexCardNumber = game.cardNumber;
        for (int index = 1; indexCardNumber < games.size() && index <= howManyMatchning; index++, indexCardNumber++){
            cout<< "\t\tit has generated "<<games[indexCardNumber].quantity<<" card of " << games[indexCardNumber].cardNumber <<endl;
            games[indexCardNumber].quantity += game.quantity;
             cout<< "\t\tCard "<<games[indexCardNumber].cardNumber<<" has now " << games[indexCardNumber].quantity <<endl;
        }

        // if (winning >= 1)
        // {    
        //     sum += winning;
        //     cout <<"winning: "<< winning<< endl;
        // }
    }

    
    int empiricSum = 0;
        // Display the extracted information
    for (const auto &game : games)
    {
        cout << "Card: " << game.cardNumber << " ";
        cout << "quantity: " << game.quantity << " ";
        empiricSum += game.quantity;
        for (const auto &winNum : game.winningNumbers)
        {
            cout << "" << winNum << " ";
        }
        cout << "| ";
        for (const auto &yourNum : game.yourNumber)
        {
            cout << "" << yourNum << " ";
        }
        cout<<endl;
    }

    std::cout << "SUM: " << sum << std::endl;
    std::cout << "Empirc: " << empiricSum << std::endl;
}