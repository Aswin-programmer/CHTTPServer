#pragma once

#include <stdlib.h>

#include "Allocator.h"

Memory *ReadHTMLFile(const char *path, size_t *outSize);
