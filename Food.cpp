#include "Food.h"
#define foodChar 'a'

Food::Food(GameMechs* foodGMRef)
{
    foodGameMechsRef = foodGMRef;
    foodPos.setObjPos(-1,-1,foodChar);
}

Food::~Food()
{
    //delete heap members
}
void Food::generateFood(objPosArrayList &blockOff)
{
// generate random x and y coord, and make sure they are NOT boarder or blockoff pos. boardSizex / V.
// check x and y against 0 and boardSizeX / Y.
// remember, in objPos class you have an IsPosEqual() method. Use this instead of comparing element-by-element
// for yoru convenience.
    bool isFoodGood = false;
    objPos tempBodySeg;
    srand(time(NULL));
    while(!isFoodGood)
    {
        foodPos.x = (rand() % (foodGameMechsRef->getBoardSizeX()-2)) + 1;
        foodPos.y = (rand() % (foodGameMechsRef->getBoardSizeY()-2)) + 1;
        isFoodGood = true;
        for(int i = 0; i < blockOff.getSize(); i++)
        {
            blockOff.getElement(tempBodySeg, i);
            if(foodPos.isPosEqual(&tempBodySeg))
            {
                isFoodGood = false;
                break;
            }
        }
    }
}


void Food::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos);
}
