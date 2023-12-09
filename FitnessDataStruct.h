#ifndef FITNESS_DATA_STRUCT_H
#define FITNESS_DATA_STRUCT_H

#include <stdio.h>

// Define an appropriate struct
typedef struct {
	char date[11];
	char time[6];
	int steps;
} FITNESS_DATA;

// Helper function prototypes
void tokeniseRecord(const char *input, const char *delimiter, char *date, char *time, char *steps);

void DisplayMenu();

int OptionA();

void OptionB();

void OptionC();

void OptionD();

void OptionE();

void OptionF();
#endif // FITNESS_DATA_STRUCT_H