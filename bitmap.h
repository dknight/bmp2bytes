#pragma pack(1)

#define BITMAPMAGICIDENTIFIER 0x4D42

typedef struct {
   uint16_t type;                  /* Magic identifier 0x4D42     */
   uint32_t size;                  /* File size in bytes          */
   uint16_t reserved1, reserved2;  /* Reversed stuff              */
   uint32_t offset;                /* Offset to image data, bytes */
} BMPHEADER;

typedef struct {
   uint32_t size;                  /* Header size in bytes      */
   int32_t width,height;           /* Width and height of image */
   uint16_t planes;                /* Number of colour planes   */
   uint16_t bits;                  /* Bits per pixel            */
   uint32_t compression;           /* Compression type          */
   uint32_t imagesize;             /* Image size in bytes       */
   int32_t xres,yres;              /* Pixels per meter          */
   uint32_t ncolours;              /* Number of colours         */
   uint32_t importantcolours;      /* Important colours         */
} BMPINFOHEADER;
