/*
 * deleteByKey.c
 *
 *  Created on: 08-Oct-2014
 *      Author: sonil
 */

#include <stdio.h>
#include <stdlib.h>
#include <pdsProject.h>
#include <stdbool.h>
#include <string.h>

void insertFreeLocations(unsigned long int freelocation[],
		unsigned long int key);
int deleteByKey(char *objectName, unsigned long int searchKey);

int deleteByKey(char *objectName, unsigned long int searchKey) {
	FILE *fp;
	int n;
	bool findkey;
	struct index iObj, iObj1;

	loadDataStore(parentFile, childFile);

	if (strcmp(objectName, childFile) == 0) {

		if (childRoot == NULL) {
			printf("\nOops!seems like there is no active record in %s",
					childFile);
			return EXIT_SUCCESS;
		}
		findkey = searchBST(childRoot, searchKey);

		if (findkey == false) {
			printf("\nOops!The Key you want to delete does not exist in %s",
					childFile);
		}

		else {
			fp = fopen(childIndexFileName, "r+b");
			if (fp == NULL) {
				printf(
						"\noops!there seems a problem opening child data file %s",
						childFile);
				exit(EXIT_FAILURE);
			}

			else {
				fread(childFreeLocations, sizeof(childFreeLocations), 1, fp);
				while (1) {
					n = fread(&iObj, sizeof(struct index), 1, fp);
					if (n == 0) {
						break;
					}

					if (iObj.key != searchKey) {
						continue;
					}

					else {
						if (iObj.flag == 'N') {
							continue;
						}

						else {
							insertFreeLocations(childFreeLocations, searchKey);
							iObj.flag = 'N';
							fseek(fp, -sizeof(struct index), 1);
							fwrite(&iObj, sizeof(struct index), 1, fp);
							printf("\nObject %s deleted successfully",
									childFile);
							fseek(fp, 0, 0);
							fwrite(childFreeLocations,
									sizeof(childFreeLocations), 1, fp);
							break;
						}
					}
				}
			}
			fclose(fp);
		}
		//loadDataStore(parentFile, childFile);
	}

	else if (strcmp(objectName, parentFile) == 0) {
		if (parentRoot == NULL) {
			printf("\nOops!seems like there is no active record in %s.",
					parentFile);
			return EXIT_SUCCESS;
		}
		findkey = searchBST(parentRoot, searchKey);

		if (findkey == false) {
			printf("\nOops!The Key you want to delete does not exist in %s",
					parentFile);
		} else {
			fp = fopen(parentIndexFileName, "r+b");
			if (fp == NULL) {
				printf(
						"\noops!there seems a problem opening child data file %s",
						parentFile);
				exit(EXIT_FAILURE);
			}

			else {
				fread(parentFreeLocations, sizeof(parentFreeLocations), 1, fp);
				while (1) {
					n = fread(&iObj1, sizeof(struct index), 1, fp);
					if (n == 0) {
						break;
					}

					if (iObj1.key != searchKey) {
						//fseek(fp,sizeof(struct index),SEEK_CUR);
						continue;
					}

					else {
						if (iObj1.flag == 'N') {
							continue;
						}

						else {
							insertFreeLocations(parentFreeLocations, searchKey);
							iObj1.flag = 'N';
							fseek(fp, -sizeof(struct index), 1);
							fwrite(&iObj1, sizeof(struct index), 1, fp);
							printf("\nObject %s deleted successfully",
									parentFile);
							fseek(fp, 0, 0);
							fwrite(parentFreeLocations,
									sizeof(parentFreeLocations), 1, fp);
							break;
						}
					}
				}
			}
		}
		fclose(fp);
	}

	else {
		printf("\noops!Object name specified is wrong.Try Again");
	}
	return EXIT_SUCCESS;
}

