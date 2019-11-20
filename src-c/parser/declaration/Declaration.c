#include "Declaration.h"

#include "../../utility/Memory.h"

Declaration* newDeclaration(void) {
	return xcalloc(1, sizeof(Declaration));
}
