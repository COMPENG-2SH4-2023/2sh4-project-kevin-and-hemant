#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.setObjPos(5,5,'@');
}

Player::~Player()
{
    // delete any heap members here
}

void Player::getPlayerPos(objPos &returnPos)
{
    returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
    // return the reference to the playerPos arrray list
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
    // PPA3 Finite State Machine logic
    switch(myDir){
        case(UP):
            playerPos.y--;
            if(playerPos.y <= 0) // Wraparound logic
                playerPos.y = mainGameMechsRef->getBoardSizeY() - 2;
            break;

        case(DOWN):
            playerPos.y++;
            if(playerPos.y >= mainGameMechsRef->getBoardSizeY() - 1); // Wraparound logic
                playerPos.y = 1;
            break;

        case(LEFT):
            playerPos.x--;
            if(playerPos.x <= 0) // Wraparound logic
                playerPos.x = mainGameMechsRef->getBoardSizeX() - 2;
            break;

        case(RIGHT):
            playerPos.x++;
            if(playerPos.y >= mainGameMechsRef->getBoardSizeX() - 1) // Wraparound logic
                playerPos.y = 1;
            break;
    }
}

