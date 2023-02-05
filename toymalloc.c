#include <stdio.h>
#include "toymalloc.h"

heap_cell HEAP[HEAP_SIZE];
heap_cell *START_ADDRESS = &HEAP[0];
heap_cell *END_ADDRESS = &HEAP[HEAP_SIZE-1];

/*
	This function assumes *block is an header.
	Sets the last bit to 1 (Allocated) without altering the other bits.
	Note: 	x or 0 = x
			x or 1 = 1
*/
void set_block_to_allocated(heap_cell *block){
	*block = *block | 0000000000000001;
}

/*
	This function assumes *block is an header.
	Sets the last bit to 0 (Free)
*/

void set_block_to_free(heap_cell *block){
	if (*block % 2 == 1)
		*block -= 1;
}

/*
	This funciton assumes *block is an header.
	The block is set to 0 and then size is shifted to the left by one 
	place so that it can be "overwrited" on the first 15 bits of "block".
*/

int set_size(heap_cell *block, size_t size){
	if (size > HEAP_SIZE){
		printf("Outside boundary error.\n");
		return 1;
	}

	*(block) = 0;

	size = size<<1;
	*(block) = *(block) | size;

	return 0;
}

/*
	Sets the first header to have "HEAP_SIZE-1" (avalaible memory - header) 
	in the first 15 bits and 0 (free) in the last bit.
*/

void initialize_heap(){
	set_size(START_ADDRESS, HEAP_SIZE-1);

	// Set the least significant bit to 0
	*(START_ADDRESS) = *(START_ADDRESS) | 0000000000000001;
	*(START_ADDRESS) -= 1;
}

/*
	Shifting the header's bit to the right by one place will drop the "is_free" bit and "size bits" will be
	the only value in the variable.
*/

size_t get_block_size(heap_cell* header){
	size_t size = *(header)>>1;
	return size;
}

/*
	binary number % 2 => last significant bit
*/

int get_last_bit(heap_cell* header){
	int last_bit = *(header) % 2;
	return last_bit;
}

/*
	This function uses the informations in the header to "jump" to the next header.
	First, it gets the size and checks if the heap memory is ended.
	Then it adds "size" + 1 to the header pointer (pointing to the next block's header)
*/

heap_cell* get_next_header(heap_cell* this_header){
	size_t size = get_block_size(this_header);
	size_t check_boundaries = (size_t)this_header + size; // This address + jump
	if (check_boundaries >= (size_t)END_ADDRESS){
		return NULL;
	}

	return this_header + (uint16_t)size + 1;
}

/*
	This function looks for the first block that is free and big enough to be written on
	(linear search)
*/

heap_cell* search_free_memory(size_t size){
	size += 1; // Add 1 cell for the header
	heap_cell *header = START_ADDRESS;
	while (header <= END_ADDRESS && header != NULL){
		if (get_last_bit(header) == 1 || get_block_size(header) < size){ // is allocated or too small
			header = get_next_header(header);
		}else{
			return (header+1); // return block's starting point
		}
	}
	return NULL;
}

void mem_free(heap_cell *ptr){
	heap_cell *header = ptr-1;
	set_block_to_free(header);
}

/*
	1. Look for free memory
	2. Initialize block (set header's bits)
	3. Initialize an header for the block that comes after this

	Note that "size" is in bytes, so it has to be converted to cells.
	Considering that every cell is two bytes "n_cells = size/2".
	
	For alignement purposes, if size is odd add 1.
*/

void *toy_malloc(size_t size){
	if ((size%2) == 1){
		size++;
	}
	size_t n_cells = size/2;
	
	// 1.
	heap_cell *block = search_free_memory(n_cells);

	if (block == NULL){
		return NULL;
	}

	// 2.
	heap_cell *header = block-1;

	size_t old_size = get_block_size(header);

	set_size(header, n_cells);
	set_block_to_allocated(header);

	// 3.
	heap_cell* next_header = block+n_cells;

	// Size before allocation - allocated cells - next block's header
	size_t next_header_size = old_size-n_cells-1;

	set_size(next_header, next_header_size);
	set_block_to_free(next_header);

	return block;
}


