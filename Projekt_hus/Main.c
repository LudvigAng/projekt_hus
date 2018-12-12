#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "houseManager.h"
#include "houseHelper.h"

int main(void) {
	system("chcp 1252");
	const int width = 35;
	const int height = 24;
	const int noOfWalls = 25;
	int playGame = 1;
	inputT playerChoice;
	MapT houseMap;
	playerValues kermit;
	kermit.keys = 0;
	kermit.points = 0;
	kermit.dynamite = 0;

	houseMap = createMap(width, height, noOfWalls);
	placePoints(houseMap);
	placeDynamite(houseMap);
	createKermit(width, height, houseMap, &kermit);
	displayMap(houseMap);

	do {
		system("cls");
		kermitVisibility(houseMap, &kermit);
		drawMap(houseMap);
		displayMap(houseMap);
		//drawMapVisibility(houseMap);

		playerChoice = getUserInput();
		removeKermitVisibility(houseMap, &kermit);
		kermitAction(playerChoice, &kermit, houseMap);

		updateKermitPosition(houseMap, &kermit);

		playGame = winGame(height, width, houseMap, &kermit);

		//fixa så snyggare sätta kermit-värden till 0? (keys, dynamite, points)
		//fixa så dynamit fungerar längst upp pch längst ned
		//fixa så problem med dynamit fixas. Om dynamit plockas upp efter man använt en dynamit blir antalet dynamit man innehar konstigt (-23)

		//lägga in <help> för att användaren ska få veta vad man kan skriva?
		//lägga in <stat> för att användaren ska få veta statistik om spelandet
		//lägga in alternativ-map. T.ex. om man hittar en spak eller ngt. I nya kartan är det helt annorlunda, surrealistiskt. Ska kunna ta sig tillbaka till vanliga om man vill.
	} while (playGame);
}