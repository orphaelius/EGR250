/*******************************************************************************

							  // CD Interest //

	This program prompts a user to enter a starting CD deposit value, an 
	interest rate, and how many years the CD is deposited. It then calculates
	the total return and prints the results.

	Written by: Jon-Austin Tharpe

	Date: 03/03/2025

*******************************************************************************/

#include <stdio.h>
#include <math.h>
// Easy to change how often the interest compounds if needed
#define COMPOUND 1 
#define HEADERWID 101 // Width of header

// Function Prototypes //
void displayDesc(void); // Display program description
double getValues(double* value); // Grabs a value via input
// Performs bulk of calculations
double calculateBalance(double* startingDeposit, double* interestRate,
	double* years);
// Displays all results
void displayResults(double startingBalance, double interestRate,
	double years, double endingBalance);

/*******************************************************************************
	Function: main()
	Description: Requests input, grabs input, processes, prints results
	Parameters: ---
	Return: ---
*******************************************************************************/
int main(void) {
	double startingDeposit = 0;
	double interestRate = 0;
	double years = 0;
	double endingBalance = 0;

	printf("Enter your starting deposit in USD: ");
	getValues(&startingDeposit);
	
	printf("Enter your interest rate as a percentage: ");
	getValues(&interestRate);
	
	printf("Enter the length of the CD in years: ");
	getValues(&years);
	
	endingBalance = calculateBalance(&startingDeposit, &interestRate, &years);
	displayResults(startingDeposit, interestRate, years, endingBalance);

	return 0;
} // End main()

/*******************************************************************************
	Function: displayDesc()
	Description: Prints program description/intent
	Parameters: ---
	Return: ---
*******************************************************************************/
void displayDesc() {
	printf("%s%s\n%s%s\n\n", 
		"This program calculates the return and ending balance",
		"of a CD by taking the initial deposit, the interest rate,",
		"and the total length of deposit in years", 
		"It then prints the results.");

} // End displayDesc()

/*******************************************************************************
	Function: getValues()
	Description: Uses scanf to take input
	Parameters: Points to a value
	Return: *value
*******************************************************************************/
double getValues(double* value) {
	scanf("%lf", value);
	return *value;

} // End getValues()

/*******************************************************************************
	Function: calculateBalance()
	Description: Converts interest rate to a decimal value, calculates the 
	total balance of intitial p after n years at an r rate. 
	Parameters: Points to startingDeposit, interestRate, and years
	Return: tempBalance (the total calculated end amount, A)
*******************************************************************************/
double calculateBalance(double* startingDeposit, double* interestRate,
	double* years) {

	// Convert interest rate to a decimal value
	double tempInterest = *interestRate / 100; 
	double tempBalance = 0;	// Placeholder to calculate balance	
	tempBalance = *startingDeposit * 
		(pow((1 + (tempInterest / COMPOUND)), (COMPOUND * *years)));		
	return tempBalance;

} // End calculateBalance()

/*******************************************************************************
	Function: displayResults()
	Description: Calculates difference between initial balance and ending 
	balance, prints a formatted header and all results neatly. 
	Parameters: startingDeposit, interestRate, years, endingBalance
	Return: ---
*******************************************************************************/
void displayResults(double startingDeposit, double interestRate,
	double years, double endingBalance) {
	double difference = endingBalance - startingDeposit;
	puts("");
	// Header
	printf("%s%20s%24s%20s%21s\n", "Starting Deposit", "Interest Rate",
		"Length of Deposit", "Total Earnings", "Ending Balance");
	// for loop here for lines
	for (int i = 0; i < HEADERWID; ++i) {
		printf("%c", '-');
	}
	puts("");
	printf("%9c%.2f%19.2f%c%18.0f%s%14c%.2f%14c%.2f\n",'$', 
		startingDeposit, interestRate, '%', years, " years",'$', difference, '$', endingBalance);	
} // End displayResults()