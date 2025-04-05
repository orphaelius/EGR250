/******************************************************************************

							// String Manipulation //

	This program manipulates strings in a variety of ways, showcasing some of 
	C's built-in string functionality. Essentially, it takes user input as a
	string, displays the string to the console, reverses that string (not by
	simply iterating through the string starting at the end, but rather by 
	copying each element in reverse order to a new string, and then moves the
	first word of the original string to the end.

	Afterwards, it requests additional user input as a string, then it 
	birfucates the first and second word of the manipulated string by placing 
	this new string in the middle. It displays the new length of this string.

	The program then requests a single character via console input, replacing
	the first 5 characters of the string with this character.

	Finally, the program requests user input to locate a string within the 
	string. It returns the string beginning with the user input if it does
	exist, or displays a "not found" message if that string is not contained
	within the original string.

	Written by: Jon-Austin

	Date: 04/01/2025

******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Defined limitation on input
#define MAXCHAR 100 

// FUNCTION PROTOTYPES //
void userInputString(char userString[MAXCHAR]);
void copyString(char userString[], char copiedString[]); 
void assignNullTerm(char string[]);
void determineWordandCharCount(char string[], int* whiteSpace, int* charsToCopy);
void reverseString(char userString[], char reversedString[]);
void moveWord(char userString[], int* whiteSpace, int* charsToCopy);
void placeInMiddle(char userString[], char middleString[], char newString[], 
	int* whiteSpace, int* charsToCopy);
int stringLength(char anyString[]);
int getCharacterFromUser(int* inputChar); 
void searchHaystack(char stringNeedle[], char string[]);
void replaceWithCharacters(char string[], int* inputChar);

void printString(char anyString[]);

/*******************************************************************************
	Function: main()
	Description: See program description above; main function for iterating 
	through exercise parameters
	Parameters: ---
	Return: ---
*******************************************************************************/
int main(void) {
	char userString[MAXCHAR]; // Input string 
	char copiedUserString[MAXCHAR]; // Copied version of original input string
	char reversedString[MAXCHAR]; // Reversed input string
	char newString[MAXCHAR]; // New string for middleString operations
	char middleString[MAXCHAR]; // String to place between first and second words
	char stringNeedle[MAXCHAR];
	int whiteSpace = 0; // Used to determine if a string has whitespace or if a single word
	int charsToCopy = 0; // Used to determine how many chars of a string to copy
	int inputChar = 0; // To grab single character input from user

	// First block grabs user input, assigns null terminator, and prints string
	printf("Enter a string to be displayed, press 'enter' when done: "); 
	userInputString(userString);
	printf("Original string: ");
	assignNullTerm(userString);
	printString(userString);

	// Second block copies the user input string to perform manipulations-- saves
	// original string for later manipulation
	copyString(userString, copiedUserString); // Copies user string to manipulate
	assignNullTerm(copiedUserString);
	printf("Copied string: ");
	printString(copiedUserString);

	// Third block reverses string and stores in reversedString
	reverseString(copiedUserString, reversedString);
	printf("String in reverse: ");
	printString(reversedString);
	
	// Fourth block moves fist word to end of a string
	moveWord(userString, &whiteSpace, &charsToCopy);
	printf("First word moved to the end: ");
	printString(userString);

	// Fifth block calls middleString to place a string between first and second 
	// words of the original string
	printf("%s %s", "\nEnter a string to place between the first", 
		"and second word of the original string, press enter when done : ");
	userInputString(middleString);
	placeInMiddle(copiedUserString, middleString, newString, &whiteSpace, &charsToCopy);
	// Prints a different array depending on if there is a single word or multiple
	if (whiteSpace == 0) {
		printf("New string: %s\n\n", copiedUserString);
		printf("Length of current string is: %d\n", stringLength(copiedUserString));
	}
	else {
		printf("New string: %s\n\n", newString);
		printf("Length of current string is: %d\n", stringLength(newString));
	}
	
	// Sixth block grabs single character from user and replaces the first 5
	// characters of the current string wth that character
	printf("Enter any single character to replace the first five elements with: ");
	getCharacterFromUser(&inputChar);	
	replaceWithCharacters(newString, &inputChar);
	while ((inputChar = getchar()) != '\n' && inputChar != EOF); // Clears stream
	printf("final string: ");
	printString(newString);

	// Seventh block requests a string needle from the user then searches for that
	// within the string
	printf("Enter a string needle: ");
	userInputString(stringNeedle);
	searchHaystack(stringNeedle, newString);

	return 0;
} // End main()

