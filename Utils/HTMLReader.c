#include <stdio.h>
#include <stdlib.h>

#include "HTMLReader.h"

Memory *ReadHTMLFile(const char *path, size_t *outSize) {
	FILE *f = fopen(path, "rb");
	if (!f) {
		printf("Failed to read HTML!.");
		return NULL;
	}

	fseek(f, 0, SEEK_END);
	size_t size = ftell(f);
	fseek(f, 0, SEEK_SET);

	Memory *memory = AllocateMemory(size + 1);
	char *data = (char *)memory->ptr;
	fread(data, 1, size, f);
	data[size] = '\0';

	fclose(f);

	if (outSize) {
		*outSize = size;
	}
	return memory;
}
