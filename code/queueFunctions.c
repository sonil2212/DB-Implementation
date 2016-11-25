/*
 * queueFunctions.c
 *
 *  Created on: 01-Sep-2014
 *      Author: sonil
 */

#include <pdsProject.h>
#include <stdio.h>
#include <stdlib.h>

int moveFreeLocations(unsigned long int freelocation[]);
void readFreeLocations();

unsigned long int findFreeLocations(unsigned long int freelocation[]) {
	unsigned long int key;

	key = freelocation[0];
	if (key == 0) {
		printf(
				"\noops!seems like there is no free locations available in data file.Hence inserting data at last.");
		return 0;

	} else
		return key;
}

int moveFreeLocations(unsigned long int freelocation[]) {
	int i = 0;
	while (i < 100 && freelocation[i] != 0) {
		freelocation[i] = freelocation[i + 1];
		i++;
	}

	if (i == 100) {
		freelocation[i - 1] = 0;
	}

	return EXIT_SUCCESS;
}

void insertFreeLocations(unsigned long int freelocation[],
		unsigned long int key) {

	int i = 0;
	while (freelocation[i] != 0 && i < 100) {
		if (key == freelocation[i]) {
			return;
		}

		i++;
	}

	freelocation[i] = key;

	if (i == 100) {
		printf("\noops!we can only keep 100 free locations.");
	}
}

void readFreeLocations() {

	FILE *fp;
	fp = fopen(parentIndexFileName, "rb");
	if (fp == NULL) {
		printf("\nproblem");
	}

	else {
		fread(parentFreeLocations, sizeof(parentFreeLocations), 1, fp);

		int i = 0;
		printf("\nParent(%s) free keys are: ", parentFile);
		while (i < 100) {
			if (parentFreeLocations[i] != 0)
				printf("%lu ", parentFreeLocations[i]);
			i++;
		}

	}
	fclose(fp);

	fp = fopen(childIndexFileName, "rb");
	if (fp == NULL) {
		printf("\nproblem");
	}

	else {
		fread(childFreeLocations, sizeof(childFreeLocations), 1, fp);

		int i = 0;
		printf("\nChild(%s) free keys are: ", childFile);

		while (i < 100) {
			if (childFreeLocations[i] != 0)
				printf("%lu ", childFreeLocations[i]);
			i++;
		}

	}
	fclose(fp);

}
