/**
 * @file fuinctions.cpp
 * @author Isaiah Justin Brian
 * @brief Descriptions and bodies of general functions
 * @version 0.1
 * @date 2025-04-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "battleshipFunctions.h"

/**
 * @brief Outputs initial prompt and rules for game
 * 
 */
void welcome() {
    cout<< endl
        << "~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~" << endl
        << "     WELCOME TO BATTLESHIP!    " << endl
        << "~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~" << endl
        << endl
        << "Ahoy, Captains! The fleet is ready and war is on the waves." << endl
        << endl
        << "RULES:" << endl
        << " - Each player hides " << shipNum << " ships on a " << rowNum << "x" << colNum << " grid." << endl
        << " - Ships vary in size: " << endl;
    for(int a = 0; a < shipNum; a++)
        cout<< "   - " << shipName[a] << ": " << shipSize[a] << endl;
    cout<< " - Take turns firing shots to sink the enemy fleet." << endl
        << " - First to sink all opposing ships wins!" << endl
        << endl
        << "May your aim be true and your seas calm." << endl
        << "Press Enter to begin your naval domination..." << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    system("clear");
}

/**
 * @brief Cins input and ensures is integer between 1 and max. 
 *          If valid, return input
 * 
 * @param max 
 * @return int 
 */
