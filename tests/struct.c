#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRINGIFY(s) XSTRINGIFY(s)
#define XSTRINGIFY(s) #s

typedef struct Token Token;

struct Token {
	int kind;
	char* value;
	size_t length;
} ;




