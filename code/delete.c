/*
 * delete.c
 *
 *  Created on: 08-Oct-2014
 *      Author: sonil
 */

#include <stdio.h>
#include <stdlib.h>
#include <pdsProject.h>

int deleteObject();

int deleteObject() {
	int numOfTimes = 1;
	char objectName[50];
	unsigned long int searchKey;

	while (numOfTimes != 0) {

		loadDataStore(parentFile, childFile); //loads index file
		printf(
				"\nPlease enter the Object type for which you want to delete the data(%s/%s): ",
				parentFile, childFile);
		scanf("%s", objectName);

		if (strcmp(objectName, childFile) == 0) {
			printf(
					"\nPlease provide the key you want to delete(Key should be of child table): ");
			scanf("%lu", &searchKey);
			deleteByKey(objectName, searchKey);
		}

		else if (strcmp(objectName, parentFile) == 0) {
			printf(
					"\nPlease provide the key you want to delete(Key should be of parent table): ");
			scanf("%lu", &searchKey);
			deleteByKey(objectName, searchKey);
			deleteCascadeByKey(objectName, searchKey);
		}

		else{
			printf("\nEnter object type is not valid");
		}

		printf("\n\n\nDo you want to select more objects.Enter 0 to exit: ");
		scanf("%d", &numOfTimes);
	}
	return EXIT_SUCCESS;

}

