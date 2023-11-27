#include "Food.h"
#define foodChar '?'

Food::Food()
{
    //foodGameMechsRef->
    for(int i = 0; i < numFoods; i++)
    {
        rangex[i] = {-1};
        rangey[i] = {-1};
    }
    foodPos.setObjPos(rangex[0],rangey[0],foodChar);
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
    int x, y;

    for(int i = 0; i < numFoods; i++)
    {
        while(rangex[i] == 0 || rangey[i] == 0)
        {
            x = (rand() % foodGameMechsRef->getBoardSizeX()) + 1;
            y = (rand() % foodGameMechsRef->getBoardSizeY()) + 1;
            for(int j = 0; j <= i; j++)
            {
                if(rangex[j] != x && rangey[j] != y && !foodPos.isPosEqual(&blockOff))
                {
                    rangex[i] = x;
                    rangey[i] = y;
                }
            }
        }
    }


}

void Food::getFoodPos(objPos &returnPos)
{
    //for(int i = 0; i < numFoods; i++)
    {
        returnPos.setObjPos(rangex[0], rangey[0], foodChar);
    }
}
