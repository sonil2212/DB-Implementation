/*
 * deleteCascadeByKey.c
 *
 *  Created on: 08-Oct-2014
 *      Author: sonil
 */

#include <stdio.h>
#include <stdlib.h>
#include <pdsProject.h>
#include <stdbool.h>


int deleteCascadeByKey(char *baseObjectName, char *relatedObjectName,
		unsigned long int key) {

	FILE *fp = NULL;
	struct dataObject dObj;; //stores temporary each object in index file
	struct index iobj;
	int n, i = 0; //keep tracks the no of records in child data file.
	unsigned long int relatedKey,tempKeys[20];


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

			if (relatedKey == key) {
				tempKeys[i] = dObj.key;
				i++;
			}

		}
	}
	fclose(fp);

	fp = fopen(childIndexFileName, "r+b");
	if (fp == NULL) {
		printf("\noops!there seems a problem opening child index file %s",
				relatedObjectName);
	}

	else {
		fread(childFreeLocations, sizeof(childFreeLocations), 1, fp);
		i = 0;
		while (tempKeys[i] != 0) {
			while (1) {
				n = fread(&iobj, sizeof(struct index), 1, fp);
				if (n == 0) {
					break;
				}

				if (tempKeys[i] == iobj.key) {
					if (iobj.flag != 'N') {
						insertFreeLocations(childFreeLocations, tempKeys[i]);
						iobj.flag = 'N';
						fseek(fp, -sizeof(struct index), 1);
						fwrite(&iobj, sizeof(struct index), 1, fp);
						printf("\nObject %s deleted successfully", childFile);
						fseek(fp, 0, 0);
						fwrite(childFreeLocations, sizeof(childFreeLocations),
								1, fp);
						break;
					}
				}

				else
					continue;
			}
			i++;
		}
	}

	fclose(fp);

	return EXIT_SUCCESS;
}