/*******************************************************************************
	Function: userInputString()
	Description: Grabs user input to store in string array using fgets(). Clears
	input stream. I attempted to use fflush() but could not get it functioning
	the same way.
	Parameters: A character string
	Return: ---
*******************************************************************************/
void userInputString(char string[MAXCHAR]) {
	fgets(string, MAXCHAR, stdin);
	size_t length = strlen(string);
	if (length > 0 && string[length - 1] == '\n') {
		string[length] = '\0';
	}
} // End userInputString()

/*******************************************************************************
	Function: copyString()
	Description: Copies original user input string to manipulate
	Parameters: Two character strings (one to copy, empty string to store
	Return: ---
*******************************************************************************/
void copyString(char userString[], char copiedString[]) {
	strcpy(copiedString, userString);
} // End copyUserString

/*******************************************************************************
	Function: assignNullTerm()
	Description: Assigns null terminator to end of a string
	Parameters: Character string
	Return: ---
*******************************************************************************/
void assignNullTerm(char string[]) {
	int strLen = strlen(string);
	string[strLen] = '\0';	
} // End assignNullTerm()

/*******************************************************************************
	Function: reversedString()
	Description: Reverses a string and stores reversed string in a new array 
	Parameters: Two character arrays: one to read, a second to store the 
	reversed version
	Return: ---
*******************************************************************************/
void reverseString(char userString[], char reversedString[]) {
	// Defines a string length to be used as a condition 
	// and assign a NULL terminator 
	int inputStrLen = strlen(userString);
	userString[inputStrLen] = '\0';
	reversedString[inputStrLen] = '\0';	
	// Loop that assigns the last element of input string to
	// the first element of the reversed string
	for (size_t i = 0; i < inputStrLen; ++i) {
		reversedString[i] = userString[inputStrLen - 1 - i];		
	}	
} // End reverseString()

/*******************************************************************************
	Function: moveWord()
	Description: Moves first word to end of a string IF the string is more than
	one word
	Parameters: Character array, points to whiteSpace and charsToCopy
	Return: ---
*******************************************************************************/
void moveWord(char userString[], int* whiteSpace, int* charsToCopy) {
	char newString[MAXCHAR];

	// Determines if string is only a single word
	// Determines how many chars to copy
	determineWordandCharCount(userString, whiteSpace, charsToCopy); 
	
	// If string is a single word, print message and exit function
	if (*whiteSpace == 0) {
		printf("String is only one word!\n");
		return;		
	}	
	userString[strlen(userString) - 1] = '\0';
	// Copies first word of userString to newString using charToCopy as 
	// the total amount of copied chars
	strncpy(newString, userString, *charsToCopy);
	newString[*charsToCopy] = '\0'; // Null terminate

	// Writes over the first *charsToCopy + 1 elements 
	strcpy(userString, userString + *charsToCopy + 1);

	// Adds a space between current iteration of userString string and new string
	// for proper formatting of string
	strcat(userString, " ");

	// Concatenates newString to end of userString
	strcat(userString, newString); 
} // End moveWord()

/*******************************************************************************
	Function: placeInMiddle()
	Description: Places a new string between the first and second words of an
	array, or places at the end of a string if the original string contains only
	one word
	Parameters: Two character arrays, points to whiteSpace and charsToCopy
	Return: ---
*******************************************************************************/
void placeInMiddle(char string[], char middleString[], char newString[], 
	int* whiteSpace, int* charsToCopy) {
	
	int stringLen = 0; 
	determineWordandCharCount(middleString, whiteSpace, charsToCopy);

	// If there is only one word in middleString, add it to the end
	// of the input string and return to main()
	if (*whiteSpace == 0) {		
		stringLen = strlen(string);		
		string[stringLen - 1] = '\0';
		strcat(string, " ");
		strcat(string, middleString);	
		stringLen = strlen(string);
		string[stringLen - 1] = '\0';
		printf("middle string is only one word.\n");
		return; // Exit placeInMiddle()
	}

	determineWordandCharCount(string, whiteSpace, charsToCopy);
	// Copies n chars from input string to new string (first word)
	strncpy(newString, string, *charsToCopy + 1); 
	newString[*charsToCopy + 1] = '\0';		
	// Concatenates middleString to end of newString
	strcat(newString, middleString); 
	stringLen = strlen(newString);
	newString[stringLen - 1] = '\0';	
	// Writes over the first charsToCopy + 1 elements (pushes rest of string forward)
	strcpy(string, string + *charsToCopy + 1);	
	string[strlen(string)] = '\0';	
	strcat(newString, " "); 
	// Concatenates modified string to end of newString
	strcat(newString, string);	
	
} // End placeInMiddle()

