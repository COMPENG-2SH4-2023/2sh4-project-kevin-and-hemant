#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>
#include <time.h>

#include "GameMechs.h"
#include "objPosArrayList.h"

using namespace std;

class Food
{
    private:
        objPosArrayList* foodPosList; //object array list to store the diifferent foods
        GameMechs* foodGameMechsRef; //passing in game mechanics
        
    public:
        Food(GameMechs* foodGMRef); //constructor 
        ~Food(); //deconstructor
        void generateFood(objPosArrayList &blockOff); //method to generate foods
        objPosArrayList* getFoodPosList(); //method that returns the positions of all the foods
};
#endif