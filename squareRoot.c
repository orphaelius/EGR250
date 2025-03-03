/*******************************************************************************

                            // Square Root Loop //

    This (short) program prompts the user for a value greater than 10. It then
    finds the square root of this input value, the square root of that result,
    and so forth until a value smaller than 1.01 is reached. The program then
    outputs the total number of times the square root is calculated.

    Written by: Jon-Austin Tharpe

    Date: 02/28/2025

*******************************************************************************/

#include <stdio.h>
#include <math.h>
#define THRESHOLD 1.01 // Preprocessor constant for end value

// Function Prototypes //
void displayDescription(void); // Describes program
void promptInput(void); // Prompts for user input
double grabValue(double* numToRoot); // Grabs user input
double findRoot(double numToRoot); // Squares the input value
void countEachSquare(int* squareCounter); // Counter for square iterations
void printTotalCounts(int* squareCounter); // Prints counter results

/*******************************************************************************
    Function: main()
    Description: Takes input for square root, processes iteratively, 
    displays results. 
    Parameters: ---
    Return: ---
*******************************************************************************/
int main(void) {
    double numToRoot = 0; // Variable to store user input and run through root
    // Counter for each square root iteration of input value
    int squareCounter = 0; 

    displayDescription();
    promptInput();
    grabValue(&numToRoot);
    
    if (numToRoot < 10) {
        printf("Invalid input.");
    }
    else {
        printf("number is %.2f\n", numToRoot);
        while (numToRoot > THRESHOLD) {
            numToRoot = findRoot(numToRoot);
            countEachSquare(&squareCounter);
            printf("number is %.2f\n", numToRoot);
            findRoot(numToRoot);
        }
       
        printTotalCounts(&squareCounter);
    }
    return 0;
} // End main()

/*******************************************************************************
    Function: displayDescription()
    Description: Displays program description.
    Parameters: ---
    Return: ---
*******************************************************************************/
void displayDescription(void) {
    printf("%s%s %s",
        "This program requests a double value greater than 10 from the user\n",
        "then iteratively finds the square root of that value until it is smaller",
        "than 1.01.\nIt then prints the total loops iterated to reach this value.\n\n");
} // End displayDescription()

/*******************************************************************************
    Function: promptInput()
    Description: Displays input message (prompts user to enter a value that 
    will be squared).
    Parameters: ---
    Return: ---
*******************************************************************************/
void promptInput(void) {
    printf("Enter a value greater than 10.0: ");
} // End promptInput()

/*******************************************************************************
    Function: grabValue()
    Description: Uses scanf to grab input value
    Parameters: points to numToRoot
    Return: numToRoot
*******************************************************************************/
double grabValue(double* numToRoot) {
    scanf("%lf", numToRoot);
    return *numToRoot;
} // End grabValue()

/*******************************************************************************
    Function: findRoot()
    Description: Calculates square root of user input value
    Parameters: numToRoot
    Return: Square root of numToRoot
*******************************************************************************/
double findRoot(double numToRoot) {
    return sqrt(numToRoot);
} // End findRoot()

/*******************************************************************************
    Function: countEachSquare()
    Description: Keeps track of square root iterations via counter
    Parameters: Points to squareCounter
    Return: ---
*******************************************************************************/
void countEachSquare(int* squareCounter) {
    (*squareCounter)++;
} // end countEachSquare()

/*******************************************************************************
    Function: printTotalCounts()
    Description: Prints final count value
    Parameters: points to squareCounter
    Return: ---
*******************************************************************************/
void printTotalCounts(int* squareCounter) {
    printf("It took %d loops for your value to fall below 1.01.\n",
        *squareCounter);
} // End printTotalCounts()



