#include "Player.h"

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2,
                      mainGameMechsRef->getBoardSizeY() / 2,
                      '@');
    playerPosList = new objPosArrayList;
    playerPosList->insertHead(tempPos);

    // For debugging purpose insert 4 more segemts
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
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
    // PPA3 Finite State Machine logic
    objPos currentHead; 
    playerPosList->getHeadElement(currentHead);

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
    // then remove the tail
    playerPosList->insertHead(currentHead);
    playerPosList->removeTail();
}

