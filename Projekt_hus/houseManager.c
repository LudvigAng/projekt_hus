/*
* File: houseManager.c
* Version: 1.1
* Last modified on Tue Nov 28 2018 by CaAn
* -----------------------------------------------------
* This interface provides the basic functions for the house game
* These functions must not be changed by the student.
*/

#include "houseManager.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

MapT createMap(int width, int heigth, int noOfWalls)
{
	MapT tMap;

	tMap.heigth = heigth;
	tMap.width = width;

	//Creates the array for the house map
	tMap.mArr = (char **)malloc(heigth * sizeof(char*)); 
	for (int r = 0; r < heigth; r++)
		tMap.mArr[r] = (char *)malloc(width);
	//Create the array for setting the visible parts of the house map 
	tMap.vArr = (int **)malloc(heigth * sizeof(int*));
	for (int r = 0; r < heigth; r++)
		tMap.vArr[r] = (int*)malloc(width * sizeof(int));

	//Fill the array's with initial values, OUTERWALL for edge and space for the inner space and 1 for visible and 0 for not visible
	for (int r = 0; r < heigth; r++)
		for (int k = 0; k < width; k++) {
			if (r == 0 || r == (heigth - 1) || k == 0 || k == (width - 1)) {
				tMap.mArr[r][k] = OUTERWALL;
				tMap.vArr[r][k] = 1;
			}
			else {
				tMap.mArr[r][k] = EMPTYSPACE;
				tMap.vArr[r][k] = 0;
			}
		}

	//Place walls INNERWALL marks a wall. An inner wall is always placed stretching from one of the edges 
	int r, k, rMax, rMin, kMax, kMin;
	int *pkValues = (int *)malloc(noOfWalls * sizeof(int)); // Remember the column for each vertical wall
	int *prValues = (int *)malloc(noOfWalls * sizeof(int)); // Remember the row for each horizontal wall
	for (int i = 0; i < noOfWalls; i++)
		pkValues[i] = prValues[i] = 0;
	//The walls are evenly distributed to stretch out from each of the 4 edges of the house
	for (int w = 0; w < noOfWalls; w++) {
		if (w % 2 == 0){
			k = rand() % (width - HIGHOFFSET) + LOWOFFSET;
			k += adjustValue(pkValues, noOfWalls, k);
			rMax = (w % 4 == 0) ? (rand() % (heigth - 2) + 1) : (heigth - 1);
			rMin = (w % 4 == 0) ? 1 : (rand() % (heigth - 2) + 1);
			for(r = rMin; r < rMax; r++)
				tMap.mArr[r][k] = INNERWALL;
		}
		else  { 
			r = rand() % (heigth - HIGHOFFSET) + LOWOFFSET;
			r += adjustValue(prValues, noOfWalls, r);
			kMax = (w % 4 == 1) ? (rand() % (width - 2) + 1) : (width - 1);
			kMin = (w % 4 == 1) ? 1 : (rand() % (width - 2) + 1);
			for (k = kMin; k < kMax; k++)
				tMap.mArr[r][k] = INNERWALL;
		}
	}
	//Release memory allocated on the heap that is only used locally when the function is run
	free(pkValues);  
	free(prValues);

	// Place one main entrance to house with "M"-character 
	// Choose side and select random position and check that no wall inside
	int side;
	do {
		side = rand() % 4 + 1;
		r = (side == 1 ? 0 : (side == 3 ? (heigth - 1) : rand() % (heigth - HIGHOFFSET) + LOWOFFSET));
		k = (side == 2 ? 0 : (side == 4 ? (width - 1) : rand() % (width - HIGHOFFSET) + LOWOFFSET));
	} while (!((side == 1 && tMap.mArr[r + 1][k] != INNERWALL) || (side == 3 && tMap.mArr[r - 1][k] != INNERWALL) || (side == 2 && tMap.mArr[r][k + 1] != INNERWALL) || (side == 4 && tMap.mArr[r][k - 1] != INNERWALL)));
	tMap.mArr[r][k] = MAINENTRANCE;

	//Place doors on the inner walls
	placeDoors(tMap);

	return tMap;
}

