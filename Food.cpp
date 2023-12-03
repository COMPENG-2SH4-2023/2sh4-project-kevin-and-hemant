#include "Food.h"
#include "objPosArrayList.h"
#define foodChar 'a'

Food::Food(GameMechs* foodGMRef)
{
    objPos tempPos;

    foodGameMechsRef = foodGMRef;

    tempPos.setObjPos(-1,-1,'a');
    foodPosList = new objPosArrayList;
    foodPosList->insertTail(tempPos);
    foodPosList->insertTail(tempPos);
    foodPosList->insertTail(tempPos);
    tempPos.setObjPos(-1,-1,'b');
    foodPosList->insertTail(tempPos);
    tempPos.setObjPos(-1,-1,'c');
    foodPosList->insertTail(tempPos);
}

Food::~Food()
{
    delete foodPosList;
}


void Food::generateFood(objPosArrayList &blockOff)
{
// generate random x and y coord, and make sure they are NOT boarder or blockoff pos. boardSizex / V.
// check x and y against 0 and boardSizeX / Y.
// remember, in objPos class you have an IsPosEqual() method. Use this instead of comparing element-by-element
// for yoru convenience.
    objPos tempBodySeg;
    objPos foodPos;
    srand(time(NULL));

    for(int j = 0; j < foodPosList->getSize(); j++)
    {
        foodPosList->removeTail();
        bool isFoodGood = false;
        while(!isFoodGood)
        {
            foodPos.x = (rand() % (foodGameMechsRef->getBoardSizeX()-2)) + 1;
            foodPos.y = (rand() % (foodGameMechsRef->getBoardSizeY()-2)) + 1;
            foodPos.symbol = foodChar;
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
            for(int i = 0; i < foodPosList->getSize(); i++)
            {
                foodPosList->getElement(tempBodySeg, i);
                if(foodPos.isPosEqual(&tempBodySeg))
                {
                    isFoodGood = false;
                    break;
                }
            }
        }
        foodPosList->insertHead(foodPos);
    }
}



objPosArrayList* Food::getFoodPosList()
{
    return foodPosList;
}
