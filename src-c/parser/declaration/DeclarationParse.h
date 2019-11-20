#pragma once

#include "Declaration.h"
#include "../../lexer/token/Token.h"

Declaration* parseDeclaration(Token*** tokens);