static void placeDoors(MapT tMap)
{
	/* This function places doors on inner walls in the house-map. It traverses the edges of the map and when an inner wall is found it 
	   follows that wall and places a door in each section of that wall. A section is the part between other walls intersecting the wall. 
	   There are four edges of the house, numbered 1 to 4. Edges 3 and 4 mirrors edges 1 and 2 resp. The function uses the indexes 
	   m for column and n for row. The function ti() is a helper function for mirroring the indexes. 
	   The function also places one key for each door. */
	int r0, r1, r2, k0, k1, k2;  //The mirrored indexes for rows (r0, r1, r2) and columns (k0, k1, k2) calculated by the function ti()
	for (int side = 1; side < 5; side++) {
		if (side == 1 || side == 3) { //Top (side = 1) or bottom (side = 3) edges of the house
			int mPrev = 1; //Collect the position of a crossing wall and remember the previous position
			for (int m = 1; m < tMap.width - 1; m++) { // Move along the edge of the house
				int n = 1;
				r1 = ti(n, tMap.heigth, side);
				r2 = ti(n + 1, tMap.heigth, side);
				k0 = ti(m - 1, tMap.width, side);
				k1 = ti(m, tMap.width, side);
				k2 = ti(m + 1, tMap.width, side);
				if (tMap.mArr[r1][k1] == INNERWALL) { //Check if we encounter a vertical inner wall
					int nPrev = n; //Collect the positon of a crossing wall and remember the previous position
					while (tMap.mArr[r1][k1] == INNERWALL) { //Move along the wall
						if ((tMap.mArr[r1][k2] == INNERWALL) || (tMap.mArr[r1][k0] == INNERWALL) || (tMap.mArr[r2][k1] == OUTERWALL)) {
							tMap.mArr[ti(nPrev + (rand() % (abs(nPrev - n) - 1)), tMap.heigth, side)][k1] = DOOR; //Places the door in a random position on the wall
							placeKey(tMap, ti(mPrev, tMap.width, side), k1, ti(nPrev, tMap.heigth, side), r1, side);
							nPrev = n + 1;
						}
						n++; 
						r1 = ti(n, tMap.heigth, side);
						r2 = ti(n + 1, tMap.heigth, side);
					}
					mPrev = m + 1;
				}
			}
		}
		else {  //Now left (side = 3) or right (side = 4) edges of the house
			int nPrev = 1; //Collect the positon of a crossing wall and remember the previous position
			for (int n = 1; n < tMap.heigth - 1; n++) { // Move along the edge of the house
				int m = 1;
				r0 = ti(n - 1, tMap.heigth, side);
				r1 = ti(n, tMap.heigth, side);
				r2 = ti(n + 1, tMap.heigth, side);
				k1 = ti(m, tMap.width, side);
				k2 = ti(m + 1, tMap.width, side);
				if (tMap.mArr[r1][k1] == INNERWALL) { //Check if we encounter a horizontal inner wall
					int mPrev = m;
					while (tMap.mArr[r1][k1] == INNERWALL) { //Move along the wall
						if ((tMap.mArr[r2][k1] == INNERWALL) || (tMap.mArr[r0][k1] == INNERWALL) || (tMap.mArr[r1][k2] == OUTERWALL)) {
							tMap.mArr[r1][ti(mPrev + (rand() % (abs(mPrev - m) - 1)), tMap.width, side)] = DOOR; //Places the door in a random position on th wall
							placeKey(tMap, ti(mPrev, tMap.width, side), k1, ti(nPrev, tMap.heigth, side), r1, side);
							mPrev = m + 1;
						}
						m++; 
						k1 = ti(m, tMap.width, side);
						k2 = ti(m + 1, tMap.width, side);
					}
					nPrev = n + 1;
				}
			}
		}
	}
}

static int ti(int ind, int v , int s)
{
	return (s < 3 ? ind : v - 1 - ind);
}

void drawMap(MapT theMap)
{
	printf("\n");
	for (int r = 0; r < theMap.heigth; r++) {
		for (int k = 0; k < theMap.width; k++)
			printf(" %c", (theMap.vArr[r][k] ? theMap.mArr[r][k] : EMPTYSPACE));
		printf("\n");
	}
}

void drawMapVisibility(MapT theMap)
{
	printf("\n");
	for (int r = 0; r < theMap.heigth; r++) {
		for (int k = 0; k < theMap.width; k++)
			printf(" %d", theMap.vArr[r][k]);
		printf("\n");
	}
}


static int adjustValue(int *pValues, int noOfValues, int searchValue)
{
	/* This function is a helper function that prohibits walls to be to close to each other */
	int i = 0;
	for (; i < noOfValues; i++) {
		if (pValues[i] == 0)
			break;
		else if (pValues[i] == searchValue)
			return 0;
		else if (abs(pValues[i] - searchValue) <= MAXWALLSEPARATION)
			return (pValues[i] - searchValue);
	}
	pValues[i] = searchValue;
	return 0;
}

static void placeKey(MapT tMap, int colPrev, int col, int rowPrev, int row, int side)
{
	int r, k;
	do {
		r = (side % 2 == 1) ? rowPrev + (2 - side)*(rand() % (abs(rowPrev - row) - 1)) : rowPrev + (3 - side)*(rand() % (abs(rowPrev - row) - 1));
		k = (side % 2 == 1) ? colPrev + (2 - side)*(rand() % (abs(colPrev - col) - 1)) : colPrev + (3 - side)*(rand() % (abs(colPrev - col) - 1));
	} while (tMap.mArr[r][k] != EMPTYSPACE);
	tMap.mArr[r][k] = 'K';
}

void freeMap(MapT theMap)
{
	for (int r = 0; r < theMap.heigth; r++)
		free(theMap.mArr[r]);
	free(theMap.mArr);
	for (int r = 0; r < theMap.heigth; r++)
		free(theMap.vArr[r]);
	free(theMap.vArr);
}


