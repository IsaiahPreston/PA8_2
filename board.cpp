/**
 * @file board.cpp
 * @author Isaiah Justin Brian
 * @brief Class of board objects to hold a 2d array of 
 *          characters. Initializes to all '-'. Updates to 
 *          with functions.
 * @version 0.1
 * @date 2025-04-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "battleshipFunctions.h"
// string logPlayer;
// string logCoordinate;
// string logHitMiss;
// string logSunk;

/**
 * @brief Construct a new Board object. Initializes mCoord 
 *          array to all '-'
 * 
 */
Board::Board() {
    for(int y = 0; y < rowNum; y++) {
        for(int x = 0; x < colNum; x++){
            mCoord[y][x] = '-';
        }
    }
}

/**
 * @brief Determines if the desired ship object at the 
 *          coordinates in the direction is overlapping 
 *          another ship
 * 
 * @param fSetShip 
 * @param fY 
 * @param fX 
 * @param fDir 
 * @return true 
 * @return false 
 */
bool Board::validShipPos(Ship fSetShip, int fY, int fX, string fDir) {
    for(int a = 1; a <= fSetShip.getShipSize(); a++) {
        if(mCoord[fY][fX] != '-')
            return false;
        if(fDir == "up") 
            fY--;
        else if(fDir == "down")
            fY++;
        else if(fDir == "left")
            fX--;
        else if(fDir == "right")
            fX++;
    }
    return true;
}

/**
 * @brief Updates mCoord array with letters of corresponding 
 *          ship object at location and direction
 * 
 * @param setShip 
 * @param y 
 * @param x 
 * @param dir 
 * @return true 
 * @return false 
 */
bool Board::placeShip(Ship setShip, int y, int x, string dir) {
    if(!validShipPos(setShip, y, x, dir))
        return false;
    for(int a = 1; a <= setShip.getShipSize(); a++) {
        mCoord[y][x] = setShip.getShipLetter();
        if(dir == "up") 
            y--;
        else if(dir == "down")
            y++;
        else if(dir == "left")
            x--;
        else if(dir == "right")
            x++;
    }
    return true;
}

/**
 * @brief Displays either full board (paramater atkBoard = 
 *          false), or board with ships hidden board 
 *          (atkBoard = true)
 * 
 */
void Board::displayBoard(bool atkBoard) {
    cout << endl;
    cout << "   1 2 3 4 5 6 7 8 9 10" << endl;
    for(int y = 0; y < rowNum; y++) {
        cout << setw(2) << y + 1 << " ";
        for(int x = 0; x < colNum; x++){
            if(atkBoard) {
                bool occupied = false;
                for(int a = 0; a < shipNum; a++)
                    if(mCoord[y][x] == shipLetter[a]) {
                        occupied = true;
                        break;
                    }
                if(occupied)
                    cout << '-' << ' ';
                else
                    cout << mCoord[y][x] << ' ';
            }
            else
                cout << mCoord[y][x] << " ";
        }
        cout << endl;
    }
}

/**
 * @brief Returns true if location is a hit, false for a miss
 * 
 * @param fY 
 * @param fX 
 * @return true 
 * @return false 
 */
bool Board::validShot(int fY, int fX) {
    if(mCoord[fY][fX] == 'X' || mCoord[fY][fX] == 'O')
        return false;
    else
        return true;
}

/**
 * @brief Return true if space has already been shot
 * 
 * @param fY 
 * @param fX 
 * @return true 
 * @return false 
 */
bool Board::shotHit(int fY, int fX) {
    if(mCoord[fY][fX] == '-') 
        return false;         
    else
        return true;        
}

/**
 * @brief Runs after every shot before updating location with 
 *          'X' or 'O'. If the location is a hit and the only 
 *          character of that ship remaining on the board, then 
 *          this shot will sink the ship. Display "sunk" message 
 *          and update board.
 * 
 * @param fY 
 * @param fX 
 */
void Board::checkSunk(int fY, int fX) {
    int targetsRemaining = 0;
    for(int a = 0; a < shipNum; a++) {
        if(mCoord[fY][fX] == shipLetter[a]) {
            for(int y = 0; y < rowNum; y++)
                for(int x = 0; x < colNum; x++)
                    if(mCoord[y][x] == shipLetter[a])
                        targetsRemaining++;
        if(targetsRemaining == 1)
        {
            cout << "You sunk the " << shipName[a] << endl;
            logSunk = shipName[a];
        }
    }
}
}

/**
 * @brief Check if coord is a dash or ship. Cout and update board
 * 
 * @param y 
 * @param x 
 * @return true 
 * @return false 
 */
bool Board::fireShot(int y, int x)
{
    if(shotHit(y, x)) {          
        cout << "Hit!" << endl; 
        checkSunk(y, x);
        mCoord[y][x] = 'X'; 
        return true;
    }
    else {
        cout << "Miss!" << endl;
        mCoord[y][x] = 'O';
        return false;
    }
}

/**
 * @brief Check board. If any ships exist, return false
 * 
 * @return true 
 * @return false 
 */
bool Board::victory() {
    for(int y = 0; y < rowNum; y++)
        for(int x = 0; x < colNum; x++)
            for(int a = 0; a < shipNum; a++)
                if(mCoord[y][x] == shipLetter[a])
                    return false;
    return true;
}

/**
 * @brief Get the coordinates on board for claculating hits and misses.
 *          Needed for the sendToLogEndgame function.
 * 
 * @param row 
 * @param col 
 * @return char 
 */
char Board::getCord(int row, int col)
{
    if(row >= 0 && row < rowNum && col >= 0 && col < colNum)
    {
        return mCoord[row][col];
    }
    else
    {
        cout << "Error with getCord in the board class.\n";
        return '.';
    }
}