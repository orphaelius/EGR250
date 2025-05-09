/*******************************************************************************

							// STOCK PORTFOLIO //

	This program is a simple cumulative exercise to showcase the bulk of the
	subject material taught during the 2025 Spring Semester of EGR 250. The
	premise is to read in data from an external data file and allow a user to
	select from an array of options to interact and manipulate that data,
	ranging from simple console display of data tables/values to more nuanced
	interactions like manipulating those values after reading via user input.

	Written by: Jon-Austin Tharpe

	Date: 05/07/2025

*******************************************************************************/

/***** LIBRARIES *****/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "menu.h" // External menu function

/***** PREPROC CONSTANTS *****/
#define COMPANIES 10 // Total companies to read in
#define STATECHAR 5 // Limit for state abbreviations
#define CITYCHAR 25 // Limit for city names
#define NAMEMAX 30 // Limit for individual names
#define SYMBCHAR 6 // Limit for stock "symbols"

/***** LOCATION STRUCT *****/
typedef struct {
	char city[CITYCHAR];
	char state[STATECHAR];
} LOCATION;

/***** CEO STRUCT *****/
typedef struct {
	char name[NAMEMAX];
	int totalComp;
} CEO;

/***** STOCK STRUCT *****/
typedef struct {
	char stockName[NAMEMAX];
	char stockSym[SYMBCHAR];
	char stockChangeString[NAMEMAX];
	float stockChange[2];
	int numShares;
	LOCATION location;
	CEO CEO;
} STOCK;

/***** FUNCTION PROTOTYPES *****/
// These are mostly in sequential order of the program excluding
// repetitive basic QOL functions which are seperated by an space

int getSwitchKey(int* switchKey);
void readStockData(STOCK allStockData[]);
void displayAllData(STOCK *allStockData);
void displaySingleStockdata(STOCK allStockData[], int i);
void displayCEOinfo(STOCK allStockData[]);
void searchStockBySymbol(STOCK allStockData[]);
void searchPortionStockName(STOCK allStockData[]);
void displayHigherPrice(STOCK allStockData[]);
void displayLowerValue(STOCK allStockData[]);
void displayHigherValue(STOCK allStockData[]);
void displayIncreaseDecrease(STOCK allStockData[]);
void displayPortfolioValue(STOCK allStockData[]);
void searchByLocation(STOCK allStockData[]);
void searchForCEO(STOCK allStockData[]);
void searchCEOCompRange(STOCK allStockData[]);
void highestCEOcomp(STOCK allStockData[]);
void lowestCEOcomp(STOCK allStockData[]);
void replaceCEO(STOCK allStockData[]);

void displayProgramHeader();
void printHeaderLines();
void rinsePalate(); // Definitely clears buffer...
void displayComma(int n);

