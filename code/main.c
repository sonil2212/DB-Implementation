/*
 * main.c
 *
 *  Created on: 27-Aug-2014
 *      Author: sonil
 */

#include <pdsProject.h>
#include <stdio.h>
#include <stdlib.h>

struct BSTNode *parentRoot = NULL;
struct BSTNode *childRoot = NULL;

char parentFile[50];
char childFile[50];

unsigned long int front = -1;
unsigned long int rear = -1;

int main() {
	int ch;
	printf("\t\t\tWelcome to database implementation using binary file system");

	printf("\nPlease enter the Parent file name: ");
	scanf("%s", parentFile);

	printf("Please enter the Child file name: ");
	scanf("%s", childFile);

	loaddataDictionary(parentFile, childFile);

	menu: printf(
			"\n\n\n\nPlease enter the choice for corresponding CRUD operation: ");
	printf("\n1.INSERT.");
	printf("\n2.UPDATE.");
	printf("\n3.SELECT.");
	printf("\n4.DELETE.");
	printf("\n5.ShowActiveKeys.");
	printf("\n6.ShowFiles.");
	printf("\n7.EXIT.\n");
	//printf("\n8.CompactDataFile.");
	scanf("%d", &ch);

	switch (ch) {
	case 1:
		insertObject();
		goto menu;
		break;

	case 2:
		updateObject();
		goto menu;
		break;

	case 3:
		selectObject();
		goto menu;
		break;

	case 4:
		deleteObject();
		goto menu;
		break;

	case 5:
		showKeys();
		goto menu;
		break;

	case 6:
		readRecords();
		goto menu;
		break;

	case 7:
		exit_main();
		break;

	case 8:
		compactFile();
		goto menu;
		break;

	default:
		printf("\nWrong choice of CRUD operation is given");
		break;
	}
	return EXIT_SUCCESS;
}
