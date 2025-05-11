#ifndef TV_H
#define TV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX	256

typedef struct {
	char *model;
	float diagonal;
	int resolution_w;
	int resolution_h;
	char *tech;
	float price;
} Television;

void inputTV(Television *tv);
void saveToFile(const Television *tv, const char *filename);
void loadAndPrintFromFile(Television *tv, const char *filename);

#endif
