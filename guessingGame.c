/*******************************************************************************

                              // Guessing Game //

    This program randomly generates a number between 0 and 10 inclusive, then
    allows a 'player' to guess that number. If a player guesses the number in 3
    attempts or less, the player wins the game, or else...

    Written by: Jon-Austin Tharpe

    Date: 03/03/2025

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MESSAGES 5 // Total messages in message array
#define MAXCHARS 60 // Max chars/string
#define MAXGUESS 3 // Max guesses allowed for player to win

// Function Prototypes //
// Displays initial game message
void displayInitialMessage(const char array[MESSAGES][MAXCHARS]);
int generateNumber(int randomNum); // Generates random number 
int getPlayerGuess(int playerGuess); // Gets player's guess
// Checks player's guess against randomly generated number,
// Increments guess count, returns an integer based on these checks
int getRoundStatus(int* roundStatus, int playerGuess, int* randomNum, 
    int* totalGuesses); 

/*******************************************************************************
    Function: main()
    Description: Calls functions, gets user input, sustains a loop until input
    matches a second value
    Parameters: ---
    Return: ---
*******************************************************************************/
int main(void) {
    int randomNum = 0; // Variable to store random number
    int playerGuess = 0; // Variable to store player's guess
    int totalGuesses = 0; // Counter to tally total guesses
    int roundStatus = 0; // Round status-- used to determine return values    
    // Array that stores game messages
    const char messages[MESSAGES][MAXCHARS] =
    { "Wrong! Guess again: ",    
    "Correct! Player wins!!",    
    "Correct, but you still dropped the ball...", 
    "I am thinking of a number between 0 and 10... got it!",
    "If you guess the number within 3 tries, you win the game."};   
    
    randomNum = generateNumber(randomNum); // Generates random number
    displayInitialMessage(messages); // Initial message for user prompt

    // Main game loop! 
    while (roundStatus != 1) {       
        playerGuess = getPlayerGuess(playerGuess);
        // Checks roundStatus within loop until player guesses correctly
        roundStatus = getRoundStatus(&roundStatus, playerGuess, &randomNum, 
            &totalGuesses); 
        // Uses return value of roundStatus as an index to print certain 
        // messages
        printf("%s", messages[roundStatus]); 

        if (roundStatus == 2) {
            printf("it took you %d attempts.\n", totalGuesses);
            break; // Ends loop if player finally guessed correctly 
            // regardless of winning
        }
    }
    return 0;
} // End main()

/*******************************************************************************
    Function: displayInitialMessage()
    Description: Displays the beginning message and prompt when game 
    initializes
    Parameters: array (messages)
    Return: ---
*******************************************************************************/
void displayInitialMessage(const char array[MESSAGES][MAXCHARS]) {
    printf("%s\n%s\n", array[3], array[4]);
    printf("Enter guess: ");   
} // End displayInitialMessage()

/*******************************************************************************
    Function: generateNumber()
    Description: uses srand() and rand() to generate a random value between
    0 and 10 inclusive
    Parameters: randomNum
    Return: randomNum
*******************************************************************************/
int generateNumber(int randomNum) {
    srand(time(NULL));
    randomNum = rand() % 10;
    return randomNum;
} // End generateNumber()

/*******************************************************************************
    Function: getPlayerGuess()
    Description: Uses scanf to take user input/playerGuess
    Parameters: playerGuess
    Return: playerGuess
*******************************************************************************/
int getPlayerGuess(int playerGuess) {
    scanf("%d", &playerGuess);
    return playerGuess;
} // End getPlayerGuess()

/*******************************************************************************
    Function: getRoundStatus()
    Description: Uses if... else statement to determine whether player guessed
    randomNum correctly. Tracks totalGuesses, return value determines if player
    wins and which messages from the messages array are printed in main()
    Parameters: Points to roundStatus, randomNum, and totalGuesses; 
    int playerGuess
    Return: the 'status' of the game
*******************************************************************************/
int getRoundStatus(int* roundStatus, int playerGuess, int* randomNum, 
    int* totalGuesses) {

    if (playerGuess == *randomNum && *totalGuesses < MAXGUESS) {        
        return 1; // Player won the game
    }
    else if (playerGuess == *randomNum) {        
        return 2; // Player guessed correctly but took too many attempts
    }
    else {        
        (*totalGuesses)++; // Increment the totalGuesses value by 1
        return 0; // Player did not guess correctly
    }    
} // End getRoundStatus()
