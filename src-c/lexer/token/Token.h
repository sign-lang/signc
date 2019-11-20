#pragma once

#include <stddef.h>

typedef struct {
	int kind;
	char* value;
	size_t length;
} Token;

Token* newToken(void);
