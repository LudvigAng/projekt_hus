/*
* File: houseHelper.c
* Version: 1.0
* Last modified on Tue Nov 16 2018 by CaAn
* -----------------------------------------------------
* This interface provides several functions for the house game
* These functions are added by the student.
*/

#include "houseManager.h"
#include "houseHelper.h"
#include <string.h>
#include <ctype.h>



int  placeObject(MapT tMap, int row, int col, char chObj, positionT *pos, int visibility)
{
	if (row < 0 || row > tMap.heigth - 1 || col < 0 || col > tMap.width - 1) //Outside housemap
		return 0;
	if (row == 0 && col == 0) { //Select random values for row and col
		for (int i = 0; i < 100 && tMap.mArr[row][col] != ' ' ; i++) {
			row = rand() % (tMap.heigth - 2) + 1;
			col = rand() % (tMap.width - 2) + 1;
		} 
	}
	if (tMap.mArr[row][col] != ' ')
		return 0;
	tMap.mArr[row][col] = chObj;
	tMap.vArr[row][col] = visibility;
	pos->row = row;
	pos->col = col;
	return 1;
}

inputT getUserInput(void)
{
	unsigned char * input = getString("\nVad vill du göra: "); // getString() from the myIOLib library or use similar function in Roberts library 
	int countA = 0, countB = 0;
	unsigned char * operationStr = NULL;
	unsigned char * objectStr = NULL;
	while (input[countA] != ' ' && input[countA] != '\0')
		countA++;
	if (countA > 0) { //Read first part of string as the operation
		operationStr = (unsigned char *)malloc((countA + 1) * sizeof(unsigned char));
		for (int i = 0; i < countA; i++)
			operationStr[i] = input[i];
		operationStr[countA] = '\0';
		if (input[countA] != '\0') { //Read second part of string as the object to operate on
			countB = countA + 1;
			while (input[countB] != '\0')
				countB++;
			objectStr = (unsigned char*)malloc((countB - countA) * sizeof(unsigned char));
			int j = 0;
			for (int i = (countA + 1); i < countB; i++, j++)
				objectStr[j] = input[i];
			objectStr[j] = '\0';
		}
	}
	//Start appropriate action
	//Find index for the operation and for the object
	enumOperation operationArr = OPERATIONTEXTS;
	enumMapObject objectArr = OBJECTTEXTS;
	inputT inpObj;
	inpObj.op = -1;
	if (operationStr != NULL)
		for (inpObj.op = endgame; inpObj.op < NUMBEROFOPERATIONS; inpObj.op++) {
			if (!strcoll(operationStr, operationArr[inpObj.op]))
				break;
		}
	inpObj.mObj = -1;
	if (objectStr != NULL)
		for (inpObj.mObj = key; inpObj.mObj < NUMBEROFOBJECTS; inpObj.mObj++) {
			if (!strcmp(objectStr, objectArr[inpObj.mObj]))
				break;
		}
	//Release memory allocated on the heap that is only used locally when the function is run
	free(input); //Memory allocated by the getString() function
	free(operationStr);
	free(objectStr);
	return inpObj;
}


void createKermit(int width, int height, MapT *houseMap, playerValues *kermit) {
	kermit->x = height / 2;
	kermit->y = width / 2;

	houseMap->mArr[kermit->x][kermit->y] = '@';
	houseMap->vArr[kermit->x][kermit->y] = 1;
}


void kermitAction(inputT playerChoice, playerValues *kermit, MapT houseMap) {
	kermit->last_x = kermit->x;
	kermit->last_y = kermit->y;

	if (playerChoice.op == 2 && (playerChoice.mObj == 1 || playerChoice.mObj == 8)) grabItem(playerChoice, houseMap, kermit);

	if (1 < playerChoice.mObj < 6) kermitMove(playerChoice, houseMap, kermit);
	
	checkIfPointPickup(houseMap, kermit);
	
	if (playerChoice.op == 3 && playerChoice.mObj == 6) {
		if (checkForDoor(houseMap, kermit) == 1) {
			openDoor(houseMap, kermit);
		}
		else if (2) {
			openExitDoor(houseMap, kermit);
		}
	}
	if (playerChoice.op == 6 && playerChoice.mObj == 8) useDynamite(houseMap, kermit);
}

void transformMap(MapT *houseMap, playerValues *kermit) {
	srand((int)time(NULL));
	int diff = 0;
	diff = rand() % 2;

	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (houseMap->mArr[kermit->x + i][kermit->y + j] == 'I') {
				if (diff == 0) {
					loadHardMap(houseMap, kermit);
				}
				if (diff == 1) {
					loadEasyMap(houseMap, kermit);
				}
			}
		}
	}
}

