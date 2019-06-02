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
    //Constructor
    Zoo(string maleName, string femaleName);
    //Destructor
    ~Zoo();

    bool animalReproduce(const string &firstParentName,const string &secondParentName,
            const string &name, Gender gender);

    bool euthanize(const string &name);

    void growUp();

    void printCommunity();

    void communitySize();

    void ancestorsPath(const vector<string> &travelOrders);


private:
    //checks a parent exitence in 'animalReproduce'
    void parentExists (const string &parentName, bool* fatherExists, bool*
    motherExists, vector<Animal*>::iterator* animalFatherPtr,
    vector<Animal*>::iterator* animalMotherPtr);

    vector< Animal *> _members; //contains pointers to all animals in the zoo

};

#endif //HW2_ZOO_H