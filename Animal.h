#ifndef HW2_ANIMAL_H
#define HW2_ANIMAL_H

#include <iostream>
#include <string>
#include<vector>
#include <sstream>

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;

typedef enum { UNKNOWN = 0, MALE , FEMALE} Gender;
typedef enum {NAME, GENDER, ADULT, MOTHER, FATHER, CHILDREN} OutputEnum;
const std::string toPrint[]= {"Name: ", ", Gender: ",", Is adult: ", ", Mother name: ",
                              ", Father name: ",", Number of children: "};


class Animal
{
public:
    //Constructor
    Animal (Animal *fatherPointer, Animal *motherPointer, const string &animalName,
            Gender animalGender);
    //Destructor
    ~Animal(){}

    void printAnimal();

    void grow();

     Animal* reproduce(Animal* partner, const string &descendantName,
             Gender descendantGender);

     friend class Zoo;

private:
    Animal * _father;
    Animal *_mother;
    vector< Animal *> _children;
    Gender _gender;
    string _name;
    bool _isAdult;
};

#endif //HW2_ANIMAL_H