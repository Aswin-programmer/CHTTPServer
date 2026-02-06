#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "Allocator.h";

static size_t totalMemoryAllocated = 0;

Memory *AllocateMemory(size_t memorySize) {
	if (memorySize == 0) {
		return NULL;
	}
	Memory *memory = (Memory *)malloc(sizeof(Memory));
	if (memory) {
		memory->ptr = malloc(memorySize);
		memory->size = memorySize;
		if (!memory->ptr) {
			free(memory);
			return NULL;
		}
		totalMemoryAllocated += memory->size;
	}
	return memory;
}

void FreeMemory(Memory *memory) {
	if (memory == NULL) {
		return;
	}
	totalMemoryAllocated -= memory->size;
	free(memory->ptr);
	free(memory);
}

size_t GetCurrentMemoryAllocatedSize() {
	return totalMemoryAllocated;
}

bool CheckIsAllMemoryFreed() {
	return GetCurrentMemoryAllocatedSize() == 0;
}
