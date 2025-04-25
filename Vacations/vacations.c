/*******************************************************************************

                            // Vacations //

    This program initializes a structure VACATIONS with 6 members, defines an
    array of structures allVacations[], and fills the array with data from a 
    data file. It displays all data in tabular output in various ways and
    requests user input to determine a user's desired cost range and travel
    range for a vacation. Finally, it requests user input to match a travel
    destination with a portion of an input string.

    Written by: Jon-Austin Tharpe

    Date: 04/25/2025

*******************************************************************************/

// Function prototypes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXCHAR 100
#define TOTALVAC 20

// VACATION structure
typedef struct {
    char destination[MAXCHAR];
    int pricePerDay; 
    int vacationDays;
    float totalCost; 
    float distanceFromReagan;
    int passport;
} VACATION;

// Function prototypes
void readDataFile(VACATION allVacations[]);
void calculateTotalCost(VACATION allVacations[]);
void displayAllVacationData(VACATION allVacations[]);
void displayDestandDist(VACATION allVacations[]);
void distanceSearch(VACATION allVacations[]);
void costSearch(VACATION allVacations[]);
void displayUSDest(VACATION allVacations[]);
void displayOutsideUS(VACATION allVacations[]);
void searchDest(VACATION allVacations[]);
void headerLines(void);
void displayHeader(void);

/*******************************************************************************
    Function: main()
    Description: Displays header, calls functions, etc
    Parameters: ---
    Return: ---
*******************************************************************************/
int main(void) {
    VACATION allVacations[TOTALVAC];
    displayHeader();

    readDataFile(allVacations);
    calculateTotalCost(allVacations);

    displayAllVacationData(allVacations);
    
    displayDestandDist(allVacations); 

    distanceSearch(allVacations);
    costSearch(allVacations);

    displayUSDest(allVacations);
    displayOutsideUS(allVacations);

    searchDest(allVacations);

   return 0;
}

/*******************************************************************************
    Function: readDataFile()
    Description: Reads data file and stores relevant data in array of structures,
    allVacations[]
    Parameters: VACATION allVacations[]
    Return: ---
*******************************************************************************/
void readDataFile(VACATION allVacations[]) {
    // Open data file
    FILE* infile = fopen("vacations-1.txt", "r");
    char endOfLine[10]; // Used to clear buffer
   
    for (size_t i = 0; i < TOTALVAC; ++i) {

        // Grab destination
        fgets(allVacations[i].destination, MAXCHAR, infile);
        allVacations[i].destination[strlen(allVacations[i].destination) - 1] = '\0';

        // Grab price per day
        fscanf(infile, "%d", &allVacations[i].pricePerDay);

        // Grab total vacation days
        fscanf(infile, "%d", &allVacations[i].vacationDays);

        // Grab distance from Reagan Airport
        fscanf(infile, "%f", &allVacations[i].distanceFromReagan);

        // Grab whether trip requires passport
        fscanf(infile, "%d", &allVacations[i].passport);

        // Clear buffer before next fgets() iteration 
        fgets(endOfLine, 10, infile);
    }

    fclose(infile); // Close file

} // End readDataFile()

/*******************************************************************************
    Function: calculateTotalCost()
    Description: Calculates the total cost of each vacation (cost per day times
    total vacation days)
    Parameters: VACATION allVacations[]
    Return: ---
*******************************************************************************/
void calculateTotalCost(VACATION allVacations[]) {
    
    for (size_t i = 0; i < TOTALVAC; ++i) {
        allVacations[i].totalCost = 
            allVacations[i].pricePerDay * allVacations[i].vacationDays;
    }
} // End calculateTotalCost()

/*******************************************************************************
    Function: displayAllVacationsData()
    Description: Displays all data for each vacation
    Parameters: VACATION allVacations[]
    Return: ---
*******************************************************************************/
void displayAllVacationData(VACATION allVacations[]) {

    printf("Displaying full data set...\n");
    headerLines();
    printf("%-30s%-13s%17s%14s%24s%20s\n",
        "Destination", "Price Per Day", "Vacation Days", "Total Cost",
        "Distance From Reagan", "Passport Required");
    headerLines();

    for (size_t i = 0; i < TOTALVAC; ++i) {
        printf("%-30s",allVacations[i].destination);
        printf("%c%-16d", '$', allVacations[i].pricePerDay);
        printf("%-17d", allVacations[i].vacationDays);
        printf("%c%-13.2f", '$', allVacations[i].totalCost);
        printf("%.1f %-17s", allVacations[i].distanceFromReagan, "miles");
        
        if (allVacations[i].passport == 1) {
            printf("%-20s", "Yes");
        }
        else {
            printf("%-20s", "No");
        } 
        puts("");
    }
} // End displayAllVacationData()

/*******************************************************************************
    Function: displayDestandDist()
    Description: Displays only destinations and their distances from Reagan
    Parameters: VACATION allVacations[]
    Return: ---
*******************************************************************************/
void displayDestandDist(VACATION allVacations[]) {

    headerLines();
    printf("Displaying only destinations and their respective distances from Reagan...\n");
    headerLines();
    printf("%-30s%s\n",
        "Destination", "Distance From Reagan");
    headerLines();
    for (size_t i = 0; i < TOTALVAC; ++i) {
        printf("%-30s", allVacations[i].destination);
        printf("%.1f %-17s", allVacations[i].distanceFromReagan, "miles");       
        puts("");
    }
} // End displayDestandDist()

