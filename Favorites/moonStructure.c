/*******************************************************************************

					        // Moon Structure //

	The parameters of this programming assignment are to create any structure
	with a minimum of 4 members, define two structure variables, take in data
	via console (as user input), then display the structure data and compare the
	structure data between the two variables. 

	I have created a moon structure with six attributes that are used to
	*loosely* determine whether or not the data gathered for a particular moon 
	might be hospitable for human habitability. The program takes input, compares 
	two	moons, and display all relevant data in clean tabular console output. 

	Written by: Jon-Austin Tharpe

	Date: 04/18/2025

*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define MEMBERS 6 // Total questions for user input
#define INPUTCHARS 100 // Max char limit for user input
// Used as habitability scoring comparison value
#define HABIT_SCORE 5 

// Moon structure!
typedef struct {
	float gravity;	
	float orbitalPeriod;
	float surfaceTemperature;
	char hasAtmosphere[INPUTCHARS];
	char liquidWater[INPUTCHARS];
	char moonName[INPUTCHARS];
} Moon;

// Function Prototypes
void printHeaderLines(void); 
void printMoonAndStars(void);  
void displayProgramHeader(void);
void displayNumberQuestions(size_t i);
void displayStringQuestions(size_t i);
void inputMoonData(Moon* myMoonPtr); 
void displayStruct(Moon myMoon, Moon mySecondMoon); 
void compareStructValues(Moon myMoon, Moon mySecondMoon, int* isHabitableFirst, 
	int* isHabitableSecond);
void determineHospitabilityScore(Moon myMoon, Moon mySecondMoon, 
	int* isHabitableFirst, int* isHabitableSecond);
void displayMostHospitableMoon(Moon myMoon, Moon mySecondMoon, 
	int* isHabitableFirst, int* isHabitableSecond);
void clearInputBuffer(void);

/*******************************************************************************
	Function: main()
	Description: Displays header, calls functions, etc
	Parameters: ---
	Return: ---
*******************************************************************************/
int main(void) {
	Moon myMoon;	
	Moon mySecondMoon;
	// Variables used to score habitability-- passed by reference
	int isHabitableFirst = 0;
	int isHabitableSecond = 0;

	// Display program header and details
	displayProgramHeader();

	// Gets data for first moon
	printf("Taking input for the first moon!\n");
	printHeaderLines();
	inputMoonData(&myMoon);
	puts("");

	// Gets data for second moon
	printf("Taking input for the second moon!\n");
	printHeaderLines(); 
	inputMoonData(&mySecondMoon);

	// Displays data for both moons
	displayStruct(myMoon, mySecondMoon);

	// Compares all members of Moon variables (primitive, strings) then displays
	// if and which moon(s) are potentially hospitable for human habitability
	compareStructValues(myMoon, mySecondMoon, &isHabitableFirst, 
		&isHabitableSecond);
	determineHospitabilityScore(myMoon, mySecondMoon, &isHabitableFirst, 
		&isHabitableSecond);
	displayMostHospitableMoon(myMoon, mySecondMoon, &isHabitableFirst, 
		&isHabitableSecond); 

	return 0;
} // End main()

