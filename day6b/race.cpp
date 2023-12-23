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
    unsigned long time;
    unsigned long distance;

    Race(unsigned long s, unsigned long l) : time(s), distance(l) {}
};

/*
Time:      7  15   30
Distance:  9  40  200
*/
vector<Race> racesTest{Race(71530, 940200)};

/*
Time:        56     97     77     93
Distance:   499   2210   1097   1440
*/
vector<Race> races{Race(56977793, 499221010971440)};

int main(int argc, char *argv[])
{
    unsigned long margin = 1;

     unsigned long printEvery1000timea = 1;

    for (const auto &race : races){
        
        unsigned long records = 0;
        // cout << endl;
        for (unsigned long velocity = 1; velocity < race.time; velocity ++){

            unsigned long distance = (race.time-velocity)*velocity;
            if (distance > race.distance){
                
                if ((printEvery1000timea%100)==0)
                 {   cout<<velocity<<" -> "<<distance<<" -> "<< records<< "\r";}
                
                records++;
            }

            printEvery1000timea++;

        }
        cout << endl;

        // cout << "\tnumber of records: "<< records << endl; 

        margin *= records;

    }

    cout << "number of ways you can beat the record: "<<   margin<<endl; 

    return 0;
}
