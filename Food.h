#ifndef FOOD_H
#define FOOD_H
#define numFoods 5

#include <cstdlib>
#include <time.h>

#include "GameMechs.h"
#include "objPosArrayList.h"

using namespace std;

class Food
{
 
    private:
    objPosArrayList *foodPosList;
    GameMechs* foodGameMechsRef;
        
    public:
    Food(GameMechs* foodGMRef);
    ~Food();
    void generateFood(objPosArrayList &blockOff);
    objPosArrayList* getFoodPos();


};

#endif
