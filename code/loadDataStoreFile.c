/*
 * loadDataStore.c
 *
 *  Created on: 04-Sep-2014
 *      Author	: sonil
 */

#include <stdio.h>
#include <stdlib.h>
#include <pdsProject.h>

int loadDataStore(char *base_object_name, char *related_object_name) {
	struct index indexObject; //stores temporary each object in index file
	FILE *fp = NULL;
	int n; //keep tracks the no of records in the index files
	unsigned long int offset=0;

	//code for loading parent index file
	fp = fopen(parentIndexFileName, "rb");
	if (fp == NULL) {
		printf("\noops!there seems a problem opening parent index file %s",
				base_object_name);
		exit(EXIT_FAILURE);
	}

	else {
		offset = offset+100 * sizeof(unsigned long int);
		fseek(fp, offset, 0);

		while (1) {
			n = fread(&indexObject, sizeof(struct index), 1, fp);
			if (n == 0) {
				break;
			}
			if (indexObject.flag != 'N') {
				insertBST(&parentRoot, indexObject.key, indexObject.offset,
						indexObject.flag);
			}

			else
				continue;
		}

		fclose(fp);
	}

	//code for loading child index file in BST
	fp = fopen(childIndexFileName, "rb");
	if (fp == NULL) {
		printf("\noops!there seems a problem opening child file %s",
				related_object_name);
	}

	else {
		fseek(fp, offset, 0);

		while (1) {

			n = fread(&indexObject, sizeof(struct index), 1, fp);
			if (n == 0) {
				break;
			}

			if (indexObject.flag != 'N') {
			insertBST(&childRoot, indexObject.key, indexObject.offset,
					indexObject.flag);
		}
		}
		fclose(fp);

	}

	return EXIT_SUCCESS;
}
