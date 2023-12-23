#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct Almanac
{
    long seed = -1;
    long soil = -1;
    long fertilizer = -1;
    long water = -1;
    long light = -1;
    long temperature = -1;
    long humidity = -1;
    long location = -1;
};

void printAlmanacs(vector<Almanac> almanacs)
{
    for (const auto &almanac : almanacs)
    {
        cout << "seed: " << almanac.seed << " -> ";
        cout << "soil: " << almanac.soil << " -> ";
        cout << "fertilizer: " << almanac.fertilizer << " -> ";
        cout << "water: " << almanac.water << " -> ";
        cout << "light: " << almanac.light << " -> ";
        cout << "temperature: " << almanac.temperature << " -> ";
        cout << "humidity: " << almanac.humidity << " -> ";
        cout << "location: " << almanac.location;
        cout << endl;
    }
}

long mapValueWithRange(long value, long destinationStart, long sourceStart, long range)
{
    cout << "\t\t\t[" << value << "," << destinationStart << "," << sourceStart << "," << range << "]" << endl;
    long sourceEnd = sourceStart + range - 1;
    cout << "\t\t\tsourceEnd:" << sourceEnd << endl;

    if (value >= sourceStart && value <= sourceEnd)
    {
        long mapping = value - sourceStart;
        cout << "\t\t\t NEW VALUE:" << destinationStart + mapping << endl;
        return destinationStart + mapping;
    }
    else
    {
        return value;
    }
}

void mapVectorValueWithRange(vector<Almanac> &almanac, vector<long> ranges, int whichValue)
{
    // printAlmanacs(almanac);
    for (int index = 0; index < almanac.size(); index++)
    {
        switch (whichValue)
        {
        case 0:                                                                          // SOIL MAPPING
            if (almanac[index].soil == -1 || almanac[index].soil == almanac[index].seed) // if you didn't find any range, you can search
            {
                almanac[index].soil = (mapValueWithRange(almanac[index].seed, ranges[0], ranges[1], ranges[2]));
            }
            break;
        case 1: // fertilizer MAPPING
            if (almanac[index].fertilizer == -1 || almanac[index].fertilizer == almanac[index].soil)
            {
                almanac[index].fertilizer = (mapValueWithRange(almanac[index].soil, ranges[0], ranges[1], ranges[2]));
            }
            break;
        case 2: // fertilizer WATER
            if (almanac[index].water == -1 || almanac[index].water == almanac[index].fertilizer)
            {
                almanac[index].water = (mapValueWithRange(almanac[index].fertilizer, ranges[0], ranges[1], ranges[2]));
            }
            break;
        case 3: // fertilizer light
            if (almanac[index].light == -1 || almanac[index].light == almanac[index].water)
            {
                almanac[index].light = (mapValueWithRange(almanac[index].water, ranges[0], ranges[1], ranges[2]));
            }
            break;
        case 4: // fertilizer temperature
            if (almanac[index].temperature == -1 || almanac[index].temperature == almanac[index].light)
            {
                almanac[index].temperature = (mapValueWithRange(almanac[index].light, ranges[0], ranges[1], ranges[2]));
            }
            break;
        case 5: // fertilizer humidity
            if (almanac[index].humidity == -1 || almanac[index].humidity == almanac[index].temperature)
            {
                almanac[index].humidity = (mapValueWithRange(almanac[index].temperature, ranges[0], ranges[1], ranges[2]));
            }
            break; 
        case 6: // fertilizer location
            if (almanac[index].location == -1 || almanac[index].location == almanac[index].humidity)
            {
                almanac[index].location = (mapValueWithRange(almanac[index].humidity, ranges[0], ranges[1], ranges[2]));
            }
            break;            

        default:
            break;
        }
    }
    // printAlmanacs(almanac);
}

void parsingMaps(string line, int type, vector<Almanac> &almanacs)
{

    std::stringstream lineStream(line);
    cout << "\t\t";
    vector<long> mappings;
    for (long seedMaps; lineStream >> seedMaps;)
    {
        cout << seedMaps << " ";
        mappings.push_back(seedMaps);
    }
    cout << endl;

    mapVectorValueWithRange(almanacs, mappings, type);
}

