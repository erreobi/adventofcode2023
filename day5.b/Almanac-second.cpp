#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <list>

using namespace std;

struct Range
{
    unsigned long start;
    unsigned long length;
    unsigned long end = (start + length - 1) > 0 ? (start + length - 1) : 0;

    Range(unsigned long s, unsigned long l) : start(s), length(l)
    {
        if (start < 0)
            cerr << "ERROR start < 0";
        if (length <= 0)
            cerr << "ERROR length <= 0";
    }
};

struct Map
{
    Range destination;
    Range source;

    Map(unsigned long d, unsigned long s, unsigned long l) : destination(d, l), source(s, l)
    {
    }
};

struct Almanac
{
    vector<Range> seeds;
    list<vector<Map>> maps;
    vector<Map> soils;
    vector<Map> fertilizers;
    vector<Map> waters;
    vector<Map> lights;
    vector<Map> temperatures;
    vector<Map> humiditys;
    vector<Map> locations;
};

ostream &operator<<(ostream &os, const Range &range)
{
    return os << "[" << range.start << "," << range.length << "]";
}

bool operator==(const Range &lhs, const Range &rhs)
{
    return lhs.start == rhs.start && lhs.length == rhs.length;
}

ostream &operator<<(ostream &os, const Map &map)
{
    return os << "{" << map.destination << "," << map.source << "}";
}

ostream &operator<<(ostream &os, const vector<Range> &map)
{
    os << "[";
    for (const auto &almanac : map)
    {
        os << almanac << ",";
    }
    return os << "]";
}
ostream &operator<<(ostream &os, const vector<Map> &maps)
{
    os << "{";
    for (const auto &map : maps)
    {
        os << "(" << map.destination << "," << map.source << "),";
    }
    return os << "}";
}
ostream &operator<<(ostream &os, const list<vector<Map>> &maps)
{
    os << "{";
    for (const auto &map : maps)
    {
        os << map << "," << endl;
    }
    return os << "}";
}

ostream &operator<<(ostream &os, const Almanac &almanac)
{
    return os << "seeds:        " << almanac.seeds << endl
              << "soils:        " << almanac.soils << endl
              << "fertilizers:  " << almanac.fertilizers << endl
              << "waters:       " << almanac.waters << endl
              << "lights:       " << almanac.lights << endl
              << "temperatures: " << almanac.temperatures << endl
              << "humiditys:    " << almanac.humiditys << endl
              << "locations:    " << almanac.locations
              << endl
              << almanac.maps
              << endl;
}

bool mapCompare(const Map &a, const Map &b)
{
    return a.destination.start < b.destination.start;
}

Map parsingMaps(string line)
{

    std::stringstream lineStream(line);
    // ROB//ROBcout << "\t\t";
    vector<unsigned long> mappings;
    for (unsigned long seedMaps; lineStream >> seedMaps;)
    {
        // ROB//ROBcout << seedMaps << " ";
        mappings.push_back(seedMaps);
    }
    // ROB//ROBcout << endl;

    Map map(mappings[0], mappings[1], mappings[2]);

    return map;
}

