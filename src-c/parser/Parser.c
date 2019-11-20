#include "Parser.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "declaration/DeclarationKind.h"
#include "declaration/DeclarationParse.h"
#include "declaration/DeclarationPrint.h"
#include "../lexer/token/TokenKind.h"
#include "../lexer/token/TokenPrint.h"
#include "../utility/Memory.h"

Declaration** Parse(Token** tokens, size_t tokenCount, size_t* outDeclCount) {
	InitDeclarationKinds();
	
	Declaration** declarations = xcalloc(tokenCount, sizeof(Declaration*));
	*outDeclCount = 0;
	
	Token*** t = &tokens;
	while (true) {
		Declaration* declaration = parseDeclaration(t);
		if (declaration == NULL) { break; }
		declarations[(*outDeclCount)++] = declaration;
	}
	
	if (!((*tokens)->kind == TokenKind_EOF)) {
		fprintf(stderr, "Unexpected token: ");
		printToken(true, *tokens);
		fprintf(stderr, "\n\n");
		printDeclarations(declarations, *outDeclCount);
		exit(EXIT_FAILURE);
	}
	
	return declarations;
}
