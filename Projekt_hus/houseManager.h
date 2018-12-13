/*
* File: houseManager.h
* Version: 1.1
* Last modified on Tue Nov 28 2018 by CaAn
* -----------------------------------------------------
* This interface provides the basic functions for the house game
* These functions must not be changed by the student.
*/

#ifndef _housemanager_h
#define _housemanager_h

#include <stdio.h>
#include <stdlib.h>

struct houseMap {
	int width;
	int heigth;
	char **mArr; //Holds the actual map 
	int **vArr; //1 for the parts visible on the map, 0 if not visible
};

typedef struct houseMap MapT;

#define HIGHOFFSET 10
#define LOWOFFSET 5
#define MAXWALLSEPARATION 3
#define OUTERWALL 'e'
#define INNERWALL 'w'
#define DOOR 'D'
#define MAINENTRANCE 'M'
#define EMPTYSPACE ' '

/********************************************************************
Function: CreateMap()
Usage: Mapt theMap = createMap(width,heigth,noOfWalls);
---------------------------------------------------------------------
Purpose: Creates the map including surrounding walls and the inner walls
Also places doors and main entrance. Each door will receive a key nearby
the door.
Arguments:The functions takes three arguments: the width, the heigth and 
the number of inner walls.It returns a structure with a pointer to a two 
dimensional array. The structure also has the size of the array i.e. 
width and heigth of the house.
********************************************************************/
MapT createMap(int width, int heigth, int noOfWalls);

/********************************************************************
Function: drawMap()
Usage: drawMap(theMap);
---------------------------------------------------------------------
Purpose: draws the map in the console window.
Arguments: The functions takes the map-structure as a parameter.
********************************************************************/
void drawMap(MapT theMap);

/********************************************************************
Function: drawMapVisibility()
Usage: drawMapVisibility(theMap);
---------------------------------------------------------------------
Purpose: draws the visibility map in the console window.
Arguments: The functions takes the map-structure as a parameter.
********************************************************************/
void drawMapVisibility(MapT theMap);

/********************************************************************
Function: adjustValue()
Usage: ---
---------------------------------------------------------------------
Purpose: A helper function that finds if a value exists already in the
array passed to the function. The value will be added to the array if
value is not in the array and not adjacent to any other value.
The purpose in this application is to prohibit that inner walls are to 
close to each other, thereby avoiding narrow passages or rooms.
The functions takes a search-value, an array and it's size as parameters.
The return-value will be:
0 if search-value is found or not adjacent to any of the values,
(found-value - search-value) if values are adjacent.
This is a helper function used by createMap-function.
********************************************************************/
static int adjustValue(int *pValues, int noOfValues, int searchValue);

/********************************************************************
Function: placeDoors()
Usage: ---
---------------------------------------------------------------------
Purpose: Places doors on the drawn map. 
Arguments: The functions takes the map-structure as a parameter.
This is a helper function used by createMap-function.
********************************************************************/
static void placeDoors(MapT theMap);

/********************************************************************
Function: placeKeys()
Usage: ---
---------------------------------------------------------------------
Purpose: Places keys on the drawn map. It should be possible to
find a key to a door inside a room. However the function will leave
one or two rooms without a key.
Arguments: The functions takes the map-structure as a parameter.
This is a helper function used by placeDoors-function.
********************************************************************/
static void placeKey(MapT theMap, int bPrev, int b, int cPrev, int c, int side);

/********************************************************************
Function: ti()
Usage: ---
---------------------------------------------------------------------
Purpose: Mirrors the map.
Arguments: The functions takes the map-index as a parameter, and returns 
the mirrored index.
This is a helper function used by getDoors-function.
********************************************************************/
static int ti(int ind, int v, int s);

/********************************************************************
Function: freeMap()
Usage: freeMap(theMap);
---------------------------------------------------------------------
Purpose: Free the allocated memory for the array's containing the map
Arguments: The functions takes the map-structure as a parameter.
********************************************************************/
void freeMap(MapT theMap);

#endif


