#include "Food.h"
#define foodChar 'a'
#define foodCharS1 'b'
#define foodCharS2 'c'

Food::Food(GameMechs* foodGMRef)
{
    foodGameMechsRef = foodGMRef;
    objPos tempPos;
    tempPos.setObjPos(-1,-1,foodChar);

    foodPosList = new objPosArrayList();
    foodPosList->insertTail(tempPos);
}

Food::~Food()
{
    delete foodPosList; //delete heap members
}

void Food::generateFood(objPosArrayList &blockOff)
{
// generate random x and y coord, and make sure they are NOT boarder or blockoff pos. boardSizex / V.
// check x and y against 0 and boardSizeX / Y.
// remember, in objPos class you have an IsPosEqual() method. Use this instead of comparing element-by-element
// for yoru convenience.
    bool isFoodGood = false;
    int i, x, y;
    objPos tempBodySeg;
    objPos tempFoodSeg;
    srand(time(NULL));
    while(!isFoodGood)
    {
        for(i = 0; i < 5; i++)
        {
            x = (rand() % (foodGameMechsRef->getBoardSizeX()-2)) + 1;
            y = (rand() % (foodGameMechsRef->getBoardSizeY()-2)) + 1;
            if(i == 3)
            {
                tempFoodSeg.setObjPos(x,y,foodCharS1);
            }
            else if(i == 4)
            {
                tempFoodSeg.setObjPos(x,y,foodCharS2);
            }
            else
            {
                tempFoodSeg.setObjPos(x,y,foodChar);
            }
            foodPosList->insertTail(tempFoodSeg);

        }
        isFoodGood = true;
        for(i = 0; i < blockOff.getSize(); i++)
        {
            blockOff.getElement(tempBodySeg, i);
            if(tempBodySeg.isPosEqual(&tempBodySeg))
            {
                isFoodGood = false;
                break;
            }
        }
    }
}


objPosArrayList* Food::getFoodPos()
{
    return foodPosList;
}