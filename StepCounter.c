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
    int StepList[100]; // new array to use later

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
            StepList[records] = atoi(token); //this is the new array to store the steps
        }
        records++;
    }
    
    // This is the New addition for option c
    int fewest = StepList[0]; //set the fewest as the first number in the array
    int indexFew = 0; //variable for the index
    for(int i = 1; i < records; i++){ //check all items in list and compare
        if (StepList[i] < fewest) {
            fewest = StepList[i]; //update the fewest variable if there is a new smallest number
            indexFew = i; // update the index of the smallest number
        }
    }
    printf("Fewest steps: %s %s\n", instance[indexFew].date, instance[indexFew].time);
}

void OptionD(){
    //this is the code from my previous coursework
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
    
    // this is the new addition which is somehwat similar to option C
    int largest = StepList[0];
    int indexLarge = 0;
    for(int j = 1; j < record; j++){
        if (StepList[j] > largest) { // main difference is the comparing sign; here it is greater thatn instead of less than
            largest = StepList[j];
            indexLarge = j; //variable names also changed
        }
    }
    printf("Largest steps: %s %s\n", instances[indexLarge].date, instances[indexLarge].time); 
}

void OptionE(){
    //this is the code from my previous corsework
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
    
    // this is the new addition
    int sum = 0; // variable for sum
    for(int i = 0; i < record; i++){
        sum = sum + StepList[i]; // go over every number and add it to get the sum
    }
    printf("Mean step count: %d\n", sum / record); // print the mean which is the sum divided by the number of items (record)
}

void OptionF() {
    // this is the code from my previous coursework
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

    //this is the new addition
    int threshold = 500; //variable for the threshold
    int CurrentStreak = 0; //variable to count the current streak
    int LongestStreak = 0; //variable to count the longest streak reached yet
    int StartIndex = 0; // variable for the starting point
    int LSSI = 0; // Longest streak start index
    int LSEI = 0; // Longest streak end index

    for (int i = 0; i < record; i++) { // go over all numbers and check if the number is above 500 or not
        if (StepList[i] > threshold) { // if it is above the treshold add 1 to the current streak
            if (CurrentStreak == 0) { //if the current streak is zero start a new streak
                StartIndex = i; // Start of a new streak
            }
            CurrentStreak++;
        } else { //if the it reaches a number that is less than the threshold, update the longest streak if possible
            if (CurrentStreak > LongestStreak) {
                LongestStreak = CurrentStreak;
                LSSI = StartIndex; //get the indecies of the starting and ending points
                LSEI = i - 1;
            }
            CurrentStreak = 0; // Reset the streak counter
        }
    }

    // Check for the longest streak at the end of the array
    if (CurrentStreak > LongestStreak) {
        LongestStreak = CurrentStreak; //update the longest streak if possible
        LSSI = StartIndex; //get the indecies of the starting and ending points
        LSEI = record - 1;
    }

    printf("Longest period start: %s %s\n", instances[LSSI].date, instances[LSSI].time);
    printf("Longest period end: %s %s\n", instances[LSEI].date, instances[LSEI].time);

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
    
    int result; //variable to use in optionA
    char choice; // variable to store user input

    do{ // using do to keep looping while a certain condition is not occuring
        DisplayMenu(); // displays the options and asks user for input
        scanf(" %c", &choice);

        switch (choice){ // switch to make an action depending on the input
            case 'a':
            case 'A':
                result = OptionA(); // stores the whatever optionA returns in result
                if (result == 0){ // if there is no error, print successfull message
                printf("File successfully loaded.\n");
                }
                break;
            case 'b': // for each option , use both uppercase and lowercase to prevent errors
            case 'B': // for each option, call the function that coresponds to the choice
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
                break; //this option just quits meaning that it does not need a function
            default:
                printf("Invalid Choice. Try again.\n"); // print this if the choice is not in the options provided
        }
    } while(choice != 'Q' && choice != 'q'); // this is the while condition that creates a loop as long as the user does not choose to quit
    


    return 0;
}