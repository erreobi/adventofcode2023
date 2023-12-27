#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <list>
#include <map>

using namespace std;

const vector<char> strenght{'J', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'Q', 'K', 'A'};

int strength(char cCard)
{
    for (int i = 0; i <= strenght.size(); i++)
    {
        if (cCard == strenght[i])
        {
            return i;
        }
    }
    return -1;
}

enum Type
{
    Five_of_a_kind = 7,
    Four_of_a_kind = 6,
    Full_house = 5,
    Three_of_a_kind = 4,
    Two_pair = 3,
    One_pair = 2,
    High_card = 1,
    Null_Hand = 0
};

ostream &operator<<(ostream &strm, Type tt)
{
    const string nameTT[] = {"Null_Hand", "High_card", "One_pair", "Two_pair", "Three_of_a_kind", "Full_house", "Four_of_a_kind", "Five_of_a_kind"};
    return strm << nameTT[tt];
}

int countCharInString(string str_V, char chr)
{
    int numberofChar = 0;

    for (int i = 0; i <= str_V.length(); i++)
    {
        if (str_V[i] == chr)
        {
            numberofChar++;
        }
    }

    return numberofChar;
}

struct Hand
{
    string cards;
    unsigned long bid;
    Type type;

    Hand(string s, unsigned long l) : cards(s), bid(l)
    {
        string sortedcards;
        int howManyJs = 0;
        // I will remove all the Jokers fro the hand. I will count them
        for (int index = 0; index < cards.length(); index++)
        {
            if (cards[index] == 'J' || cards[index] == 'j')
            {
                howManyJs++;
            }
            else
            {
                sortedcards.push_back(cards[index]);
            }
        }

        sort(sortedcards.begin(), sortedcards.end());

        bool checkAllCards = false;

        for (int index = 0; index < sortedcards.length() && !checkAllCards; index++)
        {
            char lstFodn = sortedcards[index];
            // int lstFdn = 1;
            int second = 0;

            int repitation = countCharInString(sortedcards, lstFodn);
            switch (repitation)
            {
            case 5:
                type = Type::Five_of_a_kind;
                checkAllCards = true;
                /* code */
                break;
            case 4:
                type = Type::Four_of_a_kind;
                checkAllCards = true;
                /* code */
                break;
            case 3:
                // if there aresn't enough cards
                if ((index + 3) >= sortedcards.length())
                {
                    type = Type::Three_of_a_kind;
                    checkAllCards = true;
                }
                else
                {
                    lstFodn = sortedcards[index + 3];
                    second = countCharInString(&sortedcards[index + 3], lstFodn);

                    if (second == 2)
                    {
                        type = Type::Full_house;
                        checkAllCards = true;
                    }
                    else
                    {
                        type = Type::Three_of_a_kind;
                        checkAllCards = true;
                    }
                }
                break;
            case 2:
                if ((index + 2) >= sortedcards.length())
                {
                    type = Type::One_pair;
                    checkAllCards = true;
                }
                else
                {
                    lstFodn = sortedcards[index + 2];
                    second = countCharInString(&sortedcards[index + 2], lstFodn);
                    if (second == 3)
                    {
                        type = Type::Full_house;
                        checkAllCards = true;
                    }
                    else if (second == 2)
                    {
                        type = Type::Two_pair;
                        checkAllCards = true;
                    }
                    else if ((index + 3) >= sortedcards.length())
                    { // the cards are finished
                        type = Type::One_pair;
                        checkAllCards = true;
                    }
                    else
                    {
                        // vediamo il prossimo prossimo
                        lstFodn = sortedcards[index + 3];
                        int third = countCharInString(&sortedcards[index + 3], lstFodn);
                        if (third == 2)
                        {
                            type = Type::Two_pair;
                            checkAllCards = true;
                        }
                        else
                        {
                            type = Type::One_pair;
                            checkAllCards = true;
                        }
                    }
                }

                break;
            default:
                type = Type::High_card;
                checkAllCards = false;
                break;
            }
        }

        if (howManyJs > 0)
        {
            if (howManyJs == 5)
            {
                type = Type::Five_of_a_kind;
            }else 
            if (type == Type::Two_pair)
            {
                type = Type::Full_house;
            }
            else
            {
                for (int index = 1; index <= howManyJs; index++)
                {
                    type = (Type)(type + 1);
                    if (type == Type::Two_pair || type == Type::Full_house)
                    {
                        type = (Type)(type + 1);
                    }
                }
            }
        }
    }
};
ostream &operator<<(ostream &os, const Hand &hand)
{
    return os << "[" << hand.cards << "," << hand.bid << ", " << hand.type << "]";
}

bool handCompare(const Hand &a, const Hand &b)
{
    if (a.type == b.type)
    {
        for (int index = 0; index < a.cards.length(); index++)
        {
            if (a.cards[index] != b.cards[index])
            {
                int strengthA = strength(a.cards[index]);
                int strengthB = strength(b.cards[index]);

                return strengthA < strengthB;
            }
        }
        // if they are identical
        return strength(a.cards[0]) < strength(b.cards[0]);
    }
    else
    {
        return a.type < b.type;
    }
}

vector<Hand> hands;
ostream &operator<<(ostream &os, const vector<Hand> &map)
{
    os << "{";
    for (const auto &almanac : map)
    {
        os << almanac << ",";
    }
    return os << "}";
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

    std::string line;
    while (std::getline(inputFile, line))
    {
        std::istringstream iss(line);
        string cards;
        unsigned long bid;
        iss >> cards >> bid;

        Hand hand(cards, bid);
        hands.push_back(hand);
    }

    sort(hands.begin(), hands.end(), handCompare);
    cout << hands << endl;

    unsigned long winning = 0;
    for (int index = 0; index < hands.size(); index++)
    {
        winning += hands[index].bid * (index + 1);
        cout << (index + 1) << ")" << hands[index]
             << " = " << (hands[index].bid * (index + 1))
             << " -> " << winning
             << endl;
    }

    cout << "WIN: " << winning << endl;
    return 0;
}
