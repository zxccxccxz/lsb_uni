// bitset.h
#pragma once
#include <assert.h>
#include <limits.h>
#include "error.h"
#define UINT_SIZE_BITS (CHAR_BIT * sizeof(char))

typedef char bitset_base_t;
// typedef char bitset_index_t;
typedef struct
{
	bitset_base_t* bit_arr;
	size_t size_bits;
} bitset_t;

void bitset_create(bitset_t* p, size_t size);

void bitset_setbit(bitset_t* p, size_t index, bitset_base_t data);

bitset_base_t bitset_getbit(bitset_t* p, size_t index);

void bitset_free(bitset_t* p);

void Eratosthenes(bitset_t* p);

void bitset_wcharr(bitset_t*, struct ppm*);

void bitset_printc(bitset_t* p);
