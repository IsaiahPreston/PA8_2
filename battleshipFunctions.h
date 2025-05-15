/**
 * @file ship.h
 * @author Isaiah Justin Brian
 * @brief Header funcitons and member variables for ship.cpp, 
 *          #include files, global constants and strings.
 * @version 0.1
 * @date 2025-04-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef BATTLESHIPFUNCTIONS_H
#define BATTLESHIPFUNCTIONS_H

#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <fstream>
#include <limits>
#include <algorithm>
using namespace std;

const string shipName[] = {"Carrier", "Battleship", "Cruiser", "Submarine", "Destroyer"};
const int shipSize[] = {5, 4, 3, 3, 2};
const char shipLetter[] = {'c', 'b', 'r', 's', 'd'};
const int shipNum = 5;
const int rowNum = 10;
const int colNum = 10;

extern string logPlayer;
extern string logCoordinate;
extern string logHitMiss;
extern string logSunk;

class Ship {
public:
    Ship(int shipIndex);
    string getShipName();
    int getShipSize();
    char getShipLetter();
private:
    string mShipName;
    int mShipSize;
    char mShipLetter;
};

class Board {
public:
    Board();
    bool validShipPos(Ship fSetShip, int fY, int fX, string fDir);
    bool placeShip(Ship setShip, int y, int x, string dir);
    void displayBoard(bool atkBoard);
    bool validShot(int fY, int fX);
    bool shotHit(int fY, int fX);
    void checkSunk(int fY, int fX);
    bool fireShot(int y, int x);
    bool victory();
    char getCord(int row, int col);
private:
    char mCoord[rowNum][colNum];
};

void welcome();
int validInput(int max);
bool promptCPU();
bool validDir(string dir, int y, int x, int i);
void turnover();
void setUpBoard(Board &playerBoard, bool isCPU);
bool turn(Board &defBoard, Board &atkBoard, bool isCPU);
void winner(int player);
void sendToLogInGame(string logPlayer, string logCoordinate, string logHitMiss, string logSunk, ofstream& battleLog);
void sendToLogEndgame(Board p1Board, Board p2Board, ofstream& battleLog);

#endif