/*******************************************************************************

                     // Movies, Strings, and Data Files //

    This program reads in a data file of film titles, release years, ratings, 
    and run times. It then prints a menu requesting user input to search for
    film names by full title, partial title, release year, range of release
    years, rating, or printing the entire data file in tabular format. User may
    also search by film rating.

    Written by: Jon-Austin Tharpe

    Date: 04/11/2025

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MOVIES 15 // Total films in data file
#define TITLECHAR 30 // Char limit for titles
#define RATECHAR 20 // Char limit for ratings
#define HEADERWID 100 // For printing 

// Function prototypes
void printHeader(void);
void readFile(char movieNames[][TITLECHAR], int yearReleasted[MOVIES], 
    int runTimes[MOVIES], char mpaRating[MOVIES][RATECHAR]);
void printMenu(void);
int getMenuKey(int* menuOption);
void fullStringSearch(char movieNames[][TITLECHAR], char userInputString[], 
    int yearReleased[MOVIES], int runTimes[MOVIES], 
    char mpaRating[MOVIES][RATECHAR]);
void partialStringSearch(char movieNames[][TITLECHAR], char userInputString[], 
    int yearReleased[MOVIES], int runTimes[MOVIES], 
    char mpaRating[MOVIES][RATECHAR]);
void searchByYear(char movieNames[][TITLECHAR], int yearReleased[MOVIES], 
    int* menuOption, int runTimes[MOVIES], char mpaRating[MOVIES][RATECHAR]);
void searchByRating(char userInputString[], char movieNames[][TITLECHAR], 
    char mpaRating[][RATECHAR]);
int grabYear(int year);
void printTable(char movieNames[][TITLECHAR], int yearReleased[MOVIES], 
    int runTimes[MOVIES], char mpaRating[MOVIES][RATECHAR]);
void printFilmDetails(char movieNames[][TITLECHAR], int yearReleased[MOVIES], 
    int runTimes[MOVIES], char mpaRating[MOVIES][RATECHAR], int i);
void printColumns(); 

/*******************************************************************************
    Function: main()
    Description: Displays header, menu, calls functions, etc
    Parameters: ---
    Return: ---
*******************************************************************************/
int main(void) {
    char movieNames[MOVIES][TITLECHAR] = { " " };
    int yearReleased[MOVIES] = { 0 };
    int runTimes[MOVIES] = { 0 }; // In minutes
    char mpaRating[MOVIES][RATECHAR] = { " " };
    int menuOption = 0; // For menu navigation
    char userInputString[TITLECHAR] = { " " }; // For storing user input
    printHeader(); // Displays program header
    readFile(movieNames, yearReleased, runTimes, mpaRating); // Reads in data
    printMenu(); // Displays user menu to console

    // Primary user input/menu loop-- passes menuOption into getMenuKey by 
    // reference so that it is always being updated
    while ((menuOption == getMenuKey(&menuOption)) != -1) {
        if (menuOption == -1) {
            printf("Exiting program...");
            break;
        }
        switch (menuOption) {      

        case 1: // Search film list by title
            fullStringSearch(movieNames, userInputString, yearReleased, 
                runTimes, mpaRating);
            break;
        case 2: // Search films by specific year
            searchByYear(movieNames, yearReleased, &menuOption, runTimes, 
                mpaRating);
            break;
        case 3: // Search films by range of years-- low year and high year
            searchByYear(movieNames, yearReleased, &menuOption, runTimes, 
                mpaRating); 
            break;
        case 4: // Search films by portion of title
            partialStringSearch(movieNames, userInputString, yearReleased, 
                runTimes, mpaRating); 
            break;
        case 5: // Print full table of data
            printTable(movieNames, yearReleased, runTimes, mpaRating);  
            break;
        case 6: // Search by rating
            searchByRating(userInputString, movieNames, mpaRating);
            break;
        }    
        printMenu(); // Show the menu at the end of each loop!
    }       
    
    return 0;
} // End main()

/*******************************************************************************
    Function: readFile()
    Description: Reads in data file (movies.txt), stores all relevant data
    in arrays
    Parameters: movieNames[][], yearReleased[], runTimes[], mpaRating[][]
    Return: ---
*******************************************************************************/
void readFile(char movieNames[][TITLECHAR], int yearReleased[MOVIES], 
    int runTimes[MOVIES], char mpaRating[MOVIES][RATECHAR]) {
    FILE* infile = fopen("movies.txt", "r");
    char ch;

    for (size_t i = 0; i < MOVIES; ++i) {
        // Grab movie names, add NULL terminator
        fgets(movieNames[i], TITLECHAR, infile);
        movieNames[i][strlen(movieNames[i]) - 1] = '\0';        

         // Grab year released
        fscanf(infile, "%d", &yearReleased[i]);
        
        // Grab run times
        fscanf(infile, "%d", &runTimes[i]);   
        while ((ch = fgetc(infile)) != '\n');

        // Grab movie rating, add NULL terminator
        fgets(mpaRating[i], RATECHAR, infile);
        mpaRating[i][strlen(mpaRating[i])] = '\0';       
        
        if (feof(infile))
            break; 
    }

    fclose(infile);
} // End readFile()

