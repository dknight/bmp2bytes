//
// MIT License 2017-2024 Dmitri Smirnov <https://www.whoop.ee>
//
// bmp2bytes
//
// Version 2.
//
// Converts 1-bit monochrome bitmap image (BMP format) to string
// and outputs it to `stdout`. Where data is require as text input.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "bitmap.h"

uint8_t check_error(char*);
FILE* read_file(char*, char*);
BMPImage* parse_bmp(char*, uint8_t, uint8_t, char*);
void parse_bmp_header(BMPImage*, FILE*, char*);
void parse_bmp_data(BMPImage*, FILE*, char*);
void print_meta(BMPImage*);
int32_t adjust_width(int32_t);
void check_allocation(void*, char*);
long calc_line_size(BMPImage*);
void usage();

int main(int argc, char** argv) {
	int i, rev_i, opt;
	uint32_t w, h;
	BMPImage* image;
	char* filename = NULL;
	uint8_t reverse = 0;
	uint8_t invert = 0;
	uint8_t meta = 0;
	uint8_t newline = 0;
	char* error = NULL;
	char* format = "0x%02X";
	char* delim = ",";

	while((opt = getopt(argc, argv, "mrihnf:d:")) != -1) {
		switch(opt) {
			case 'n':
				newline = 1;
				break;
			case 'm':
				meta = 1;
				break;
			case 'i':
				invert = 1;
				break;
			case 'r':
				reverse = 1;
				break;
			case 'f':
				format = optarg;
				break;
			case 'd':
				delim = optarg;
				break;
			case 'h':
				usage();
				return EXIT_SUCCESS;
			default:
				break;
		}
	}

	// optind is for the extra arguments
	// which are not parsed
	for(; optind < argc; optind++){
		filename = argv[optind];
		// Only one unparsed argument is required, it is a file name
		if (filename != NULL) {
			break;
		}
	}

	if (access(filename, F_OK) != 0) {
		error = "file missing";
	}
	if (check_error(error)) {
		return EXIT_FAILURE;
	}

	image = parse_bmp(filename, reverse, invert, error);
	check_error(error);

	w = adjust_width(image->header.width);
	h = image->header.height;

	if (meta == 1) {
		print_meta(image);
		return EXIT_SUCCESS;
	}

	for (i = h *( w / 8) - 1; i >= 0 ; i--) {
		printf(format, image->data[i]);
		// Do not print last comma?
		if (i != 0) {
			printf(delim);
		}

		if (newline == 1) {
			print("\n")
		}
	}

	free(image);
	return EXIT_SUCCESS;
}

// In 1-bit image rows have 4 bytes border.
// 2-bit images and more have color in every byte.
long calc_line_size(BMPImage* image) {
	long len = (image->header.width / 32) * 4;
	if (image->header.width % 32) {
		len += 4;
	}
	return len;

}
uint8_t check_error(char* error) {
	if (error != NULL) {
		fprintf(stderr, "%s\n", error);
		return 1;
	}
	return 0;
}

void check_allocation(void* cs, char* error) {
	if (cs == NULL) {
		error = "failed allocate memory";
	}
}

FILE* read_file(char *filename, char* error) {
	FILE* fp = fopen(filename, "rb");
	if (fp == NULL) {
		sprintf(error, "%s cannot be opened.", filename);
		return NULL;
	}
	return fp;
}

// Minimum width size is 8.
int32_t adjust_width(int32_t w) {
	if (w < 8) {
		return 8;
	}
	return w;
}

void parse_bmp_header(BMPImage* image, FILE* fp, char* error) {
	int status = fread(&image->header, sizeof(BMPHeader), 1, fp);
	if (status != 0) {
		error = "cannot read file";
		return;
	}

	if (image->header.type != BITMAP_IDENTIFIER) {
		error = "file is not bitmap image";
		return;
	}

	if (image->header.bits != 1) {
		error = "only 1-bit monochrome bitmap files are supported.";
		return;
	}
}

