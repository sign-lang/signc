#include "DeclarationParse.h"

#include <stdbool.h>
#include <string.h>

#include "Declaration.h"
#include "DeclarationKind.h"
#include "../../lexer/token/TokenKind.h"

Declaration* parseDeclaration(Token*** tokens) {
	Declaration* declaration = newDeclaration();
	declaration->kind = DeclarationKind_Invalid;
	declaration->start = *tokens;
	declaration->count = 0;
	
	if ((**tokens)->kind == TokenKind_EOF) {
		return NULL;
	}
	
	if ((**tokens)->length == 7 && strncmp((**tokens)->value, "typedef", (**tokens)->length) == 0) {
		declaration->kind = DeclarationKind_Struct;
		(*tokens) += 2;
		declaration->count += 2;
		if (!((**tokens)->kind == TokenKind_OpenCurly)) { return NULL; }
		++(*tokens);
		++declaration->count;
		size_t count = 1;
		while (true) {
			if ((**tokens)->kind == TokenKind_OpenCurly) {
				++count;
			}
			if ((**tokens)->kind == TokenKind_CloseCurly) {
				--count;
			}
			++(*tokens);
			++declaration->count;
			if (count == 0) { break; }
		}
		*tokens += 2;
		declaration->count += 2;
	} else {
		while (true) {
			++(*tokens);
			++declaration->count;
			if ((**tokens)->kind == TokenKind_OpenCurly) {
				declaration->kind = DeclarationKind_Func;
				break;
			}
			if ((**tokens)->kind == TokenKind_Semicolon) {
				declaration->kind = DeclarationKind_Var;
				break;
			}
		}
		++(*tokens);
		++declaration->count;
		if (declaration->kind == DeclarationKind_Func) {
			size_t count = 1;
			while (true) {
				if ((**tokens)->kind == TokenKind_OpenCurly) {
					++count;
				}
				if ((**tokens)->kind == TokenKind_CloseCurly) {
					--count;
				}
				++(*tokens);
				++declaration->count;
				if (count == 0) { break; }
			}
		}
	}
	
	return declaration;
}