/*******************************************************************************
    Function: distanceSearch()
    Description: Requests user input for a max distance to travel, displays
    which destinations are within bounds (if any)
    Parameters: VACATION allVacations[]
    Return: ---
*******************************************************************************/
void distanceSearch(VACATION allVacations[]) {
    int found = 0;
    puts("");
    headerLines();
    float maxDistance = 0.0;
    printf("Enter the maximum distance, in miles, you are willing to travel from Reagan: ");
    scanf("%f", &maxDistance);
    printf("You entered %.1f miles. Searching...\n", maxDistance);
    headerLines();

    for (size_t i = 0; i < TOTALVAC; ++i) {
        if ((int)(allVacations[i].distanceFromReagan * 1000) <= (int)(maxDistance * 1000)) {
            printf("%s is within %.1f miles of Reagan.\n", allVacations[i].destination, maxDistance);
            found = 1;
        }
    }

    if (!found) {
        printf("No destinations matched to this criteria.\n");
    }
} // End distanceSearch()

/*******************************************************************************
    Function: costSearch()
    Description: Requests user input for max money user is willing to spend
    for a vacation. Displays results within bounds (if any)
    Parameters: VACATION allVacations[]
    Return: ---
*******************************************************************************/
void costSearch(VACATION allVacations[]) {
    int found = 0;
    headerLines();
    float maxSpend = 0.0;
    printf("Enter the most you are willing to spend on a vacation (in USD): ");
    scanf("%f", &maxSpend);

    for (size_t i = 0; i < TOTALVAC; ++i) {
        if ((int)(allVacations[i].totalCost * 1000) <= (int)(maxSpend * 1000)) {
            printf("%s is within your spend range of $%.2f at $%.2f.\n", 
                allVacations[i].destination, maxSpend, allVacations[i].totalCost);
            found = 1;
        }
    }

    if (!found) {
        printf("There are no vacations in your price range.\n");
    }
} // End costSearch()

/*******************************************************************************
    Function: displayUSDest()
    Description: Displays only US vacation destinations
    Parameters: VACATION allVacations[]
    Return: ---
*******************************************************************************/
void displayUSDest(VACATION allVacations[]) {

    char US[30] = { "US" };
    char* search;
    headerLines();
    printf("Displaying all vacation destinations within the US...\n");
    headerLines();
    printf("%s\n", "Destination");
    headerLines();
    for (size_t i = 0; i < TOTALVAC; ++i) {
        search = strstr(allVacations[i].destination, US);
        if (search) {
            printf("%s\n", allVacations[i].destination);
        }  
    }
} // End displayUSDest

/*******************************************************************************
    Function: displayOutsideUS()
    Description: Displays only vacation destinations outside the US
    Parameters: VACATION allVacations[]
    Return: ---
*******************************************************************************/
void displayOutsideUS(VACATION allVacations[]) {

    char US[30] = { "US" };
    char* search;
    headerLines();
    printf("Displaying all vacation destinations outside the US...\n");
    headerLines();
    printf("%s\n", "Destination");
    headerLines();
    for (size_t i = 0; i < TOTALVAC; ++i) {
        search = strstr(allVacations[i].destination, US);
        if (!search) {
            printf("%s\n", allVacations[i].destination);
        }
    }
} // End displayOutsideUS()

/*******************************************************************************
    Function: searchDest()
    Description: Requests input from user for a portion of a vacation destination
    string and runs search to see if any destinations contain that partial
    string. Displays results.
    Parameters: VACATION allVacations[]
    Return: ---
*******************************************************************************/
void searchDest(VACATION allVacations[]) {
    headerLines();
    int found = 0;
    char endOfLine[10];
    fgets(endOfLine, 10, stdin); 
    char searchDest[MAXCHAR] = { " " };
    char* search;
    printf("Enter any portion of a destination to search for: ");
    fgets(searchDest, MAXCHAR, stdin);
    searchDest[strlen(searchDest) - 1] = '\0';
    printf("You entered: %s\n", searchDest); 
    headerLines();
    printf("%s%s \n", "Destinations containing ", searchDest);
    headerLines(); 

    for (size_t i = 0; i < TOTALVAC; ++i) {
        search = strstr(allVacations[i].destination, searchDest);
        if (search) {
            printf("%-30s\n", allVacations[i].destination);
            found = 1;
        }
    }

    if (!found) {
        printf("No destinations containing the string %s", searchDest);
    }
    
} // End searchDest()

/*******************************************************************************
    Function: displayHeader()
    Description: Displays program header
    Parameters: ---
    Return: ---
*******************************************************************************/
void displayHeader() {   
    headerLines();
    printf("%s %s %s",
        "------------------------------------------------------",
        "VACATION DATA",
        "-----------------------------------------------------\n");
    headerLines();
} // End displayHeader()

/*******************************************************************************
    Function: headerLines()
    Description: Clean function to print lines between functions, etc
    Parameters: ---
    Return: ---
*******************************************************************************/
void headerLines() {
    for (size_t i = 0; i < 122; ++i) {
        printf("%c", '-');
    }
    puts("");
} // End headerLines()

