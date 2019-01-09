/*
* File: houseHelper.h
* Version: 1.0
* Last modified on Tue Nov 5 2018 by CaAn
* -----------------------------------------------------
* This interface provides several functions for the house game
* These functions are added by the student.
*/

#ifndef _househelper_h
#define _househelper_h

#include "houseManager.h"
#include "myIOLib.h"

enum operation { endgame, help, take, open, show, hide };
typedef enum operation operationT;
typedef const char *enumOperation[];
#define OPERATIONTEXTS { "avsluta", "hjälp", "tag", "öppna", "visa", "göm", "använd" }
#define NUMBEROFOPERATIONS 7

enum mapObject { none, key, up, down, left, right, door, map };
typedef enum mapObject mapObjectT;
typedef const char *enumMapObject[];
#define OBJECTTEXTS { "ingen", "nyckel","uppåt","nedåt","vänster","höger", "dörr","karta","dynamit", "spak" }
#define NUMBEROFOBJECTS 10

struct userInput {
	operationT op;
	mapObjectT mObj;
};
typedef struct userInput inputT;

struct userPosition {
	int row, col;
};
typedef struct userPosition positionT;

typedef struct {
	int x;
	int y;
	int last_x;
	int last_y;
	int keys;
	int points;
	int dynamite;
} playerValues;

/********************************************************************
Function: placeObject()
Usage: int success = placeObject(theMap, xPos, yPos,chr,posReceived,success);
---------------------------------------------------------------------
Purpose:Places a specific charater, symbolising an object, on the map.
Arguments: The functions takes the map-structure as a parameter, the
indexes of the place and the character to place. If index 0,0 is passed
the function will pick a random index. If the character gets a randomly 
determined position it is returned via positionT-argument.The last argument 
determines if the object-charater should be visible on the map (1=visible/0=not shown).
If placement is successful the function return 1 (true) otherwise 0 (false).
********************************************************************/
int placeObject(MapT , int, int, char, positionT *, int);

/********************************************************************
Function: getUserInput()

Purpose:reads the userinput as a string and tries to determine the operation 
and the object (to operate on).
Arguments: The functions takes no arguments.
The function return the input object as a structure of type inputT. 
This structure has two components op (of type operationT) and 
mObj (of type mapObjectT). If successful they are given the appropriate 
values, otherwhise both are set to -1.
********************************************************************/
inputT getUserInput(void);

/********************************************************************
Function: createKermit()

Purpose: Spawns Kermit (the player's character) on the map based on the map's
width and length.
********************************************************************/
void createKermit(int width, int height, MapT *houseMap, playerValues *kermit);

/********************************************************************
Function: kermitAction()

Purpose: Reads the player's input and executes an action based on it.
Things like movement, object pickups, object usage etc.
********************************************************************/
void kermitAction(inputT playerChoice, playerValues *kermit, MapT houseMap);

/********************************************************************
Function: updateKermitValues()

Purpose: Updates Kermit's last position into a blank space in order to
not make a trail of Kermits after the player. Also fills Kermit's new
position on the map.
********************************************************************/
void updateKermitValues(MapT houseMap, playerValues *kermit);

/********************************************************************
Function: kermitVisibility()

Purpose: Makes every element one step away form Kermit visible in order
to simulate his vision.
********************************************************************/
void kermitVisibility(MapT houseMap, playerValues *kermit);

/********************************************************************
Function: removeKermitVisibility()

Purpose: Removes Kermit's visibility around him, unless it's an outer
wall or outer door.
********************************************************************/
void removeKermitVisibility(MapT houseMap, playerValues *kermit);

/********************************************************************
Function: kermitMove()

Purpose: Moves Kermit into a new position based on userinput. Kermit
may only move vertically or horizontally.
********************************************************************/
void kermitMove(inputT playerChoice, MapT houseMap, playerValues *kermit);

/********************************************************************
Function: checkifPointPickup()

Purpose: Checks to see if Kermit steps on a point-symbol. If so, the 
player will be awarded 20 points.
********************************************************************/
void checkIfPointPickup(MapT houseMap, playerValues *kermit);

/********************************************************************
Function: placePoints()

Purpose: Places points for the player to pickup on the map upon creation.
The amount of points placed depends on the mapstate.
********************************************************************/
void placePoints(MapT *houseMap, int mapstate);

/********************************************************************
Function: placeDynamite()

Purpose: Places dynamites for the player to pickup on the map upon creation.
The amount of dynamites placed depends on the mapstate.
********************************************************************/
void placeDynamite(MapT *houseMap, int mapstate);

