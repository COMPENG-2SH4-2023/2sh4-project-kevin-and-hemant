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
bool cheats;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{

    Initialize();

    //the essential game functions are looped while the exit flag is false
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
    cheats = false;
}

void GetInput(void)
{
    if(MacUILib_hasChar() == 1)
    {
        //stores the input of the userd
        char input = MacUILib_getChar();

        //if space (32) is clicked  exit flag is set to true
        if(input == 32)
        {
            myGM->setExitTrue(); 
        }
        // If c is clicked enable cheats 
        if(input == 'c')
        { 
            cheats = true;
        }
        //sets the input in game mechanics
        myGM->setInput(input);
    }
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); 
    
    bool drawn;
    objPos tempPos; //creating a tempPos object for player
    objPosArrayList* playerBody = myPlayer->getPlayerPosList(); //creating a and storing playerBody object with the players positions
    objPosArrayList* tempFoodList = myFood->getFoodPosList(); //creating a and storing tempFoodList object with the random foods spawining
    objPos tempBodySeg;
    
    //major nested for loops to print the game board, snake, and foods accordingly
    for(int i = 0; i <= myGM->getBoardSizeY(); i++)
    {
        for(int j = 0; j <= myGM->getBoardSizeX(); j++)
        {
            drawn = false;

            //for loop that displays the snake body in each coordinate on the board
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

            //for loop that displays the generated foods at their coordinates on the board
            for(int k = 0; k < tempFoodList->getSize(); k++)
            {
                tempFoodList->getElement(tempBodySeg, k);
                if(tempBodySeg.x == j && tempBodySeg.y == i)
                {
                    MacUILib_printf("%c", tempBodySeg.symbol);
                    drawn = true;
                    break;
                }
            }

            if(drawn) continue;

            // draws the border of the board
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
    
    //messages printed under the game board to explain special foods, cheats, board size, player position, score and length of snake
    MacUILib_printf("There are 2 special foods in disguise, \nOne makes you shorter by 2 units, \nThe other adds 10 to score!\n\n");
    MacUILib_printf("Press c to show where the special foods are\n");

    MacUILib_printf("Board size: %dx%d, Player Position: <%d,%d> + %c\n\n", myGM->getBoardSizeX(), myGM->getBoardSizeY(), tempBodySeg.x, tempBodySeg.y, tempBodySeg.symbol);
    
    MacUILib_printf("Score: %d\n", myGM->getScore());
    MacUILib_printf("Snake length: %d\n", playerBody->getSize());
    
    // If cheats are enabled print the locations for all of the food
    if(cheats == true)
    {
        for(int k = 0; k < tempFoodList->getSize(); k++)
        {
            tempFoodList->getElement(tempBodySeg, k);
            if(k == 0)
            {
                MacUILib_printf("\nSuper Food 1, <%d,%d> \n", tempBodySeg.x, tempBodySeg.y);
            }
            else if(k == 1)
            {
                MacUILib_printf("Super Food 2, <%d,%d> \n", tempBodySeg.x, tempBodySeg.y);
            }
        }
    }
    
    if(myGM->getLoseFlagStatus() == true)
    {
        MacUILib_printf("\nYou Lost! Your score was: %d\n", myGM->getScore());
    }
    
    myGM->clearInput();
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{  
    MacUILib_uninit();
    
    //remove heap instances
    delete myGM;
    delete myPlayer;
    delete myFood;
}