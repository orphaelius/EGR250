/******************************************************************************

							// Ordered Pairs //

	This program requests asks a user to input x and y values, then it 
	determines where that point lies on a Cartesian plane and prints the 
	results.

	Written by: Jon-Austin Tharpe

	Date: 02/25/2025

******************************************************************************/

#include <stdio.h>

// Function Prototypes //
void displayDescription(void);
int grabCoordinate(int*);
int detectQuadrant(int* xValue, int* yValue);
void printLocation(int switchKey, int* xValue, int* yValue); 

/******************************************************************************
	Function: main()
	Description: Main function for program. Runs through each function to get
		x and y values, then determines those locations on the plane, 
		subsequently printing the result.
	Side Effects: ---
	Parameters: ---
	Return: ---
******************************************************************************/
int main(void) {

	int xValue = 0;
	int yValue = 0;
	// Variable that holds the return value from detectQuadrant; used in 
	// printLocation's switch statement to print where that point lies on the
	// graph.
	int switchKey = 0; 

	displayDescription(); 

	printf("Enter the x-value: ");
	xValue = grabCoordinate(&xValue);
	printf("Enter the y-value: ");
	yValue = grabCoordinate(&yValue);

	// Grabs return value from detectQuadrant to print location in subsequent
	// function call below it
	switchKey = detectQuadrant(&xValue, &yValue);  
	printLocation(switchKey, &xValue, &yValue);

	return 0;
} // End main()

/******************************************************************************
	Function: displayDescription()
	Description: Displays program intentions.
	Side Effects: ---
	Parameters: ---
	Return: ---
******************************************************************************/
void displayDescription(void) {
	printf("%s%s", "This program requests x and y values from a user",
		"then prints where those points are located on a Cartesian plane.");
	puts("");
	puts("");
} // End displayDescription()

/******************************************************************************
	Function: grabCoordinate()
	Description: Uses scan function to grab user input for a point value. Passes
	by address.
	Side Effects: Changes value
	Parameters: Points to an input value
	Return: *value
******************************************************************************/
int grabCoordinate(int* value) {
	scanf("%d", value);
	return *value;  
} // End grabCoordinate()

/******************************************************************************
	Function: detectQuadrant()
	Description: Determines where these x and y values lie on a Cartesian plane
	using a series of if... else statements.
	Side Effects: ---
	Parameters: Pointers to x and y values
	Return: A specific number value representing a 'quadrant' or a 'location'
	on the plane.
******************************************************************************/
int detectQuadrant(int* xValue, int* yValue) {
	if (*xValue < 0) {
		if (*yValue < 0) {
			return 3; // Quadrant 3
		}
		else {
			return 2; // Quadrant 2
		}
	}
	else if (*xValue > 0) {
		if (*yValue > 0) {
			return 1; // Quadrant 1
		}
		else {
			return 4; // Quadrant 4
		}

	} // End determine specific quadrant portion

	// Start location on a particular axis portion
	else if (*xValue == 0) {
		if (*yValue == 0) {
			return 5; // Origin indicator 
		}
		else if (*yValue > 0) {
			return 6; // Positive y value indicator 
		}
		else {
			return 7; // negative y value indicator
		}
	}
	else if (*yValue == 0) {
		if (*xValue == 0) {
			return 8; // Origin indicator 
		}
		else if (*xValue > 0) {
			return 9; // Positive x value indicator 
		}
		else {
			return 10; // negative x value indicator
		}
	}
} // End detectQuadrant()
 
/******************************************************************************
	Function: printLocation()
	Description: Uses a switch statement to print a specific message/ location
	of the point user entered using the return value of detectQuadrant().
	Side Effects: ---
	Parameters: switchKey, pointers to x and y values
	Return: ---
******************************************************************************/
void printLocation(int switchKey, int* xValue, int* yValue) {

	switch (switchKey) { 
	case 1:
		printf("The point (%d, %d) lies in Quadrant I.\n", *xValue, *yValue); 
		break;

	case 2: 
		printf("The point (%d, %d) lies in Quadrant II.\n", *xValue, *yValue);
		break; 

	case 3:
		printf("The point (%d, %d) lies in Quadrant III.\n", *xValue, *yValue);
		break;

	case 4:
		printf("The point (%d, %d) lies in Quadrant IV.\n", *xValue, *yValue);
		break;

	case 5:
		printf("The point (%d, %d) rests soundly at the origin.\n", 
			*xValue, *yValue);
		break;

	case 6:
		printf("The point (%d, %d) lies on the positive y-axis.\n", 
			*xValue, *yValue);
		break;

	case 7:
		printf("The point (%d, %d) lies on the negative y-axis.\n", 
			*xValue, *yValue); 
		break;

	case 8:
		printf("The point (%d, %d) rests soundly at the origin.\n", 
			*xValue, *yValue);
		break;

	case 9:
		printf("The point (%d, %d) lies on the positive x-axis.\n", 
			*xValue, *yValue);
		break;

	case 10:
		printf("The point (%d, %d) lies on the negative y-axis.\n", 
			*xValue, *yValue);
		break;
	default:
		printf("Should not be here...\n");
		break;
	}
} // End printLocation()