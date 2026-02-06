#pragma once
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Memory {
	void *ptr;
	size_t size;
} Memory;

Memory *AllocateMemory(size_t memorySize);
void FreeMemory(Memory *memory);
size_t GetCurrentMemoryAllocatedSize();
bool CheckIsAllMemoryFreed();
