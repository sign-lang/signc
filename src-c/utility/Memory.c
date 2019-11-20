#include "Memory.h"

#include <stdlib.h>
#include <stdio.h>

void* xcalloc(size_t count, size_t size) {
	void* pointer = calloc(count, size);
	if (pointer == NULL) {
		perror("xcalloc");
		exit(EXIT_FAILURE);
	}
	return pointer;
}
