#pragma once
/*
* File: myIOLib.h
* Version: 1.0
* Last modified on Tue Nov 7 2017 by CaAn
* -----------------------------------------------------
* This interface provides several functions for user input 
* 
*/

#ifndef _myIOLib_h
#define _myIOLib_h

#include <stdio.h>

#define MAXSTRINGSIZE 100

/* Function prototypes */
/************************************************************************************	
* This function reads an integer input from the user. It checks that the input is 
* correctly formatted as an integer. If not correct the user is prompted to input again.
* The string as parameter is written to the console as a prompt for the input.
************************************************************************************/
int getInteger(char* text);
long int getLong(char* text);

/************************************************************************************
* This function reads a float input from the user. It checks that the input is
* correctly formatted as a float. If not correct the user is prompted to input again.
* The string as parameter is written to the console as a prompt for the input.
************************************************************************************/
float getFloat(char* text);

/************************************************************************************
* This function reads a double input from the user. It checks that the input is
* correctly formatted as a double. If not correct the user is prompted to input again.
* The string as parameter is written to the console as a prompt for the input.
************************************************************************************/
double getDouble(char* text);


unsigned char * getString(char * text);

void clearStdin(void);
#endif