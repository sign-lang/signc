#include "DeclarationPrint.h"

#include <stdio.h>

void printDeclaration(Declaration* declaration) {
	Token** token = declaration->start;
	char* start = (*token)->value;
	char* end = (*(token + declaration->count))->value;
	
	while (start < end) {
		putc(*(start++), stdout);
	}
}

void printDeclarations(Declaration** declarations, size_t count) {
	for (size_t i = 0; i < count; ++i) {
		printDeclaration(declarations[i]);
		printf("\n\n");
	}
}
