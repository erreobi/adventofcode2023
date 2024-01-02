#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <list>
#include <map>
#include <numeric>

using namespace std;

struct Analisys
{

    vector<vector<long>> foreSees;
    long estimation = 0;

    Analisys(vector<long> r)
    {
        foreSees.push_back(r);
    }

    void add(vector<long> r)
    {
        foreSees.push_back(r);
    }

    void update(long e)
    {
        estimation = e;
    }
};

vector<Analisys> reports;

ostream &operator<<(ostream &strm, Analisys tt)
{

    for (const auto &A : tt.foreSees)
    {
        for (const auto &V : A)
        {
            strm << V << " ";
        }
        strm << endl;
    }
    strm << endl;
    strm << "Estimation: " << tt.estimation << endl
         << endl;

    return strm;
}

ostream &operator<<(ostream &strm, vector<Analisys> tt)
{
    for (const Analisys &report : tt)
    {

        strm << report;
    }
    return strm << endl;
}

int calcRecForesee(long *analisys, long size)
{
    if (size == 0)
        return -1;

    bool allzero = true;
    long difference[size-1];
    for (long j = (size-1); j > 0; j--)
    {
        allzero &= (analisys[j] == 0);
        difference[j-1]=(analisys[j] - analisys[j-1]);
    }

    if (allzero)
        return 0;

    return analisys[0] - calcRecForesee(difference, size-1);
}

void calulareForesee()
{
    long totEstimation = 0;
    for (auto &report : reports)
    {
        long foreseevalue = calcRecForesee(&(report.foreSees[0][0]), report.foreSees[0].size());
        totEstimation += foreseevalue;
        report.update(foreseevalue);
    }

    cout << reports;
    cout << "TOT: " << totEstimation << endl;
}

void calulareForeseeold()
{

    for (auto &report : reports)
    {

        for (long j = 0; j < report.foreSees.size(); j++)
        {
            vector<long> &analisys = report.foreSees[j];

            bool allzero = false;
            vector<long> newDiff;
            for (long i = 0; i < analisys.size(); i++)
            {
                long diff = 0;
                if ((i + 1) < analisys.size())
                {
                    diff = analisys[i + 1] - analisys[i];
                    if (diff != 0)
                    {
                        allzero = false;
                    }
                    else
                    {
                        allzero = true;
                    }

                    newDiff.push_back(diff);
                }
            }

            if (!allzero)
            {
                report.add(newDiff);
                // cout << report;
            }
        }
    }

    long totEstimation = 0;
    for (auto &report : reports)
    {
        long estimation = 0;
        for (long j = 0; j < report.foreSees.size(); j++)
        {
            vector<long> &analisys = report.foreSees[j];
            estimation += analisys[(analisys.size() - 1)];
            // report.foreSees[j].push_back(estimation);
        }

        report.update(estimation);
        totEstimation += estimation;
        cout << "Est: " << estimation << endl;
    }

    cout << reports;
    cout << "TOT: " << totEstimation << endl;
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

    string line;
    string uselessChar;

    while (getline(inputFile, line))
    {
        istringstream iss(line);
        long node;
        vector<long> oneReport;

        while (iss >> node)
        {
            // cout << node << " ";
            oneReport.push_back(node);
        }

        Analisys analisys(oneReport);
        reports.push_back(analisys);

        // cout << endl;
    }

    // cout << reports;

    calulareForesee();

    return 0;
}