/*******************************************************************************
    Function: printMenu()
    Description: Displays user menu options to console
    Parameters: ---
    Return: ---
*******************************************************************************/
void printMenu(void) {
    printf("\n\n");
    char menuOptions[7][55] = {
        { "Enter 1 to search film list by title"},
        { "Enter 2 to search films by release year"},
        { "Enter 3 to search films by a range of years"},
        { "Enter 4 to search film list by a portion of the title"},
        { "Enter 5 to display the data table"},
        { "Enter 6 to search by film rating (R, PG-13, etc)"},
        { "-1 to exit program"} };

    for (size_t i = 0; i < 7; ++i) {    
        printf("%s\n", menuOptions[i]);
    }
    printf("Enter menu option: ");
} // End printMenu()

/*******************************************************************************
    Function: getMenuKey()
    Description: Uses scanf to grab menu option from user.
    Parameters: Points to menuOption
    Return: No return, but affects menuOption value
*******************************************************************************/
int getMenuKey(int* menuOption) {
    scanf("%d", menuOption);
    while (getchar() != '\n');
    return *menuOption;
} // End getMenuKey()

/*******************************************************************************
    Function: fullStringSearch()
    Description: Requests user to input full film name and then uses strcmp() to 
    compare user input with films in data file. Displays to console if found or
    not.
    Parameters: movieNames[][], userInputString[], yearReleased[], runTimes[],
    mpaRating[][]
    Return: ---
*******************************************************************************/
void fullStringSearch(char movieNames[][TITLECHAR], char userInputString[], 
    int yearReleased[MOVIES], int runTimes[MOVIES], 
    char mpaRating[MOVIES][RATECHAR]) {
    int found = 0;
    int header = 0;
    printf("Enter the full, grammatically correct film title you are searching for: ");
    fgets(userInputString, TITLECHAR, stdin);
    userInputString[strlen(userInputString) - 1] = '\0';
    
    for (size_t i = 0; i < MOVIES; ++i) {
         
        if ((strcmp(movieNames[i], userInputString)) == 0) {               
            if (header == 0) {
                printColumns();
                header++;
            }
            if (header != 0) {
                printFilmDetails(movieNames, yearReleased, runTimes, mpaRating, i);
                found++;
            }
        }
    }

    if (found == 0) {
        printf("Film '%s' not in the list.\n", userInputString);
    }
    else {
        return;
    }
} // End fullStringSearch()

/*******************************************************************************
    Function: partialStringSearch()
    Description: Compares portion of a string to all film titles, displays if 
    any films are found with that partial string.
    Parameters: movieNames[][], userInputString[], yearReleased[], runTimes[],
    mpaRating[][]
    Return: ---
*******************************************************************************/
void partialStringSearch(char movieNames[][TITLECHAR], char userInputString[], 
    int yearReleased[MOVIES], int runTimes[MOVIES], 
    char mpaRating[MOVIES][RATECHAR]){
    char* film = 0;
    int found = 0;
    int header = 0;
    printf("Forgot the film? Enter any part of a title you are searching for: ");
    fgets(userInputString, TITLECHAR, stdin);
    userInputString[strlen(userInputString) - 1] = '\0';
    
    for (size_t i = 0; i < MOVIES; ++i) {
        if ((film = strstr(movieNames[i], userInputString)) != NULL) {            
            if (header == 0) {
                printf("%30s%15s\n", "Movie", "Rating");
                printf("---------------------------------------------\n");
                header++;
            }
            if (header != 0) {
                printf("%30s%15s\n", movieNames[i], mpaRating[i]);
                found++;
            }
        }
    }

    if (found == 0) {
        printf("No instances of '%s' on the list.\n", userInputString);
    }
    else {
        return;
    }
} // End partialStringSearch()

