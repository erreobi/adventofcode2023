#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <list>

using namespace std;

struct Race
{
    int time;
    int distance;

    Race(unsigned long s, unsigned long l) : time(s), distance(l) {}
};

/*
Time:      7  15   30
Distance:  9  40  200
*/
vector<Race> racesTest{Race(7, 9),
                   Race(15, 40),
                   Race(30, 200)};

/*
Time:        56     97     77     93
Distance:   499   2210   1097   1440
*/
vector<Race> races{Race(56, 499),
                   Race(97, 2210),
                   Race(77, 1097),
                   Race(93,1440)};

int main(int argc, char *argv[])
{
    long margin = 1;

    for (const auto &race : races){
        
        int records = 0;
        cout << endl;
        for (int velocity = 1; velocity < race.time; velocity ++){

            int distance = (race.time-velocity)*velocity;
            if (distance > race.distance){
                cout<<"\t"<<velocity<<" -> "<<distance<< endl;
                records++;
            }

        }
        cout << endl;

        cout << "\tnumber of records: "<< records << endl; 

        margin *= records;

    }

    cout << "number of ways you can beat the record: "<<   margin; 

    return 0;
}