/*******************************************************************************
	Function: main()
	Description: Displays header, calls functions, etc
	Parameters: ---
	Return: ---
*******************************************************************************/
int main(void) {
	STOCK allStockData[COMPANIES]; // Array of structures
	int switchKey = 0; // Used for menu navigation
	
	displayProgramHeader(); // Displays small program header
	readStockData(allStockData); // Reads data from data file

	printf("M E N U  O P T I O N S:\n");
	printHeaderLines();

	// Shows menu
	showMenu();

	// Main loop, reiterates menu options eternally until user enters -1 or loses power
	while ((switchKey = getSwitchKey(&switchKey))) {

		if (switchKey == -1) {
			printf("Exiting program...\n");
			break;
		}

		switch (switchKey) {

		case 1: // Displays all data
			displayAllData(allStockData);
			break;
		case 2: // Displays stock name, CEO, and location data
			displayCEOinfo(allStockData);
			break;

		case 3: // Search for stock by symbol
			rinsePalate();
			searchStockBySymbol(allStockData);
			break;

		case 4: // Search for portion of any stock/company name
			rinsePalate();
			searchPortionStockName(allStockData);
			break;

		case 5: // Display stocks that have a higher current price than user entry			
			displayHigherPrice(allStockData);
			break;

		case 6: // Display stocks that have diminished in value since purchase
			displayLowerValue(allStockData);
			break;

		case 7: // Display stocks that have increased in value since purchase
			displayHigherValue(allStockData);
			break;

		case 8: // Display stock symbols and value change by percentage since purchase
			displayIncreaseDecrease(allStockData);
			break;

		case 9: // Display portfolio value by individual stock and total sum
			displayPortfolioValue(allStockData);
			break;

		case 10: // Search for stocks by location data			
			searchByLocation(allStockData);
			break;

		case 11: // Search by CEO name
			rinsePalate();
			searchForCEO(allStockData);
			break;

		case 12: // Search by CEO comp ranges
			searchCEOCompRange(allStockData);
			break;

		case 13: // display CEO who has the greatest total comp
			highestCEOcomp(allStockData);
			break;

		case 14: // Display the CEO with the lowest total comp
			lowestCEOcomp(allStockData);
			break;

		case 15: // Replace CEO name and total comp package
			rinsePalate();
			replaceCEO(allStockData);
			break;
		}

		printHeaderLines();
		printf("M E N U  O P T I O N S:\n");
		printHeaderLines();
		showMenu();
	}
} // End main()

/*******************************************************************************
	Function: getSwitchKey()
	Description: Passes switch key back into main body loop
	Parameters: Points to switchKey, allowing for perpetual update of value to
	navigate the main loop accordingly
	Return: switchKey
*******************************************************************************/
int getSwitchKey(int* switchKey) {
	scanf("%d", switchKey);
	return *switchKey;
} // End getSwitchKey()

/*******************************************************************************
	Function: readStockData()
	Description: Reads all data from data file, stockdataFINAL.txt, assigns
	values to array of structures, allStockData[]
	Parameters: STOCK allStockData[]
	Return: ---
*******************************************************************************/
void readStockData(STOCK allStockData[]) {
	FILE* infile = fopen("stockdataFINAL.txt", "r");
	char endOfLine[10];

	for (size_t i = 0; i < COMPANIES; ++i) {

		// Get city name, null terminate
		fgets(allStockData[i].location.city, CITYCHAR, infile);
		allStockData[i].location.city[strlen(allStockData[i].location.city) - 1] = '\0';

		// Get state abbreviation, null terminate
		fgets(allStockData[i].location.state, STATECHAR, infile);
		allStockData[i].location.state[strlen(allStockData[i].location.state) - 1] = '\0';

		// Get CEO name, null terminate
		fgets(allStockData[i].CEO.name, NAMEMAX, infile);
		allStockData[i].CEO.name[strlen(allStockData[i].CEO.name) - 1] = '\0';

		// Scan totalComp
		fscanf(infile, "%d", &allStockData[i].CEO.totalComp);
		fgets(endOfLine, 10, infile);

		// Get stock name, null terminate
		fgets(allStockData[i].stockName, NAMEMAX, infile);
		allStockData[i].stockName[strlen(allStockData[i].stockName) - 1] = '\0';

		// Get stock abbreviation, null terminate
		fgets(allStockData[i].stockSym, SYMBCHAR, infile);
		allStockData[i].stockSym[strlen(allStockData[i].stockSym) - 1] = '\0';

		// Get stockChangeString, null terminate, tokenize, convert to float, etc
		fgets(allStockData[i].stockChangeString, NAMEMAX, infile);
		allStockData[i].stockChangeString[strlen(allStockData[i].stockChangeString) - 1] = '\0';
		int j = 0;
		char* token = strtok(allStockData[i].stockChangeString, ",");
		while (token != NULL && j < 2) {
			allStockData[i].stockChange[j] = atof(token);
			token = strtok(NULL, ",");
			j++;
		}

		// Get number shares
		fscanf(infile, "%d", &allStockData[i].numShares);
		fgets(endOfLine, 10, infile);
	}
} // End readStockData()

