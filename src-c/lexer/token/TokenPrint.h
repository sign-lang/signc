#pragma once

#include <stdbool.h>

#include "Token.h"

void printToken(bool error, Token* token);
void printTokens(bool error, Token** tokens, size_t count);
