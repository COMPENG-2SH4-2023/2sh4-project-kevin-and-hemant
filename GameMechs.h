#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

class GameMechs
{
    private:
        char input; //stores the user's input
        bool exitFlag; 

        bool loseFlag; //lose boolean
        int score; //tracks score of player
        
        int boardSizeX; //size of the board in X axis
        int boardSizeY; //size of the board in Y axis

    public:
        GameMechs(); //default constructor
        GameMechs(int boardX, int boardY); //specialized constructor that sets the board to a specified size

        ~GameMechs(); //deconstructor to delete heap members
        
        void setExitTrue(); //sets exit to exit
        bool getExitFlagStatus(); //returns the exit flag status

        void setLoseFlag(); //set lose status
        bool getLoseFlagStatus(); //returns the lose status

        char getInput(); //returns the input stored
        void setInput(char this_input); //sets input to a new input entered
        void clearInput(); //sets input to 0

        int getBoardSizeX(); //the size of the board in the X axis
        int getBoardSizeY(); //the size of the board in the Y axis

        int getScore(); //getter for score
        void incrementScore(); //increments the score
};
#endif