/*******************************************************************************
	Function: displayAllData()
	Description: Displays all data from data file in clean tabular output using
	pass by reference
	Parameters: Pointer to STOCK allStockData
	Return: ---
*******************************************************************************/
void displayAllData(STOCK *allStockData) {
	int n = 0;
	printHeaderLines();
	printf("%-26s %-17s %-9s %-26s %-18s %-22s %-20s %-23s %-20s\n", "Company",
		"City", "State", "CEO", "CEO Total Comp", "Stock Abbreviation",
		"Last Stock Price", "Current Stock Price", "Number of Shares");
	printHeaderLines();
	for (size_t i = 0; i < COMPANIES; ++i) {
		printf("%-27s", (allStockData + i)->stockName);
		printf("%-18s", (allStockData + i)->location.city);
		printf("%-10s", (allStockData + i)->location.state);
		printf("%-27s", (allStockData + i)->CEO.name);
		n = (allStockData + i )->CEO.totalComp;
		displayComma(n);
		printf("%-9c", ' ');
		printf("%-23s", (allStockData + i)->stockSym);
		printf("$%-21.2f$%-24.2f", (allStockData + i)->stockChange[0],
			(allStockData + i )->stockChange[1]);
		printf("%-20d", (allStockData + i)->numShares);
		puts("");
	}
} // End displayAllData()

/*******************************************************************************
	Function: displaySingleStockData()
	Description: Displays data relevant to single stock using counter value from
	a loop as the index
	Parameters: STOCK allStockData[], int i (current counter)
	Return: ---
*******************************************************************************/
void displaySingleStockdata(STOCK allStockData[], int i) {
	int n = 0;
	printHeaderLines();
	printf("%-26s %-17s %-9s %-26s %-18s %-22s %-20s %-23s %-20s\n", "Company",
		"City", "State", "CEO", "CEO Total Comp", "Stock Abbreviation",
		"Last Stock Price", "Current Stock Price", "Number of Shares");

	printHeaderLines();

	printf("%-27s", allStockData[i].stockName);
	printf("%-18s", allStockData[i].location.city);
	printf("%-10s", allStockData[i].location.state);
	printf("%-27s", allStockData[i].CEO.name);
	n = allStockData[i].CEO.totalComp;
	displayComma(n);
	printf("%-9c", ' ');
	printf("%-23s", allStockData[i].stockSym);
	printf("$%-21.2f$%-24.2f", allStockData[i].stockChange[0],
		allStockData[i].stockChange[1]);
	printf("%-20d", allStockData[i].numShares);
	puts("");
	puts("");

} // End displaySingleStockData()

/*******************************************************************************
	Function: displayCEOinfo()
	Description: Displays stock company, CEO name, and location data
	Parameters: STOCK allStockData[]
	Return: ---
*******************************************************************************/
void displayCEOinfo(STOCK allStockData[]) {
	printHeaderLines();
	printf("%-26s %-25s %-17s %-20s\n", "Company", "CEO", "City", "State");
	printHeaderLines();
	for (size_t i = 0; i < COMPANIES; ++i) {
		printf("%-27s", allStockData[i].stockName);
		printf("%-26s", allStockData[i].CEO.name);
		printf("%-18s", allStockData[i].location.city);
		printf("%-20s", allStockData[i].location.state);
		puts("");
	}
} // End displayCEOinfo()

