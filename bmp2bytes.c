/*
* bmp2bytes
* Converts 1-bit bitmap image (BMP format) to C byte array.
*
* By Dmitri Smirnov <smirnov.dmitri@gmail.com>
* 2017-02-27
* Version 1.0
*
* Usage:
*   bmp2bytes <filename> [r [i]] 
*   Eg1. bmp2bytes test16x16.bmp r i
*   Eg2. bmp2bytes test16x16.bmp r
*   Eg3. bmp2bytes test16x16.bmp
*
*   r and i argument can be any values except NULL.
*   TODO: for better usage use GCC library getopt.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include "bitmap.h"

// Exit codes
#define EXIT_ERR_FILE_DOESNT_EXISTS   1
#define EXIT_ERR_FILE_NOT_BITMAP      2
#define EXIT_ERR_MEMORY_ALLOCATION    3
#define EXIT_ERR_MEMORY_ALLOCATION    4
#define EXIT_ERR_READ                 5
#define EXIT_ERR_1BIT_SUPPORTED       6

/**
 *  Prints errors text
 */
void puterr(char* msg) {
  printf("%s\n", msg);
  printf("Quit\n");
  return;
}

/**
 *  Parses 1-bit bitmap file.
 */
unsigned char *parse_bmp(char *fname, int *_w, int *_h,
                          char *_order, char *_invert) {

  BMPHEADER header;
  BMPINFOHEADER infoheader;
  unsigned char *img;
  unsigned char *data;
  int i, j, rev_j, pos, ipos;

  FILE *fp = fopen(fname, "rb");
  if (fp == NULL) {
    puterr("File doesnt exists of cannot be opened.");
    exit(EXIT_ERR_FILE_DOESNT_EXISTS);
  }

  // Read header information
  fread(&header, sizeof(BMPHEADER), 1, fp);

  // Check that this is BMP.
  if (header.type != BITMAPMAGICIDENTIFIER) {
    fclose(fp);
    puterr("File isn't bitmap image. Only BMP files are supported.");
    exit(EXIT_ERR_FILE_NOT_BITMAP);
  }

  fread(&infoheader, sizeof(BMPINFOHEADER), 1, fp);

  if (infoheader.bits != 1) {
    fclose(fp);
    puterr("Only 1-bit monochrome bitmap files are supported.");
    exit(EXIT_ERR_1BIT_SUPPORTED);
  }

  // In 1-bit image rows have 4 bytes border.
  int lineSize = (infoheader.width / 32) * 4;
  if (infoheader.width % 32) {
    lineSize += 4;
  }
  // Is this wrong?
  //int lineSize = (infoheader.width / 8 + (infoheader.width / 8) % 4);
  int fileSize = lineSize * infoheader.height;

  //allocate enough memory for the bitmap image data
  data = malloc(fileSize);
  img = malloc(infoheader.width * infoheader.height);

  // Verify memory allocation
  if (!img || !data) {
    free(img);
    free(data);
    puterr("Cannot allocate memory");
    fclose(fp);
    exit(EXIT_ERR_MEMORY_ALLOCATION);
  }

  //move file point to the begging of bitmap data
  fseek(fp, header.offset, SEEK_SET);

  //read in the bitmap image data
  fread(data, 1 , fileSize, fp);

  //make sure bitmap image data was read
  if (data == NULL) {
    fclose(fp);
    puterr("Cannot read image data");
    exit(EXIT_ERR_READ);
  }

  // Here you can specity byte order.
  ipos = 0;
  for (j = 0, rev_j = infoheader.height-1;j < infoheader.height; j++, rev_j--) {
    for (i = infoheader.width/8-1; i >= 0; i--) {

      // Revere byte order or not
      if (_order == NULL) {
        pos = rev_j * lineSize + i;
      } else {
        pos = j * lineSize + i;
      }

      // Invert image or not
      if (_invert == NULL) {
        img[ipos] = data[pos];
      } else {
        img[ipos] = 0xFF - data[pos];
      }

      ipos += 1;
    }
  }

  
  fclose(fp);
  free(data);
  *_w = infoheader.width;
  *_h = infoheader.height;
  return img;
}

/**
 *  Here we go!
 */
int main(int argc, char *argv[]) {

  int i, rev_i, w, h;
  unsigned char* img;

  if (argc < 2) {
    puterr("Please enter file name as 1st arguments");
    return 1;
  }

  img = parse_bmp(argv[1], &w, &h, argv[2], argv[3]);
  for(i = 0, rev_i = h * (w/8)-1; i < h * (w/8); i++, rev_i--) {
    printf("0x%02X", img[rev_i]);

    // Dont print last comma
    // if (i != h * (w/8)-1) printf(",");

    printf(",");

    // Print new line
    if ((i+1) % (w/8) ==0) {
      printf("\n");
    }
  }

  printf("\n");
  free(img);
  return 0;
}