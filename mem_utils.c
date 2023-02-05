#include "mem_utils.h"
#include <stdio.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define RESET   "\x1b[0m"

void decToBinary(int n){
    // array to store binary number
    int binaryNum[32];

    // counter for binary array
    int i = 0;
    while (n > 0) {
        // storing remainder in binary array
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }

	for(int j = 16; j > i; j--){
		printf("0");
	}
  
    // printing binary array in reverse order
    for (int j = i - 1; j >= 0; j--)
        printf(GREEN "%d" RESET, binaryNum[j]);

   printf("\n");
}

void print_formatted(heap_cell* address, size_t size, int free){
	printf(YELLOW "[%p]" RESET "\t%ld\t\t%s\n" RESET, address, size, !free ? GREEN"Free" : RED"Allocated");
}

void dump_memory(){
	heap_cell *header = START_ADDRESS; // Header del primo blocco

	int i;
	size_t size;
	int last_bit;

	printf("\n=========================================\n");
	printf("Address\t\t\tSize (blocks)\tState\n\n");
	for(i = 0; i < HEAP_SIZE; ){
		size = get_block_size(header);
		last_bit = get_last_bit(header);

		if (size != 0){
			print_formatted(header, size, last_bit);
		}
		
		i += size;

		if (get_next_header(header) == NULL){
			break;
		}
		header = get_next_header(header);
	}
	printf("=========================================\n");
}

// Same as decToBinary() just with an other color :)
void print_header(int content){
    int binaryNum[32];

    int i = 0;
    while (content > 0) {
        binaryNum[i] = content % 2;
        content = content / 2;
        i++;
    }

	for(int j = 16; j > i; j--){
		printf("0");
	}
  
    for (int j = i - 1; j >= 0; j--){
		if (j == 0)
			printf("|");
        printf(YELLOW "%d" RESET, binaryNum[j]);
	}

   printf("\n");
}

void dump_bin_memory(size_t n_blocks){
	heap_cell *header = START_ADDRESS;
	
	printf("Dumping memory in binary!!!!!!!\n\n\n");

	int header_index = 0;
	int i;
	for(i = 0; i < n_blocks; i++){
		printf("%d\t", i+1);

		if (i == 0 || i == header_index){
			header_index += get_block_size(header+i)+1;
			print_header(*(header+i));
		}else{
			decToBinary(*(header+i));
		}
	}
}