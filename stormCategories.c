/*******************************************************************************

							 // Storm Categories //

	This program reads wind speeds from a data file (windSpeedsStorms2020.txt),
	stores those speeds in an array, determines how many hurricanes and non-
	hurricanes there were in the Atlantic Ocean during the year 2020. It 
	displays these results at the end of the program.

	Written by: Jon-Austin Tharpe

	Date: 03/25/2025

*******************************************************************************/

#include <stdio.h>
#define MAXDATA 45 // Total data points
#define HEADERWID 35 // Width of header for printing a nice table

// FUNCTION PROTOTYPES // 
// Takes wind speeds from data file
void inputWindSpeeds(FILE* infile, int* speed); 
// Determines which speeds are hurricanes or not
void determineIfHurricane(int windSpeeds[MAXDATA], int* totalHurricanes, 
	int* totalNonHurricanes);
// Prints all data in a formatted table
void printDataTable(int windSpeeds[MAXDATA],int totalHurricanes, 
	int totalNonHurricanes);

/*******************************************************************************
	Function: main()
	Description: Declares and initializes windSpeeds array, variables for 
	hurricane/non, an index for moving through the array, and speed (used to
	pull data from data set and assign to elements in the array). Uses while 
	loop to call inputWindSpeeds until EOF, determines if hurricane, and prints
	results. Closes file when complete.
	Parameters: ---
	Return: ---
*******************************************************************************/
int main(void) {
	int windSpeeds[MAXDATA] = { 0 }; // Array to store data
	int totalHurricanes = 0; // Hurricane variable
	int totalNonHurricanes = 0; // Non-hurricane variable
	int index = 0; // Index for iterating through windSpeeds array
	int speed = 0; // Variable to pull data from data file

	FILE* infile = fopen("windSpeedsStorms2020.txt", "r");

	if (infile == NULL) {
		printf("Confirm data file location...\n");	
	}

	// Main while loop to iterate through data file
	while (!feof(infile)) {
		inputWindSpeeds(infile, &speed);  
		windSpeeds[index] = speed;
		index++;
	}

	// Determines if speeds from data file are hurricae or not
	determineIfHurricane(windSpeeds, &totalHurricanes, &totalNonHurricanes);
	// Prints data to table
	printDataTable(windSpeeds, totalHurricanes, totalNonHurricanes);
	fclose(infile);

	return 0;
} // End main()

/*******************************************************************************
	Function: inputWindSpeeds()
	Description: Reads in data from data file
	Parameters: infile, points to speed
	Return: ---
*******************************************************************************/
void inputWindSpeeds(FILE* infile, int* speed) {
	fscanf(infile, "%d", speed);
} // End inputWindSpeeds()

/*******************************************************************************
	Function: determineIfHurricane()
	Description: Determines if each speed value from data file is a hurricane
	or not
	Parameters: windSpeeds array, points to hurricane and non-hurricane variables
	Return: No return, although it updates the counts for hurricane
	variables
*******************************************************************************/
void determineIfHurricane(int windSpeeds[MAXDATA], int* totalHurricanes, 
	int* totalNonHurricanes) {

	for (size_t i = 0; i < MAXDATA; ++i) {
		if (windSpeeds[i] > 73) {
			(*totalHurricanes)++; // Update hurricane counts
		}
		else if (windSpeeds[i] > 0 && windSpeeds[i] <= 73) {
			(*totalNonHurricanes)++; // Update non hurricane counts
		}
		else {
			printf("Error reading data.\n");
			break;
		}
	}
} // End determineIfHurricane()

/*******************************************************************************
	Function: printDataTable()
	Description: Prints clean data table with speeds and if that speed is a 
	hurricane or not
	Parameters: windSpeeds array, totalHurricanes, totalNonHurricanes
	Return: ---
*******************************************************************************/
void printDataTable(int windSpeeds[MAXDATA], int totalHurricanes, 
	int totalNonHurricanes) {
	printf("-----------------------------------------------------------\n");
	printf("-------------- ATLANTIC OCEAN HURRICANES 2020 -------------\n");
	printf("-----------------------------------------------------------\n");
	printf("Total Hurricanes: %d\t\t", totalHurricanes);
	printf("%sTotal Non-hurricanes: %d\n\n","   ", totalNonHurricanes);
	printf("------------- Dataset -------------\n");	
	printf("%s%25s\n", "Wind Speed", "Hurricane or Not");

	for (size_t i = 0; i < HEADERWID; ++i) {
		printf("%c", '-');
	} puts("");

	for (size_t i = 0; i < MAXDATA; ++i) {
		printf("%6d %s\t", windSpeeds[i], "mph");
		if (windSpeeds[i] > 73) {
			printf("%20s", "Hurricane\n");
		}
		else if (windSpeeds[i] < 39) { 			
			printf("%s", "Tropical Depression\n");
		}
		else {			
			printf("%20s","Tropical Storm\n");
		}
	} puts("");	
} // End printDataTable()