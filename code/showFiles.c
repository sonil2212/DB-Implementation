/*
 * temp.c
 *
 *  Created on: 20-Sep-2014
 *      Author: sonil
 */

#include <stdio.h>
#include <stdlib.h>
#include <pdsProject.h>

int readRecords();
void datafileread(char *filename);
void indexfileread(char *filename);
void indexfileread(char *filename);

int readRecords() {
	readFreeLocations(parentFreeLocations);
	printf("\nDepartment data files entries are:");
	datafileread("/home/sonil/Documents/DBMS/PDS/data/department.dat");
	printf("\n\nDepartment index files entries are:");
	indexfileread("/home/sonil/Documents/DBMS/PDS/index/department.ndx");
	printf("\n\n\nEmployee data files entries are:");
	datafileread("/home/sonil/Documents/DBMS/PDS/data/employee.dat");
	printf("\n\nEmployee index files entries are:");
	indexfileread("/home/sonil/Documents/DBMS/PDS/index/employee.ndx");
	printf("\n\nNew Department data files entries are:");
	datafileread("/home/sonil/Documents/DBMS/PDS/data/temp.dat");
	return EXIT_SUCCESS;

}

void datafileread(char *filename) {
	FILE *fp;
	int n;
	struct dataObject db;

	fp = fopen(filename, "rb");

	if (fp == NULL) {
		printf("\nproblem");
	}

	else {
		//fread(&db, sizeof(db), 1, fp);

		while (1) {

			n = fread(&db, sizeof(db), 1, fp);
			if (n == 0) {
				break;
			}
			printf("\n%lu", db.key);
			printf("\t\t%s", db.fileld1);
			printf("\t\t%s", db.fileld2);
			printf("\t\t%s", db.fileld3);
			printf("\t\t%s", db.fileld4);

		}

		fclose(fp);
	}
}

void indexfileread(char *filename) {
	FILE *fp;
	int n;
	struct index i;
	unsigned long int offset;

	fp = fopen(filename, "rb");

	if (fp == NULL) {
		printf("\nproblem");
	}

	else {
		offset = 100 * sizeof(unsigned long int);
		fseek(fp, offset, 0);

		while (1) {
			n = fread(&i, sizeof(i), 1, fp);
			if (n == 0) {
				break;
			}
			printf("\n%lu", i.key);
			printf("\t\t%lu", i.offset);
			printf("\t\t%c", i.flag);
		}
		fclose(fp);
	}

}

