#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

// Struct moved to header file

// Define any additional variables here
// Global variables for filename and FITNESS_DATA array
void DisplayMenu(){
    printf("Menu Options: \n");
    printf("A: Specify the filename to be imported\n");
    printf("B: Display the total number of records in the file\n");
    printf("C: Find the date and time of the timeslot with the fewest steps\n");
    printf("D: Find the date and time of the timeslot with the largest number steps\n");
    printf("E: Find the mean step count of all the records in the file\n");
    printf("F: Find the longest continuous period where the step count is above 500 steps\n");
    printf("Q: Quit\n");
    printf("Please enter your choice: \n");
}

int OptionA(){
    char filename[50]; // variable for storing the input of the user

    // Get filename from user
    printf("Input filename: ");
    if (scanf("%49s", filename) != 1) { //if the filename exceeds the size limit print error
        fprintf(stderr, "Error: Could not find or open file.\n");
        return 1;
    }

    // Check if the filename is correct
    if (strcmp(filename, "FitnessData_2023.csv") != 0) { // if filename does not match print error
        fprintf(stderr, "Incorrectly named data file\n");
        return 1;
    }

    // Open the file
    FILE *file = fopen(filename, "r"); // open file except if it is empty
    if (file == NULL) {
        fprintf(stderr, "Error: Could not find or open file.\n");
        return 1;
    }

    // Close the file when done
    fclose(file);

    return 0;
}

void OptionB(){
    // This code is from my previous coursework
    FILE *file = fopen("FitnessData_2023.csv", "r"); //opening file
    if (file == NULL) { //check if its empty
        perror(""); //print error
        exit(1);
    }
    int records = 0; //variable for number of records
    char line[100]; //variable for lines
    FITNESS_DATA instance[100]; //array to use later

    while( fgets(line, 100, file) !=NULL ) //while loop to go over each line
    {
        
        char *token;
        char *delim = ",";

        token = strtok(line, delim); //seperate date time and steps
        if (token != NULL){
            strncpy(instance[records].date, token, sizeof(instance[records].date)); //store date in the instance array
            instance[records].date[sizeof(instance[records].date) - 1] = '\0'; //make sure it is a standard C string by setting last character as null terminator
        }

        token = strtok(NULL, delim); //same as above but for time
        if (token != NULL){
            strncpy(instance[records].time, token, sizeof(instance[records].time));
            instance[records].time[sizeof(instance[records].time) - 1] = '\0';
        }

        token = strtok(NULL, delim);
        if (token != NULL){
            instance[records].steps = atoi(token); //change from string to integer
        }
        records++; //add 1 to number of records each loop
    }
    printf ("Total records: %d\n", records);
}

void OptionC(){
    // This code is from my previous coursework
    FILE *file = fopen("FitnessData_2023.csv", "r"); //opening file
    if (file == NULL) { //check if its empty
        perror(""); //print error
        exit(1);
    }
    int records = 0; //variable for number of records
    char line[100]; //variable for lines
    FITNESS_DATA instance[100]; //array to use later
    int StepList[100];

    while( fgets(line, 100, file) !=NULL ) //while loop to go over each line
    {
        
        char *token;
        char *delim = ",";

        token = strtok(line, delim); //seperate date time and steps
        if (token != NULL){
            strncpy(instance[records].date, token, sizeof(instance[records].date)); //store date in the instance array
            instance[records].date[sizeof(instance[records].date) - 1] = '\0'; //make sure it is a standard C string by setting last character as null terminator
        }

        token = strtok(NULL, delim); //same as above but for time
        if (token != NULL){
            strncpy(instance[records].time, token, sizeof(instance[records].time));
            instance[records].time[sizeof(instance[records].time) - 1] = '\0';
        }

        token = strtok(NULL, delim);
        if (token != NULL){
            instance[records].steps = atoi(token); //change from string to integer
            StepList[records] = atoi(token);
        }
        records++;
    }
    
    // This is the New addition for option c
    int fewest = StepList[0];
    int indexFew = 0;
    for(int i = 1; i < records; i++){
        if (StepList[i] < fewest) {
            fewest = StepList[i];
            indexFew = i;
        }
    }
    printf("Fewest steps: %s %s\n", instance[indexFew].date, instance[indexFew].time);
}

void OptionD(){
    FILE *file = fopen("FitnessData_2023.csv", "r"); //opening file
    if (file == NULL) { //check if its empty
        perror(""); //print error
        exit(1);
    }
    int record = 0; //variable for number of records
    char line[100]; //variable for lines
    FITNESS_DATA instances[100]; //array to use later
    int StepList[100];

    while( fgets(line, 100, file) !=NULL ) //while loop to go over each line
    {
        
        char *token;
        char *delim = ",";

        token = strtok(line, delim); //seperate date time and steps
        if (token != NULL){
            strncpy(instances[record].date, token, sizeof(instances[record].date)); //store date in the instance array
            instances[record].date[sizeof(instances[record].date) - 1] = '\0'; //make sure it is a standard C string by setting last character as null terminator
        }

        token = strtok(NULL, delim); //same as above but for time
        if (token != NULL){
            strncpy(instances[record].time, token, sizeof(instances[record].time));
            instances[record].time[sizeof(instances[record].time) - 1] = '\0';
        }

        token = strtok(NULL, delim);
        if (token != NULL){
            instances[record].steps = atoi(token); //change from string to integer
            StepList[record] = atoi(token);
        }
        record++;
    }
    
    int largest = StepList[0];
    int indexLarge = 0;
    for(int j = 1; j < record; j++){
        if (StepList[j] > largest) {
            largest = StepList[j];
            indexLarge = j;
        }
    }
    printf("Largest steps: %s %s\n", instances[indexLarge].date, instances[indexLarge].time);
}

