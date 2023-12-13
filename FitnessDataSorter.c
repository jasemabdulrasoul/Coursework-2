#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the struct for the fitness data
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FitnessData;

// Function to tokenize a record
void tokeniseRecord(char *record, char delimiter, char *date, char *time, int *steps) {
    char *ptr = strtok(record, &delimiter);
    if (ptr != NULL) {
        strcpy(date, ptr);
        ptr = strtok(NULL, &delimiter);
        if (ptr != NULL) {
            strcpy(time, ptr);
            ptr = strtok(NULL, &delimiter);
            if (ptr != NULL) {
                *steps = atoi(ptr);
            }
        }
    }
}


int main() {
    
    char filename[100]; //variable to store input
    char newFilename[105]; //variable to change from .csv to .tsv
    FitnessData instance[1000]; //array of data
    int records = 0; //number of lines

    printf("Enter Filename: \n"); //get input from the user
    scanf("%s", filename);
    
    FILE *file = fopen(filename, "r"); //open file except if it is empty
     if (file == NULL) {
        fprintf(stderr, "Error: invalid file.\n");
        return 1;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) { //tokenise and check for the validity of the data
        tokeniseRecord(line, ',', instance[records].date, instance[records].time, &instance[records].steps);
        int lengthOfDate = strlen(instance[records].date);
        int lengthOfTime = strlen(instance[records].time);
        if(lengthOfDate != 10 || lengthOfTime !=5) { // checking validity by using the length of the date and time
            printf("Error: invalid file\n");
            fclose(file);
            return 1;
        }
        records++;
    }
    fclose(file);
    
    for (int i = 0; i < records - 1; i++) { //sorting the data in descending order
        for (int j = 0; j < records - i - 1; j++) {
            if (instance[j].steps < instance[j + 1].steps) { //checking all steps and  comparing them with each other
                FitnessData temp = instance[j]; //if the first line that is being checked has less steps than the one after it, switch their places
                instance[j] = instance[j + 1]; // store the first one in temp and swap the data.
                instance[j + 1] = temp; //swap the second one with the data that was stored in temp
            }
        }
    }

    strcpy(newFilename, filename);
    strcat(newFilename, ".tsv"); // copy filename and add .tsv at the end
    file = fopen(newFilename, "w"); //open the new file in write mode which creates a new file if it is not already available
    if (file == NULL) {
        printf("Error: Could not create output file\n");
        return 1;
    }
    
    for (int i = 0; i < records; i++) { //print the new sorted data with tabs in between the values
        fprintf(file, "%s\t%s\t%d\n", instance[i].date, instance[i].time, instance[i].steps);
    }
    fclose(file);
    
    printf("Data sorted and written to FitnessData_2023.csv.tsv");
    
    return 0;
}