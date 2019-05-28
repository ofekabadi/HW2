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


//constructor
Zoo::Zoo(string maleName, string femaleName){

    Animal* firstMale= new Animal(NULL, NULL, maleName, MALE);

    Animal* firstFemale= new Animal(NULL, NULL, femaleName, FEMALE);

    _members.push_back(firstMale);

    _members.push_back(firstFemale);

}





bool Zoo::euthanize(const string &name)
{

    for (vector<Animal*> ::iterator findAnimal = _members.begin();findAnimal!=_members
    .end();findAnimal++)
    {
        if(name==((*findAnimal)->_name))
        {
            Gender animalGender = (*findAnimal)->_gender;
            for(vector<Animal*>::iterator childrenItr = (*findAnimal)->_children.begin()
                    ; childrenItr !=  (*findAnimal)->_children.end(); childrenItr++)
            {
                if(((*childrenItr)->_isAdult)== false)
                {
                    if((*childrenItr)->_father == NULL ||(*childrenItr)->_mother == NULL )
                    {
                        euthanize((*childrenItr)->_name);
                    }
                }
                if(animalGender == MALE)
                {
                    ((*childrenItr)->_father)= NULL;
                }
                if(animalGender == FEMALE)
                {
                    ((*childrenItr)->_mother)= NULL;
                }
            }
            delete (*findAnimal);
            _members.erase (findAnimal);
            return true;
        }
    }
    return false;
}



void Zoo::growUp(){

    for (vector<Animal*>::const_iterator animalItr=_members.begin();
    animalItr!=_members.end();++animalItr)

    {
        (**animalItr).grow();
    }
}



void Zoo::printCommunity(){

    for (vector<Animal*>::const_iterator animalItr =_members.begin();
    animalItr!=_members.end();++animalItr)

    {

        cout<<(*animalItr)->_name<<endl;

    }

}



void Zoo::communitySize(){

    int size=_members.size();

    cout<<"number of animals in the community is: "<<size<<endl;




}

void Zoo:: ancestorsPath(const vector<string> &travelOrders)
{
    Animal *currentAnimal = NULL;
    for (vector<Animal *>::const_iterator it = _members.begin(); it != _members.end(); ++it) {
        if ((**it)._name == travelOrders[0]) {
            (**it).printAnimal();
            currentAnimal = (*it);
        }
    }
    if(currentAnimal == NULL)
    {
        cout<<"The animal was not found"<<endl;
    }

    vector<string>::const_iterator iter;
    for (iter = travelOrders.begin()+1;iter != travelOrders.end() ; iter++) {
        if(*iter == "m" && (currentAnimal)->_mother != NULL)
        {
            (*currentAnimal)._mother->printAnimal();
            currentAnimal = (currentAnimal)->_mother;
            continue;
        }
         if(*iter == "f" && (currentAnimal)->_father != NULL)
        {
            (*currentAnimal)._father->printAnimal();
            currentAnimal = (currentAnimal)->_father;
            continue;
        }

        cout<<"failed"<<endl;
    }





}

bool Zoo::animalReproduce(const string &firstParentName,const string

&secondParentName, const string  &name,  Gender gender) {



    bool fatherExists=false, motherExists=false;

    vector<Animal*>::const_iterator animalFatherPtr, animalMotherPtr;



    for (vector<Animal *>::const_iterator it = _members.begin();

         it != _members.end(); ++it) {

        if (firstParentName == (*it)->_name){

            if((**it)._gender==MALE)

            {

                fatherExists=true;

                animalFatherPtr=it;
                break;

            }
            if((**it)._gender==FEMALE)
                {

                motherExists=true;

                animalMotherPtr=it;
                break;
            }

        }

    }



    for (vector<Animal *>::const_iterator it = _members.begin();

         it != _members.end(); ++it) {

        if (secondParentName == (*it)->_name){

            if((**it)._gender==FEMALE)

            {

                motherExists=true;

                animalMotherPtr=it;
                break;
            }

            if((**it)._gender==MALE)

            {

                fatherExists=true;

                animalFatherPtr=it;
                break;
            }

        }

    }



    bool uniqueName = true;                  //this is new

    for (vector<Animal *>::const_iterator it = _members.begin();

         it != _members.end(); ++it) {

        if (name == (*it)->_name){

            uniqueName = false;

            break;

        }

    }



    if(fatherExists && motherExists && uniqueName)

    {

        Animal* newAnimalPtr= (*animalFatherPtr)->reproduce(*animalMotherPtr,

                                                            name, gender);

        if(newAnimalPtr!= NULL)          //this is new

        {

            _members.push_back(newAnimalPtr);

            return true;

        }

    }



    return false;

}