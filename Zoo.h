#ifndef HW2_ZOO_H
#define HW2_ZOO_H

#include <iostream>
#include <string>
#include<vector>
#include <sstream>
#include "Animal.h"

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;



class Zoo
{
public:
    Zoo(string maleName, string femaleName);
    ~Zoo()
    {
        for (vector<Animal*>::const_iterator it=_members.begin(); it!=_members.end(); ++it)
        {
            delete *it;
        }
        _members.clear();
    }
    bool animalReproduce(const string &firstParentName,const string
        &secondParentName, const string  &name,  Gender gender);
    bool euthanize(const string &name);
    void growUp();
    void printCommunity();
    void communitySize();
    void ancestorsPath(const vector<string> &travelOrders);


private:
    vector< Animal *> _members;
};


#endif //HW2_ZOO_H
