/******************************************************************************

						// Generations //

	This program takes a reasonable year (via user input) and determines which
	conventional generation that year belongs to, then displays the result.

	Written by: Jon-Austin

	Date: 02/19/2025

******************************************************************************/

#include <stdio.h>
// Decided to make the current year a constant so program could be easily 
// modified for future needs
#define CURYEAR 2025

// FUNCTION PROTOTYPES //
void displayDescription(void);
int getYear(int year);
void determineGeneration(int year); 

/******************************************************************************
	Function: main()
	Description: Main function for program. Runs through each function to get
		year, determine generation, and display result.
	Side Effects: ---
	Parameters: ---
	Return: ---
******************************************************************************/
int main(void) {
	// For storing user input and passing as argument
	int year = 0; 

	displayDescription(); // Displays program description
	year = getYear(year); // Gets input (year)

	// Passes year as argument to determine generation
	// and display result
	determineGeneration(year); 

	return 0;
} // End main()

/******************************************************************************
	Function: displayDescription()
	Description: Displays program description
	Side Effects: ---
	Parameters: ---
	Return: ---
******************************************************************************/
void displayDescription(void) {
	printf("%s %s", "This program takes a reasonable birth year and outputs", 
		"their respective generation.\n");
} // End displayDescription()

/******************************************************************************
	Function: getYear()
	Description: Requests user input, takes user input, returns value to main()
	Side Effects: ---
	Parameters: integer (year)
	Return: year
******************************************************************************/
int getYear(int year) {
	printf("Enter the year of birth: ");
	scanf("%d", &year);	
	return year;
} // End getYear()

/******************************************************************************
	Function: determineGeneration()
	Description: Uses if... else statements to determine which generation the 
		user year input belongs to then displays that respective generation
	Side Effects: ---
	Parameters: year
	Return: ---
******************************************************************************/
void determineGeneration(int year) {

	if (year >= 1883 && year <= 1900) {
		printf("A person born in the year %d belongs to The Lost Generation.\n",
			year);
	}
	else if (year >= 1901 && year <= 1927) {
		printf("A person born in the year %d belongs to the Greatest Generation.\n",
			year);
	}
	else if (year >= 1928 && year <= 1945) {
		printf("A person born in the year %d belongs to The Silent Generation.\n",
			year);
	}
	else if (year >= 1946 && year <= 1965) {
		printf("A person born in the year %d belongs to The Baby Boomers generation.\n",
			year);
	}
	else if (year >= 1966 && year <= 1976) {
		printf("A person born in the year %d belongs to Generation X.\n", 
			year);
	}
	else if (year >= 1977 && year <= 1995) {
		printf("A person born in the year %d belongs to Generation Y/Millenials.\n", 
			year);
	}
	else if (year >= 1996 && year <= CURYEAR) {
		printf("A person born in the year %d belongs to Generation Z/Centennials.\n", 
			year);
	}
	else if (year > CURYEAR) {
		printf("This date exists only in the quantum realm.\n");
		printf("Please enter a valid date.\n");
	}
	else {
		printf("The year %d occurred prior to the conventional naming of generations.\n", 
			year);		
	}
} // End determineGeneration()