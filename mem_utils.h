#ifndef UTILS
#define UTILS

#include "toymalloc.h"

void decToBinary(int n);
void print_formatted(heap_cell* address, size_t size, int free);
void dump_memory();
void dump_bin_memory(size_t n_blocks);

#endif