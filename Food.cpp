#include "Food.h"
#define foodChar '?'

Food::Food(GameMechs* foodGMRef)
{
    foodGameMechsRef = foodGMRef;
    foodPos.setObjPos(-1,-1,foodChar);
}

Food::~Food()
{
    //delete heap members
}
void Food::generateFood(objPos blockOff)
{
// generate random x and y coord, and make sure they are NOT boarder or blockoff pos. boardSizex / V.
// check x and y against 0 and boardSizeX / Y.
// remember, in objPos class you have an IsPosEqual() method. Use this instead of comparing element-by-element
// for yoru convenience.
    srand(time(NULL));
    
    while(true)
    {
        int x = (rand() % (foodGameMechsRef->getBoardSizeX()-2)) + 1;
        int y = (rand() % (foodGameMechsRef->getBoardSizeY()-2)) + 1;
        if(!foodPos.isPosEqual(&blockOff))
        {
            foodPos.setObjPos(x,y,foodChar);
            break;
        }
    }
}


void Food::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos);
}