void OptionE(){
    FILE *file = fopen("FitnessData_2023.csv", "r"); //opening file
    if (file == NULL) { //check if its empty
        perror(""); //print error
        exit(1);
    }
    int record = 0; //variable for number of records
    char line[100]; //variable for lines
    FITNESS_DATA instances[100]; //array to use later
    int StepList[100];

    while( fgets(line, 100, file) !=NULL ) //while loop to go over each line
    {
        
        char *token;
        char *delim = ",";

        token = strtok(line, delim); //seperate date time and steps
        if (token != NULL){
            strncpy(instances[record].date, token, sizeof(instances[record].date)); //store date in the instance array
            instances[record].date[sizeof(instances[record].date) - 1] = '\0'; //make sure it is a standard C string by setting last character as null terminator
        }

        token = strtok(NULL, delim); //same as above but for time
        if (token != NULL){
            strncpy(instances[record].time, token, sizeof(instances[record].time));
            instances[record].time[sizeof(instances[record].time) - 1] = '\0';
        }

        token = strtok(NULL, delim);
        if (token != NULL){
            instances[record].steps = atoi(token); //change from string to integer
            StepList[record] = atoi(token);
        }
        record++;
    }
    int sum = 0;
    for(int i = 0; i < record; i++){
        sum = sum + StepList[i];
    }
    printf("Mean step count: %d\n", sum / record);
}

void OptionF() {
    FILE *file = fopen("FitnessData_2023.csv", "r"); //opening file
    if (file == NULL) { //check if its empty
        perror(""); //print error
        exit(1);
    }
    int record = 0; //variable for number of records
    char line[100]; //variable for lines
    FITNESS_DATA instances[100]; //array to use later
    int StepList[100];

    while( fgets(line, 100, file) !=NULL ) //while loop to go over each line
    {
        
        char *token;
        char *delim = ",";

        token = strtok(line, delim); //seperate date time and steps
        if (token != NULL){
            strncpy(instances[record].date, token, sizeof(instances[record].date)); //store date in the instance array
            instances[record].date[sizeof(instances[record].date) - 1] = '\0'; //make sure it is a standard C string by setting last character as null terminator
        }

        token = strtok(NULL, delim); //same as above but for time
        if (token != NULL){
            strncpy(instances[record].time, token, sizeof(instances[record].time));
            instances[record].time[sizeof(instances[record].time) - 1] = '\0';
        }

        token = strtok(NULL, delim);
        if (token != NULL){
            instances[record].steps = atoi(token); //change from string to integer
            StepList[record] = atoi(token);
        }
        record++;
    }

    int threshold = 500;
    int CurrentStreak = 0;
    int LongestStreak = 0;
    int StartIndex = 0;
    int LSSI = 0; // Longest streak start index
    int LSEI = 0; // Longest streak end index

    for (int i = 0; i < record; i++) {
        if (StepList[i] > threshold) {
            if (CurrentStreak == 0) {
                StartIndex = i; // Start of a new streak
            }
            CurrentStreak++;
        } else {
            if (CurrentStreak > LongestStreak) {
                LongestStreak = CurrentStreak;
                LSSI = StartIndex;
                LSEI = i - 1;
            }
            CurrentStreak = 0; // Reset the streak counter
        }
    }

    // Check for the longest streak at the end of the array
    if (CurrentStreak > LongestStreak) {
        LongestStreak = CurrentStreak;
        LSSI = StartIndex;
        LSEI = record - 1;
    }

    if (LongestStreak > 0) {
        printf("Longest period start: %s %s\n", instances[LSSI].date, instances[LSSI].time);
        printf("Longest period end: %s %s\n", instances[LSEI].date, instances[LSEI].time);
    }

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
    
    int result;
    char choice;

    do{
        DisplayMenu();
        scanf(" %c", &choice);

        switch (choice){
            case 'a':
            case 'A':
                result = OptionA();
                if (result == 0){
                printf("File successfully loaded.\n");
                }
                break;
            case 'b':
            case 'B':
                OptionB();
                break;
            case 'c':
            case 'C':
                OptionC();
                break;
            case 'd':
            case 'D':
                OptionD();
                break;
            case 'e':
            case 'E':
                OptionE();
                break;
            case 'f':
            case 'F':
                OptionF();
                break;
            case 'q':
            case 'Q':
                break;
            default:
                printf("Invalid Choice. Try again.\n");
        }
    } while(choice != 'Q' && choice != 'q');
    


    return 0; // Return 0 to indicate success
}