/*******************************************************************************
	Function: inputMoonData()
	Description: Uses scanf() and fgets() to take user input, passing those
	values and strings into a moon's structure variable
	Parameters: Points to a moon structure
	Return: No return, but does affect the member values of a moon
*******************************************************************************/
void inputMoonData(Moon* myMoonPtr) {
	for (size_t i = 0; i < MEMBERS / 2; ++i) {
		displayNumberQuestions(i); // Displays series of user questions
		switch (i) {
		case 0:
			scanf("%f", &myMoonPtr->gravity);
			clearInputBuffer();
			break;
		case 1:
			scanf("%f", &myMoonPtr->orbitalPeriod);
			clearInputBuffer();
			break;
		case 2:
			scanf("%f", &myMoonPtr->surfaceTemperature);
			clearInputBuffer();
			break;
		}
	}
	// Seperated scanf() and fgets() for my sanity!
	for (size_t i = 0; i < MEMBERS / 2; ++i) {
		displayStringQuestions(i); // Displays series of user questions
		switch (i) {
		case 0:
			fgets(myMoonPtr->hasAtmosphere, INPUTCHARS, stdin);
			myMoonPtr->hasAtmosphere[strcspn(myMoonPtr->hasAtmosphere, "\n")] = '\0';			
			break;
		case 1:
			fgets(myMoonPtr->liquidWater, INPUTCHARS, stdin);
			myMoonPtr->liquidWater[strcspn(myMoonPtr->liquidWater, "\n")] = '\0';
			break;
		case 2:
			fgets(myMoonPtr->moonName, INPUTCHARS, stdin);
			myMoonPtr->moonName[strcspn(myMoonPtr->moonName, "\n")] = '\0';
			break;
		}
	}
} // End inputMoonData()

/*******************************************************************************
	Function: displayValueQuestions()
	Description: Displays questions to take number values
	Parameters: Takes in current iteration of i in inputMoonData() for loop
	Return: ---
*******************************************************************************/
void displayNumberQuestions(size_t i) {
	char const questions[MEMBERS / 2][INPUTCHARS] = {
		{"Enter a numerical value for the gravity of this moon (in m/s^2): "},
		{"Enter a numerical value for the orbital period (in months): "},
		{"Enter the average surface temperature (in Celsius): "},
	};	
	printf("%s", questions[i]);
} // End displayValueQuestions()

/*******************************************************************************
	Function: displayStringQuestions()
	Description: Displays questions to take string values
	Parameters: Takes in current iteration of i in inputMoonData() for loop
	Return: ---
*******************************************************************************/
void displayStringQuestions(size_t i) {
	char const questions[MEMBERS / 2][INPUTCHARS] = {		
		{"Does this moon have an atmosphere (yes or no)? "},
		{"Does this moon contain liquid water on or below the surface (yes or no)? "},
		{"Enter the moon name: "},
	};
	printf("%s", questions[i]);	
} // End displayStringQuestions()

/*******************************************************************************
	Function: displayProgramHeader()
	Description: Displays program header at initialization
	Parameters: ---
	Return: ---
*******************************************************************************/
void displayProgramHeader() {
	printHeaderLines();
	printf("%s %s %s",
		"---------------------------------------------------------------",
		"COMPARING MOON DATA",
		"------------------------------------------------------------\n");	
	printHeaderLines();
	printMoonAndStars(); // Calls function to display "moon" and "stars"
	printHeaderLines();	
	printf("Initializing program...\n\n");		
} // End displayProgramHeader()

/*******************************************************************************
	Function: displayStruct()
	Description: Displays all data related to both structure variables in 
	formatted tabular output
	Parameters: Takes in two Moon structure variables
	Return: ---
*******************************************************************************/
void displayStruct(Moon myMoon, Moon mySecondMoon) {
	printHeaderLines();
	printf("%65s Data for %s\n", " ", myMoon.moonName);
	printHeaderLines();

	// Displays first moon dataset
	printf("%s%29s%40s%16s%11s%24s",
		"Gravity Strength (m/s^2)",
		"Orbital Period (months)",
		"Average Surface Temperature (in C)",
		"Atmosphere",
		"Water",
		"Name of Moon");
	puts("");
	printHeaderLines();
	printf("%24.2f%29.2f%40.2f%16s%11s%24s", myMoon.gravity, 
		myMoon.orbitalPeriod, myMoon.surfaceTemperature,
		myMoon.hasAtmosphere, myMoon.liquidWater, myMoon.moonName);
	printf("\n\n");

	// Displays second moon dataset
	printHeaderLines();
	printf("%65s Data for %s\n", " ", mySecondMoon.moonName);
	printHeaderLines();
	printf("%s%29s%40s%16s%11s%24s",
		"Gravity Strength (m/s^2)",
		"Orbital Period (months)",
		"Average Surface Temperature (in C)",
		"Atmosphere",
		"Water",
		"Name of Moon");
	puts("");
	printHeaderLines();
	printf("%24.2f%29.2f%40.2f%16s%11s%24s", mySecondMoon.gravity, 
		mySecondMoon.orbitalPeriod, mySecondMoon.surfaceTemperature,
		mySecondMoon.hasAtmosphere, mySecondMoon.liquidWater, mySecondMoon.moonName);
	puts("");
	puts(""); // Just additional padding for user experience improvement
} // End displayStruct()

