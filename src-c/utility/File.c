#include "File.h"

#include <stdio.h>
#include <stdlib.h>

#include "Memory.h"

size_t NewlinesBetweenFiles = 3;

size_t readFiles(char** fileNames, size_t fileCount, char** buffer) {
	FILE** files = xcalloc(fileCount, sizeof(FILE*));
	size_t* lengths = xcalloc(fileCount, sizeof(size_t));
	size_t totalLength = 0;
	
	for (size_t i = 0; i < fileCount; ++i) {
		files[i] = fopen(fileNames[i], "r");
		if (files[i] == NULL) {
			perror(fileNames[i]);
			exit(EXIT_FAILURE);
		}
		fseek(files[i], 0, SEEK_END);
		lengths[i] = (size_t)ftell(files[i]);
		totalLength += lengths[i] + NewlinesBetweenFiles;
		fseek(files[i], 0, SEEK_SET);
	}
	
	size_t currentLength = 0;
	*buffer = xcalloc(totalLength + 1, sizeof(char));
	
	for (size_t i = 0; i < fileCount; ++i) {
		if (!(fread(&(*buffer)[currentLength], lengths[i], 1, files[i]) == 1)) {
			fprintf(stderr, "could not read ");
			perror(fileNames[i]);
			exit(EXIT_FAILURE);
		}
		currentLength += lengths[i];
		for (size_t _z = 0; _z < NewlinesBetweenFiles; ++_z) {
			(*buffer)[currentLength++] = 10;
		}
	}
	
	for (size_t i = 0; i < fileCount; ++i) {
		fclose(files[i]);
		files[i] = NULL;
	}
	
	free(files);
	free(lengths);
	
	(*buffer)[totalLength] = 0;
	return totalLength;
}
