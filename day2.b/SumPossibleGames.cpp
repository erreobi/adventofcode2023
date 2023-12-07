#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

//12 red cubes, 13 green cubes, and 14 blue cubes?
const int MAX_BLUE  = 14;
const int MAX_RED   = 12;
const int MAX_GREEN = 13;


struct Subsets {
    int blue;
    int red;
    int green;
};

struct Game {
    int gameNumber;
    bool possible = true;
    int minBlue=0;
    int minRed=0;
    int minGreen=0;
    long power=1;
    std::vector<Subsets> sessions;
};


std::vector<Game> populate (char *filename)
{
    std::ifstream inputFile(filename); // Replace with the actual file name
    std::vector<Game> games; // Store information about each game

    if (!inputFile.is_open()) {
        std::cerr << "Unable to open the file." << std::endl;
        return games;
    }

    std::string line;
    while (std::getline(inputFile, line)) {

        std::cout << "Line: "<<line<<"\n";
        std::string token;
        std::stringstream lineStream (line);

        // GAME Part:
        std::getline(lineStream, token, ':');
        std::cout << "\t token: "<< token<<"\n";

        std::istringstream iss(token);

        Game currentGame;
        // Read "Game 1:" and extracts 1
        iss >> token >> currentGame.gameNumber; // Read "Game", game number, ":"

        std::getline(lineStream, token, ':');
        std::cout << "\t token: "<< token<<"\n";

        //colors part
        std::stringstream tokenStream (token);
        string subToken;

        
        while(std::getline(tokenStream, subToken, ';'))
        {
            std::cout << "\t\t sub token: "<< subToken<<"\n";

            //single color
            std::stringstream subTokenStream (subToken);
            string colorToken;
            std::cout << "\t\t\t sub token: "<< colorToken<<"\n";

            Subsets currentSubset{0, 0, 0};
            while(std::getline(subTokenStream, colorToken, ','))
            {
                std::istringstream iss(colorToken);
                string color;
                int colorValue;

                iss >> colorValue >> color;
                std::cout << "\t\t\t\tsub colorValue: "<< colorValue<<"\n";
                std::cout << "\t\t\t\tsub color: "<< color<<"\n";

                if (color == "blue") {
                    currentSubset.blue = colorValue;
                    if (colorValue > MAX_BLUE)
                    {
                        currentGame.possible = false;
                    }
                    if (colorValue > currentGame.minBlue)
                    {
                        currentGame.minBlue = colorValue;
                    }

                } else if (color == "red") {
                    currentSubset.red = colorValue;
                    if (colorValue > MAX_RED)
                    {
                        currentGame.possible = false;
                    }
                    if (colorValue > currentGame.minRed)
                    {
                        currentGame.minRed = colorValue;
                    }

                } else if (color == "green") {
                    currentSubset.green = colorValue;
                    if (colorValue > MAX_GREEN)
                    {
                        currentGame.possible = false;
                    }
                    if (colorValue > currentGame.minGreen)
                    {
                        currentGame.minGreen = colorValue;
                    }

                }

            }
            currentGame.power=currentGame.minGreen*currentGame.minBlue*currentGame.minRed;
            currentGame.sessions.push_back(currentSubset);

        }

        games.push_back(currentGame);
    }

    inputFile.close();

    // Display the extracted information
    for (const auto& game : games) {
        std::cout << "Game " << game.gameNumber << " ";
        std::cout << "minBlue " << game.minBlue << " ";
        std::cout << "minGreen " << game.minGreen << " ";
        std::cout << "minRed " << game.minRed << " ";
        std::cout << "power " << game.power << " ";
        std::cout << "Possible " << game.possible << ": [";
        for (const auto& session : game.sessions) {
            std::cout << "[" << session.blue << "," << session.red << "," << session.green << "],";
        }
        std::cout << "]" << std::endl;
    }

    return games;
}


int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        std::cerr << "You need to pass the file in input";
        return -1;
    }

    std::vector<Game> games = populate(argv[1]);

    int sum = 0;
    long sumPower = 0;
    for (const auto& game : games) {
        if(game.possible)
            sum+=game.gameNumber;

        sumPower += game.power;
    }   

    std::cout << "SUM: " << sum << std::endl;
    std::cout << "SUM Power: " << sumPower << std::endl;
}