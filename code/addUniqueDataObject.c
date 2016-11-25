/*
 ============================================================================
 Name        : PDS_Project.c
 Author      : Sonil
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pdsProject.h>

//defining variables

struct dataObject obj;
struct index i1, i2;

//function declarations
void addUniqueDataObject(char *dataObjectName, char* dataObjectType);
void makeEntryIndex(char* indexFileName, unsigned long int ParKey,
		unsigned long int ParOffset, char ParFlag);
bool checkKeyUniqueness(unsigned long int Parkey, char *dataObjectType);
bool checkReferentialIntegrity(unsigned long int Parkey);
int makeFreeLocationEntry(char *dataObjectType);

//function definitions

bool checkKeyUniqueness(unsigned long int Parkey, char *dataObjectType) {
	bool searchSuccesfull;
	if (strcmp(dataObjectType, "parent") == 0) {
		if (parentRoot == NULL) {
			printf("\nCongratulation!First entry is made successfully.");
		} else {
			searchSuccesfull = searchBST(parentRoot, Parkey);
		}
	}

	else if (strcmp(dataObjectType, "child") == 0) {
		if (childRoot == NULL) {
			printf("\nCongratulation!First entry is made successfully.");
		} else {
			searchSuccesfull = searchBST(childRoot, Parkey);
		}
	}

	else
		printf("\ndataObjectType can only be parent/child");
	return searchSuccesfull;

}

bool checkReferentialIntegrity(unsigned long int Parkey) {
	bool keyFound;
	keyFound = searchBST(parentRoot, Parkey);
	return keyFound;
}

void makeEntryIndex(char* indexFileName, unsigned long int ParKey,
		unsigned long int ParOffset, char ParFlag) {

	i1.key = ParKey;
	i1.offset = ParOffset;
	i1.flag = ParFlag;

	FILE *findex;
	findex = fopen(indexFileName, "a+b");

	if (findex == NULL)
		printf("oops!facing problems while opening the index file");
	else {
		//printf("\nCongratulations index file is opened");
		fwrite(&i1, sizeof(i1), 1, findex);

	}
	fclose(findex);

}

int makeFreeLocationEntry(char *dataObjectType) {
	FILE *fp;
	if (strcmp(dataObjectType, "child") == 0) {
		fp = fopen(childIndexFileName, "r+b");
		if (fp == NULL) {
			printf("\nProblem");
		}

		else {
			fwrite(childFreeLocations, sizeof(childFreeLocations), 1, fp);
		}

		fclose(fp);
	} else if (strcmp(dataObjectType, "parent") == 0) {
		fp = fopen(parentIndexFileName, "r+b");
		if (fp == NULL) {
			printf("\nProblem");
		}

		else {
			fwrite(parentFreeLocations, sizeof(parentFreeLocations), 1, fp);
		}

		fclose(fp);
	} else {
		printf("\nObject type can only be %s or %s", parentFile, childFile);
	}

	return EXIT_SUCCESS;
}

void addUniqueDataObject(char *dataObjectName, char* dataObjectType) {
	FILE *fptr;
	int ch = 1;
	char *fieldPos;
	unsigned long int fptrPos, relatedKey, freelocation;
	bool violateKeyUnique = false;
	bool parentKeyFound = false;

	if (strcmp(dataObjectType, "child") == 0) {
		freelocation = findFreeLocations(childFreeLocations);

		if (freelocation == 0) {
			printf("\nPlease insert the key value:");
			scanf("%lu", &obj.key);
			if (obj.key == 0) {
				printf("oops!you are giving null to primary key.Try again");
				return;
			}
		}

		else {
			obj.key = freelocation;
			printf("\nKey assigned to the object is %lu", obj.key);
		}

		violateKeyUnique = checkKeyUniqueness(obj.key, dataObjectType);

		if (violateKeyUnique) {
			printf(
					"\noops!the key you entering is not unique.Hence key is violating uniqueness constrain ");
			return;
		}

		//include logic for checking refrential integrity and non unique PK

		fieldPos = obj.fileld1;
		printf("\nPlease insert the related key value:");
		fflush(stdin);
		scanf("%s", fieldPos);

		char *ptr;
		relatedKey = strtoul(fieldPos, &ptr, 10);

		parentKeyFound = checkReferentialIntegrity(relatedKey);

		if (parentKeyFound == false) {
			printf(
					"Oops!the key you entering is not present in parent table.Hence key is violating RI constrain. ");
			return;
		}

		fieldPos = obj.fileld2;

		while (ch != 0) {
			printf("\nPlease insert the field value:");
			fflush(stdin);
			scanf("%s", fieldPos);
			fieldPos = fieldPos + (sizeof(char) * 25);
			printf(
					"Please enter 0 if you do not want to enter more filed values:");
			scanf(" %d", &ch);
		}

		fptr = fopen(childDataFileName, "a+b");
		if (fptr == NULL)
			printf("oops!facing problems while opening the data file");
		else {
			fseek(fptr, 0, 2);
			fptrPos = ftell(fptr);
			makeEntryIndex(childIndexFileName, obj.key, fptrPos, 'Y');
			fwrite(&obj, sizeof(obj), 1, fptr);
			moveFreeLocations(childFreeLocations);
			makeFreeLocationEntry(dataObjectType);
			printf("\nCongratulations child object inserted successfully");
			fclose(fptr);
		}
	}

	else if (strcmp(dataObjectType, "parent") == 0) {
		freelocation = findFreeLocations(parentFreeLocations);
		if (freelocation == 0) {
			printf("\nPlease insert the key value:");
			scanf("%lu", &obj.key);

			if (obj.key == 0) {
				printf("oops!you are giving null to primary key.Try again");
				return;
			}
		}

		else {
			obj.key = freelocation;
			printf("\nKey assigned to the object is %lu", obj.key);
		}

		violateKeyUnique = checkKeyUniqueness(obj.key, dataObjectType);

		if (violateKeyUnique) {
			printf(
					"\noops!the key you entering is not unique.Hence key is violating uniqueness constrain ");
			return;
		}

		fieldPos = obj.fileld1;
		ch = 1;
		while (ch != 0) {
			printf("\nPlease insert the field value:");
			fflush(stdin);
			scanf("%s", fieldPos);
			fieldPos = fieldPos + (sizeof(char) * 25);
			printf(
					"Please enter 0 if you do not want to enter more filed values:");
			scanf(" %d", &ch);
		}

		fptr = fopen(parentDataFileName, "a+b");
		if (fptr == NULL)
			printf("oops!facing problems while opening the data file");
		else {

			fseek(fptr, 0, 2);
			fptrPos = ftell(fptr);
			makeEntryIndex(parentIndexFileName, obj.key, fptrPos, 'Y');
			fwrite(&obj, sizeof(obj), 1, fptr);
			moveFreeLocations(parentFreeLocations);
			makeFreeLocationEntry(dataObjectType);

			printf(
					"\nCongratulations parent object data inserted successfully");
			fclose(fptr);
		}
	}

	else {
		printf("oops!dataFile can only be of parent/child.Please try again");
		return;
	}
}
