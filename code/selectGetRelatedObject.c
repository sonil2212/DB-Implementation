/*
 * selectGetRelatedObject.c
 *
 *  Created on: 06-Oct-2014
 *      Author: sonil
 */

#include <stdio.h>
#include <stdlib.h>
#include <pdsProject.h>
#include <stdbool.h>
#include <string.h>

unsigned long int offset;
extern struct BSTNode *currentNode;
struct dataObject obj, pobj;
struct cumulativeObject cobj;
extern int parentColumnCount, childColumnCount;
extern char str[60], strc[60], *parentColumnName[25], *childColumnName[25];
char *cobjPtr, *objPtr;

//function declaration

int getRelatedObject(char *baseObjectName, char *relatedObjectName,
		unsigned long int key);

//function definition
int getRelatedObject(char *baseObjectName, char *relatedObjectName,
		unsigned long int key) {
	FILE *fp;
	bool findkey; //searches whether key present or not
	unsigned long int relatedkey;
	char *ptr;

	findkey = searchBST(childRoot, key);
	if (findkey == false) {
		printf(
				"\noops!the key you want to select does not present in %s.Please try again",
				childFile);
		return EXIT_SUCCESS;
	}

	offset = currentNode->offset;
	if (currentNode->flag == 'N') {
		printf(
				"\noops!the key you want to select already deleted from %s.Please try again",
				childFile);
		return EXIT_SUCCESS;
	}

	fp = fopen(childDataFileName, "rb");

	if (fp == NULL) {
		printf(
				"\noops!seems there is problem in opening parent file for select(getRelatedObject).Please check");
	} else {
		int i = 0;
		fseek(fp, offset, 0);
		fread(&obj, sizeof(obj), 1, fp);
		objPtr = obj.fileld1;
		cobjPtr = cobj.field2;

		char buffer[25];
		sprintf(buffer, "%lu", obj.key); //conversion of key from int to string
		strcpy(cobj.field1, buffer);

		while (i < childColumnCount - 1) {
			strcpy(cobjPtr, objPtr);
			cobjPtr = cobjPtr + 25 * sizeof(char);
			objPtr = objPtr + 25 * sizeof(char);
			i++;
		}
		fclose(fp);

		relatedkey = strtoul(cobj.field2, &ptr, 10);
		findkey = searchBST(parentRoot, relatedkey);

		offset = currentNode->offset;

		fp = fopen(parentDataFileName, "rb");

		if (fp == NULL) {
			printf(
					"\noops!seems there is problem in opening parent file for select(getRelatedObject).Please check");
		} else {
			i = 0;
			fseek(fp, offset, 0);
			fread(&pobj, sizeof(pobj), 1, fp);
			strcpy(cobjPtr, obj.fileld1);
			cobjPtr = cobjPtr + 25 * sizeof(char);
			objPtr = pobj.fileld1;

			while (i < parentColumnCount - 1) {
				strcpy(cobjPtr, objPtr);
				cobjPtr = cobjPtr + 25 * sizeof(char);
				objPtr = objPtr + 25 * sizeof(char);
				i++;
			}
		}
		fclose(fp);

		i = 0;
		while (i < childColumnCount) {
			printf("%s\t\t", childColumnName[i]);
			i++;
		}

		i = 0;
		while (i < parentColumnCount) {
			printf("%s\t\t", parentColumnName[i]);
			i++;
		}

		printf(
				"\n---------------------------------------------------------------------------------------------------------------------------------------------\n");
		//printf("\n%s\t", cobj.field1);
		i = 0;
		char *fieldPos = cobj.field1;
		while (i < (childColumnCount + parentColumnCount)) {
			if (strcmp(fieldPos, "") == 0)
				printf("NULL\t\t");
			else
				printf("%s\t\t", fieldPos);
			fieldPos = fieldPos + (sizeof(char) * 25);
			i++;
		}

	}

	return EXIT_SUCCESS;
}