/*******************************************************************************
	Function: compareStructValues()
	Description: Runs intial comparison checks between two structure variables 
	and modifies isHabitable values if either moon's data rests in specific 
	ranges
	Parameters: Two moon structure variables, points to both isHabitable variables
	Return: ---
*******************************************************************************/
void compareStructValues(Moon myMoon, Moon mySecondMoon, int* isHabitableFirst, 
	int* isHabitableSecond) {
	printf("Comparing the two moons...\n");

	// Compare gravity between each moon
	if (myMoon.gravity == mySecondMoon.gravity) {
		printf("These moons have the same gravity!\n");
	}
	else if (myMoon.gravity > mySecondMoon.gravity) {
		printf("%s has stronger gravity.\n", myMoon.moonName);
	}
	else {
		printf("%s has stronger gravity.\n", mySecondMoon.moonName);
	}

	// Compare orbital period beteen each moon
	if (myMoon.orbitalPeriod == mySecondMoon.orbitalPeriod) {
		printf("These moons have the same orbital period!\n");
	}
	else if (myMoon.orbitalPeriod > mySecondMoon.orbitalPeriod) {
		printf("%s has a longer orbital period.\n", myMoon.moonName);
	}
	else {
		printf("%s has the longer orbital period.\n", mySecondMoon.moonName);
	}

	// Compare temperatures between both moons
	if (myMoon.surfaceTemperature == mySecondMoon.surfaceTemperature) {
		printf("These moons have the same surface temperature!\n");
	}
	else if (myMoon.surfaceTemperature > mySecondMoon.surfaceTemperature) {
		printf("%s has a warmer surface temperature.\n", myMoon.moonName);
	}
	else {
		printf("%s has a warmer surface temperature.\n", mySecondMoon.moonName);
	}

	// Compare atmosphere between moons
	char confirmed[4] = { "yes" };

	if (strcmp(confirmed, myMoon.hasAtmosphere) == 0 && 
		strcmp(confirmed, mySecondMoon.hasAtmosphere) == 0) {
		printf("Both moons have atmospheres!\n");
		(*isHabitableFirst)++;
		(*isHabitableSecond)++;
	}
	else if (strcmp(confirmed, myMoon.hasAtmosphere) == 0) {
		printf("Only %s has an atmosphere.\n", myMoon.moonName); 
		(*isHabitableFirst)++;		
	}
	else if (strcmp(confirmed, mySecondMoon.hasAtmosphere) == 0) {
		printf("Only %s has an atmosphere.\n", mySecondMoon.moonName);
		(*isHabitableSecond)++; 
	}
	else {
		printf("Neither moon has an atmosphere.\n");		
	}

	// Compare water between moons
	if (strcmp(confirmed, myMoon.liquidWater) == 0 && 
		strcmp(confirmed, mySecondMoon.liquidWater) == 0) {
		printf("Both moons contain liquid water!\n");
		(*isHabitableFirst)++;
		(*isHabitableSecond)++;
	}
	else if (strcmp(confirmed, myMoon.liquidWater) == 0) {
		printf("Only %s contains liquid water\n", myMoon.moonName);
		(*isHabitableFirst)++;
	}
	else if (strcmp(confirmed, mySecondMoon.liquidWater) == 0) {
		printf("Only %s has an atmosphere.\n", mySecondMoon.moonName);
		(*isHabitableSecond)++;
	}
	else {
		printf("Neither %s or %s has liquid water.\n", 
			myMoon.moonName, mySecondMoon.moonName);
	}
	puts("");
} // End compareStructValues()

