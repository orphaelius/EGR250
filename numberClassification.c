/*******************************************************************************

             // Factorial, Prime, Composite, and Perfect Numbers //

    This program prompts a user to select between the above function options to
    determine its factorial value or whether it is prime, composite, or perfect.

    Written by: Jon-Austin Tharpe

    Date: 03/01/2025

*******************************************************************************/

#include <stdio.h>

// Function Prototypes //
void promptSelection(void); // Prompts user to select case label (menu option)
void promptInputValue(void); // Prompts for an input value
int grabKey(int* switchKey); // Grabs switch key via user input
double grabValue(double inputVal); // Takes input value from user
void computeFactorial(double inputVal); // Computes a factorial value    
int primeOrComposite(int inputVal); // Determines prime or composite 
void isItPerfect(int inputVal); // Determines if perfect

/*******************************************************************************
    Function: main()
    Description: Takes user input, process, prints output.. Allows user to 
    select from a 'menu' to run varying functions.
    Parameters: ---
    Return: ---
*******************************************************************************/
int main(void) {
    int switchKey = 0; // Stores switch key to navigate menu options
    double inputVal = 0; // Takes user input

    promptSelection(); // Displays menu
    // While loop to stay inside program and iterate menu 
    // until user decides to exit
    while ((switchKey = grabKey(&switchKey)) != 9) {

        switch (switchKey) {

        case 1: // Compute inputVal! 
            promptInputValue();
            inputVal = grabValue(inputVal);
            computeFactorial(inputVal);
            break;

        case 2: // Determine whether prikme or composite
            promptInputValue();
            // I decided to cast inputVal to int type in both cases 2 and case 3. 
            // I felt like factorial values inherently require more memory, even 
            // while computing 'smaller' initial values. This allows me to only need
            // one variable, one scan function, and one prompt.
            inputVal = grabValue((int)inputVal); 
            primeOrComposite(inputVal);
            break;

        case 3: // Determines if input is a perfect number
            promptInputValue();
            inputVal = grabValue((int)inputVal);
            isItPerfect(inputVal);
            break;

        default:
            // Default message for edge cases
            printf("Did you mean to enter that?\n");
        }
        // Displays menu again after function calls/etc
        promptSelection();
    }
    return 0;
} // End main()

/*******************************************************************************
    Function: promptSelection()
    Description: Prints menu prompt for user selection
    Parameters: ---
    Return: ---
*******************************************************************************/
void promptSelection(void) {
    printf("%s\n%s\n%s\n%s\n", "Enter (1) to calculate factorial values",
        "Enter (2) to determine whether a value is prime or composite",
        "Enter (3) to determine whether a number is perfect",
        "Enter (9) to exit program.");
    printf("Selection: ");
} // End promptSelection()

/*******************************************************************************
    Function: promptInputValue()
    Description: Takes user input, process, prints output.. Allows user to
    select from a 'menu' to run varying functions.
    Parameters: ---
    Return: ---
*******************************************************************************/
void promptInputValue(void) {
    printf("Enter the number to calculate: ");
} // End promptInputValue()

/*******************************************************************************
    Function: grabKey()
    Description: Gets user menu selection (key to use in switch statement)
    Parameters: Points to switchKey-- allows the dynamic update of this in 
    memory to iterate through main loop.
    Return: switchKey to main loop
*******************************************************************************/
int grabKey(int* switchKey) {
    scanf("%d", switchKey);
    return *switchKey;
} // End grabKey()

/*******************************************************************************
    Function: grabValue()
    Description: Gets an initial input value from user to pass into various 
    compute functions
    Parameters: inputVal
    Return: inputVal
*******************************************************************************/
double grabValue(double inputVal) {
    scanf("%lf", &inputVal);
    return inputVal;
} // grabValue()

/*******************************************************************************
    Function: computeFactorial()
    Description: Computes inputVal! (the sum of [value * (value - 1)]) iteratively 
    until counter reaches 1; This loop keeps the sum of numbers starting at 1 times
    an incremental counter until the loop == the user inputVal, accomplishing the 
    same conceptually. 
    Parameters: inputVal
    Return: ---
*******************************************************************************/
void computeFactorial(double inputVal) { 
    double tempFact = 1;     
    for (int i = 1; i <= inputVal; i++) {
        tempFact *= i; 
    } 
    printf("Factorial %.0f! = %.0f\n\n", inputVal, tempFact);   
} // End computeFactorial()

/*******************************************************************************
    Function: primeOrComposite()
    Description: Determines whether an input value is prime or composite. This
    function ended up being messier than I intended, but it's the only way I 
    could figure out how to accomplish both in the same function. I had 
    originally used the return values to trigger statements in the main switch
    statement, but thought this made more sense in the end-- using the return 
    values to exit the function instead.
    Parameters: inputVal
    Return: ---
*******************************************************************************/
int primeOrComposite(int inputVal) {

    if (inputVal < 2) {
        printf("The number %d is neither prime or composite.\n", inputVal);
        return 0;
    }
    else if (inputVal == 2) {
        printf("The number %d is prime!\n", inputVal); 
        return 0;
    }
    else {
        for (int i = 2; i < inputVal; i++) {
            if (inputVal % i == 0) { 
                printf("The number %d is composite!\n", inputVal);
                return 0;
            }
        }
    }
    printf("The number %d is prime!\n", inputVal);
    return 0;
} // End primeOrComposite()

/*******************************************************************************
    Function: isItPerfect()
    Description: Determines whether a number is perfect (the sum of its divisors
    except the number itself).
    Parameters: inputVal
    Return: ---
*******************************************************************************/
void isItPerfect(int inputVal) { 
    int sum = 0;
    for (int i = 1; i < inputVal; i++) {
        if (inputVal % i == 0) {
            sum += i;
        }
    }
    if (sum == inputVal) {
        printf("the number %d is perfect!\n", inputVal);
    }
    else {
        printf("The number %d is not perfect.\n", inputVal);
    }
} // End isItPerfect()


