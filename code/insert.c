/*
 * insert.c
 *
 *  Created on: 06-Sep-2014
 *      Author: sonil
 */

#include <stdio.h>
#include <stdlib.h>
#include <pdsProject.h>

int insertObject();

int insertObject() {
	int choice,numOfTimes=1;
	char objType[50];

	while(numOfTimes!=0){
	printf("\nPlease enter object type(Parent/Child) you want to insert: ");
	printf("\n1.PARENT");
	printf("\n2.CHILD\n");
	scanf("%d", &choice);

	loadDataStore(parentFile,childFile);

	switch(choice){
	case 1:
		addUniqueDataObject(parentFile,"parent");
		break;

	case 2:
		addUniqueDataObject(childFile,"child");
		break;

	default :
		printf("\noops!wrong choice is given");
		break;
	}

	printf("\n\n\nDo you want to insert more objects.Enter 0 to exit: ");
	scanf("%d",&numOfTimes);
	}
	return EXIT_SUCCESS;

}
