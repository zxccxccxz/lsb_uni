// main.c
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "bitset.h"
#include "ppm.h"

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "en_GB");

	// path: .\res\du1.ppm
	struct ppm* img = ppm_read(argv[1]);

	bitset_t p;

	printf("%s\n", argv[1]);

	bitset_create(&p, img->xsize * img->ysize * 3);

	bitset_wcharr(&p, img);
	bitset_printc(&p);

	printf("\n");

	bitset_free(&p);
	ppm_free(img);

	return 0;
}