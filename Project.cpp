#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"
#include "objPosArrayList.h"

// super food 1 = increase snake length by 5 and increase score by 10
// super food 2 = decrease snake length by 2

using namespace std;

#define DELAY_CONST 100000

GameMechs* myGM;
Player* myPlayer;
Food* myFood;

// super food 1 (S1) = increase snake length by 5 and increase score by 10
// super food 2 (S2) = decrease snake length by 2

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    myGM = new GameMechs(26,13); //creates board size 26x13
    myFood = new Food(myGM);
    myPlayer = new Player(myGM, myFood);
    myFood->generateFood(*(myPlayer->getPlayerPosList()));
    // Think about when to generate the new food... 
    // Think about whether you want to set up a debug key to call the food generation routine for verification
    // remember, "myFood->generateFood(objPos blockOff)" requires player reference. You will need to provide it AFTER player object is instantiated.
}

void GetInput(void)
{
    if(MacUILib_hasChar() == 1)
    {
        char input = MacUILib_getChar();
        if(input == 32)
        {
            myGM->setExitTrue();
        }
        myGM->setInput(input);
    }
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
    //clear input was here (moved to last line in draw for now)
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); 
    
    objPosArrayList* playerBody = myPlayer->getPlayerPosList() ;
    objPos tempPos; //creating a tempPos object for player
    objPos tempFood; //creating tempFood object for the food
    playerBody->getHeadElement(tempPos); // Look at tut video and change
    myFood->getFoodPos(tempFood);
    bool drawn;
    objPos tempBodySeg;
    for(int i = 0; i <= myGM->getBoardSizeY(); i++)
    {
        for(int j = 0; j <= myGM->getBoardSizeX(); j++)
        {
            drawn = false;
            for(int k = 0; k < playerBody->getSize(); k++)
            {
                playerBody->getElement(tempBodySeg, k);
                if(tempBodySeg.x == j && tempBodySeg.y == i)
                {
                    MacUILib_printf("%c", tempBodySeg.symbol);
                    drawn = true;
                    break;
                }
            }

            if(drawn) continue; // If player body was drawn, dont draw anything after

            // draw the border
            if(i == 0 || i == myGM->getBoardSizeY() || j == 0 || j == myGM->getBoardSizeX())
            {
                MacUILib_printf("#");
            }
            else if(tempFood.y == i && tempFood.x == j)
            {
                MacUILib_printf("%c", tempFood.symbol);
            }
            else
            {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    }

    playerBody->getHeadElement(tempBodySeg);
    MacUILib_printf("Score: %d\n", myGM->getScore());
    MacUILib_printf("Board size: %dx%d, Player Position: <%d,%d> + %c\n", myGM->getBoardSizeX(), myGM->getBoardSizeY(), tempBodySeg.x, tempBodySeg.y, tempBodySeg.symbol);
    MacUILib_printf("Food: <%d,%d> + %c", tempFood.x, tempFood.y, tempFood.symbol);

    if(myGM->getLoseFlagStatus())
    {
        MacUILib_printf("\n\nYou Lost :( ");
    }

    myGM->clearInput();

    
    
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    //MacUILib_clearScreen();    
  
    MacUILib_uninit();
    
    //remove heap instances
    delete myGM;
    delete myPlayer;
    delete myFood;
}