/*******************************************************************************
	Function: searchStockBySymbol()
	Description: Allows user to input a string to search for a specific
	stock by symbol. Converts input to uppercase, compares via strcmp()
	Parameters: STOCK allStockData[]
	Return: ---
*******************************************************************************/
void searchStockBySymbol(STOCK allStockData[]) {
	puts("");
	char inputSymbol[SYMBCHAR] = { "" };
	int found = 0;
	printf("Enter the stock symbol: ");
	fgets(inputSymbol, SYMBCHAR, stdin);
	inputSymbol[strlen(inputSymbol) - 1] = '\0';

	// Converts input to uppercase to properly use strcmp()
	for (size_t i = 0; i < strlen(inputSymbol); ++i) {
		inputSymbol[i] = toupper(inputSymbol[i]);
	}

	printf("Searching...\n");

	for (size_t i = 0; i < COMPANIES; ++i) {
		if (strcmp(inputSymbol, allStockData[i].stockSym) == 0) {
			printf("%s is in your portfolio!\n", allStockData[i].stockSym);
			found = 1;
		}
	}

	if (!found) {
		printf("No stock symbol matches %s in your portfolio\n", inputSymbol);
	}
} // End searchStockBySymbol()

// ADD FORMATTING TO DISPLAY ALL STOCK INFO IF FOUND
/*******************************************************************************
	Function: searchPortionStockName()
	Description: Takes user input and searches for any portion of a stock name
	Parameters: STOCK allStockData[]
	Return: ---
*******************************************************************************/
void searchPortionStockName(STOCK allStockData[]) {
	puts("");
	char inputStockName[NAMEMAX] = { "" };
	char* search;
	int found = 0;
	printf("Enter any portion of a company name to search: ");
	fgets(inputStockName, NAMEMAX, stdin);
	inputStockName[strlen(inputStockName) - 1] = '\0';

	printf("Searching...\n");

	for (size_t i = 0; i < COMPANIES; ++i) {
		search = strstr(allStockData[i].stockName, inputStockName);

		if (search) {
			displaySingleStockdata(allStockData, i);
			found = 1;
		}
	}

	if (!found) {
		printf("No company matches %s\n", inputStockName);
	}
} // End searchPortionStockName()

/*******************************************************************************
	Function: displayHigherPrice()
	Description: Takes user input to compare stocks with a higher current value
	Parameters: STOCK allStockData[]
	Return: ---
*******************************************************************************/
void displayHigherPrice(STOCK allStockData[]) {
	puts("");
	int inputHigh = 0;
	int found = 0;
	printf("Enter a stock value in USD and I will return all stocks with a higher current value: ");
	scanf("%d", &inputHigh);

	for (size_t i = 0; i < COMPANIES; ++i) {

		if (allStockData[i].stockChange[1] > inputHigh) {
			found++;
			if (found == 1) { // Print message once
				printf("%s", "Stocks:\n");
			}
			printf("%s\n", allStockData[i].stockName);
		}
	}

	if (!found) {
		printf("No stocks are currently higher than that value.\n");
	}

} // End displayHighterPrice()

/*******************************************************************************
	Function: displayLowerPrice()
	Description: Compares stock values and displays any stocks whose values have
	diminished since purchase
	Parameters: STOCK allStockData[]
	Return: ---
*******************************************************************************/
void displayLowerValue(STOCK allStockData[]) {
	puts("");
	int found = 0;
	for (size_t i = 0; i < COMPANIES; ++i) {

		if (allStockData[i].stockChange[1] < allStockData[i].stockChange[0]) {
			found++;
			if (found == 1) { // Print message once
				printf("Stocks that have lost value since purchase:\n");
				printf("%-20s%-20s%-20s", "Stock", "Purchase Price", "Current Value");
			}
			printf("%-20s%-20f%-20f\n", allStockData[i].stockName,
				allStockData[i].stockChange[0], allStockData[i].stockChange[1]);
		}
	}

	if (!found) {
		printf("No stocks in your portfolio have lost value since purchase.\n");
	}

} // End displayLowerValue()

