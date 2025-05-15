/**
 * @file main.cpp
 * @author Isaiah Justin Brian
 * @brief Determine if players will be controlled by users or 
 *          cpus, initiate boards, run game loop, send data 
 *          to log file
 * @version 0.1
 * @date 2025-04-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "battleshipFunctions.h"
string logPlayer;
string logCoordinate;
string logHitMiss;
string logSunk;

int main() {
    srand(time(0));
    Board p1Board = Board();
    Board p2Board = Board(); 
    bool p1CPU;
    bool p2CPU;

    welcome();

    cout << endl << "Player 1" << endl;
    p1CPU = promptCPU();
    setUpBoard(p1Board, p1CPU);

    cout << endl << "Player 2" << endl;
    p2CPU = promptCPU();
    setUpBoard(p2Board, p2CPU);
    
    if(rand() % 2 == 0) {
        cout << "Player 2 will go first." << endl << endl;
        turnover(); 
        if(turn(p2Board, p1Board, p2CPU))
            winner(2);
    }
    else {
        cout << "Player 1 will go first." << endl << endl;
        turnover();
    }

    // Open battleship.log file
    ofstream battleLog;
    battleLog.open("battleship.log");

    // Check file was opened
    if(battleLog.fail())
    {
        // Error message
        cout << "Error with log: Failed to open battleship.log\n";
    }

    while(1) {
        if(turn(p1Board, p2Board, p1CPU)) {
            winner(1);
            break;
        }
        else if(turn(p2Board, p1Board, p2CPU)) {
            winner(2);
            break;
        }  
        sendToLogInGame(logPlayer, logCoordinate, logHitMiss, logSunk, battleLog);
    }

    sendToLogEndgame(p1Board, p2Board, battleLog);

    // Close file
    battleLog.close();

    return 0;
}