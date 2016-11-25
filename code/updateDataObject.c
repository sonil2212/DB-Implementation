/*
 * updateDataObject.c
 *
 *  Created on: 06-Sep-2014
 *      Author: sonil
 */

#include <stdio.h>
#include <stdlib.h>
#include <pdsProject.h>
#include <stdbool.h>
#include <string.h>

struct index indexObject;
int n;
unsigned long int offset;
extern struct BSTNode *currentNode;
struct dataObject obj1;
struct dataObject obj2;

int updateDataObject(char* data_object_name, unsigned long int key);
void updateDataFile(FILE *parFP, char* data_object_name, unsigned long int key,
		char* dataObjectType);

void updateDataFile(FILE *parFP, char* data_object_name, unsigned long int key,
		char* dataObjectType) {
	bool parentKeyFound;
	char *fieldPos;
	int ch;
	unsigned long int rkey;

	if (strcmp(dataObjectType, "parent") == 0) {

		obj1.key = key;
		fieldPos = obj1.fileld1;
		ch = 1;
		while (ch != 0) {
			printf("Please insert the field value:");
			fflush(stdin);
			scanf("%s", fieldPos);
			fieldPos = fieldPos + (sizeof(char) * 25);
			printf(
					"Please enter 0 if you do not want to enter more filed values:");
			scanf(" %d", &ch);
		}

		fwrite(&obj1, sizeof(obj1), 1, parFP);
		printf("\nCongratulations %s object updated successfully",parentFile);
		fclose(parFP);

	}

	if (strcmp(dataObjectType, "child") == 0) {
		obj2.key = key;
		fieldPos = obj2.fileld1;
		printf("\nPlease insert the related key value:");
		fflush(stdin);
		scanf("%s", fieldPos);

		char *ptr;
		rkey = strtoul(fieldPos, &ptr, 10);

		parentKeyFound = checkReferentialIntegrity(rkey);

		if (parentKeyFound == false) {
			printf(
					"\noops!the key you entering is not present in parent table.Hence key is violating RI constrain ");
			return;
		}
		ch = 1;
		fieldPos = obj2.fileld2;

		while (ch != 0) {
			printf("Please insert the field value:");
			fflush(stdin);
			scanf("%s", fieldPos);
			fieldPos = fieldPos + (sizeof(char) * 25);
			printf(
					"Please enter 0 if you do not want to enter more filed values:");
			scanf(" %d", &ch);
		}

		fwrite(&obj2, sizeof(obj2), 1, parFP);
		printf("\nCongratulations %s object updated successfully ",childFile);
		fclose(parFP);
	}
}

int updateDataObject(char* data_object_name, unsigned long int key) {
	FILE *fp;
	bool findkey; //searches whether key needs to be update present or not

	if (strcmp(data_object_name, parentFile) == 0) {
		findkey = searchBST(parentRoot, key);
		if (findkey == false) {
			printf(
					"\noops!the key you want to update does not present in %s.Please try again",
					parentFile);
			return EXIT_SUCCESS;
		}

		offset = currentNode->offset;

		fp = fopen(parentDataFileName, "r+b");
		if (fp == NULL) {
			printf(
					"\noops!seems there is problem in opening parent file in update.Please check");
		}

		else {
			fseek(fp, offset, 0);
			updateDataFile(fp, data_object_name, key, "parent");
		}

	}

	else if (strcmp(data_object_name, childFile) == 0) {
		findkey = searchBST(childRoot, key);
		if (findkey == false) {
			printf(
					"\noops!the key you want to update does not present in %s.Please try again",
					childFile);
			return EXIT_SUCCESS;
		}

		offset = currentNode->offset;

		fp = fopen(childDataFileName, "r+b");
		if (fp == NULL) {
			printf(
					"\noops!seems there is problem in opening child file in update.Please check");
		}

		else {
			fseek(fp, offset, 0);
			updateDataFile(fp, data_object_name, key, "child");
		}

	}

	return EXIT_SUCCESS;
}

