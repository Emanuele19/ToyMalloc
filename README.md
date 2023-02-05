# ToyMalloc

This repo contains two headers ment to "emulate" how a dynamic allocation malloc could work on a 16 bit architecture.
Note that the toymalloc() function doesn't use system calls as the real malloc does, but instead uses an array of characters statically allocated to manage 16-bit aligned blocks.

-------- toymalloc.h

The functions declared in this header manage the HEAP array.
A block is made of 16-bit cells and starts with an additional cell called "header".
This header contains a 15-bit value representing the size and a single bit representing the state, which can be eather "1" (allocated) or "0" (free).

The 15-bit value acts as a pointer to the cell right before the header of the following block.

The allocation algorithm follows this steps:
1. Look for a contigous block that is big enough to contain the block and the header (linear search);
2. Make and properly format the header and modify the following block's header (because the size has changed after the allocation)

This header also contains a "mem_free()" functions that simply modifies the least significant bit to 0 (sets the block to free).

--------- memutils.h

This header is optional and contains some utilities to "view" the fake heap's state.

--------- main.c

This main file contains some tests functions to show how the toymalloc can be used.

IMPORTANT NOTE: The function works with 16-bits cells, this means that if you want to allocate a 4byte integer you have to allocate 2 cells.