/*******************************************************************************
	Function: displayHigherPrice()
	Description: Compares stock values and displays any stocks whose values have
	increased since purchase
	Parameters: STOCK allStockData[]
	Return: ---
*******************************************************************************/
void displayHigherValue(STOCK allStockData[]) {
	puts("");
	int found = 0;
	for (size_t i = 0; i < COMPANIES; ++i) {

		if (allStockData[i].stockChange[1] > allStockData[i].stockChange[0]) {
			found++;
			if (found == 1) { // Print message once
				printHeaderLines();
				printf("%-26s%-20s%-20s\n", "Stock", "Purchase Price", "Current Value");
				printHeaderLines();
			}
			printf("%-26s$%-20.2f$%-20.2f\n", allStockData[i].stockName,
				allStockData[i].stockChange[0], allStockData[i].stockChange[1]);
		}
	}

	if (!found) {
		printf("No stocks in your portfolio have increased value since purchase.\n");
	}

} // End displayHigherValue()

/*******************************************************************************
	Function: displayIncreaseDecrease()
	Description: Determines percent change between purchase price and
	current value, displays stock symbols and relevant percentage changes
	Parameters: STOCK allStockData[]
	Return: ---
*******************************************************************************/
void displayIncreaseDecrease(STOCK allStockData[]) {
	puts("");
	float percentChange = 0.0;
	printHeaderLines();
	printf("%-20s%-20s\n", "Stock Symbol", "Percent Change (%)");
	printHeaderLines();
	for (size_t i = 0; i < COMPANIES; ++i) {
		percentChange = (allStockData[i].stockChange[1] -
			allStockData[i].stockChange[0]) / allStockData[i].stockChange[0];
		percentChange *= 100;
		printf("%-20s%-20.1f%\n", allStockData[i].stockSym, percentChange);
	}
} // End displayIncreaseDecrease()


/*******************************************************************************
	Function: displayPortfolioValue()
	Description: Displays portfolio percentage changes and total sum value
	Parameters: STOCK allStockData[]
	Return: ---
*******************************************************************************/
void displayPortfolioValue(STOCK allStockData[]) {
	puts("");
	float tempSum = 0.0;
	float totalSum = 0.0;
	printHeaderLines();
	printf("%-26s%-20s%-20s\n", "Stock", "Total Shares", "Total Value");
	printHeaderLines();
	for (size_t i = 0; i < COMPANIES; ++i) {
		tempSum = allStockData[i].stockChange[1] * allStockData[i].numShares;
		totalSum += tempSum;
		printf("%-26s%-20d$%-20.2f\n", allStockData[i].stockName, allStockData[i].numShares, tempSum);
	}

	printf("%s%$%.2f\n", "Total portfolio value: ", totalSum);
} // End displayPortfolioValue()

/*******************************************************************************
	Function: searchByLocation()
	Description: Allows user to search for company location data using user
	input and strstr()
	Parameters: STOCK allStockData[]
	Return: ---
*******************************************************************************/
void searchByLocation(STOCK allStockData[]) {
	puts("");
	rinsePalate();

	char inputLocation[CITYCHAR] = { "" };
	char* search;
	int found = 0;
	printf("Enter any portion of city or state to search for companies in those jurisdictions: ");
	fgets(inputLocation, CITYCHAR, stdin);
	inputLocation[strlen(inputLocation) - 1] = '\0';

	printf("Searching...\n");

	for (size_t i = 0; i < COMPANIES; ++i) {
		search = strstr(allStockData[i].location.city, inputLocation);

		if (search) {
			printf("Company found! %s\n", allStockData[i].stockName);
			found = 1;
		}
	}

	for (size_t i = 0; i < COMPANIES; ++i) {
		// Converts input to uppercase to properly use strcmp() to compare state abbreviations
		for (size_t i = 0; i < strlen(inputLocation); ++i) {
			inputLocation[i] = toupper(inputLocation[i]);
		}
		search = strstr(allStockData[i].location.state, inputLocation);
		if (search) {
			printf("Company found! %s\n", allStockData[i].stockName);
			found = 1;
		}
	}

	if (!found) {
		printf("No companies found.\n", inputLocation);
	}
} // End searchByLocation()

