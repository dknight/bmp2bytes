//
// MIT License 2017-2024 Dmitri Smirnov <https://www.whoop.ee>
//
// bmp2bytes
//
// Converts 1-bit monochrome bitmap image (BMP format) to C byte array as string.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "bitmap.h"

// Exit codes
#define EXIT_ERR_FILE_DOESNT_EXISTS	1
#define EXIT_ERR_FILE_NOT_BITMAP	2
#define EXIT_ERR_MEMORY_ALLOCATION	3
#define EXIT_ERR_READ				4
#define EXIT_ERR_1BIT_SUPPORTED		5

/**
 *  Prints errors text
 * TODO report stderr
 */
void puterr(char* msg) {
	printf("%s\n", msg);
}

// Read header information
void read_header(FILE *fp, BMPHeader *header) {
	fread(header, sizeof(BMPHeader), 1, fp);
}

FILE *get_file_pointer(char *filename) {
	FILE *fp = fopen(filename, "rb");
	if (fp == NULL) {
		printf("%s\n", filename);
		puterr("File does not exists of cannot be opened.");
		exit(EXIT_ERR_FILE_DOESNT_EXISTS);
	}
	return fp;
}

/**
 *  Parses 1-bit bitmap file.
 */
unsigned char *parse_bmp(
	char *filename,
	int *width,
	int *height,
	bool reverseBytes,
	bool invert
) {
	BMPHeader header;
	unsigned char *img, *data;
	int i, j, rev_j, pos, ipos, tmp_w;

	FILE *fp = get_file_pointer(filename);
	read_header(fp, &header);

	// Check that this is Bitmap file.
	if (header.type != BITMAP_MAGIC_IDENTIFIER) {
		fclose(fp);
		puterr("File isn't bitmap image. Only BMP files are supported.");
		exit(EXIT_ERR_FILE_NOT_BITMAP);
	}

	if (header.bits != 1) {
		fclose(fp);
		puterr("Only 1-bit monochrome bitmap files are supported.");
		exit(EXIT_ERR_1BIT_SUPPORTED);
	}

	// In 1-bit image rows have 4 bytes border.
	// 2-bit images and more have color in every byte.
	int lineSize = (header.width / 32) * 4;
	if (header.width % 32) {
		lineSize += 4;
	}

	// Is this wrong?
	//int lineSize = (header.width / 8 + (header.width / 8) % 4);
	int fileSize = lineSize * header.height;

	//allocate enough memory for the bitmap image data
	data = malloc(fileSize);
	img = malloc(header.width * header.height);

	// Verify memory allocation
	if (!img || !data) {
		free(img);
		free(data);
		puterr("Cannot allocate memory");
		fclose(fp);
		exit(EXIT_ERR_MEMORY_ALLOCATION);
	}

	// Move file point to the begging of bitmap data
	fseek(fp, header.offset, SEEK_SET);

	// Read in the bitmap image data
	fread(data, 1 , fileSize, fp);

	// Make sure bitmap image data was read
	if (data == NULL) {
		fclose(fp);
		puterr("Cannot read image data");
		exit(EXIT_ERR_READ);
	}

	// Here you can specify byte order.
	ipos = 0;
	if (header.width < 8) {
		tmp_w = 8;
	} else {
		tmp_w = header.width;
	}
	for (j = 0, rev_j = header.height - 1; j < header.height; j++, rev_j--) {
		for (i = tmp_w/8 - 1; i >= 0; i--) {
			// Revere byte order
			if (reverseBytes == true) {
				pos = rev_j*lineSize + i;
			} else {
				pos = j*lineSize + i;
			}

			// Invert image
			if (invert == true) {
				img[ipos] = data[pos];
			} else {
				img[ipos] = 0xFF - data[pos];
			}
			ipos++;
		}
	}

	fclose(fp);
	free(data);
	*width = tmp_w;
	*height = header.height;
	return img;
}

void print_meta(BMPHeader *header) {
	printf("type %d\n", header->type);
	printf("size %d\n", header->size);
	printf("reserved1 %d\n", header->reserved1);
	printf("reserved2 %d\n", header->reserved2);
	printf("offset %d\n", header->offset);
	printf("dibheadersize %d\n", header->dibheadersize);
	printf("width %d\n", header->width);
	printf("height %d\n", header->height);
	printf("planes %d\n", header->planes);
	printf("bits %d\n", header->bits);
	printf("compression %d\n", header->compression);
	printf("imagesize %d\n", header->imagesize);
	printf("xres %d\n", header->xres);
	printf("yres %d\n", header->yres);
	printf("ncolours %d\n", header->ncolors);
	printf("importantcolours %d\n", header->importantcolors);
}

int main(int argc, char **argv) {
	int i, rev_i, w, h, opt;
	unsigned char* img;
	char* filename = NULL;
	bool reverseBytes = false;
	bool invert = false;
	bool printMeta = false;

	while((opt = getopt(argc, argv, "mrih")) != -1) {
		switch(opt)
		{
			case 'm':
				printMeta = true;
				break;
			case 'h':
				printf("usage %c\n", opt);
				return 0;
				break;
			case 'i':
				invert = true;
				break;
			case 'r':
				reverseBytes = true;
				break;
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

	if (filename == NULL) {
		puterr("file missing");
		return EXIT_ERR_FILE_DOESNT_EXISTS;
	}

	img = parse_bmp(filename, &w, &h, reverseBytes, invert);
	for(i = 0, rev_i = h*(w/8) - 1; i < h*(w/8); i++, rev_i--) {
		printf("0x%02X", img[rev_i]);

		// Dont print last comma??
		// if (i != h * (w/8)-1) printf(",");

		printf(",");

		// Print new line every row to get better readability on output.
		if ((i+1) % (w/8) ==0) {
			printf("\n");
		}
	}

	printf("\n");
	free(img);
	return 0;
}
