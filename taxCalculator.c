/******************************************************************************

						// Tax Calculator //

	This program requests a user's marital status, base salary, then computes
	their total taxes based on their tax bracket. It then displays the results.

	Written by: Jon-Austin Tharpe

	Date: 02/24/2025

******************************************************************************/

#include <stdio.h>
#define HEADERWID 89 // Used for printing lines beneath header (neatness..)

// Function Prototypes //
void displayDescription(void); // Nothing hidden here
void maritalStatusMessage(void); // Requests user's marital status
void singleMessage(void); // If single, requent one salary
void marriedMessage(void); // Else request combined salary
// Gets user's marital status as a character data type
char getMaritalStatus(char maritalKey); 
// Gets salary via input
float getBaseSalary(float baseSalary); 
// Calculates tax rate for single status
float calculateSingleTaxRate(float baseSalary);
// Calculates tax rate for married status
float calculateMarriedTaxRate(float baseSalary); 
// Calculates total taxes
float calculateTotalTaxes(float taxRate, float baseSalary);
// Prints results!
void printResults(char maritalKey, float baseSalary, float taxRate,
	float totalTaxes);

/******************************************************************************
	Function: main()
	Description: Main function for program. Runs through each function to get
		marital status, salary, and the call various functions to compute
		tax rate and taxes; prints at end. 
	Side Effects: ---
	Parameters: ---
	Return: ---
******************************************************************************/
int main(void) {

	char maritalKey = ' '; // Variable to grab marital status
	float baseSalary = 0; 
	float taxRate = 0; // coulduse int then reassign to float....
	float totalTaxes = 0;

	displayDescription(); 
	maritalStatusMessage(); // Request user marital status
	// Grabs switch key for determining which case to enter
	maritalKey = getMaritalStatus(maritalKey); 
	
	switch (maritalKey) {

	// Case label for single status
	case 'S':
	case 's':		
		singleMessage();
		baseSalary = getBaseSalary(baseSalary);  
		taxRate = calculateSingleTaxRate(baseSalary);
		totalTaxes = calculateTotalTaxes(taxRate, baseSalary);						
		break;

	// Case label for married status
	case 'M':
	case 'm':		
		marriedMessage(); 
		baseSalary = getBaseSalary(baseSalary);
		taxRate = calculateMarriedTaxRate(baseSalary);  
		totalTaxes = calculateTotalTaxes(taxRate, baseSalary);
		break;

	// Exits if user so pleases
	case 'E':
	case 'e':
		printf("ending program...");		
		break;

	// Default for any abnormal user behavior
	default:
		printf("That is not a valid entry.\n");
		break;
	}

	// Prints results
	printResults(maritalKey, baseSalary, taxRate, totalTaxes);

	return 0;
} // End main()

/******************************************************************************
	Function: displayDescription()
	Description: Displays program intentions.
	Side Effects: ---
	Parameters: ---
	Return: ---
******************************************************************************/
void displayDescription() {
	printf("%s %s %s %s", "This program requests a users marital status",
		   "and base salary,", "computes the taxes,", "then displays the results.");
	puts("");
	puts("");
} // End displayDescription()

/******************************************************************************
	Function: maritalStatusMssage()
	Description: Requests (prints message) user marital status
	Side Effects: ---
	Parameters: ---
	Return: ---
******************************************************************************/
void maritalStatusMessage() {
	printf("%s %s", "First, select your marital status. Enter (S) for single,",
		"(M) for married, or (E) to exit: ");
} // End maritalStatusMessage()

/******************************************************************************
	Function: getMaritalStatus()
	Description: Uses scan function to grab user's marital status as a char
	data type
	Side Effects: Assigns new value
	Parameters: char maritalKey
	Return: maritalKey (marital status)
******************************************************************************/
char getMaritalStatus(char maritalKey) {
	scanf(" %c", &maritalKey); 
	return maritalKey;
} // End getMaritalStatus()

