#ifndef PHONE_H
#define PHONE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX	256

typedef struct {
	char *model;
	int internal_memory;
	int ram;
	int year;
	char *color;
	float price;
} Phone;

void inputPhone(Phone *phone);
void saveToFile(const Phone *phone, const char *filename);
void loadAndPrintFromFile(Phone *phone, const char *filename);

#endif
