#define BITMAP_IDENTIFIER 0x4D42

#include <stdint.h>

; // suppress #pragma warning
#pragma pack(push, 1)
typedef struct {
	uint16_t type;			// Magic identifier 0x4D42
	uint32_t size;			// File size in bytes
	uint16_t reserved1;		// not in use
	uint16_t reserved2;		// not in use
	uint32_t offset;		// Offset to image data in bytes from beginning of file
	uint32_t dibheadersize;		// DIB Header size in bytes
	int32_t  width;			// Width of the image
	int32_t  height;		// Height of the image
	uint16_t planes;		// Number of color planes
	uint16_t bits;			// Bits per pixel
	uint32_t compression;		// Compression type
	uint32_t imagesize;		// Image size in bytes
	int32_t  xres;			// Pixels per meter
	int32_t  yres;			// Pixels per meter
	uint32_t ncolors;		// Number of colors
	uint32_t importantcolors;	// Important colors
} BMPHeader;

typedef struct {
	BMPHeader header;
	unsigned char *data;

} BMPImage;
#pragma pack(pop)
