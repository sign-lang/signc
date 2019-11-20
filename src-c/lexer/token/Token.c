#include "Token.h"

#include "../../utility/Memory.h"

Token* newToken(void) {
	return xcalloc(1, sizeof(Token));
}
