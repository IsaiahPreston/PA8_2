/**
 * @file ship.cpp
 * @author Isaiah Justin Brian
 * @brief Class of ships initialized with some index. Index 
 *          corresponds to ship name, size, and character via 
 *          global constants in ship.h. Functions here call 
 *          those values for the ship.
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
 * @brief Construct a new Ship object of index shipIndex
 * 
 * @param shipIndex 
 */
Ship::Ship(int shipIndex) {
    mShipName = shipName[shipIndex];
    mShipSize = shipSize[shipIndex];
    mShipLetter = shipLetter[shipIndex];
}

/**
 * @brief Get the Ship Name object
 * 
 * @return string 
 */
string Ship::getShipName() {
    return mShipName;
}

/**
 * @brief Get the Ship Size object
 * 
 * @return int 
 */
int Ship::getShipSize() {
    return mShipSize;
}

/**
 * @brief Get the Ship Letter object
 * 
 * @return char 
 */
char Ship::getShipLetter() {
    return mShipLetter;
}