/*******************************************************************************
	Function: determineHospitabilityScore()
	Description: Runs each moon through a set of checks to determine if their
	data values reside in determined hospitability ranges, updates each 
	isHospitable variable if they meet certain criteria
	Parameters: Two moon structure variables, points to both isHabitable
	Return: ---
*******************************************************************************/
void determineHospitabilityScore(Moon myMoon, Moon mySecondMoon, 
	int* isHabitableFirst, int* isHabitableSecond) {
	printf("%s %s\n",
		"Those are just some inital comparisons. Running full dataset",
		"to determine which moon is most habitable based on potential habitability ranges...");
	
	// Variables that define range of hospitable gravity-- 80% to 150% of
	// Earth's gravity
	int lowerBoundsGravity = 7.848;
	int higherBoundsGravity = 14.715;

	if (myMoon.gravity >= lowerBoundsGravity && 
		myMoon.gravity <= higherBoundsGravity) {
		(*isHabitableFirst)++;
	}

	if (mySecondMoon.gravity >= lowerBoundsGravity && 
		mySecondMoon.gravity <= higherBoundsGravity) {
		(*isHabitableSecond)++;
	}

	// Variables that define limitations on orbital periodicity. Loosely based on our 
	// observations of other orbital satellites 
	int lowerBoundOrbit = 1;
	int upperBoundOrbit = 45;

	if (myMoon.orbitalPeriod >= lowerBoundOrbit && 
		myMoon.orbitalPeriod <= upperBoundOrbit) {
		(*isHabitableFirst)++;
	}

	if (mySecondMoon.orbitalPeriod >= lowerBoundOrbit && 
		mySecondMoon.orbitalPeriod <= upperBoundOrbit) {
		(*isHabitableSecond)++;
	}

	// Variables to define limitations on hospitable temperature ranges. While it is 
	// proposed that life could exist anywhere between the freezing and boiling point 
	// of water, and even though this program is elementary conjecture, I decided to 
	// define a slightly more realistic limitation given that we are to determine 
	// *human* hospitability
	int lowerBoundsTemp = 0;
	int upperBoundsTemp = 50;
	if (myMoon.surfaceTemperature >= lowerBoundsTemp && 
		myMoon.surfaceTemperature <= upperBoundsTemp) {
		(*isHabitableFirst)++;
	}

	if (mySecondMoon.surfaceTemperature >= lowerBoundsTemp && 
		mySecondMoon.surfaceTemperature <= upperBoundsTemp) {
		(*isHabitableSecond)++;
	}
} // End determineHospitabilityScore()

