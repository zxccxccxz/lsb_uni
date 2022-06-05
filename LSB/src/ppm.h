#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "error.h"

struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[3 * 8000 * 8000];    // 3* xsize * yszie
};

struct ppm* ppm_read(const char* filename);

void ppm_free(struct ppm* p);

int isPrime(int n);