#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

// Struct moved to header file

// Define any additional variables here
// Global variables for filename and FITNESS_DATA array
void DisplayMenu(){
    printf("A\n");
    printf("B\n");
    printf("C\n");
    printf("D\n");
    printf("E\n");
    printf("F\n");
    printf("D\n");
    printf("Please Enter Your Choice:\n");
}

int OptionA(){
    char filename[50]; // Adjust the size as needed

    // Get filename from user
    printf("Enter the filename: ");
    if (scanf("%49s", filename) != 1) {
        fprintf(stderr, "Error: Could not open file\n");
        return 1;
    }

    // Check if the filename is correct
    if (strcmp(filename, "FitnessData_2023.csv") != 0) {
        fprintf(stderr, "Error: Could not open file\n");
        return 1;
    }

    // Open the file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file\n");
        return 1;
    }

    // File opened successfully, you can perform further operations here

    // Close the file when done
    fclose(file);

    return 0; // Return 0 to indicate success
}



// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    }
    
    // Free the duplicated string
    free(inputCopy);

                    }




// Complete the main function
int main() {
    // Call the function to open the file
    int result = OptionA();


    return 0; // Return 0 to indicate success
}