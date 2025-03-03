/*******************************************************************************
* 
                              // Ohm's Law //

    This program takes user input for resistance and voltage then computes the
    current. It uses a mixture of passing by reference and passing by value
    to operate. After a user enters their measurements and the program computes
    the current, it displays each measurement in formatted tabular output.

    Written by: Jon-Austin Tharpe

    Date: 02/16/2025

*******************************************************************************/

#include <stdio.h>

// Function Prototypes //
// Grabs resistance and voltage via user input
void getMeasurements(float* resistance, float* voltage);
// Calculates current from input values
void calcCurrent(float resistance, float voltage, float* current);
// Prints all measurements
void printValues(float resisitance, float voltage, float current);

/*******************************************************************************
    Function: main()
    Description: Takes user input, process, prints output..
    Parameters: ---
    Return: ---
*******************************************************************************/
int main(void) {
    float resistance = 0;
    float voltage = 0;
    float current = 0;

    getMeasurements(&resistance, &voltage);   
    calcCurrent(resistance, voltage, &current);
    printValues(resistance, voltage, current);

    return 0;
}

/*******************************************************************************
    Function: getMeasurements()
    Description: Grabs two measurements from user input
    Parameters: Points to resistance and voltage; passes by reference
    Return: ---
*******************************************************************************/
void getMeasurements(float* resistance, float* voltage) {
    printf("Enter the resistance (in ohms) : ");
    scanf("%f", resistance); 

    printf("Now enter the voltage (in volts): ");
    scanf("%f", voltage);
} // End getMeasurements

/*******************************************************************************
    Function: calcCurrent()
    Description: Calculates the current, in amps, from resistance and voltage
        measurements taken via input
    Parameters: Resistance and voltage by value, current by reference
    Return: ---
*******************************************************************************/
void calcCurrent(float resistance, float voltage, float* current) {
    *current = voltage / resistance; 
} // End calcCurrent

/*******************************************************************************
    Function: printValues()
    Description: Prints results in formatted tabular output
    Parameters: resistance, voltage, and curren values
    Return: ---
*******************************************************************************/
void printValues(float resistance, float voltage, float current) {
    printf("\n%s%20s%20s\n", "Resistance (R)", "Voltage (V)", "Current (I)");
    printf("------------------------------------------------------\n");
    printf("%9.2f ohms%14.2f volts%15.2f amps\n", resistance, voltage, current);
} // End printValues

