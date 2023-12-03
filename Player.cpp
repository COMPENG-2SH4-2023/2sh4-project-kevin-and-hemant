#include "Player.h"

Player::Player(GameMechs* thisGMRef, Food* thisFoodRef) 
{
    mainGameMechsRef = thisGMRef;
    mainFoodRef = thisFoodRef;
    myDir = STOP;

    // more actions to be included
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2,
                      mainGameMechsRef->getBoardSizeY() / 2,
                      '@');
    playerPosList = new objPosArrayList;
    playerPosList->insertHead(tempPos);
}

Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPosList()
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    switch(mainGameMechsRef->getInput()){
        case 'w':
            if(myDir != UP && myDir != DOWN)
                myDir = UP;
            break;

        case 'a':
            if(myDir != LEFT && myDir != RIGHT)
                myDir = LEFT;
            break;

        case 's':
            if(myDir != UP && myDir != DOWN)
                myDir = DOWN;
            break;

        case 'd':
            if(myDir != LEFT && myDir != RIGHT)
                myDir = RIGHT;
            break;
    }        
}

void Player::movePlayer()
{
    int i;
    objPos currentHead; 
    objPosArrayList* tempFoodList;
    objPos tempPos;
    // Get refrences to the snake pos array and food pos array
    playerPosList->getHeadElement(currentHead);
    tempFoodList = mainFoodRef->getFoodPosList(); 

    // PPA3 Finite State Machine logic
    switch(myDir){
        case(UP):
            currentHead.y--;
            if(currentHead.y <= 0) // Wraparound logic
                currentHead.y = mainGameMechsRef->getBoardSizeY() - 1;
            break;

        case(DOWN):
            currentHead.y++;
            if(currentHead.y >= mainGameMechsRef->getBoardSizeY()){ // Wraparound logic
                currentHead.y = 1;}
            break;

        case(LEFT):
            currentHead.x--;
            if(currentHead.x <= 0) // Wraparound logic
                currentHead.x = mainGameMechsRef->getBoardSizeX() - 1;
            break;

        case(RIGHT):
            currentHead.x++;
            if(currentHead.x >= mainGameMechsRef->getBoardSizeX()) // Wraparound logic
                currentHead.x = 1;
            break;
    }
    // New current Head should be inserted in to the head of the list
    playerPosList->insertHead(currentHead);

    // Iterate through the food positions in the temporary food list
    for(i = 0; i < tempFoodList->getSize(); i++)
    {
        // Store the food position from the food list in a temporary variable
        tempFoodList->getElement(tempPos, i);
         // Check if the current head position is equal to the food position
        if(currentHead.isPosEqual(&tempPos) == true)
        {   
            // If they are equal, increment the score and generate new food
            mainGameMechsRef->incrementScore();
            mainFoodRef->generateFood(*playerPosList);

            // The first 2 food positions are always the special foods
            // Check for the first/second position and take appropriate actions
            if(i == 0 && playerPosList->getSize() > 3)
            {
                // If it's the first position and the snake length is greater than 3, remove 2 tail segments
                // I know it looks like 3 are removed but it is actually 2
                playerPosList->removeTail();
                playerPosList->removeTail();
                playerPosList->removeTail();
            }
            else if(i == 1)
            {
                // If it's the second position, increment the score by 10
                // Again it looks like its 9 but 1 is allredy added before 
                for(int h = 0; h < 9; h++)
                {
                    mainGameMechsRef->incrementScore();
                }
            }
            // Break out of the loop since landing on two foods simultaneously is not allowed
            break;
        }
    }
    // If the loop didn't break early, i would be 5, indicating no food was landed on, so remove the tail
    if(i == 5)
    {
        playerPosList->removeTail();
    }

    // Similar logic for checking if the snake head collides with its own body
    // Start at i = 1 since we don't want to check if the head collides with itself 
    for(i = 1; i < playerPosList->getSize(); i++)
    {
        // Get the position of the body segment
        playerPosList->getElement(tempPos, i);
        // If the head collides with a body segment, set exit flag and lose flag
        if(currentHead.isPosEqual(&tempPos))
        {
            mainGameMechsRef->setExitTrue();
            mainGameMechsRef->setLoseFlag();
            break;
        }
    }
}