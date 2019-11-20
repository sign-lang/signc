#pragma once

#include <stddef.h>

#include "../../lexer/token/Token.h"

typedef struct {
	int kind;
	Token** start;
	size_t count;
} Declaration;

Declaration* newDeclaration(void);
