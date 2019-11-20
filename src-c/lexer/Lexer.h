#pragma once

#include "token/Token.h"

Token** Lex(char* code, size_t codeLength, size_t* outTokenCount);
