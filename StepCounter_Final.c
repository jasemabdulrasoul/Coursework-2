#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

// Struct moved to header file

// Define any additional variables here
// Global variables for filename and FITNESS_DATA array
void DisplayMenu(){
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
    char filename[50]; // Adjust the size as needed

    // Get filename from user
    printf("Enter the filename: ");
    if (scanf("%49s", filename) != 1) {
        fprintf(stderr, "Error: Could not find or open file.\n");
        return 1;
    }

    // Check if the filename is correct
    if (strcmp(filename, "FitnessData_2023.csv") != 0) {
        fprintf(stderr, "Error: Could not find or open file.\n");
        return 1;
    }

    // Open the file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not find or open file.\n");
        return 1;
    }

    // File opened successfully, you can perform further operations here

    // Close the file when done
    fclose(file);

    return 0; // Return 0 to indicate success
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
    printf ("Number of records in file: %d\n", records);
}

void OptionC(){
    FILE *file = fopen("FitnessData_2023.csv", "r"); //opening file
    if (file == NULL) { //check if its empty
        perror(""); //print error
        exit(1);
    }
    int records = 0; //variable for number of records
    char line[100]; //variable for lines
    FITNESS_DATA instance[100]; //array to use later
    int StepsList[100];

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
            StepsList[records] = atoi(token);
        }
        records++;
    }
    
    int fewest = StepsList[0];
    int indexFew = 0;
    for(int i = 1; i < records; i++){
        if (StepsList[i] < fewest) {
            fewest = StepsList[i];
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

    DisplayMenu();
    scanf("%c", &choice);

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
        //case 'f':
        //case 'F':
            //OptionF();
            //break;
        case 'q':
        case 'Q':
            break;
        default:
            printf("Invalid choice. Try again.\n");
    }


    return 0; // Return 0 to indicate success
}