#include "toymalloc.h"
#include "mem_utils.h"
#include <stdio.h>

/*

TODO: 	Ricerca "allineamento".
TODO: 	La free() dovrebbe controllare se ci sono blocchi liberi concatenati ed eventualmente unirli.
TODO: 	Definisci una funzione mem_write() che prende in input il valore da copiare e la locazione 
		dove copiarlo (puntatore a locazione allocata con toy_malloc()).
TODO: 	toy_calloc().
TODO: 	toy_realloc().

*/

void test();

typedef struct prova{
	int number;
	char character;
	double big_number;
}prova;

int main(){
	initialize_heap();

	test();	
	test_struttura();

	return 0;
}

void test_struttura(){
	prova* struttura = toy_malloc(sizeof(prova)*2);
	struttura->number = 400000000;
	struttura->character = 'A';
	struttura->big_number = 3.14;
	struttura[1].number = 255;
	struttura[1].character = 'B';
	struttura[1].big_number = 1024;

	dump_memory();
	dump_bin_memory(50);
}

void test(){	
	printf("\n\n[!] Allocating 10 cells\n\n");

	void *ptr = toy_malloc(10);
	dump_memory();

	printf("\n\n[!] Allocating 16 cells\n\n");

	void *ptr2 = toy_malloc(16);
	dump_memory();

	printf("\n\n[!] Freeing first block...\n\n");
	mem_free(ptr);

	dump_memory();
	dump_bin_memory(20);

	printf("\n\n[!] Allocating 5 cells.\n\n");
	toy_malloc(5);

	dump_memory();
	dump_bin_memory(20);

	printf("\n\n[!] Allocating 4 cells.\n\n");
	toy_malloc(4);

	dump_memory();

	printf("\n\n[!] Allocating 2 cells.\n\n");
	toy_malloc(2);

	dump_memory();
}