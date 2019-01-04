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

		//fixa så snyggare sätta kermit-värden till 0? (keys, dynamite, points)
		//fixa så dynamit fungerar längst upp pch längst ned (fel på x?)

		//lägga in <help> för att användaren ska få veta vad man kan skriva och göra
	} while (playGame);
}