/*******************************************************************************
	Function: searchForCEO()
	Description: Allows user to input any portion of a CEO name to search for
	that CEO using strstr()
	Parameters: STOCK allStockData[]
	Return: ---
*******************************************************************************/
void searchForCEO(STOCK allStockData[]) {
	puts("");
	char inputSymbol[NAMEMAX] = { "" };
	char* search;
	int found = 0;
	printf("Enter any portion of the CEO name to search for: ");
	fgets(inputSymbol, NAMEMAX, stdin);
	inputSymbol[strlen(inputSymbol) - 1] = '\0';

	printf("Searching...\n");

	for (size_t i = 0; i < COMPANIES; ++i) {
		search = strstr(allStockData[i].CEO.name, inputSymbol);
		if (search) {
			found++;
			if (found == 1) { // Print once
				printf("CEO found!\n");
			}
			printf("%s\n", allStockData[i].CEO.name);
		}
	}

	if (!found) {
		printf("No CEO found with %s in their name.\n", inputSymbol);
	}
} // End searchForCEO()

/*******************************************************************************
	Function: searchCEOCompRange()
	Description: Takes user input for upper and lower comp ranges, determines
	which CEOs exist within that range. Displays results.
	Parameters: STOCK allStockData[]
	Return: ---
*******************************************************************************/
void searchCEOCompRange(STOCK allStockData[]) {
	puts("");
	int upperLimit = 0;
	int lowerLimit = 0;
	int found = 0;

	printf("Enter a lower comp limit in USD: ");
	scanf("%d", &lowerLimit);
	printf("Enter an upper comp limit in USD: ");
	scanf("%d", &upperLimit);

	for (size_t i = 0; i < COMPANIES; ++i) {

		if (allStockData[i].CEO.totalComp <= upperLimit && allStockData[i].CEO.totalComp >= lowerLimit) {
			found++;
			if (found == 1) { // Print header once
				printHeaderLines();
				printf("%-26s%-20s\n", "CEO Name", "Company");
				printHeaderLines();
			}
			printf("%-26s%-20s\n", allStockData[i].CEO.name, allStockData[i].stockName);
		}
	}

	if (!found) {
		printf("No CEOs have a total comp package in that range\n");
	}
} // End searchCEOCompRange()

/*******************************************************************************
	Function: highestCEOcomp()
	Description: Determines which CEO has highest comp, displays results.
	Parameters: STOCK allStockData[]
	Return: ---
*******************************************************************************/
void highestCEOcomp(STOCK allStockData[]) {
	puts("");
	int highest = 0;
	int j = 0;
	int comp = 0;

	for (size_t i = 0; i < COMPANIES; ++i) {
		if (allStockData[i].CEO.totalComp > highest) {
			highest = allStockData[i].CEO.totalComp;
			j = i;
			comp = allStockData[i].CEO.totalComp;
		}
	}

	printf("%s has the highest comp at ", allStockData[j].CEO.name);
	displayComma(comp);
	puts("");
} // End highestCEOcomp()

/*******************************************************************************
	Function: lowestCEOcomp()
	Description: Determines which CEO has lowest comp, displays results.
	Parameters: STOCK allStockData[]
	Return: ---
*******************************************************************************/
void lowestCEOcomp(STOCK allStockData[]) {
	puts("");
	int lowest = allStockData[0].CEO.totalComp;
	int j = 0;
	int comp = 0;

	for (size_t i = 0; i < COMPANIES; ++i) {

		if (allStockData[i].CEO.totalComp < lowest) {
			lowest = allStockData[i].CEO.totalComp;
			j = i;
			comp = allStockData[j].CEO.totalComp;
		}
	}
	printf("%s has the lowest comp at ", allStockData[j].CEO.name);
	displayComma(comp);
	puts("");
} // End lowesttCEOcomp()

