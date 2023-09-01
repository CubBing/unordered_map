/*
Name: Yujesh Joshi, NSHE: 2001780531, Section 1001/1003, Assignment 5
Description: poker game
Input: txt file
Output: a poker game
*/

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <vector>
#include <string>

using namespace std;

class cardCompare
{
    public:
        bool operator()(const string& c1, const string& c2) const
        { //map to go through all cases
            map<string, int> cards;
            cards["2"] = 2;
            cards["3"] = 3;
            cards["4"] = 4;
            cards["5"] = 5;
            cards["6"] = 6;
            cards["7"] = 7;
            cards["8"] = 8;
            cards["9"] = 9;
            cards["10"] = 10;
            cards["J"] = 11;
            cards["Q"] = 12;
            cards["K"] = 13;
            cards["A"] = 14;

            if (cards[c1] < cards[c2]) //c1 must be before c2
            {
                return true;
            }
            
            return false;
        }
};

int main()
{
    //declaration of all variables
    unordered_map<string, int> face;
    unordered_map<string, int> suits;
    map<string, int, cardCompare> cardSorted;
    vector<string> currentHand;
    string card;

    cout << "Welcome to video poker" << endl;

    cout << "Time to randomly generate hand" << endl;
    cout << "Ahem ... please enter the 5 cards" << endl;

    for (int i = 0; i < 5; i++)
    { //standard input of all cards
        cin >> card;
        currentHand.push_back(card);
    }


    cout << "\n\nCurrent hand\n\n";

    for (int i = 0; i < 5; i++)
    { //outputs the current hand we have 
        cout << "[" << i << "] : " << currentHand[i] << endl;
    }

    cout << endl << endl;

    int selection = 0;
    int loop = 0;

    while (loop < 5) //loop through the 5 choices 
    {
        cout << "Enter the index of cards you do not want" << endl;
        cout << "Enter -1 to stop: ";
        cin >> selection; //input the index we want to change
        cout << endl;

        if (selection == -1)
        { //break if -1 is selected 
            break;
        }

        cout << "Enter new card: ";
        cin >> card;
        cout << endl;

        currentHand.at(selection) = card; //swap the card at index

        loop++;
    }


    cout << "Final Hand\n\n";

    for (int i = 0; i < 5; i++) //we output our final hand as well as add keys to map
    {
        cout << currentHand[i] << " ";

        if (currentHand[i].length() > 2)
        { //check to see if the card 10 is picked
            face["10"]++; //increment key value
            suits[currentHand[i].substr(2, 1)]++; //increment suits value
            cardSorted["10"]++; //increment sorting map key value
        }
        else
        {
            face[currentHand[i].substr(0, 1)]++; //increment key value
            suits[currentHand[i].substr(1, 1)]++; //increment suits value
            cardSorted[currentHand[i].substr(0, 1)]++; //increment sorting map key value
        }

    }

    cout << endl;

    int temp;
    //checks to see if the last value is a letter value or not
    //if a last value is a letter value, we assign a temp int accordingly for later use
    if (cardSorted.rbegin()->first == "J")
    {
        temp = 11;  //assign 11 to J
    }
    else if (cardSorted.rbegin()->first == "Q")
    {
        temp = 12;  //assign 12 to Q
    }
    else if (cardSorted.rbegin()->first == "K")
    {
        temp = 13;  //assign 13 to K
    }
    else if (cardSorted.rbegin()->first == "A")
    {
        temp = 14;  //assign 14 to A
    }
    else
    {
        temp = atoi(cardSorted.rbegin()->first.c_str()); //if not a letter than make temp the biggest value
    }

    int difference = temp - atoi(cardSorted.begin()->first.c_str()); //find the difference for a straight


    for (auto t : cardSorted) //our loop to check for hand rank 
    {
        if (suits.size() == 1) //first check is to see if a flush is valid
        {
            if (cardSorted.size() == 5 && difference == 4) //next check is for a straight flush 
            {
                if (cardSorted.rbegin()->first == "A") //check for royal flush
                {
                    cout << "ROYAL FLUSH!!!!!!!!!!!!!" << endl;
                    return 0;
                }
                else //if not royal flush we know it's a straight flush
                {
                    cout << cardSorted.rbegin()->first << "high straight flush" << endl;
                    return 0;
                }
            }
            //if it isn't one of those then we know it is a flush
            cout << "Flush: " << cardSorted.rbegin()->first << " high" << endl; 
            return 0;
        }
        if (cardSorted.size() == 5 && difference == 4) //straight check
        {
            cout << "Straight: " << cardSorted.begin()->first << " to " << cardSorted.rbegin()->first << endl;
            return 0;
        }
        if (cardSorted.size() == 5)
        {
            cout << cardSorted.rbegin()->first << " High" << endl; //high card check
            return 0;
        }
        if (cardSorted.size() == 4 && t.second == 2)
        { //check to see if a pair is valid 
            cout << "Pair: " << t.first << endl;
            return 0;
        }
        if (cardSorted.size() == 3)
        { //since size 3 means a 2 pair or a three of a kind we split
            if (t.second == 2) //if a value of the key is 2 it will be two pair
            {
                cout << "Two pair:";

                for (auto c = cardSorted.end(); c != cardSorted.begin(); c--)
                { //iterate through backwards to get the greatest value first
                  //this ends before the very first index, so we have to add a check for the first
                    if (c->second == 2)
                    {
                        cout << " " << c->first;
                    }
                }

                if (cardSorted.begin()->second == 2)
                { //if the first index is valid
                    cout << " " << cardSorted.begin()->first;
                }

                return 0;
            }
            else if (t.second == 3)
            { //if not two of pair, must be three of a kind 
                cout << "Three of a kind: " << t.first << endl;
                return 0;
            }
        }
        if (cardSorted.size() == 2)
        { //size 2 means it could be either 4 of kind or full house, split up
            if (t.second == 4)
            { //if a key has a value of 4 we know it's 4 of a kind 
                cout << "4 of a kind: " << t.first << endl;
                return 0;
            }
            else
            { //if not 4 of a kind it must be full house 
                cout << "Full house: ";
                if (cardSorted.begin()->second == 3)
                { //check to see which one of the 2 keys has the value of 3 
                    cout << cardSorted.begin()->first << " over " << cardSorted.rbegin()->first;
                }
                else
                {
                    cout << cardSorted.rbegin()->first << " over " << cardSorted.begin()->first;
                }

                return 0;
            }
        }
    }

    return 0;
}

/*
royal flush: check if cardsorted size is 5 & first value is 10 & and last value is A & suits size is 1
straight flush: check if cardsorted size is 5 & suits size is 1 & first value and last value is difference is 4
four of a kind: check if face key has a value of 4
full house: check if face size is 2 and if face key has a value 3
flush: check if suit size equals 1
straight: check if cardsorted size is 5 & first value and last value is difference is 4
three of a kind: check if face key has a value of 3
two pair: check if size is 3 and face key has a value of 2
pair: check if face key has a value of 2
high card: just check to see if there are 5 cards, idk tbh
*/

