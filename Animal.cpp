#include <iostream>
#include <string>
#include<vector>
#include <sstream>
#include "animal.h"

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;

//consturctor
Animal::Animal( Animal *fatherPointer, Animal *motherPointer, const string &animalName,
        Gender animalGender): _father(fatherPointer), _mother(motherPointer),
        _gender (animalGender), _name(animalName), _isAdult(false){}

//turn an animal into an adult
void Animal::grow() {
    _isAdult=true;
}

//prints out all of the animal's data
void Animal::printAnimal() {
    cout<<toPrint[NAME]<<_name<<toPrint[GENDER]<<_gender<<toPrint[ADULT]<<_isAdult<<
    toPrint[MOTHER]<<((_mother == NULL ) ? "" :_mother->_name)<< //in case animal has no
    toPrint[FATHER]<<((_father == NULL ) ? "" :_father->_name)<<// father/mother (pointer)
                                                                // - will print nothing
    toPrint[CHILDREN]<<_children.size()<<endl;
}

//get reproduce data from zoo's 'animalReproduce' function and  creates a new 'Animal'
// object and a pointer to it, in case all of the conditions apply.
Animal* Animal::reproduce(Animal* partner, const string &descendantName, Gender
descendantGender){
    //reproduce can only happen between two adults
    if(partner->_isAdult==false)
    {
        return NULL;
    }
    //reproduce can only happen between two adults of a different gender
    if(partner->_gender==_gender || partner->_gender==UNKNOWN)
    {
        return NULL;
    }
    //in case all conditions apply:
    else
    {
        Animal* newAnimalPtr = new Animal (this, partner, descendantName,
                descendantGender);   //calls 'Animal''s constructor
        _children.push_back(newAnimalPtr); //sends a pointer of the newborn to parents'
        partner->_children.push_back(newAnimalPtr); // 'children' vector
        cout<<"in animal reproduce: "<<(*newAnimalPtr)._name<<endl;//******related
        // printing
        return newAnimalPtr;
    }
}