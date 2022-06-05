// bitset.c
#include "bitset.h"
#include "ppm.h"

void bitset_create(bitset_t* p, size_t size) {
	//assert(size > 0);

	size_t elems_to_alloc = 1;
	p->size_bits = size;

	elems_to_alloc = size / UINT_SIZE_BITS;

	//printf("[bitset_create] debug: \tsize: %zu\n", size);
	//printf(" \telems_to_alloc: %zu\n", elems_to_alloc);

	p->bit_arr = calloc(elems_to_alloc, sizeof(bitset_base_t));
	if (p->bit_arr == NULL) {
		perror("calloc() failed");
		exit(1);
	}
}

void bitset_setbit(bitset_t* p, size_t index, bitset_base_t data) {
	//assert((data == 0 || data == 1) && index < p->size_bits);
	const size_t block_idx = index >> 3;
	//const size_t block_idx = index / 8;

	index %= UINT_SIZE_BITS;

	if (data >= 1)
		p->bit_arr[block_idx] |= (0x1 << index);
	else
		p->bit_arr[block_idx] &= ~(0x1 << index);
}

bitset_base_t bitset_getbit(bitset_t* p, size_t index) {
	size_t block_idx = index / UINT_SIZE_BITS;
	index %= UINT_SIZE_BITS;
	// printf("isbitset(): idx = %u, arr = %u\n", index, p->bit_arr[index]);
	bitset_base_t result = ((p->bit_arr[block_idx] >> index) & 0x1);
	return result;
}

void bitset_free(bitset_t* p) {
	free(p->bit_arr);
}

void bitset_wcharr(bitset_t* p, struct ppm* src) {
	for (int k = 0; src->data[k] != '\0'; ++k) {
		char toadd = src->data[k];
		bitset_setbit(p, k, ((toadd & 1) == 0 ? 0 : 1));
	}
}

void bitset_printc(bitset_t* p)
{
	for (int i = 0; i < p->size_bits / 8 && p->bit_arr[i] != '\0'; ++i)
		printf("%c", p->bit_arr[i]);
}