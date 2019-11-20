#pragma once

#include "declaration/Declaration.h"
#include "../lexer/token/Token.h"

Declaration** Parse(Token** tokens, size_t tokenCount, size_t* outDeclCount);
