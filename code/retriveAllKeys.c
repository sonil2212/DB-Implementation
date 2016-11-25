/*
 * retriveAllKeys.c
 *
 *  Created on: 12-Oct-2014
 *      Author: sonil
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pdsProject.h>

struct BSTNode * retrieveAllActiveKeys(char *indexFileName);

struct BSTNode * retrieveAllActiveKeys(char *indexFileName) {
	loadDataStore(parentFile, childFile);
	if (strcmp(indexFileName, parentIndexFileName) == 0) {
		return parentRoot;
	} else if (strcmp(indexFileName, childIndexFileName) == 0) {
		return childRoot;
	} else {
		printf("Oops!Given index file seems wrong.Please try again.");
		return 0;
	}
}

int showKeys() {
	char objectName[50];
	struct BSTNode *tempNode;

	printf(
			"\nPlease enter Object name for which you want to see the active keys: ");
	scanf("%s", objectName);
	if (strcmp(objectName, parentFile) == 0) {
		tempNode = retrieveAllActiveKeys(parentIndexFileName);
		printf("Active keys are : \n");
		inorderTraversalBST(parentRoot);
		return 0;
	}

	else if (strcmp(objectName, childFile) == 0) {
		tempNode = retrieveAllActiveKeys(childIndexFileName);
		printf("Active keys are : \n");
		inorderTraversalBST(childRoot);
		return 0;
	}

	else {
		printf("\nOops!Provided object name seems wrong.Please try again.");
		return 1;
	}
}

