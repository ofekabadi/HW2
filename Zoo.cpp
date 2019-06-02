#include <iostream>
#include <string>
#include<vector>
#include <sstream>
#include "Zoo.h"

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;

//constructor
Zoo::Zoo(string maleName, string femaleName){
    Animal* firstMale= new Animal(NULL, NULL, maleName, MALE);//create the first two
    Animal* firstFemale= new Animal(NULL, NULL, femaleName, FEMALE);// animals in the zoo
    _members.push_back(firstMale);//and a pointer to them
    _members.push_back(firstFemale);
}

//Destructor
Zoo::~Zoo()
{   //will delete all dynamically located 'Animal' objects
    for (vector<Animal*>::const_iterator it=_members.begin(); it!=_members.end(); ++it)
    {
        delete *it;
    }
}

//destroys requested 'Animal' object, if exists
bool Zoo::euthanize(const string &name)
{
    for (vector<Animal*>::iterator findAnimal = _members.begin();
    findAnimal!=_members.end(); findAnimal++)
    {   //searches for an animal of the same name requested
        if(name==((*findAnimal)->_name))
        {
            Gender animalGender = (*findAnimal)->_gender;
            for(vector<Animal*>::iterator childrenItr = (*findAnimal)->_children.begin()
                    ; childrenItr !=  (*findAnimal)->_children.end(); childrenItr++)
            {//if euthanized animal's children are'nt adults, they might die themselves
                if(((*childrenItr)->_isAdult)== false)
                {
                    if((*childrenItr)->_father == NULL ||(*childrenItr)->_mother == NULL )
                    {//if a not adult animal's parents are dead, it will die, according
                        euthanize((*childrenItr)->_name);// to the  the laws of nature
                    }
                }
                if(animalGender == MALE)
                {
                    ((*childrenItr)->_father)= NULL; //if the parent has been
                }
                if(animalGender == FEMALE)// euthanized, the father/ mother pointer will
                {
                    ((*childrenItr)->_mother)= NULL; // no longer point to them
                }
            }
            delete (*findAnimal); //delocates object
            _members.erase (findAnimal); //removes pointer to it
            return true;
        }
    }
    return false; //is an animal of the same name was not found, will return false
}

//grows all the zoo's animals to adulthood
void Zoo::growUp(){
    for (vector<Animal*>::const_iterator animalItr=_members.begin();
    animalItr!=_members.end();++animalItr)
    {
        (**animalItr).grow();
    }
}

//will print all of the zoo's animals' names to screen
void Zoo::printCommunity(){
    for (vector<Animal*>::const_iterator animalItr =_members.begin();
    animalItr!=_members.end();++animalItr)
    {
        cout<<(*animalItr)->_name<<endl;
    }
}

//will print the number of animals is the zoo names to screen
void Zoo::communitySize(){
    int size=_members.size();
    cout<<"number of animals in the community is: "<<size<<endl;
}

//retrieves animal ancestors path, if exists
void Zoo:: ancestorsPath(const vector<string> &travelOrders) {
    Animal *currentAnimal = NULL; //will store current ancestor
    for (vector<Animal *>::const_iterator findAnimal = _members.begin();
         findAnimal !=
         _members.end(); ++findAnimal) {//if requested animal exist, will print its details
        if ((*findAnimal)->_name == travelOrders[0]) {
            (*findAnimal)->printAnimal();
            currentAnimal = (*findAnimal); //the ancestors path begins from current animal
        }
    }
    if (currentAnimal == NULL) //in case the animal requested doesn't exists
    {
        cout << "The animal was not found" << endl;
        return;
    }

    vector<string>::const_iterator iter;
    for (iter = travelOrders.begin() + 1; iter != travelOrders.end(); iter++) {
        if (*iter == "m" && (currentAnimal)->_mother != NULL) //will print the
        {                                                   //next ancestor
            (*currentAnimal)._mother->printAnimal();        //and will assign
            currentAnimal = (currentAnimal)->_mother;       //it to the current
            continue;                                         //animal's pointer
        }
        if (*iter == "f" && (currentAnimal)->_father != NULL) {
            (*currentAnimal)._father->printAnimal();
            currentAnimal = (currentAnimal)->_father;
            continue;
        }

        cout << "failed" << endl;
    }
}


//this function is being called by 'animalReproduce' in order to verify the
// newborn's parents existence, and find their pointers
void Zoo:: parentExists (const string &parentName, bool* fatherExists, bool*
motherExists, vector<Animal*>::iterator* animalFatherPtr,
vector<Animal*>::iterator* animalMotherPtr){
    for (vector<Animal *>::iterator it = _members.begin(); it != _members.end();
         ++it){
        if (parentName == (*it)->_name){
            //cout<<"******name: "<<(*it)->_name<<endl;
            if((*it)->_gender==MALE)
            {
                *fatherExists=true;
                *animalFatherPtr=it;
                //cout<<"******is father: "<<(*it)->_name<<endl;
                return;
            }
            if((*it)->_gender==FEMALE)
            {
                *motherExists=true;
                *animalMotherPtr=it;
                //cout<<"******is mother: "<<(*it)->_name<<endl;
                return;
            }
        }
    }
}


bool Zoo::animalReproduce(const string &firstParentName,const string &secondParentName,
        const string  &name,  Gender gender) {

    bool fatherExists=false, motherExists=false;
    vector<Animal*>::iterator animalFatherPtr, animalMotherPtr;


    //******the new part, the function is implemented above this one^.
    //left the printing for you to see that it works, also ralets printing in reproduce
    parentExists(firstParentName, &fatherExists, &motherExists, &animalFatherPtr,
            &animalMotherPtr);
    parentExists(secondParentName, &fatherExists, &motherExists, &animalFatherPtr,
                 &animalMotherPtr);
    cout<<"$$$$$$"<<name<<", father "<<(*animalFatherPtr)->_name<<", mother "<<
    (*animalMotherPtr)->_name<<endl;


    bool uniqueName = true;
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
        if(newAnimalPtr!= NULL)
        {
            _members.push_back(newAnimalPtr);
            return true;
        }
    }

    return false;
}