/*******************************************************************************
    Function: searchByYear()
    Description: User searches for specific films by year or range of years
    depending on menu option. Displays relevant information.
    Parameters: movieNames[][], yearReleased[], points to menuOption, runTimes[],
    mpaRating[][]
    Return: ---
*******************************************************************************/
void searchByYear(char movieNames[][TITLECHAR], int yearReleased[MOVIES], 
    int* menuOption, int runTimes[MOVIES], char mpaRating[MOVIES][RATECHAR]) {
    int userInputYear = 0;
    int userInputYearLow = 0;
    int userInputYearHigh = 0;
    int found = 0;
    int header = 0;

    if (*menuOption == 2) { // Simple release year search
        printf("Enter the release year: ");
        userInputYear = grabYear(userInputYear);
               
        for (size_t i = 0; i < MOVIES; ++i) {
            if (userInputYear == yearReleased[i]) {
                if (header == 0) {
                    printColumns();
                    header++;
                }
                if (header != 0) {
                    printFilmDetails(movieNames, yearReleased, runTimes, 
                        mpaRating, i);
                    found++;
                }
            }
        }
        if (found == 0) {
            printf("No films in the data file were released in the year %d", 
                userInputYear);
            return;
        }
    }    

    if (*menuOption == 3) { // Search by range of years
        header = 0;
        found = 0;
        printf("Enter the lower limit to search (enter when done): ");
        userInputYearLow = grabYear(userInputYearLow);
        printf("Enter the upper limit to search (enter when done): ");
        userInputYearHigh = grabYear(userInputYearHigh);        
        for (size_t i = 0; i < MOVIES; ++i) {
            if (userInputYearLow <= yearReleased[i] && 
                userInputYearHigh >= yearReleased[i]) {
                if (header == 0) {
                    printf("%26s %d and %d\n", "Movies between",
                        userInputYearLow, userInputYearHigh);
                    printf("----------------------------------------\n");
                    header++;
                }
                if (header != 0) {
                    printf("%40s\n", movieNames[i]);                    
                    found++;
                }
            }
            
        }
        if (found == 0) {
            printf("No films in the data file were released in the year %d", 
                userInputYear);
            return;
        }
    }
} // End searchByYear()

/*******************************************************************************
    Function: grabYear()
    Description: Clean function to get year from user and clear input stream
    Parameters: year
    Return: year
*******************************************************************************/
int grabYear(int year) {
    scanf("%d", &year);
    while (getchar() != '\n');
    return year;
} // End grabYear()

/*******************************************************************************
    Function: searchByRating()
    Description: Uses strcmp() to compare userInputString to mpaRatings; displays
    films with respective ratings if that rating is found, else displays
    not found.
    Parameters: userInputString[], movieNames[][], mpaRating[][]
    Return: ---
*******************************************************************************/
void searchByRating(char userInputString[], char movieNames[][TITLECHAR], char mpaRating[][RATECHAR]) {
    int header = 0;
    int found = 0;
    printf("Enter the film rating: ");
    fgets(userInputString, TITLECHAR, stdin);
    userInputString[strlen(userInputString) - 1] = '\0';

    for (size_t i = 0; i < MOVIES; ++i) {
        if ((strcmp(mpaRating[i], userInputString)) == 0) {
            if (header == 0) {
                printf("%30s%15s\n", "Movie", "Rating");
                printf("---------------------------------------------\n");
                header++;
            }
            if (header != 0) {
                printf("%30s%15s\n", movieNames[i], mpaRating[i]);
                found++;
            }
        }
    }

    if (found == 0) {
        printf("No films found with the rating '%s'\n", mpaRating);
        return;
    }
} // End searchByRating()

/*******************************************************************************
    Function: printTable()
    Description: Prints entire data file in clean tabular format
    Parameters: movieNames[][], yearReleased[], runTimes[], mpaRating[][]
    Return: ---
*******************************************************************************/
void printTable(char movieNames[][TITLECHAR], int yearReleased[MOVIES], 
    int runTimes[MOVIES], char mpaRating[MOVIES][RATECHAR]) {
    for (int i = 0; i < HEADERWID; ++i) {
        printf("%c", '-');
    }
    puts("");
    printColumns();   

    for (size_t i = 0; i < MOVIES; ++i) {
        printFilmDetails(movieNames, yearReleased, runTimes, mpaRating, i);
    }
} // End printTable()

/*******************************************************************************
    Function: printFilmDetails()
    Description: Quick function to print the simple details of a particular film
    Parameters: movieNames[][], yearReleased[], runTimes[], mpaRating[][], counter
    variable in loop (i)
    Return: ---
*******************************************************************************/
void printFilmDetails(char movieNames[][TITLECHAR], int yearReleased[MOVIES], 
    int runTimes[MOVIES], char mpaRating[MOVIES][RATECHAR], int i) {
    
    printf("%25s%25d%25d%25s\n", movieNames[i], yearReleased[i], runTimes[i], 
        mpaRating[i]);
    
} // End printFilmDetails()

/*******************************************************************************
    Function: printColumns()
    Description: Essentially the 'header' for printing films in clean tabular/ 
    user friendly formatting
    Parameters: ---
    Return: ---
*******************************************************************************/
void printColumns() {
    printf("%25s%25s%25s%25s\n", "Movie Title", "Year Released", "Run Time", 
        "Film Rating");
    for (int i = 0; i < HEADERWID; ++i) {
        printf("%c", '-');
    }
    puts("");
} // End printColumns()

/*******************************************************************************
    Function: printHeader()
    Description: Initial program header-- added for flair
    Parameters: ---
    Return: ---
*******************************************************************************/
void printHeader(void) {    
    for (int i = 0; i < HEADERWID; ++i) {
        printf("%c", '-');
    }
    puts("");
    printf("--------------------------------- FINDING DATA IN A LIST OF FILMS ----------------------------------\n");
    for (int i = 0; i < HEADERWID; ++i) {
        printf("%c", '-');

    }
    puts("");
} // End printHeader()

