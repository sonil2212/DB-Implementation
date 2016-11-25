/*
 * selectGetRelatedObjectMany.c
 *
 *  Created on: 07-Oct-2014
 *      Author: sonil
 */

#include <stdio.h>
#include <stdlib.h>
#include <pdsProject.h>
#include <stdbool.h>

extern struct BSTNode *currentNode;
extern int parentColumnCount, childColumnCount;
extern char str[60], strc[60], *parentColumnName[25], *childColumnName[25];

bool checkDataActiveInIndex(int num);

bool checkDataActiveInIndex(int num) {
	FILE *fp;
	unsigned long int offset = 0;
	struct index i;

	fp = fopen(childIndexFileName, "rb");
	if (fp == NULL) {
		printf("\nOoops!Seemslike there is some problem while opening index file.please try again!");
		return false;
	}

	else {
		offset = offset + 100 * sizeof(unsigned long int)+num * sizeof(struct index);
		fseek(fp,offset,0);
		fread(&i, sizeof(struct index), 1, fp);
		if (i.flag == 'Y'){
			fclose(fp);
			return true;
		}
		else{
			fclose(fp);
			return false;
	}

}
}

int getRelatedObjectMany(char *baseObjectName, char *relatedObjectName,
		unsigned long int key) {

	struct dataObject dObj, obj1; //stores temporary each object in index file
	FILE *fp = NULL;
	int n, i = 0, countLines = 0; //keep tracks the no of records in child data file.
	unsigned long int relatedKey, offset;
	struct dataObject obj[20];
	bool findkey;
	char *parPtr, *childPtr;

	fp = fopen(childDataFileName, "rb");
	if (fp == NULL) {
		printf("\noops!there seems a problem opening child data file %s",
				relatedObjectName);
		exit(EXIT_FAILURE);
	}

	else {
		while (1) {
			n = fread(&dObj, sizeof(struct dataObject), 1, fp);
			if (n == 0) {
				break;
			}
			char *ptr;
			relatedKey = strtoul(dObj.fileld1, &ptr, 10);

			bool fKey = checkDataActiveInIndex(countLines);

			if (relatedKey == key && fKey == true) {
				obj[i] = dObj;
				i++;
			}

			countLines++;
		}
	}
	fclose(fp);

	findkey = searchBST(parentRoot, key);
	if (findkey == false) {
		printf(
				"\noops!the key you want to select does not present in %s.Please try again",
				parentFile);
		return EXIT_SUCCESS;
	}

	offset = currentNode->offset;

	fp = fopen(parentDataFileName, "rb");
	if (fp == NULL) {
		printf(
				"\noops!seems there is problem in opening parent file for select(getRelatedObjectMany).Please check");
	}

	else {

		int k = 0;
		fseek(fp, offset, 0);
		fread(&obj1, sizeof(obj1), 1, fp);

		while (k < parentColumnCount) {
			printf("%s\t\t", parentColumnName[k]);
			k++;
		}

		k = 0;
		while (k < childColumnCount) {
			printf("%s\t\t", childColumnName[k]);
			k++;
		}

		printf(
				"\n--------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

		int j = 0;
		while (j <= i - 1) {
			k = 0;
			printf("\n%lu\t\t", obj1.key);
			parPtr = obj1.fileld1;
			while (k < parentColumnCount - 1) {
				if (strcmp(parPtr, "") == 0)
					printf("NULL\t\t");
				else
					printf("%s\t\t", parPtr);
				parPtr = parPtr + 25 * sizeof(char);
				k++;
			}

			k = 0;

			printf("%lu\t\t", obj[j].key);
			childPtr = obj[j].fileld1;
			while (k < childColumnCount - 1) {
				if (strcmp(childPtr, "") == 0)
					printf("NULL\t\t");
				else
					printf("%s\t\t", childPtr);
				childPtr = childPtr + 25 * sizeof(char);
				k++;
			}

			j++;
		}
	}

	fclose(fp);

	return EXIT_SUCCESS;
}

