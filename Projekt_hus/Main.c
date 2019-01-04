#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "houseManager.h"
#include "houseHelper.h"

int main(void) {
	system("chcp 1252");
	int width = 35, height = 24, noOfWalls = 25, playGame = 1, mapstate = 1;
	inputT playerChoice;
	MapT houseMap;
	playerValues kermit;
	kermit.keys = 0;
	kermit.points = 0;
	kermit.dynamite = 0;

	houseMap = createMap(width, height, noOfWalls);
	placeObjectsOnMap(&houseMap, mapstate);
	createKermit(width, height, &houseMap, &kermit);
	displayMap(houseMap);

	do {
		system("cls");
		kermitVisibility(houseMap, &kermit);
		drawMap(houseMap);
		displayMap(houseMap);
		//drawMapVisibility(houseMap);
		printInventory(&kermit);

		playerChoice = getUserInput();
		removeKermitVisibility(houseMap, &kermit);
		kermitAction(playerChoice, &kermit, houseMap);
		
		updateKermitValues(houseMap, &kermit);
		checkIfTransformMap(playerChoice, &houseMap, &kermit);
		playGame = winGame(height, width, houseMap, &kermit);

		//fixa s� snyggare s�tta kermit-v�rden till 0? (keys, dynamite, points)
		//fixa s� dynamit fungerar l�ngst upp pch l�ngst ned (fel p� x?)

		//l�gga in <help> f�r att anv�ndaren ska f� veta vad man kan skriva och g�ra
	} while (playGame);
}