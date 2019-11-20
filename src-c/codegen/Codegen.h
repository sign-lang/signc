#pragma once

#include <stddef.h>

#include "../parser/declaration/Declaration.h"

void Codegen(Declaration** declarations, size_t count);
