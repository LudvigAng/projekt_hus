#include <stdio.h>
#include <stdlib.h>
#include "myIOLib.h"

int getInteger(char* text)
{
	int anIntegerNumber, c, count = 0, retValScanf = 0; //Forces into the loop
	while (!retValScanf || count > 0)
	{
		count = 0;
		printf("%s", text);
		retValScanf = scanf_s("%d", &anIntegerNumber);
		while ((c = getchar()) != '\n' && c != EOF) // Remove unnecessary characters
			count++;
		if (!retValScanf || count > 0)
			printf("\nWrong input. Try again!");
	}
	return anIntegerNumber;
}

long int getLong(char* text)
{
	long int anIntegerNumber;
	int c, count = 0, retValScanf = 0; //Forces into the loop
	while (!retValScanf || count > 0)
	{
		count = 0;
		printf("%s", text);
		retValScanf = scanf_s("%li", &anIntegerNumber);
		while ((c = getchar()) != '\n' && c != EOF) // Remove unnecessary characters
			count++;
		if (!retValScanf || count > 0)
			printf("\nWrong input. Try again!");
	}
	return anIntegerNumber;
}

float getFloat(char* text)
{
	float aFloatNumber;
	int c, count = 0, retValScanf = 0; //Forces into the loop
	while (!retValScanf || count > 0)
	{
		printf("%s", text);
		retValScanf = scanf_s("%f", &aFloatNumber);
		count = 0;
		while ((c = getchar()) != '\n' && c != EOF) // Remove unnecessary characters
			count++;
		if (!retValScanf || count > 0)
			printf("\nWrong input. Try again!");
	}
	return aFloatNumber;
}

double getDouble(char* text)
{
	double aDoubleNumber;
	int c, count = 0, retValScanf = 0; //Forces into the loop
	while (!retValScanf || count > 0)
	{
		printf("%s", text);
		retValScanf = scanf_s("%lf", &aDoubleNumber);
		count = 0;
		while ((c = getchar()) != '\n' && c != EOF) // Remove unnecessary characters
			count++;
		if (!retValScanf || count > 0)
			printf("\nWrong input. Try again!");
	}
	return aDoubleNumber;
}

unsigned char * getString(char * text)
{
	unsigned char * aString = (unsigned char *)malloc(MAXSTRINGSIZE * sizeof(unsigned char));
	char c;
	int i = 0;
	printf("%s", text);
	while ((c = getchar()) != '\n' && i < (MAXSTRINGSIZE - 2))
		aString[i++] = c;
	aString[i] = '\0';
	return aString;
}

void clearStdin(void)
{
	int c;
	while ((c = getchar()) != '\n' && (c != EOF));
}