void loadEasyMap(MapT *houseMap, playerValues *kermit) {
	system("cls");
	printf("Du har tur! Du hittar en enklare karta att ta dig igenom!");
	getchar();
	int width = 35, height = 24, noOfWalls = 12, mapstate = 2;
	kermit->keys += 3;
	kermit->dynamite += 1;

	*houseMap = createMap(width, height, noOfWalls);
	placeObjectsOnMap(houseMap, mapstate);
	createKermit(width, height, houseMap, kermit);
}

void loadHardMap(MapT *houseMap, playerValues *kermit) {
	system("cls");
	printf("Du har otur! Du hittar en svårare karta att ta dig igenom!");
	getchar();
	int width = 35, height = 24, noOfWalls = 32, mapstate = 3;

	*houseMap = createMap(width, height, noOfWalls);
	placeObjectsOnMap(houseMap, mapstate);
	createKermit(width, height, houseMap, kermit);
}

void checkIfTransformMap(inputT playerChoice, MapT *houseMap, playerValues *kermit) {
	if (playerChoice.op == 6 && playerChoice.mObj == 9) transformMap(houseMap, kermit);
}


void checkIfPointPickup(MapT houseMap, playerValues *kermit) {
	if (houseMap.mArr[kermit->x][kermit->y] == '*') {
		kermit->points += 50;
	}
}

int grabItem(inputT playerChoice, MapT houseMap, playerValues *kermit) {
	if (playerChoice.mObj == 1) {
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				if (houseMap.mArr[kermit->x + i][kermit->y + j] == 'K') {
					houseMap.mArr[kermit->x + i][kermit->y + j] = ' ';
					kermit->keys++;
					return 1;
				}
			}
		}
	}
	if (playerChoice.mObj == 8) {
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				if (houseMap.mArr[kermit->x + i][kermit->y + j] == 'X') {
					houseMap.mArr[kermit->x + i][kermit->y + j] = ' ';
					kermit->dynamite++;
					return 1;
				}
			}
		}
	}
	printf("Det finns inget i närheten att plocka upp.");
	getchar();
	return 0;
}

void useDynamite(MapT houseMap, playerValues *kermit) {
	if (kermit->dynamite > 0) {
		for (int i = -2; i < 3; i++) {
			for (int j = -2; j < 3; j++) {
				if (houseMap.mArr[kermit->x + i][kermit->y + j] != 'e' && houseMap.mArr[kermit->x + i][kermit->y + j] != 'M') {
					houseMap.mArr[kermit->x + i][kermit->y + j] = ' ';
				}
			}
		}
		kermit->dynamite--;
	}
	else {
		printf("Du har ingen dynamit att använda!");
		getchar();
	}
}

void updateKermitValues(MapT houseMap, playerValues *kermit) {
	houseMap.mArr[kermit->last_x][kermit->last_y] = ' ';
	houseMap.mArr[kermit->x][kermit->y] = '@';
	houseMap.vArr[kermit->x][kermit->y] = 1;
}

void printInventory(playerValues *kermit) {
	printf("\t\t\t\t\t\t\t\tNycklar: %d\n\t\t\t\t\t\t\t\tDynamiter: %d\n\t\t\t\t\t\t\t\tPoäng: %d", kermit->keys, kermit->dynamite, kermit->points);
}

void kermitVisibility(MapT houseMap, playerValues *kermit) {
	for (int row = -1; row < 2; row++) {
		for (int col = -1; col < 2; col++) {
			houseMap.vArr[kermit->x + row][kermit->y + col] = 1;
		}
	}
}

void removeKermitVisibility(MapT houseMap, playerValues *kermit) {
	for (int row = -1; row < 2; row++) {
		for (int col = -1; col < 2; col++) {
			if (houseMap.mArr[kermit->x + row][kermit->y + col] != 'e' && houseMap.mArr[kermit->x + row][kermit->y + col] != 'M') {
				houseMap.vArr[kermit->x + row][kermit->y + col] = 0;
			}
		}
	}
}

void kermitMove(inputT playerChoice, MapT houseMap, playerValues *kermit) {
	if (playerChoice.mObj == 2 && allowingMovementSymbols(playerChoice, houseMap, kermit)) kermit->x--;
	else if (playerChoice.mObj == 3 && allowingMovementSymbols(playerChoice, houseMap, kermit)) kermit->x++;
	else if (playerChoice.mObj == 4 && allowingMovementSymbols(playerChoice, houseMap, kermit)) kermit->y--;
	else if (playerChoice.mObj == 5 && allowingMovementSymbols(playerChoice, houseMap, kermit)) kermit->y++;
}

