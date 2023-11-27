#include "Food.h"

Food::Food()
{
    //foodGameMechsRef->
    foodPos.setObjPos(-1,-1,'o');
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

    int rangex[5] = {0};
    int rangey[5] = {0};
    int x, y, show;

    for(int i = 0; i < 5; i++)
    {
        show = 0;
        while(show == 0)
        {
            show = 1;
            x = (rand() % foodGameMechsRef->getBoardSizeX()) + 1;
            y = (rand() % foodGameMechsRef->getBoardSizeY()) + 1;
            for(int j = 0; j < 5; j++)
            {
                if(rangex[j] == x || rangey[j] == y || x == foodPos.isPosEqual(&blockOff) || y == foodPos.isPosEqual(&blockOff))
                {
                    show = 0;
                }
            }
            
        }
        rangex[i] = x;
        rangey[i] = y;
    }


}

void Food::getFoodPos(objPos &returnPos)
{
    //returnPos.setObjPos();
}
