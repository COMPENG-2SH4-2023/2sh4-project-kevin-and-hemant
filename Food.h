#ifndef FOOD_H
#define FOOD_H
#define numFoods 5

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
    int rangex[numFoods];
    int rangey[numFoods];
        
    public:
    Food();
    ~Food();
    void generateFood(objPos blockOff);
    void getFoodPos(objPos &returnPos);


};

#endif