/*******************************************************************************
	Function: determineWordandCharCount()
	Description: Determines if a string is only one word and counts characters
	in first word to determine where a NULL terminator is applied
	Parameters: Character array, points to whiteSpace and charsToCopy
	Return: ---
*******************************************************************************/
void determineWordandCharCount(char string[], int* whiteSpace, int* charsToCopy) {
	*whiteSpace = 0; // Assumes one word by default
	*charsToCopy = 0; // Reset char count
	for (size_t i = 0; string[i] != '\0'; ++i) {
		if (string[i] == ' ') {
			*whiteSpace = 1;
			*charsToCopy = i;
			break;
		}
	}
} // End determineWordandCharCount()

/*******************************************************************************
	Function: stringLength()
	Description: Determines the length of a string
	Parameters: Any string
	Return: ---
*******************************************************************************/
int stringLength(char anyString[]) {
	int stringLen = strlen(anyString);
	return stringLen;
} // End stringLength()

/*******************************************************************************
	Function: getCharacterFromUser()
	Description: Grabs a character via user input
	Parameters: Points to inputChar
	Return: No return, but affects the value of inputChar
*******************************************************************************/
int getCharacterFromUser(int* inputChar) {
	*inputChar = getchar();
	return *inputChar; 
} // End getCharacterFromUser()

/*******************************************************************************
	Function: replaceWitCharacters()
	Description: Replaces the first 5 spaces of a string with *inputChar
	Parameters: Any char string, points to inputChar
	Return: ---
*******************************************************************************/
void replaceWithCharacters(char string[], int* inputChar) {		
	int isString = 0; // Assumes string is one word by default
	int stringLen = 0;
	stringLen = stringLength(string);
	
	
	for (size_t i = 0; string[i] != '\0'; ++i) {
		if (string[i] == ' ') {
			isString = 1; // More than one word in string
			break;
		}
	}		
	if (isString) {		
		memset(string, *inputChar, 5);
		stringLen = stringLength(string);
		string[stringLen] = '\0';
		return;
	}		
	else {		
		int stringLen = stringLength(string);		
		int replaceCount = (stringLen >= 5) ? 5 : stringLen;
		memset(string, *inputChar, replaceCount);
		string[replaceCount] = '\0';
	} 	
} // End replaceWithCharacter()

/*******************************************************************************
	Function: searchHaystack()
	Description: Searches a string ("haystack") for any occurrence of the user
	input string ("needle") and prints if found or not.
	Parameters: Any character array, stringNeedle (via user input)
	Return: ---
*******************************************************************************/
void searchHaystack(char stringNeedle[], char string[]) {	
		
	// Strip any lingering newline characters etc from input steam
	size_t length = strlen(stringNeedle);
	if (length > 0 && stringNeedle[length - 1] == '\n') {
		stringNeedle[length - 1] = '\0';
	}

	// Used to compare input string to haystack string
	char* chToFind = strstr(string, stringNeedle);

	// If occurrence is found!
	if (chToFind != NULL) {
		printf("%s located within the string %s!\n", stringNeedle, chToFind);
	}
	else {
		printf("No occurrence of %s was found.\n", stringNeedle);
	}	
} // End searchHaystack()

/*******************************************************************************
	Function: printString()
	Description: Prints any character string
	Parameters: Any character string
	Return: ---
*******************************************************************************/
void printString(char anyString[]) {
	printf("%s\n", anyString);
} // End printString()