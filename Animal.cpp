#include "animal.h"

#include <iostream>
#include <string>
#include<vector>
#include <sstream>

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;

void Animal::grow() {
    _isAdult=true;
}

void Animal::printAnimal() {
    cout<<toPrint[NAME]<<_name<<toPrint[GENDER]<<_gender<<toPrint[ADULT]<<_isAdult<<
    toPrint[MOTHER]<<_mother->_name<<toPrint[FATHER]<<_father->_name<<
    toPrint[CHILDREN]<<_children.size()<<endl;
}

Animal* Animal::reproduce(Animal* partner, const string &descendantName, Gender
descendantGender){
    if(partner->_isAdult==false)
    {
        return NULL;
    }
    if(partner->_gender==_gender || partner->_gender==UNKNOWN)
    {
        return NULL;
    }
    else
    {
        Animal* newAnimalPtr = new Animal (this, partner, descendantName,
                descendantGender);

        cout<<"father: "<<this->_name<<" mother: "<<partner->_name          //printings
        <<" name: "<<descendantName<<" gender: "<<descendantGender<<endl;

        _children.push_back(newAnimalPtr);
        return newAnimalPtr;
    }
}