/*******************************************************************************
	Function: displayMostHospitableMoon()
	Description: Compares the isHabitable score for each moon structure variable
	and then prints whether both/either moon is potentially hospitable for human
	habitation
	Parameters: Two Moon structure variables, points to both isHabitable 
	variables
	Return: ---
*******************************************************************************/
void displayMostHospitableMoon(Moon myMoon, Moon mySecondMoon, 
	int* isHabitableFirst, int* isHabitableSecond) {
	
	if ((*isHabitableFirst) == (*isHabitableSecond)) {
		printf("Both %s and %s are equally hospitable!\n",
			myMoon.moonName, mySecondMoon.moonName);
	}
	else if (*isHabitableFirst > *isHabitableSecond) {
		printf("%s is more hospitable than %s!\n", 
			myMoon.moonName, mySecondMoon.moonName);
	}
	else {
		printf("%s is more hospitable than %s!\n", 
			mySecondMoon.moonName, myMoon.moonName); 
	}

	printf("Hospitability rating:\n"); 
	printf("%s habitability score: %d\n", 
		myMoon.moonName, *isHabitableFirst);
	printf("%s habitability score: %d\n", 
		mySecondMoon.moonName, *isHabitableSecond);
	printf("But... is either moon objectively feasible to sustain human life? Let's check!\n\n");
	printf("Scanning...\n");

	if (*isHabitableFirst < HABIT_SCORE && *isHabitableSecond < HABIT_SCORE) {
		printf("Even though the data is intriguing, neither moon offers sufficient evidence for human habitation.\n");
		printf("%s and %s yearn for eternal solitude in the cruel embrace of the cosmos...\n", 
			myMoon.moonName, mySecondMoon.moonName);
	}
	else if (*isHabitableFirst == HABIT_SCORE && *isHabitableSecond == HABIT_SCORE) {
		printf("Wow! Both of these moons offer promising potential signs for sustaining human habitation.\n");
		printf("%s and %s, here we come!\n", myMoon.moonName, mySecondMoon.moonName);
	}
	else if (*isHabitableFirst == HABIT_SCORE) {
		printf("%s is potentially habitable!! All aboard to sail the stars towards %s!", 
			myMoon.moonName, myMoon.moonName);
	}
	else {
		printf("%s is potentially habitable!! All aboard to sail the stars towards %s!", 
			mySecondMoon.moonName, mySecondMoon.moonName);
	}
	puts("");
} // End displayMostHospitableMoon()

/*******************************************************************************
	Function: printHeaderLines()
	Description: Displays lines for clean formatting of data
	Parameters: ---
	Return: ---
*******************************************************************************/
void printHeaderLines() {
	for (size_t i = 0; i < 144; ++i) {
		printf("%c", '-');
	}
	puts("");
} // End printHeaderLines()

/*******************************************************************************
	Function: printMoonAndStars()
	Description: Just adds some creative UI as "moon" and "stars" in console. 
	Found algorithm online to display a circle and then modified to display
	only a semicircle.
	Parameters: ---
	Return: ---
*******************************************************************************/
void printMoonAndStars() {
	char moonCharacter = 'x'; // Variable for displaying moon characters
	int radius = 13;
	// These are used to reshape the circular shape on the console. Without them,
	// the "moon" tends to print more elliptical than anything
	float xScale = 1.5; // Stretches the x values to flatten out the height 
	float yScale = 0.6; // Compresses the y values to reduce verticality

	// Displays a few random "stars" to console
	printf("%20s%c\n", " ", 'x');
	printf("%80s%c\n", " ", 'X');
	printf("%70s%c\n\n", " ", 'x');
	printf("%10s%c\n", " ", 'X');
	printf("%110s%c\n", " ", 'X');

	// Outer loop acts as the y-coord. 
	// Starts at defined radius,iterates until decrementing to 0
	for (int i = radius; i >= 0; i--) { 
		printf("%85s", " "); // Pushes moon away from left edge

		for (int j = -radius * xScale; j <= radius * xScale; j++) {
			// j is the x coord scaled by the xScale value.
			// The range is -radius to radius in order to cover the 
			// entire diameter of the moon
			float x = j / xScale;
			float y = i / yScale;
			// Calculate dstance from origin (x and y centered)
			float distance = sqrt(x * x + y * y);
			// If that distance is less than or equal to radius, display the x
			if (distance <= radius) {
				printf("%c", moonCharacter);
			}
			else {
				printf("%s", " ");
			}
		}
		printf("\n"); 
	}
} // End printMoonAndStars()

/*******************************************************************************
	Function: clearInputBuffer()
	Description: Clean function to clear buffer 
	Parameters: ---
	Return: ---
*******************************************************************************/
void clearInputBuffer() {
	char trash;
	while ((trash = getchar()) != '\n');
} // End clearInputBuffer()