/******************************************************************************
	Function: singleMessage()
	Description: Requests single base salary
	Side Effects: ---
	Parameters: ---
	Return: ---
******************************************************************************/
void singleMessage() {
	printf("Enter your total base salary: ");		
} // End singleMessage()

/******************************************************************************
	Function: marriedMessage()
	Description: Requests a "combined" base salary
	Side Effects: ---
	Parameters: ---
	Return: ---
******************************************************************************/
void marriedMessage() {
	printf("Enter your total combined base salary: ");
} // End marriedMessage()

/******************************************************************************
	Function: getBaseSalary()
	Description: Uses scan function to grab user's base salary
	Side Effects: Updates user's base salary
	Parameters: baseSalary
	Return: baseSalary
******************************************************************************/
float getBaseSalary(float baseSalary) {
	scanf("%f", &baseSalary); 
	return baseSalary;
} // End getBaseSalary()

/******************************************************************************
	Function: calculateSingleTaxRate()
	Description: Uses an if... else statement to determine a user's tax rate
	Side Effects: Returns taxRate value
	Parameters: baseSalary
	Return: taxRate
******************************************************************************/
float calculateSingleTaxRate(float baseSalary) {

	if (baseSalary <= 9875) {
		return 10;
	}
	else if (baseSalary <= 40125) {
		return 12;
	}
	else if (baseSalary <= 85525) {
		return 22;
	}
	else if (baseSalary <= 163300) {
		return 24;
	}
	else if (baseSalary <= 207350) {
		return 32;
	}
	else if (baseSalary <= 518400) {
		return 35;
	}
	else { // Tax rate for anything above $518,400
		return 37;
	}	
} // End calculateSingleTaxRate()

/******************************************************************************
	Function: calculateMarriedTaxRate()
	Description: Uses an if... else statement to determine a user's combined 
	tax rate
	Side Effects: Returns taxRate value
	Parameters: baseSalary
	Return: taxRate
******************************************************************************/
float calculateMarriedTaxRate(float baseSalary) {

	if (baseSalary <= 19750) {
		return 10;
	}
	else if (baseSalary <= 80250) {
		return 12;
	}
	else if (baseSalary <= 171050) {
		return 22;
	}
	else if (baseSalary <= 326600) {
		return 24;
	}
	else if (baseSalary <= 414701) {
		return 32;
	}
	else if (baseSalary <= 622050) {
		return 35;
	}
	else { // Tax rate for anything above $622050
		return 37;
	}
} // End calculateMarriedTaxRate()

/******************************************************************************
	Function: calculateTotalTaxes()
	Description: Converts taxRate to a decimal value, multiplies by user's 
	baseSalary to determine totalTaxes
	Side Effects: Updates totalTaxes
	Parameters: taxRate, baseSalary
	Return: value for totalTaxes
******************************************************************************/
float calculateTotalTaxes(float taxRate, float baseSalary) {
	// Convert taxRate to a decimal, multiply by baseSalary
	return (taxRate / 100) * baseSalary; 
} // End calculateTotalTaxes

/******************************************************************************
	Function: printResults()
	Description: Checks marital status and updates to string for printing, 
	prints results with a neat header, etc.
	Side Effects: ---
	Parameters: maritalKey, baseSalary, taxRate, totalTaxes
	Return: ---
******************************************************************************/
void printResults(char maritalKey, float baseSalary, float taxRate, 
	float totalTaxes) {

	char maritalStatus[2][8] = { "Single", "Married" }; 
	int status = 0;

	if (maritalKey == 's') {
		status = 0; 
	}
	else {
		status = 1; 
	}

	printf("%s%25s%25s%25s\n", "Marital Status", "Total Salary", "Tax Rate",
		"Total Taxes");

	for (int i = 0; i < HEADERWID; i++) { 
		printf("%c", '-');
	} 
	puts("");
	
	printf("%14s %15c%9.2f %23.0f%% %15c%8.2f", maritalStatus[status], '$', 
		baseSalary, taxRate, '$', totalTaxes);
} // End printResults