int validInput(int max) {
    int input;
    while(!(cin >> input) || (input < 1) || (input > max)) { 
        cout << "   Error: Enter an integer from 1-" << max << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return input;
}

/**
 * @brief Ask if player will be user or cpu. Retrun bool
 * 
 * @return true 
 * @return false 
 */
bool promptCPU() {
    cout
        << "Will this player be run by a user or the computer?" << endl
        << "(Enter 1 for user, 2 for computer): ";
    return validInput(2) == 2;
}

/**
 * @brief Given a direction dir at position y and x of ship i, 
 *          check if position will put ship off board. If so, 
 *          return false. Else return true
 * 
 * @param dir 
 * @param y 
 * @param x 
 * @param i 
 * @return true 
 * @return false 
 */
bool validDir(string dir, int y, int x, int i) {
    if (((dir == "up") && (y - shipSize[i] >= -1)) ||
        ((dir == "down") && (y + shipSize[i] <= 10)) ||
        ((dir == "left") && (x - shipSize[i] >= -1)) ||
        ((dir == "right") && (x + shipSize[i] <=10)))
        return true;
    else
        return false;
}

/**
 * @brief Prompt user to enter to clear screen and conitue game. 
 *          Used between turns to hide boards.
 * 
 */
void turnover() {
    cout << endl << "Turnover players. Press enter to continue . . . ";

    if (cin.peek() == '\n') {
        // If the next character is already '\n', just consume it
        cin.get();
    } else {
        // Otherwise, flush garbage up to newline
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cin.get(); // Now wait for one clean Enter press
    cout << "\033[2J\033[1;1H"; 
}

/**
 * @brief Given a board as a reference and a boolean to 
 *          determine if player is user or cpu. If cpu, 
 *          randomize. Otherwise, ask to randomize or not. If 
 *          not, run through each ship placement validating 
 *          input, placement, and placing ships.
 * 
 * @param playerBoard 
 * @param isCPU 
 */
void setUpBoard(Board &playerBoard, bool isCPU) {
    int col;
    int row;
    string face;
    bool placed;

    if(!isCPU) {
        cout
        << endl
        << "Would you like to randomize or control the placement of your ships?" << endl
        << "(Enter 1 to randomize, 2 to control): ";        
    }
    if(validInput(2) == 1 || isCPU) {
        for(int a = 0; a < shipNum; a++) {
            do {
                row = rand() % 10;
                col = rand() % 10;
                do {
                    string directions[4] = {"up", "down", "left", "right"};
                    face = directions[rand() % 4];
                } while(!validDir(face, row, col, a));
            } while(!playerBoard.placeShip(Ship(a), row, col, face));
        }
        playerBoard.displayBoard(false);
        if(isCPU)
            system("clear");    
        turnover();
    }
    else {
        cout
            << endl
            << "Choose a location for the stern of each ship. Then, chose a direction." << endl;
        playerBoard.displayBoard(false);

        for(int a = 0; a < shipNum; a++) {
            cout << shipName[a] << endl;
            do {
                cout << " - Row: ";
                row = validInput(rowNum);
                row--;
                cout << " - Collumn: ";
                col = validInput(colNum);
                col--;
                cout << " - Up, Down, Left, or Right: ";
                while(1) {
                    cin >> face;
                    transform(face.begin(), face.end(), face.begin(), ::tolower);
                    if (validDir(face, row, col, a))
                        break;  
                    else 
                        cout << "   Error: Invalid direction or ship is off board. Select a new choice from above: ";
                }
                placed = playerBoard.placeShip(Ship(a), row, col, face);
                if(!placed)
                    cout << "   Error: Overlapping ships. Reposition ship." << endl;
            } while(!placed);
            playerBoard.displayBoard(false);
        }
        turnover();
    }
}

/**
 * @brief Run a random turn if cpu, otherwise prompt row and 
 *          column. Validate input, shot location, then fire 
 *          the shot. If its a hit, prompt a new shot.
 * 
 * @param defBoard 
 * @param atkBoard 
 * @param isCPU 
 * @return true 
 * @return false 
 */
bool turn(Board &defBoard, Board &atkBoard, bool isCPU) {
    int row;
    int col;

    if(isCPU) {
        do {
            if(atkBoard.victory())
                return true;
            do {
                row = rand() % 10;
                col = rand() % 10;            
            } while(!atkBoard.validShot(row, col));
        } while(atkBoard.fireShot(row, col));
        system("clear");
        turnover();
        return false;
    }
    else {
        do {
            do {
                atkBoard.displayBoard(true);
                defBoard.displayBoard(false);
                cout << endl;
                if(atkBoard.victory())
                    return true;
                cout << "Take your shot!" << endl
                    << " - Row: ";
                row = validInput(rowNum);
                row--;
                cout << " - Column: ";
                col = validInput(colNum);
                col--;
                if(!atkBoard.validShot(row, col)) 
                    cout << "Position has already been shot. Chose a new target." << endl;    
            } while(!atkBoard.validShot(row, col));

        } while(atkBoard.fireShot(row, col));
        
        atkBoard.displayBoard(true);
        defBoard.displayBoard(false);
        turnover();
        turnover();
        return false;        
    }

}

/**
 * @brief Display victory screen
 * 
 * @param player 
 */
void winner(int player)
{
    cout 
    << "* * * * * * * * * * * *" << endl
    << "VICTORY! PLAYER " << player << " WINS!" << endl
    << "* * * * * * * * * * * *" << endl 
    << endl;
}

/**
 * @brief This function will log the plays made by the players and print some
 *          statistics at the end of the game.
 * 
 * Global Variables above main:
 * string logPlayer = "\0";
 * string logCoordinate = "\0";
 * string logHitMiss = "\0";
 * string logSunk = "\0";
 * 
 */
void sendToLogInGame(string logPlayer, string logCoordinate, string logHitMiss, string logSunk, ofstream& battleLog)
{
    // Organize the input data and send to the battleship.log
    battleLog << logPlayer << ": " << logCoordinate << " " << logHitMiss << " " << logSunk << endl;

    //I think it might be necessary to reset logSunk so that it doesnt spam the log until a new ship is sunk
    logSunk = "";
}

/**
 * @brief This function calculates the statistics of the game and writes that to the log file
 * 
 * @param p1Board 
 * @param p2Board 
 * @param battleLog 
 */
void sendToLogEndgame(Board p1Board, Board p2Board, ofstream& battleLog)
{
    // Initialize variables
    int p1HitSum = 0;
    int p1MissSum = 0;
    int p1TotalShots = 0;
    int p2HitSum = 0;
    int p2MissSum = 0;
    int p2TotalShots = 0;
    double p1Ratio = 0.0;
    double p2Ratio = 0.0;
    
    for(int rowCount = 0; rowCount < rowNum; rowCount++)
    {
        for(int colCount = 0; colCount < colNum; colCount++)
        {
            char grid1 = p1Board.getCord(rowCount, colCount);
            if(grid1 == 'X')
            {
                // Add to player1HitSum
                p1HitSum++;
            }
            else if(grid1 == 'O')
            {
                // Add to player1MissSum
                p1MissSum++;
            }
        }
    }

    for(int i = 0; i < rowNum; i++)
    {
        for(int count = 0; count < colNum; count++)
        {
            char grid2 = p2Board.getCord(i, count);
            if(grid2 == 'X')
            {
                // Add to player1HitSum
                p2HitSum++;
            }
            else if(grid2 == 'O')
            {
                // Add to player1MissSum
                p2MissSum++;
            }
        }
    }

    // Add hits and misses for total shots
    p1TotalShots = p1HitSum + p1MissSum;

    // Calculate Hit/Miss Ratio
    // I think it's supposed to be the ratio of hits to total shots (I edited it) -Isaiah
    p1Ratio = (static_cast<double>(p1HitSum) / p1TotalShots) * 100;

    // Add hits and misses for total shots
    p2TotalShots = p2HitSum + p2MissSum;

    // Calculate Hit/Miss Ratio
    // I think it's supposed to be the ratio of hits to total shots (I edited it) -Isaiah
    p2Ratio = (static_cast<double>(p2HitSum) / p2TotalShots) * 100;

    // player1HitSum compared to player2HitSum (Higher value wins the game)
    if(p1HitSum > p2HitSum)
    {
        battleLog << "Player1 wins, Player2 loses\n\n";
    }
    else if(p1HitSum < p2HitSum)
    {
        battleLog << "Player2 wins, Player1 loses\n\n";
    }

    battleLog 
    << "*** Player1 Stats ***" << endl
    << "Number of Hits   : " << p1HitSum << endl
    << "Number Misses    : " << p1MissSum << endl
    << "Total Shots      : " << p1TotalShots << endl
    << "Hit/Miss Ratio   : " << p1Ratio << "%" << endl
    << endl
    << "*** Player2 Stats ***" << endl
    << "Number of Hits   : " << p2HitSum << endl
    << "Number Misses    : " << p2MissSum << endl
    << "Total Shots      : " << p2TotalShots << endl
    << "Hit/Miss Ratio   : " << p2Ratio << "%" << endl;
}

