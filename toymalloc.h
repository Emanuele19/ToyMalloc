#ifndef TOYMALLOC
#define TOYMALLOC

#include <stdint.h>
#include <stddef.h>

#define WORD 16
#define MAX_SIZE_16BIT 65536
#define HEAP_SIZE (MAX_SIZE_16BIT / 2) // 32768

typedef uint16_t heap_cell;

extern heap_cell HEAP[HEAP_SIZE];
extern heap_cell *START_ADDRESS;
extern heap_cell *END_ADDRESS;

// Header manipulation

void set_block_to_allocated(heap_cell *block);
void set_block_to_free(heap_cell *block);
int set_size(heap_cell *block, size_t size);

// Memory management

void initialize_heap();
size_t get_block_size(heap_cell* header);
int get_last_bit(heap_cell* header);
heap_cell* get_next_header(heap_cell* this_header);
heap_cell* search_free_memory(size_t size);
void mem_free(heap_cell *ptr);

// Actual malloc

void *toy_malloc(size_t size);


#endif