void parse_bmp_data(BMPImage* image, FILE* fp, char* error) {
	// Move file point to the begging of bitmap data
	int status = fseek(fp, image->header.offset, SEEK_SET);
	if (status != 0) {
		error = "failed to set file offset";
	}

	// Read in the bitmap image data
	status = fread(image->data, image->header.size, 1, fp);
	if (status != 0) {
		error = "failed to read image data";
	}
}

BMPImage* parse_bmp(
	char* filename,
	uint8_t reverse,
	uint8_t invert,
	char* error
) {
	int32_t j, i, rev_i, pos, dw;
	int32_t ipos = 0;
	BMPImage* image = malloc(sizeof(BMPImage));
	check_allocation(image, error);

	FILE* fp = read_file(filename, error);
	if (check_error(error)) {
		fclose(fp);
		free(image);
		return NULL;
	}

	parse_bmp_header(image, fp, error);
	if (check_error(error)) {
		fclose(fp);
		free(image);
		return NULL;
	}
	dw = adjust_width(image->header.width);

	// In 1-bit image rows have 4 bytes border.
	// 2-bit images and more have color in every byte.
	long line_size = calc_line_size(image);
	long martix_size = line_size * image->header.height;

	 // Allocate enough memory for the bitmap image data.
	image->data = malloc(martix_size);
	uint8_t* temp_data = malloc(martix_size);

	check_allocation(image->data, error);
	if (check_error(error)) {
		fclose(fp);
		free(image);
		return NULL;
	}

	parse_bmp_data(image, fp, error);
	if (check_error(error)) {
		fclose(fp);
		free(image);
		return NULL;
	}

	ipos = 0;
	for (
		i = 0, rev_i = image->header.height - 1;
		i < image->header.height;
		i++, rev_i--
	) {
		for (j = dw/8 - 1; j >= 0; j--) {
			// Revere byte order
			if (reverse == 1) {
				pos = rev_i*line_size + j;
			} else {
				pos = i*line_size + j;
			}

			// Invert image
			if (invert == 1) {
				temp_data[ipos] = image->data[pos];
			} else {
				temp_data[ipos] = 0xFF - image->data[pos];
			}
			ipos++;
		}
	}
	image->data = temp_data;
	free(temp_data);
	fclose(fp);
	return image;
}

void print_meta(BMPImage* image) {
	printf("type %d\n", image->header.type);
	printf("size %d\n", image->header.size);
	printf("reserved1 %d\n", image->header.reserved1);
	printf("reserved2 %d\n", image->header.reserved2);
	printf("offset %d\n", image->header.offset);
	printf("dibheadersize %d\n", image->header.dibheadersize);
	printf("width %d\n", image->header.width);
	printf("height %d\n", image->header.height);
	printf("planes %d\n", image->header.planes);
	printf("bits %d\n", image->header.bits);
	printf("compression %d\n", image->header.compression);
	printf("imagesize %d\n", image->header.imagesize);
	printf("xres %d\n", image->header.xres);
	printf("yres %d\n", image->header.yres);
	printf("ncolours %d\n", image->header.ncolors);
	printf("importantcolours %d\n", image->header.importantcolors);
}

void usage() {
	printf("bmp2bytes usage:\n");
	printf("bmp2tpues [-mrihfd] <file.bmp>\n");
	printf("  -h: prints usage;\n");
	printf("  -r: reverse rows;\n");
	printf("  -i: invert image bits;\n");
	printf("  -m: prints meta data of the image and exit;\n");
	printf("  -f <string>: format of the output, any number qualifier ");
	printf("for `printf` function is accepted.\n");
	printf("    Examples: %%d, %%X, %%02X, etc. Default: 0x%%02X\n");
	printf("  -d: delimiter of the output. Default: \",\" (comma).\n");
	printf("  -n: print new line at the end of output");
}
