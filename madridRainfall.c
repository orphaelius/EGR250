/*******************************************************************************

							 // Madrid Rainfall //

	This program reads and stores daily rainfall amounts from Madrid, Spain
	for the month of September 2020 via a data file (madridRainfallSept2020.txt).
	It then displays the date with the largest amount of rainfall for that month
	and then prints the total rainfall for the month in both millimeters and 
	inches. 

	Written by: Jon-Austin Tharpe

	Date: 03/26/2025

*******************************************************************************/
#include <stdio.h>
#define DAYS 30 // Total days in September

// FUNCTION PROTOTYPES //
// Inputs data via FILE*
void inputRainfallFromFile(FILE* infile, float* dailyRain);
// Determines which specific date had the highest volume of rainfall
int determineHighestRainfall(float rainfallData[DAYS], int maxRainfallDate);
// Determines total rainfall for the month of September
float determineTotalRainfall(float rainfallData[DAYS], float rainfallSum);
// Prints data
void printData(float rainfallData[DAYS], int maxRainfallDate, float rainfallSum);

/*******************************************************************************
	Function: main()
	Description: Scans data from data file, stores, and computes data; displays
	to console after.
	Parameters: ---
	Return: ---
*******************************************************************************/
int main(void) {
	// Array to store rainfall data
	float rainfallData[DAYS] = { 0.0 };
	int index = 0; // Index to loop through array
	float dailyRain = 0.0; // Variable to store data values from file
	int maxRainfallDate = 0; // Date of max rainfall
	float rainfallSum = 0.0; // Sum of monthly rainfall

	// Declares and opens data file
	FILE* infile = fopen("madridRainfallSept2020.txt", "r");

	// Checks if file exists
	if (infile == NULL) {
		printf("Check location of data file!\n");
	}

	// Loops through dat file, storing dailyRain at each subsequent index
	while (!feof(infile)) {
		inputRainfallFromFile(infile, &dailyRain);
		rainfallData[index] = dailyRain;
		index++;
	}

	maxRainfallDate = determineHighestRainfall(rainfallData, maxRainfallDate);
	rainfallSum = determineTotalRainfall(rainfallData, rainfallSum);
	printData(rainfallData, maxRainfallDate, rainfallSum);

	return 0;
} // End main()

/*******************************************************************************
	Function: inputRainfallFromFile()
	Description: Reads in data from data file
	Parameters: infile, points to dailyRain
	Return: ---
*******************************************************************************/
void inputRainfallFromFile(FILE* infile, float* dailyRain) {
	fscanf(infile, "%f", dailyRain);
} // End inputRainfallFromFile()

/*******************************************************************************
	Function: determineHighestRainfall()
	Description: Loops through rainfallData array and determines which date
	(index + 1) experiences the greatest amount of rainfall
	Parameters: rainfallData array, maxRainfallDate 
	Return: maxRainfallDate
*******************************************************************************/
int determineHighestRainfall(float rainfallData[DAYS], int maxRainfallDate) {
	float maxRainfall = 0.0;
	for (size_t i = 0; i < DAYS; ++i) {
		if (rainfallData[i] > maxRainfall) {
			maxRainfall = rainfallData[i];
			maxRainfallDate = i;
		}
	}
	return maxRainfallDate + 1; // Adds one to index for proper dating
} // End determineHighestRainfall()

/*******************************************************************************
	Function: determineTotalRainfall()
	Description: Sums rainfall for the month
	Parameters: rainfallData array, rainfallSum
	Return: rainfallSum
*******************************************************************************/
float determineTotalRainfall(float rainfallData[DAYS], float rainfallSum) {
	for (size_t i = 0; i < DAYS; ++i) {
		rainfallSum += rainfallData[i];
	}
	return rainfallSum;
} // End determineTotalRainfall()

/*******************************************************************************
	Function: printData()
	Description: Converts rainfall in mm to inches, prints data to console
	Parameters: rainfallData array, maxRainfallDate, rainfallSum
	Return: ---
*******************************************************************************/
void printData(float rainfallData[DAYS], int maxRainfallDate, float rainfallSum) {
	float rainfallInches = rainfallSum * (0.03937007874);
	printf("-----------------------------------------------------------\n");
	printf("------------- MADRID, SPAIN SEPT 2020 RAINFALL ------------\n");
	printf("-----------------------------------------------------------\n");	
	printf("=> Madrid experienced %.2fmm or %.2fin of rainfall this month\n", rainfallSum, rainfallInches);
	printf("=> Date with the greatest amount of rainfall: September %d\n", maxRainfallDate);
} // End printDataTable()

