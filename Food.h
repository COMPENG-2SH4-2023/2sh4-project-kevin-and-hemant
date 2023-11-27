#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>
#include <time.h>

#include "GameMechs.h"

//MAY include these 2 below...
//#include "objPos.h"
//#include "objPosArrayList.h"

using namespace std;

class Food
{
 
    private:
    objPos foodPos;
    GameMechs* foodGameMechsRef;
        
    public:
    Food();
    ~Food();
    void generateFood(objPos blockOff);
    void getFoodPos(objPos &returnPos);


};

#endif
