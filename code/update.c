/*
 * update.c
 *
 *  Created on: 13-Sep-2014
 *      Author: sonil
 */

#include <stdio.h>
#include <stdlib.h>
#include <pdsProject.h>

extern char parentFile[50];
extern char childFile[50];

int updateObject();

int updateObject() {

	char objectName[50];
	unsigned long int updateKey;
	printf("\nPlease enter the Object you want to update(%s/%s)", parentFile,
			childFile);
	scanf("%s", objectName);

	printf("\nPlease provide the key you want to update: ");
	scanf("%lu", &updateKey);

	loadDataStore(parentFile, childFile);
	updateDataObject(objectName,updateKey);

	return EXIT_SUCCESS;
}