/*******************************************************************************
	Function: replaceCEO()
	Description: Allows user to search for stock company and replace CEO/total
	comp for a particular stock
	Parameters: STOCK allStockData[]
	Return: ---
*******************************************************************************/
void replaceCEO(STOCK allStockData[]) {
	puts("");
	char endOfLine[10];
	char stockSym[SYMBCHAR] = { "" };
	char newCEO[NAMEMAX] = { "" };
	int newComp = 0;
	int confirmation = 0;
	int found = 0;

	printf("Enter the stock symbol to replace the CEO and comp: ");
	fgets(stockSym, SYMBCHAR, stdin);
	stockSym[strlen(stockSym) - 1] = '\0';

	// Converts input to uppercase to properly use strcmp()
	for (size_t i = 0; i < strlen(stockSym); ++i) {
		stockSym[i] = toupper(stockSym[i]);
	}

	for (size_t i = 0; i < COMPANIES; ++i) {

		if (strcmp(stockSym, allStockData[i].stockSym) == 0) {
			found = 1;
			printf("Found %s\n", stockSym);
			printf("Enter (1) to confirm replacement of %s or (0) to return: ", allStockData[i].CEO.name);
			scanf("%d", &confirmation);

			if (confirmation) {
				rinsePalate();
				printf("Enter the new CEO name: ");
				fgets(newCEO, NAMEMAX, stdin);
				newCEO[strlen(newCEO) - 1] = '\0';

				strcpy(allStockData[i].CEO.name, newCEO);
				printf("new ceo of %s is %s\n", allStockData[i].stockSym, allStockData[i].CEO.name);

				printf("Enter the new comp in USD: ");
				scanf("%d", &newComp);
				allStockData[i].CEO.totalComp = newComp;

				printf("new comp for %s is %d\n", allStockData[i].CEO.name, allStockData[i].CEO.totalComp);
			}

			if (!confirmation) {
				printf("Exiting menu option...\n");
				return;
			}
		}
	}

	if (!found) {
		printf("No matching stock symbol to %s in portfolio.\n", stockSym);
	}
} // End replaceCEO()

/*******************************************************************************
	Function: displayProgramHeader()
	Description: Displays program header at initialization
	Parameters: ---
	Return: ---
*******************************************************************************/
void displayProgramHeader() {
	printHeaderLines();
	puts("");
	printf("%s %s %s",
		"---------------------------------------------------------------------------",
		"M Y  T R A D I N G  P O R T F O L I O",
		"-----------------------------------------------------------------------\n");
	puts("");
	printHeaderLines();
} // End displayProgramHeader()

/*******************************************************************************
	Function: printHeaderLines()
	Description: Displays lines for clean formatting of data
	Parameters: ---
	Return: ---
*******************************************************************************/
void printHeaderLines() {
	for (size_t i = 0; i < 185; ++i) {
		printf("%c", '-');
	}
	puts("");
} // End printHeaderLines()

/*******************************************************************************
	Function: displayComma()
	Description: Displays comma between 3-digit groups. Thanks to paxdiablo via
	Stackoverflow for posting this solution:
	stackoverflow.com/questions/1449805/how-to-format-a-number-using-comma-as-thousands-separator-in-c
	Parameters: An integer
	Return: ---
*******************************************************************************/
void displayComma(int n) {
	if (n < 1000) {
		printf("$%d", n);
		return;
	}
	displayComma(n / 1000);
	printf(",%03d", n % 1000);
} // End displayComma()

/*******************************************************************************
	Function: rinsePalate()
	Description: Clears buffer
	Parameters: ---
	Return: ---
*******************************************************************************/
void rinsePalate() {
	char endOfLine[10];
	fgets(endOfLine, 10, stdin);
} // End rinsePalate()