/********************************************************************
Function: grabItem()

Purpose: Checks if there are any keys or dynamites nearby for the player to pickup.
If so, the object-symbol will be replaced by a blank space. If there is
no object to pickup the player will receive a message.
********************************************************************/
int grabItem(inputT playerChoice, MapT houseMap, playerValues *kermit);

/********************************************************************
Function: checkForDoor()

Purpose: Checks to see if there's a door nearby the player can open.
If there's an inner door the function returns 1. A nearby outer door
returns 2.
********************************************************************/
int checkForDoor(MapT houseMap, playerValues *kermit);

/********************************************************************
Function: openDoor()

Purpose: Replaces a nearby inner door with blank space and takes away
a key from the player. If the player is out of keys he/she will receive
a message.
********************************************************************/
int openDoor(MapT houseMap, playerValues *kermit);

/********************************************************************
Function: openExitDoor()

Purpose: Replaces a nearby outer door with blank space and takes away
a key from the player. If the player is out of keys he/she will receive
a message.
********************************************************************/
int openExitDoor(MapT houseMap, playerValues *kermit);

/********************************************************************
Function: checkIfGameExit()

Purpose: Checks to see if Kermit is outside the house, which will result
in the game ending. If so, the player will receive 100 points and the function
will return 0, ending the game loop. If Kermit is not outside the house
the game will continue.
********************************************************************/
int checkIfGameExit(int height, int width, inputT playerChoice, MapT houseMap, playerValues *kermit);

/********************************************************************
Function: allowingMovementSymbols()

Purpose: Checks to see the element Kermit is about to step into is 
allowed, which is either has to be a blank space or a point. If such
is the case the function will return 1. If the element is something else
the function will return 0 and block a potential move by the player.
********************************************************************/
int allowingMovementSymbols(inputT playerChoice, MapT houseMap, playerValues *kermit);

/********************************************************************
Function: useDynamite()

Purpose: Replaces all elements in a 5x5 radius with blank spaces, except
for outer walls and outer doors. Upon usage the player loses a dynamite.
If the player doesn't have a dynamite he/she will receive a message.
********************************************************************/
void useDynamite(MapT houseMap, playerValues *kermit);

/********************************************************************
Function: printInventory()

Purpose: Prints the player's inventory. E.g. the keys, dynamite and points.
********************************************************************/
void printInventory(playerValues *kermit);

/********************************************************************
Function: placeLevers()

Purpose: Places levers for the player to pickup on the map upon creation.
The amount of levers placed depends on the mapstate.
********************************************************************/
void placeLevers(MapT *houseMap, int mapstate);

/********************************************************************
Function: transformMap()

Purpose: Transforms the map into an easier or harder one randomly.
********************************************************************/
void transformMap(MapT *houseMap, playerValues *kermit);

/********************************************************************
Function: loadEasyMap()

Purpose: Loads an easier map with fewer walls and more points and objects
for the player to pickup. The player also receives three keys and a dynamite.
********************************************************************/
void loadEasyMap(MapT *houseMap, playerValues *kermit);

/********************************************************************
Function: placeObjectsOnMap()

Purpose: Places all points, dynamites and levers on the map.
********************************************************************/
void placeObjectsOnMap(MapT *houseMap, int mapstate);

/********************************************************************
Function: checkIfTransformMap()

Purpose: Checks to see if the user wants to pull a nearby lever.
********************************************************************/
void checkIfTransformMap(inputT playerChoice, MapT *houseMap, playerValues *kermit);

/********************************************************************
Function: loadHardMap()

Purpose: Loads a harder map with more walls and less points and objects
for the player to pickup.
********************************************************************/
void loadHardMap(MapT *houseMap, playerValues *kermit);

/********************************************************************
Function: showHelp()

Purpose: Prints the rules and descriptions for objects for the player to read.
********************************************************************/
void showHelp(void);




void exitSave(MapT houseMap, playerValues *kermit);

void openSave(MapT *houseMap, playerValues *kermit);

//int HighscoreSave(playerValues *kermit);

void winGame(playerValues *kermit);

int playerExit(MapT houseMap, playerValues *kermit);

//void newGame(int width, int height, int noOfWalls, int *playGame, int mapstate, MapT *houseMap, playerValues *kermit);

/********************************************************************
Function: displayMap()

Purpose: Makes the entire map visible for the player. (IS/WAS ONLY USED
DURING THE MAKING OF THE GAME).
********************************************************************/
void displayMap(MapT houseMap);
#endif
