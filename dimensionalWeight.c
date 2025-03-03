/*******************************************************************************

							// Dimensional Weight //

	This program computes the dimensional weight of a package
	as a floating point value via user input and outputs the
	results. The dimensional weight reflects density: the space
    an object occupies in relation to weight. Additionally,
	this program implements the concept of passing by reference.

	Written by: Jon-Austin Tharpe

	Date: 02/11/2025

*******************************************************************************/ 

#include <stdio.h>
#define FEDEX 139 // Divisors for each
#define USPS 166 // delivery service,
#define UPS 139 // cubic inches / lb
#define SERVICES 3 // Current total delivery services
#define CHARLIM 6 // Character limitation for char arrays

// FUNCTION PROTOTYPES //
void displayDescription(void); // Displays program description
// Grabs length, width, and height in inches via user input
void getDimensions(float* length, float* width, float* height);
// Calculates volume from input packages dimensions (in cubic inches)
float getVolume(float* length, float* width, float* height, float* volume);
// Calculates dimensional weight for each deilivery service (in lbs)
float calcDimWeight(int divisors[SERVICES], float dimWeight[SERVICES],
	float* volume);
float getValues(float value); // Basic scanf function to grab user input
// Displays results in formatted tabular ouput
void printServices(char array[SERVICES][CHARLIM], float dimWeight[SERVICES],
	float* length, float* width, float* height, float* volume);

/*******************************************************************************
	Function: main()
	Description: Allows user to navigate between various delivery services,
		input dimensions of their packages, then calculate the volume and
		dimensional weight of those packages
	Parameters: No parameters!
	Return: ---
*******************************************************************************/
int main(void) {

	// Main variables	
	float volume = 0; // Volume.. in cubic inches
	float length = 0; // In inches.. et al
	float width = 0;
	float height = 0;

	// Array holding each delivery service. Used to print in formatted output
	char deliveryService[SERVICES][CHARLIM] = { "FEDEX", "USPS", "UPS" };
	// Array holding divisors for each delivery service, elements aligned
	// respectively
	int divisors[SERVICES] = { 139, 166, 139 };
	// Array to store dimensional weight of each delivery service
	float dimWeight[SERVICES] = { 0 };

	displayDescription(); // Displays description
	getDimensions(&length, &width, &height); // Grabs package dimensions
	getVolume(&length, &width, &height, &volume); // Calculates volume of package
	calcDimWeight(divisors, dimWeight, &volume); // Calculates dimensional weight
	// Displays results
	printServices(deliveryService, dimWeight, &length, &width, &height, &volume);

	return 0;
} // End main

/*******************************************************************************
	Function: displayDescription()
	Description: Displays program description/instructions
	Parameters: No parameters!
	Return: Void function, does not return anything ('---' going forward)
*******************************************************************************/
void displayDescription(void) {
	printf("%s %s\n%s\n\n",
		"This program computes the dimensional weight of a package",
		"by taking the length, width, and height dimensions (in inches) via user input.",
		"It then displays the resulting dimensional weight (in lbs) each delivery service.");
} // End displayDescription

/*******************************************************************************
	Function: getDimensions()
	Description: Requests user input for length, width, and height of package
	Parameters: Points to length, width, and height
	Return: ---
*******************************************************************************/
void getDimensions(float* length, float* width, float* height) {
	printf("Enter the length of the package in inches: ");
	(*length) = getValues(*length);

	printf("Enter the width of the package in inches: ");
	(*width) = getValues(*width);

	printf("Enter the height of the package in inches: ");
	(*height) = getValues(*height);
} // End getDimensions

/*******************************************************************************
	Function: getVolume()
	Description: Calculates volume of package
	Parameters: Points to length, width, height, and volume
	Return: *Volume

	Question on pointers: If I've used them in something like getDimensions()
		above, do I need to repeatedly pass them by reference to functions going
		forward if I don't directly modify the values, or can I just pass by value
		after my initial modification? I just want to make sure I'm not being 
		redundant in how I am using them.
*******************************************************************************/
float getVolume(float* length, float* width, float* height, float* volume) {
	*volume = (*length) * (*width) * (*height);
	return *volume;
} // End getVolume

/*******************************************************************************
	Function: calcDimWeight()
	Description: Calculates dimensional weight of package for each delivery
		service, returns values to dimWeight array
	Parameters: arrays divisors and dimWeight, points to volume
	Return: calculated dimWeight elements
*******************************************************************************/
float calcDimWeight(int divisors[SERVICES], float dimWeight[SERVICES],
	float* volume) {
	for (size_t i = 0; i < SERVICES; ++i) {
		dimWeight[i] = (*volume) / divisors[i];
	}
	return dimWeight[SERVICES];
} // End calcDimWeight

/*******************************************************************************
	Function: getValues()
	Description: Basic scanf function to grab input values
	Parameters: Value
	Return: Value
*******************************************************************************/
float getValues(float value) {
	scanf("%f", &value);
	return value;
} // End getValues

/*******************************************************************************
	Function: printServices()
	Description: Displays results in formatted tabular output after calculating
		values
	Parameters: delivery services array and dimWeight array, points to length
		width, height, and volume
	Return: ---
*******************************************************************************/
void printServices(char array[SERVICES][CHARLIM], float dimWeight[SERVICES],
	float* length, float* width, float* height, float* volume) {

	// print package dimensions: 
	// add cubic inches for volume
	// add lbs for dimensional weight
	printf("\nThe dimensions of your package are: %.2f in x %.2f in x %.2f in\n",
		*length, *width, *height);
	printf("The volume of your package is: %.2f in^3\n", *volume);
	puts("");
	puts("The dimensional weight for each provider is outlined below:");
	puts("");

	printf("%s%30s\n", "Delivery service", "Dimensional weight");
	for (size_t i = 0; i < 46; i++) {
		printf("%s", "-");
	}
	puts("");
	for (size_t i = 0; i < SERVICES; ++i) {
		for (size_t j = 0; j < CHARLIM; ++j) {
			printf("%c", array[i][j]);  
		}
		printf("%28.2flbs", dimWeight[i]);
		puts(""); 		
	}	
} // End printServices

