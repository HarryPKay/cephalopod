/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Initiates and runs the game controller which is responsible
 *                  for game flow.
 *
 *        Version:  1.0
 *        Created:  04/05/19 10:02:31
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  HARRY KAY (), HARRYKAY94@GMAIL.COM
 *   Organization:  
 *
 * =====================================================================================
 */

#include "GameController.h"
#include <iostream>


//TODO: maybe have a rule checker to abstract from model
int main()
{
    int selection = 0;
    while (selection == 0) {
        GameController game;
        game.run();
        cout << "Play again?.\n\n";
        cout << "1) Yes\n\n> ";
        std::cin >> selection;
        --selection;
    }

    return 0;
}
