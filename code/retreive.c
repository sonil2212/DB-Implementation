/*
 * retreive.c
 *
 *  Created on: 05-Oct-2014
 *      Author: sonil
 */

#include <stdio.h>
#include <stdlib.h>
#include <pdsProject.h>

int selectObject();

int selectObject() {
	int choice, numOfTimes = 1;
	char objectName[50];
	unsigned long int searchKey;

	loadDataStore(parentFile, childFile); //loads index file

	while (numOfTimes != 0) {
		printf(
				"\n\nPlease enter the way you want to do the select operation: ");
		printf("\n1.getByKey");
		printf("\n2.getRelatedObject(key should be of child table)");
		printf("\n3.getRelatedObjectMany(key should be of parent table)\n");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			printf(
					"\nPlease enter the Object type for which you want to select the data(%s/%s): ",
					parentFile, childFile);
			scanf("%s", objectName);

			printf("\nPlease provide the key you want to search: ");
			scanf("%lu", &searchKey);
			getByKey(objectName, searchKey);

			break;

		case 2:
			printf("\nPlease provide the key you want to search: ");
			scanf("%lu", &searchKey);
			getRelatedObject(parentFile, childFile, searchKey);

			break;

		case 3:
			printf("\nPlease provide the key you want to search: ");
			scanf("%lu", &searchKey);
			getRelatedObjectMany(parentFile, childFile, searchKey);

			break;

		default:
			printf("\noops!wrong choice is given");
			break;
		}

		printf("\n\n\nDo you want to select more objects.Enter 0 to exit: ");
		scanf("%d", &numOfTimes);
	}
	return EXIT_SUCCESS;

}