int allowingMovementSymbols(inputT playerChoice, MapT houseMap, playerValues *kermit) {
	if (playerChoice.mObj == 2) {
		if (houseMap.mArr[kermit->x - 1 ][kermit->y] == ' ') return 1;
		else if (houseMap.mArr[kermit->x - 1][kermit->y] == '*') return 1;
	}
	else if (playerChoice.mObj == 3) {
		if (houseMap.mArr[kermit->x + 1][kermit->y] == ' ') return 1;
		else if (houseMap.mArr[kermit->x + 1][kermit->y] == '*') return 1;
	}
	else if (playerChoice.mObj == 4) {
		if (houseMap.mArr[kermit->x][kermit->y - 1] == ' ') return 1;
		else if (houseMap.mArr[kermit->x][kermit->y - 1] == '*') return 1;
	}
	else if (playerChoice.mObj == 5) {
		if (houseMap.mArr[kermit->x][kermit->y + 1] == ' ') return 1;
		else if (houseMap.mArr[kermit->x][kermit->y + 1] == '*') return 1;
	}
	return 0;
}


int checkForDoor(MapT houseMap, playerValues *kermit) {
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (houseMap.mArr[kermit->x + i][kermit->y + j] == 'D') {
				return 1;
			}
			else if (houseMap.mArr[kermit->x + i][kermit->y + j] == 'M') {
				return 2;
			}
		}
	}
	return 0;
}

int openDoor(MapT houseMap, playerValues *kermit) {
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (houseMap.mArr[kermit->x + i][kermit->y + j] == 'D') {
				if (kermit->keys > 0) {
					houseMap.mArr[kermit->x + i][kermit->y + j] = ' ';
					kermit->keys--;
					return 1;
				}
				else {
					printf("Du har ingen nyckel på dig! Hitta en nyckel och kom tillbaka...");
					getchar();
					return 0;
				}
			}
		}
	}
	return 0;
}


int openExitDoor(MapT houseMap, playerValues *kermit) {
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (houseMap.mArr[kermit->x + i][kermit->y + j] == 'M') {
				if (kermit->keys > 0) {
					houseMap.mArr[kermit->x + i][kermit->y + j] = ' ';
					//houseMap.vArr[kermit->x + i][kermit->y + j] = 0;
					kermit->keys--;
					printf("Ytterdörren öppnad! Gå ut för att vinna spelet...");
					getchar();
					return 1;
				}
				else {
					printf("Du har ingen nyckel på dig! Hitta en nyckel och kom tillbaka...");
					getchar();
					return 0;
				}
			}
		}
	}
	return 0;
}

int winGame(int height, int width, MapT houseMap, playerValues *kermit) {
	if (kermit->x == 0 || kermit->x == height - 1 || kermit->y == 0 || kermit->y == width - 1) {
		system("cls");
		kermit->points += 200;
		printf("Du har tagit dig ur huset och vunnit!\nDina poäng: %d", kermit->points);
		getchar();
		return 0;
	}
	else {
		return 1;
	}
}

void placePoints(MapT *houseMap, int mapstate) {
	int xPos = 0, yPos = 0, visibility = 0, i = 0;
	char pointChr = '*';
	positionT pos;

	if (mapstate == 1) {
		i = 0;
	}
	else if (mapstate == 2) {
		i = -8;
	}
	else if (mapstate == 3) {
		i = 8;
	}

	for (; i <= 18; i++) {
		placeObject(*houseMap, xPos, yPos, pointChr, &pos, visibility);
	}
}

void placeLevers(MapT *houseMap, int mapstate) {
	char pointChr = 'I';
	int visibility = 0, xPos = 0, yPos = 0, i = 0;
	positionT pos;

	if (mapstate == 1) {
		i = 0;
	}
	else if (mapstate == 2) {
		i = 3;
	}
	else if (mapstate == 3) {
		i = 3;
	}

	for (; i <= 2; i++) {
		placeObject(*houseMap, xPos, yPos, pointChr, &pos, visibility);
	}
}

void placeDynamite(MapT *houseMap, int mapstate) {
	char pointChr = 'X';
	int visibility = 0, xPos = 0, yPos = 0, i = 0;
	positionT pos;

	if (mapstate == 1) {
		i = 0;
	}
	else if (mapstate == 2) {
		i = -6;
	}
	else if (mapstate == 3) {
		i = 14;
	}

	for (; i <= 20; i++) {
		placeObject(*houseMap, xPos, yPos, pointChr, &pos, visibility);
	}
}

void placeObjectsOnMap(MapT *houseMap, int mapstate) {
	placePoints(houseMap, mapstate);
	placeLevers(houseMap, mapstate);
	placeDynamite(houseMap, mapstate);
}


void displayMap(MapT houseMap) {
	for (int i = 0; i < 24; i++) {
		for (int j = 0; j < 35; j++) {
			houseMap.vArr[i][j] = 1;
		}
	}
}