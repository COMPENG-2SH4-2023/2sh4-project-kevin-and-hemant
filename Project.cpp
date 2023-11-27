#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"
#include "objPosArrayList.h"


using namespace std;

#define DELAY_CONST 100000

GameMechs* myGM;
Player* myPlayer;
Food* myFood;

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
    myPlayer = new Player(myGM);
    myFood = new Food();
    // Think about when to generate the new food... 
    // Think about whether you want to set up a debug key to call the food generation routine for verification
    // remember, "myFood->generateFood(objPos blockOff)" requires player reference. You will need to provide it AFTER player object is instantiated.
}

void GetInput(void)
{
    myGM->getInput();
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
    myGM->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); 

    bool drawn ;   

    objPos tempBodySeg;
    objPosArrayList* playerBody = myPlayer->getPlayerPosList() ;
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
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
  
    MacUILib_uninit();
    
    //remove heap instances
    delete myGM;
    delete myPlayer;
    delete myFood;
}