std::vector<Almanac> populate(char *filename)
{
    std::ifstream inputFile(filename); // Replace with the actual file name
    std::vector<Almanac> almanacs;     // Store information about each game

    if (!inputFile.is_open())
    {
        std::cerr << "Unable to open the file." << std::endl;
        return almanacs;
    }

    std::string line;
    std::getline(inputFile, line);
    std::cout << "Line: " << line << endl;
    std::string seedToken;
    std::stringstream lineStream(line);

    // SEEDS
    std::getline(lineStream, seedToken, ':'); // it reads the string seeds
    std::getline(lineStream, seedToken, ':'); // it reads the number seed
    std::stringstream seedStream(seedToken);
    for (long i; seedStream >> i;)
    {
        Almanac almanac;
        almanac.seed = i;

        almanacs.push_back(almanac);
    }

    long lowestLocationNumber = LLONG_MAX;

    while (std::getline(inputFile, line))
    {
        std::cout << "Line: " << line << endl;
        if (line.compare("seed-to-soil map:") == 0)
        { // SOIL
            std::cout << "\tFound seed-to-soil map" << endl;

            getline(inputFile, line);
            while (!line.empty())
            {
                cout << "\tparsing SOIL [" << line << "]" << endl;
                parsingMaps(line, 0, almanacs);

                std::getline(inputFile, line);
            }
        }
        else if (line.compare("soil-to-fertilizer map:") == 0)
        { // fertilizer
            std::cout << "\tFound fertilizer map" << endl;

            std::getline(inputFile, line);
            while (!line.empty())
            {
                cout << "\tparsing fertilizer [" << line << "]" << endl;
                parsingMaps(line, 1, almanacs);

                std::getline(inputFile, line);
            }
        }
        else if (line.compare("fertilizer-to-water map:") == 0)
        { // fertilizer
            std::cout << "\tFound water map" << endl;

            std::getline(inputFile, line);
            while (!line.empty())
            {
                cout << "\tparsing water [" << line << "]" << endl;
                parsingMaps(line, 2, almanacs);

                std::getline(inputFile, line);
            }
        }
        // water-to-light map:
        else if (line.compare("water-to-light map:") == 0)
        { // fertilizer
            std::cout << "\tFound light map" << endl;

            std::getline(inputFile, line);
            while (!line.empty())
            {
                cout << "\tparsing light [" << line << "]" << endl;
                parsingMaps(line, 3, almanacs);

                std::getline(inputFile, line);
            }
        }
        // light-to-temperature map:
        else if (line.compare("light-to-temperature map:") == 0)
        { // fertilizer
            std::cout << "\tFound temperature map" << endl;

            std::getline(inputFile, line);
            while (!line.empty())
            {
                cout << "\tparsing temperature [" << line << "]" << endl;
                parsingMaps(line, 4, almanacs);

                std::getline(inputFile, line);
            }
        }
        // temperature-to-humidity map:
        else if (line.compare("temperature-to-humidity map:") == 0)
        { // fertilizer
            std::cout << "\tFound humidity map" << endl;

            std::getline(inputFile, line);
            while (!line.empty())
            {
                cout << "\tparsing humidity [" << line << "]" << endl;
                parsingMaps(line, 5, almanacs);

                std::getline(inputFile, line);
            }
        }
        // humidity-to-location map:
        else if (line.compare("humidity-to-location map:") == 0)
        { // fertilizer
            std::cout << "\tFound location map" << endl;

            std::getline(inputFile, line);
            while (!line.empty())
            {
                cout << "\tparsing location [" << line << "]" << endl;
                parsingMaps(line, 6, almanacs);

                std::getline(inputFile, line);
            }
        }
    }

    printAlmanacs(almanacs);

    for (const auto &almanac : almanacs)
    {
        if (almanac.location <= lowestLocationNumber)
        {
            lowestLocationNumber=almanac.location;
        }   
    }

    cout<<endl<<"LOWEXT LOCATION: "<<lowestLocationNumber<<endl;


    return almanacs;
}

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        std::cerr << "You need to pass the file in input";
        return -1;
    }

    std::vector<Almanac> almanacs = populate(argv[1]);
}