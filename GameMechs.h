#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;


class GameMechs
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    private:
        char input;
        bool exitFlag;

        bool loseFlag; //lose boolean
        int score; //tracks score of player
        
        int boardSizeX;
        int boardSizeY;

    public:
        GameMechs();
        GameMechs(int boardX, int boardY);

        ~GameMechs(); //deconstructor
        
        void setExitTrue(); //sets exit to exit
        bool getExitFlagStatus();

        void setLoseFlag(); //set lose status
        bool getLoseFlagStatus(); //get lose status

        char getInput();
        void setInput(char this_input);
        void clearInput();

        int getBoardSizeX();
        int getBoardSizeY();

        int getScore(); //getter for score
        void incrementScore(); //increments the score
      

};

#endif