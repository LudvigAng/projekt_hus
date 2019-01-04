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

void createKermit(int width, int height, MapT *houseMap, playerValues *kermit);

void kermitAction(inputT playerChoice, playerValues *kermit, MapT houseMap);

void updateKermitValues(MapT houseMap, playerValues *kermit);

void kermitVisibility(MapT houseMap, playerValues *kermit);

void removeKermitVisibility(MapT houseMap, playerValues *kermit);

void kermitMove(inputT playerChoice, MapT houseMap, playerValues *kermit);

void checkIfPointPickup(MapT houseMap, playerValues *kermit);

void placePoints(MapT *houseMap, int mapstate);

void placeDynamite(MapT *houseMap, int mapstate);

int grabItem(inputT playerChoice, MapT houseMap, playerValues *kermit);

int checkForDoor(MapT houseMap, playerValues *kermit);

int openDoor(MapT houseMap, playerValues *kermit);

int openExitDoor(MapT houseMap, playerValues *kermit);

int winGame(int height, int width, MapT houseMap, playerValues *kermit);

int allowingMovementSymbols(inputT playerChoice, MapT houseMap, playerValues *kermit);

void useDynamite(MapT houseMap, playerValues *kermit);

void printInventory(playerValues *kermit);

void placeLevers(MapT *houseMap, int mapstate);

void transformMap(MapT *houseMap, playerValues *kermit);

void loadEasyMap(MapT *houseMap, playerValues *kermit);

void placeObjectsOnMap(MapT *houseMap, int mapstate);

void checkIfTransformMap(inputT playerChoice, MapT *houseMap, playerValues *kermit);

void loadHardMap(MapT *houseMap, playerValues *kermit);


void displayMap(MapT houseMap);
#endif
