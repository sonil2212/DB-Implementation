/*
 * selectGetByKey.c
 *
 *  Created on: 05-Oct-2014
 *      Author: sonil
 */

#include <stdio.h>
#include <stdlib.h>
#include <pdsProject.h>
#include <stdbool.h>
#include <string.h>

unsigned long int offset;
extern struct BSTNode *currentNode;
struct dataObject obj;
struct cumulativeObject cobj;
extern int parentColumnCount, childColumnCount;
extern char str[60], strc[60], *parentColumnName[25], *childColumnName[25];

//function declaration
int getByKey(char* dataObjectName, unsigned long int key);

int getByKey(char* dataObjectName, unsigned long int key) {

	FILE *fp;
	bool findkey; //searches whether key needs to be update present or not

	if (strcmp(dataObjectName, parentFile) == 0) {
		findkey = searchBST(parentRoot, key);
		if (parentRoot == NULL) {
			printf("Oops!Seems like there is no active records in the %s.",
					parentFile);
			return EXIT_SUCCESS;
		}
		if (findkey == false) {
			printf(
					"\nOops!the key you want to select does not present in %s.Please try again.",
					parentFile);
			return EXIT_SUCCESS;
		}


		offset = currentNode->offset;

		fp = fopen(parentDataFileName, "rb");
		if (fp == NULL) {
			printf(
					"\noops!seems there is problem in opening parent file for select(getByKey).Please check.");
		}

		else {

			int i = 0;
			fseek(fp, offset, 0);
			fread(&obj, sizeof(obj), 1, fp);

			while (parentColumnName[i] != NULL) {
				printf("%s\t\t", parentColumnName[i]);
				i++;
			}
			printf(
					"\n-------------------------------------------------------------------------------------------------");
			printf("\n%lu\t\t", obj.key);
			i = 2;
			char *fieldPos = obj.fileld1;
			while (i <= (parentColumnCount)) {
				if (strcmp(fieldPos, "") == 0)
					printf("NULL");
				else
					printf("%s\t\t", fieldPos);
				fieldPos = fieldPos + (sizeof(char) * 25);
				i++;
			}
		}
		fclose(fp);
	}

	//select fuction for child table
	else if (strcmp(dataObjectName, childFile) == 0) {
		if (childRoot == NULL) {
			printf("Oops!Seems like there is no active records in the %s.",
					childFile);
			return EXIT_SUCCESS;
		}
		findkey = searchBST(childRoot, key);
		if (findkey == false) {
			printf(
					"\noops!the key you want to select does not present in %s.Please try again.",
					childFile);
			return EXIT_SUCCESS;
		}

		offset = currentNode->offset;

		fp = fopen(childDataFileName, "rb");
		if (fp == NULL) {
			printf(
					"\noops!seems there is problem in opening parent file for select(getByKey).Please check");
		} else {
			int i = 0;
			fseek(fp, offset, 0);
			fread(&obj, sizeof(obj), 1, fp);

			while (childColumnName[i] != NULL) {
				printf("%s\t\t", childColumnName[i]);
				i++;
			}
			printf(
					"\n-------------------------------------------------------------------------------------------------");
			printf("\n%lu\t\t", obj.key);
			i = 2;
			char *fieldPos1 = obj.fileld1;

			while (i <= (childColumnCount)) {
				if (strcmp(fieldPos1, "") == 0)
					printf("NULL");
				else
					printf("%s\t\t", fieldPos1);
				fieldPos1 = fieldPos1 + (sizeof(char) * 25);
				i++;
			}
		}
		fclose(fp);
	}

	else {
		printf("\noops!Object name specified is wrong.Try Again");
	}
	return EXIT_SUCCESS;
}