Almanac populate(char *filename)
{
    std::ifstream inputFile(filename); // Replace with the actual file name
    Almanac almanac;                   // Store information about each game

    if (!inputFile.is_open())
    {
        std::cerr << "Unable to open the file." << std::endl;
        return almanac;
    }

    std::string line;
    std::getline(inputFile, line);
    // ROB//ROBcout << "Line1: " << line << endl;
    std::string seedToken;
    std::stringstream lineStream(line);

    // SEEDS
    std::getline(lineStream, seedToken, ':'); // it reads the string seeds
    std::getline(lineStream, seedToken, ':'); // it reads the number seed
    std::stringstream seedStream(seedToken);

    vector<Range> ranges;
    for (unsigned long i, j; seedStream >> i >> j;)
    {

        Range seed(i, j);
        ranges.push_back(seed);
    }

    almanac.seeds = ranges;

    while (std::getline(inputFile, line))
    {

        // ROB//ROBcout << "Line: " << line << endl;
        if (line.compare("seed-to-soil map:") == 0)
        {
            vector<Map> maps;
            // ROB//ROBcout << "\tFound " <<line<<endl;

            getline(inputFile, line);
            while (!line.empty())
            {
                maps.push_back(parsingMaps(line));
                std::getline(inputFile, line);
            }
            std::sort(maps.begin(), maps.end(), mapCompare);
            almanac.maps.push_back(maps);
            almanac.soils = maps;
        }
        else if (
            line.compare("soil-to-fertilizer map:") == 0)
        {
            vector<Map> maps;
            // ROB//ROBcout << "\tFound " <<line<<endl;

            getline(inputFile, line);
            while (!line.empty())
            {
                maps.push_back(parsingMaps(line));
                std::getline(inputFile, line);
            }
            std::sort(maps.begin(), maps.end(), mapCompare);
            almanac.maps.push_back(maps);
            almanac.fertilizers = maps;
        }
        else if (
            line.compare("fertilizer-to-water map:") == 0)
        {
            vector<Map> maps;
            // ROB//ROBcout << "\tFound " <<line<<endl;

            getline(inputFile, line);
            while (!line.empty())
            {
                maps.push_back(parsingMaps(line));
                std::getline(inputFile, line);
            }
            std::sort(maps.begin(), maps.end(), mapCompare);
            almanac.maps.push_back(maps);
            almanac.waters = maps;
        }
        else if (
            line.compare("water-to-light map:") == 0)
        {
            vector<Map> maps;
            // ROB//ROBcout << "\tFound " <<line<<endl;

            getline(inputFile, line);
            while (!line.empty())
            {
                maps.push_back(parsingMaps(line));
                std::getline(inputFile, line);
            }
            std::sort(maps.begin(), maps.end(), mapCompare);
            almanac.maps.push_back(maps);
            almanac.lights = maps;
        }
        else if (
            line.compare("light-to-temperature map:") == 0)
        {
            vector<Map> maps;
            // ROB//ROBcout << "\tFound " <<line<<endl;

            getline(inputFile, line);
            while (!line.empty())
            {
                maps.push_back(parsingMaps(line));
                std::getline(inputFile, line);
            }
            std::sort(maps.begin(), maps.end(), mapCompare);
            almanac.maps.push_back(maps);
            almanac.temperatures = maps;
        }
        else if (
            line.compare("temperature-to-humidity map:") == 0)
        {
            vector<Map> maps;
            // ROB//ROBcout << "\tFound " <<line<<endl;

            getline(inputFile, line);
            while (!line.empty())
            {
                maps.push_back(parsingMaps(line));
                std::getline(inputFile, line);
            }
            std::sort(maps.begin(), maps.end(), mapCompare);
            almanac.maps.push_back(maps);
            almanac.humiditys = maps;
        }
        else if (
            line.compare("humidity-to-location map:") == 0)
        {
            vector<Map> maps;
            // ROB//ROBcout << "\tFound " <<line<<endl;

            getline(inputFile, line);
            while (!line.empty())
            {
                maps.push_back(parsingMaps(line));
                std::getline(inputFile, line);
            }
            std::sort(maps.begin(), maps.end(), mapCompare);
            almanac.maps.push_back(maps);
            almanac.locations = maps;
        }
    }

    return almanac;
}


void function1(Almanac almanac)
{

    // Search from the locatin 0 till it will find somthing
    bool foundMinLocation = false;
    for (unsigned long tryLocation = 0; !foundMinLocation; tryLocation++)
    {
        cout << "Location to try: " << tryLocation << endl;
        unsigned long transformValue = tryLocation;
        // start from the location and end to the soil
        for (std::list<vector<Map>>::reverse_iterator rit = almanac.maps.rbegin(); rit != almanac.maps.rend(); ++rit)
        {
            vector<Map> mapRanges = *rit;
            // search on each range mapping
            for (const auto &mapRange : mapRanges)
            {
                // cout << "\tSearch on this range:" << mapRange << endl;
                if (mapRange.destination.start <= transformValue &&
                    mapRange.destination.end >= transformValue)
                {
                    // cout << "\tFound a possible range" << mapRange << endl;
                    transformValue = mapRange.source.start + (transformValue - mapRange.destination.start);
                    break;
                }
                else
                {
                    // cout << "\tNot Found a possible range" << endl;
                    transformValue = transformValue; // Useles code ... but it helps to understand it.
                }
            }
            // cout << "For this session of mapping the value is: " << transformValue;
            cout << endl;
        }

        // cout << "So, the possible sees is: " << transformValue << endl;
        // Now the transformValue should have the possible SEED value, we should chec if it is a valid number
        for (const auto &seedRange : almanac.seeds)
        {
            // cout << "\t searcing in " << seedRange;
            if (seedRange.start <= transformValue &&
                seedRange.end >= transformValue)
            {
                cout << "\t FOUND!! " << transformValue << endl;
                foundMinLocation = true;
                cout << "The min location is " << tryLocation << endl;
            }
        }

        if (!foundMinLocation)
        {
            // cout << "The location " << tryLocation << " hasn't a valid seed" << endl;
        }

        // cout<<"------------------"<<endl;
        // cout<<"------------------"<<endl;
        //return;
    }


}

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        std::cerr << "You need to pass the file in input";
        return -1;
    }

    Almanac almanac = populate(argv[1]);

    cout << "ALMANAC: " << almanac << endl;

    function1(almanac);

    // cout << "LOCATION: " << mapLocationFromSeed(almanac.seeds, almanac)<< endl;

    return 0;
}
