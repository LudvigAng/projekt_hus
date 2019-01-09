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

	printf("Vad vill du g�ra?\n\n");
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

		//L�gga i huvudmenyn i egen funktion?
		//l�gga till error f�r n�r filer inte kan �ppnas. N�r spel laddas, spel sparas, highscore sparas
		//Lyckas med highscore-lista
		//fixa s� inte kermit skapas i v�gg. kollar s� �r blank spaces runt innan spawnar!
		//fixa s� finns minor p� golvet. Ska kunna se att man �r n�ra en. Om man g�r p� f�rlorar man, OM man inte har po�ng att ge bort. En mina tar bort 10-50 po�ng.
	}
}