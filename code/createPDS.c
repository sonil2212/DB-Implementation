/*
 * createPDS.c
 *
 *  Created on: 04-Oct-2014
 *      Author: sonil
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pdsProject.h>

unsigned long int parentFreeLocations[100], childFreeLocations[100];
int parentColumnCount = 0, childColumnCount = 0;
char *parentColumnName[25], *childColumnName[25], str[60], strc[60];
char parentIndexFileName[100]; //stores parent file name
char childIndexFileName[100];
char parentDataFileName[100]; //stores parent file name
char childDataFileName[100]; //stores child file name

int loaddataDictionary(char *base_object_name, char *related_object_name);

int loaddataDictionary(char *base_object_name, char *related_object_name) {
	FILE *fp;
	char s[] = ",", *token;
	int i = 0;

	strcpy(parentIndexFileName, "");
	strcat(parentIndexFileName, "/home/sonil/Documents/DBMS/PDS/index/");
	strcat(parentIndexFileName, base_object_name);
	strcat(parentIndexFileName, ".ndx");

	strcpy(childIndexFileName, "");
	strcat(childIndexFileName, "/home/sonil/Documents/DBMS/PDS/index/");
	strcat(childIndexFileName, related_object_name);
	strcat(childIndexFileName, ".ndx");

	strcpy(parentDataFileName, "");
	strcat(parentDataFileName, "/home/sonil/Documents/DBMS/PDS/data/");
	strcat(parentDataFileName, base_object_name);
	strcat(parentDataFileName, ".dat");

	strcpy(childDataFileName, "");
	strcat(childDataFileName, "/home/sonil/Documents/DBMS/PDS/data/");
	strcat(childDataFileName, related_object_name);
	strcat(childDataFileName, ".dat");

	//for checking whether index files exits or not.
	if (access(parentIndexFileName, F_OK) == -1) {
		fp = fopen(parentIndexFileName, "a+b");

		if (fp == NULL) {
			printf(
					"\noops!there seems to be some problem while opening the parent index file",
					parentFile);
		}

		else {
			fwrite(parentFreeLocations, sizeof(parentFreeLocations), 1, fp);
			printf("\nfree locations written successfully");
		}
		fclose(fp);
	}

	if (access(childIndexFileName, F_OK) == -1) {
		fp = fopen(childIndexFileName, "a+b");

		if (fp == NULL) {
			printf(
					"\noops!there seems to be some problem while opening the %s index file",
					childFile);
		}

		else {
			fwrite(childFreeLocations, sizeof(childFreeLocations), 1, fp);
			printf("\nfree locations written successfully");
		}

		fclose(fp);
	}

//for loading the column names
	fp = fopen("/home/sonil/Documents/DBMS/PDS/dataDict.txt", "rb");
	if (fp == NULL) {
		printf(
				"\noops!there seems to be some problem while opening the data dictionary file");
	}

	else {
		fgets(str, 60, fp);
		strtok(str, "\n");
		parentColumnName[i] = strtok(str, s);
		token = parentColumnName[i];

		i = 1;
		while (token != NULL) {
			parentColumnName[i] = strtok(NULL, s);
			token = parentColumnName[i];
			parentColumnCount++;
			i++;
		}

		i = 0;
		fgets(strc, 60, fp);
		strtok(strc, "\n");
		childColumnName[i] = strtok(strc, s);
		token = childColumnName[i];

		i = 1;
		while (token != NULL) {
			childColumnName[i] = strtok(NULL, s);
			token = childColumnName[i];
			childColumnCount++;
			i++;
		}

		printf("\nData Dictionary loaded successfully.");
	}

	fclose(fp);
	readFreeLocations();


	return EXIT_SUCCESS;

}

