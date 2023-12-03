#include "Food.h"
#include "objPosArrayList.h"
#define foodChar 'a'

Food::Food(GameMechs* foodGMRef)
{
    objPos tempPos; //creates an object for position of the foods

    foodGameMechsRef = foodGMRef; //creates a useable game mechanics object to be used

    //intializes the array list of foods to be generated
    tempPos.setObjPos(-1,-1,foodChar);
    foodPosList = new objPosArrayList; //creates the food position list on the heap
    foodPosList->insertTail(tempPos);
    foodPosList->insertTail(tempPos);
    foodPosList->insertTail(tempPos);
    foodPosList->insertTail(tempPos);
    foodPosList->insertTail(tempPos);
}

Food::~Food()
{
    delete foodPosList;
}

void Food::generateFood(objPosArrayList &blockOff)
{
    objPos tempBodySeg;
    objPos foodPos;
    srand(time(NULL));

    //for loop generates certain number of foods by removing the tail and adding a head to the array list
    //randomly generated X and Y coordinates for foods and stores it in array list of foods
    //also checks if the food generated is on the snake body if so make new food
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