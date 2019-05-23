#include "Zoo.h"

#include <iostream>
#include <string>
#include<vector>
#include <sstream>

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;

Zoo::Zoo(string maleName, string femaleName){
    Animal* firstMale= new Animal(NULL, NULL, maleName, MALE);
    Animal* firstFemale= new Animal(NULL, NULL, femaleName, FEMALE);
    _members.push_back(firstMale);
    _members.push_back(firstFemale);
}


bool Zoo::euthanize(const string &name) {
    for (vector<Animal*>::const_iterator it=_members.begin(); it!=_members.end(); ++it)
    {
        if(name==(**it)._name)
        {
            delete *it;
            return  true;
        }
    }
    return false;
}

void Zoo::growUp(){
    for (vector<Animal*>::const_iterator it=_members.begin(); it!=_members.end(); ++it)
    {
        (**it).grow();
    }
}

void Zoo::printCommunity(){
    for (vector<Animal*>::const_iterator it=_members.begin(); it!=_members.end(); ++it)
    {
        cout<<(*it)->_name<<endl;
    }
}

void Zoo::communitySize(){
    int size=_members.size();
    cout<<size<<endl;

}

bool Zoo::animalReproduce(const string &firstParentName,const string
    &secondParentName, const string  &name,  Gender gender) {

    bool fatherExists=false, motherExists=false;
    vector<Animal*>::const_iterator animalFatherPtr, animalMotherPtr;

    for (vector<Animal *>::const_iterator it = _members.begin();
         it != _members.end(); ++it) {
        if (firstParentName == (**it)._name){
            if((**it)._gender=MALE)
            {
                fatherExists=true;
                animalFatherPtr=it;
            }
            else
            {
                motherExists=true;
                animalMotherPtr=it;
            }
        }
    }

    for (vector<Animal *>::const_iterator it = _members.begin();
         it != _members.end(); ++it) {
        if (secondParentName == (**it)._name){
            if((**it)._gender=FEMALE)
            {
                motherExists=true;
                animalMotherPtr=it;
            }
            else
            {
                fatherExists=true;
                animalFatherPtr=it;
            }
        }
    }

    if(fatherExists==true, motherExists==true)
    {
        Animal* newAnimalPtr= (*animalFatherPtr)->reproduce(*animalMotherPtr,
                name, gender);
        if(newAnimalPtr!=NULL)          //this is new
        {
            _members.push_back(newAnimalPtr);
            return true;
        }
    }
    else
    {
        return false;
    }
}