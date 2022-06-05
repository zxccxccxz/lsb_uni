#include "ppm.h"
#include "error.h"
#include <string.h>

struct ppm* ppm_read(const char* filename)
{
	// check extension to be .ppm
	char* dotpos = strrchr(filename, '.');
	if (!dotpos || dotpos == filename) {
		warning_msg("No file extension!\n");
		return NULL;
	}
	char* ext = dotpos + 1;
	if (strcmp(ext, "ppm") != 0) {
		warning_msg("Wrong file extension!\n");
		return NULL;
	}

	// open file & create vars
	char buff[16];
	struct ppm* img;
	FILE* fp;
	int ch;

	errno_t err = fopen_s(&fp, filename, "rb");

	if (err)
		error_exit("Cannot open file %s\n", filename);
	else {

		// check format
		if (!fgets(buff, sizeof(buff), fp)) {
			perror(filename);
			exit(1);
		}

		if (buff[0] != 'P' || buff[1] != '6')
			error_exit("Invalid magic number (must be P6)\n");

		// allocate memory
		img = malloc(sizeof(struct ppm));
		if (!img) error_exit("Allocation failed\n");

		// delete comments
		ch = getc(fp);
		while (ch == '#') {
			while (getc(fp) != '\n');
			ch = getc(fp);
		}

		ungetc(ch, fp);

		// get img size
		if (fscanf_s(fp, "%u %u", &img->xsize, &img->ysize) != 2)
			error_exit("Img size not found\n");

		// printf("%u, %u\n", img->xsize, img->ysize);

		// get rgb
		int rgb;
		if (fscanf_s(fp, "%u", &rgb) != 1)
			error_exit("RGB not found\n");
		if (rgb > 255)
			error_exit("RGB > 255\n");

		// fill array
		while (fgetc(fp) != '\n');

		char c;
		int elemscounter = 0;

		int idx = 0;

		for (size_t i = 0; i < img->xsize * img->ysize * 3; ++i) {

			c = fgetc(fp);

			if (c == '\0') {
				img->data[idx] = '\0';
				break;
			}

			if (i >= 29 && isPrime(i)) {
				img->data[idx] = c;
				++idx;
			}
		}

		return img;
	}
}

void ppm_free(struct ppm* p) {
	free(p);
}

int isPrime(int n) {
	if (n > 1) {
		for (int i = 2; i < n; i++)
			if (n % i == 0)
				return 0;
		return 1;
	}
	else
		return 0;
}