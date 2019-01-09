#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "houseManager.h"
#include "houseHelper.h"

int main(void) {
	system("chcp 1252");
	int width = 35, height = 24, noOfWalls = 25, playGame = 1, mapstate = 1, menuChoice = 0;
	inputT playerChoice;
	MapT houseMap;
	playerValues kermit;
	kermit.keys = 0;
	kermit.points = 0;
	kermit.dynamite = 0;

	printf("Vad vill du göra?\n\n");
	printf("1. Nytt spel\n2. Ladda sparat spel\n3. Avsluta\n");
	scanf_s("%d", &menuChoice);

	if (menuChoice == 1) {
		playGame = 1;
		houseMap = createMap(width, height, noOfWalls);
		placeObjectsOnMap(&houseMap, mapstate);
		createKermit(width, height, &houseMap, &kermit);
	}
	else if (menuChoice == 2) {
		playGame = 1;
		houseMap = createMap(width, height, noOfWalls);
		createKermit(width, height, &houseMap, &kermit);
		openSave(&houseMap, &kermit);

	}
	else if (menuChoice == 3) playGame = 0;
	system("cls");

	while (playGame) {
		system("cls");
		kermitVisibility(houseMap, &kermit);
		drawMap(houseMap);
		printInventory(&kermit);

		playerChoice = getUserInput();
		removeKermitVisibility(houseMap, &kermit);
		kermitAction(playerChoice, &kermit, houseMap);
		
		updateKermitValues(houseMap, &kermit);
		checkIfTransformMap(playerChoice, &houseMap, &kermit);
		playGame = checkIfGameExit(height, width, playerChoice, houseMap, &kermit);

		//Lägga i huvudmenyn i egen funktion?
		//lägga till error för när filer inte kan öppnas. När spel laddas, spel sparas, highscore sparas
		//Lyckas med highscore-lista
		//fixa så inte kermit skapas i vägg. kollar så är blank spaces runt innan spawnar!
		//fixa så finns minor på golvet. Ska kunna se att man är nära en. Om man går på förlorar man, OM man inte har poäng att ge bort. En mina tar bort 10-50 poäng.
	}
}