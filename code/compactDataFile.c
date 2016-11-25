/*
 * compactDataFile.c
 *
 *  Created on: 12-Oct-2014
 *      Author: sonil
 */

#include <pdsProject.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compactDataFile(char *dataObjectName);
int compactFile();

int compactDataFile(char *dataObjectName) {
	FILE *fpReadIndex, *fpWrite, *fpReadData;
	struct index indexObject;
	struct dataObject dobj;
	unsigned long int offset;

	if (strcmp(dataObjectName, parentFile) == 0) {
		fpReadData = fopen(parentDataFileName, "rb");
		if (fpReadData == NULL) {
			printf("\nOops!seems there is problem while opening data file.");
		}

		fpReadIndex = fopen(parentIndexFileName, "rb");
		if (fpReadIndex == NULL) {
			printf("\nOops!seems there is problem while opening index file.");
		}

		else {
			fread(parentFreeLocations, sizeof(parentFreeLocations), 1,
					fpReadIndex);
			fpWrite = fopen("/home/sonil/Documents/DBMS/PDS/data/temp.dat",
					"wb");
			if (fpWrite == NULL) {
				printf(
						"\nOops!seems there is problem while opening new data file.");
			}

			else {
				while (!feof(fpReadIndex)) {
					fread(&indexObject, sizeof(struct index), 1, fpReadIndex);

					if (indexObject.flag == 'Y') {
						//offset = indexObject.offset;
						//fseek(fpReadData, offset, 0);
						fread(&dobj, sizeof(struct dataObject), 1, fpReadData);
						fwrite(&dobj, sizeof(struct dataObject), 1, fpWrite);
					}

					else
						continue;
				}

			}

		}
	}
	printf("\ndataFiles compacted successfully");
	fclose(fpWrite);
	fclose(fpReadData);
	fclose(fpReadIndex);
}

int compactFile() {
	char objectName[50];
	printf(
			"\nPlease enter the object type(%s/%s) for which you want to compact data file",
			parentFile, childFile);
	scanf("%s", objectName);

	compactDataFile(objectName);
	return EXIT_SUCCESS;
}

