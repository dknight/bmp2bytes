# bmp2bytes

Converts 1-bit monochrome bitmap image (BMP format) to string
and outputs it to `stdout`. Where data is require as text input.

Used in Arduino project with [TVOut library](https://github.com/Avamander/arduino-tvout).

This is version 2.

To get legacy version 1 check out [v1-legacy](https://github.com/dknight/bmp2bytes/tree/v1-legacy) branch.

## Install

```sh
make build
```

## Usage

```
bmp2tpues [-mrihfd] <file.bmp>
```
- **-h**: Prints usage;
- **-r**: reverse rows;
- **-i**: invert image bits;
- **-m**: prints meta data of the image and exit;
- **-f** <string>: format of the output, any number qualifier for `printf` function is accepted. Examples: %d, %X, %02X, etc. Default: 0x%02X;
- **-d**: delimiter of the output. Default: "," (comma);
- **-n**: print new line after the outpit.

## Example

### Image

![Test Bitmap](https://raw.githubusercontent.com/dknight/bmp2bytes/master/tests/girl.bmp)

### Output

```
0xFF,0xFE,0x00,0x00,0x5F,0xFF,0xFF,0x6A,0x80,0x00,0x00,0x7F,0xFA,0xAA,0xAD,
0xDD,0xFD,0x00,0x00,0x35,0xBB,0xB5,0xB5,0x00,0x00,0x00,0x7F,0x7F,0x55,0x55,
0xFF,0xEF,0x00,0x00,0x3F,0xDD,0xFF,0x5A,0x60,0x00,0x00,0x3B,0xEA,0xD6,0xD6,
0x7F,0x7E,0x00,0x00,0x55,0xFF,0xAD,0xEF,0x80,0x00,0x00,0x3F,0xFD,0x52,0x5B,
0xDB,0xFD,0x00,0x00,0x7E,0xDD,0xF6,0xB2,0xE0,0x00,0x00,0x3B,0xFE,0xBB,0x4D,
0xFF,0xEE,0x00,0x00,0xB7,0xFF,0xBF,0xDF,0x10,0x00,0x00,0x7E,0xDD,0x4D,0xB6,
0xEF,0xFC,0x00,0x00,0x5F,0x6D,0xFD,0x74,0xE0,0x00,0x00,0x2F,0xF7,0xB4,0xA9,
0xFD,0xFC,0x00,0x00,0xF7,0xFF,0xDF,0xDE,0x90,0x00,0x00,0x3F,0xFA,0xA6,0x6D,
0xFF,0xFC,0x00,0x00,0xBF,0xFD,0xF7,0xF7,0x50,0x00,0x00,0x37,0xBF,0x57,0x56,
0xFE,0xDC,0x00,0x01,0x7E,0xEF,0xFD,0x5D,0xC0,0x00,0x00,0x3E,0xFA,0xB2,0xB6,
0xDF,0xFC,0x00,0x00,0xF1,0xBF,0xAF,0xFF,0x58,0x00,0x00,0x3F,0xED,0x4D,0x4D,
0xEF,0xF4,0x00,0x01,0x00,0x15,0xFB,0xB5,0x40,0x00,0x00,0x16,0xFD,0xD5,0xB5,
0xFF,0xF8,0x00,0x00,0xFA,0x01,0x7D,0xDF,0xF8,0x00,0x00,0x7F,0xDE,0x4A,0x96,
0xFB,0xF8,0x00,0x01,0x7F,0x80,0x6F,0xFA,0xA0,0x00,0x00,0x36,0xFB,0x75,0x6B,
0xFF,0xB8,0x00,0x00,0xD4,0x68,0x1A,0x6F,0x00,0x00,0x00,0x3F,0x6A,0x8A,0xDC,
0x7D,0xF8,0x00,0x00,0x40,0x03,0x2F,0xB0,0x00,0x00,0x00,0x17,0xFA,0xEA,0x47,
0xDF,0xF8,0x00,0x04,0x40,0x01,0xF7,0xB0,0x00,0x00,0x00,0x7A,0xDD,0x2A,0xB2,
0xFF,0xD0,0x00,0x01,0x00,0x00,0x5A,0xC8,0x0A,0x00,0x00,0x0F,0xB6,0xD5,0x5B,
0xF7,0x70,0x00,0x0C,0x00,0x08,0x2F,0xA8,0x01,0x00,0x00,0x26,0xF9,0x2A,0xA4,
0xBF,0xF0,0x00,0x03,0x50,0x00,0x5A,0xA0,0x00,0x00,0x00,0x33,0xDE,0x4D,0xB7,
0xFB,0xD0,0x00,0x09,0x11,0x00,0x2F,0x80,0x00,0x00,0x00,0x39,0x75,0x64,0xB2,
0xFF,0x60,0x00,0x02,0xCE,0xEA,0x9E,0x40,0x10,0x00,0x00,0x15,0xFB,0x16,0xCD,
0xAF,0xE0,0x00,0x09,0x6D,0x39,0x6B,0x40,0x00,0x00,0x00,0x1D,0x55,0x69,0x36,
0xFB,0xE0,0x02,0x06,0xB7,0xED,0x5F,0xA8,0x00,0x00,0x00,0x15,0x5E,0x96,0x93,
0xFF,0xE0,0x01,0x01,0x52,0xAA,0xF6,0x85,0x40,0x00,0x00,0x0F,0xEA,0x92,0xD9,
0xDD,0xE0,0x00,0x1A,0xDD,0xF5,0x5F,0x6A,0xA8,0x00,0x00,0x04,0xAD,0x69,0x25,
0xFF,0xA0,0x00,0x01,0x6A,0xAF,0xEE,0x91,0x50,0x00,0x00,0x03,0xFA,0x96,0xD6,
0xEF,0xF0,0x00,0x05,0xAF,0xF7,0x77,0x5B,0x58,0x00,0x00,0x08,0xAE,0x52,0x55,
0xFF,0xE0,0x00,0x00,0xAA,0xBB,0xDD,0x29,0xAA,0x00,0x00,0x04,0xD3,0x5A,0xAA,
0xFB,0x70,0x00,0x01,0xA7,0x75,0x77,0x9E,0xD4,0x00,0x00,0x06,0x7C,0x85,0x55,
0xDF,0xF0,0x00,0x00,0x59,0xDE,0xDE,0xA5,0x68,0x00,0x00,0x01,0x8B,0x5A,0xAB,
0xF7,0xB8,0x00,0x09,0x4D,0xEB,0x7F,0x9B,0x2A,0x00,0x00,0x00,0x69,0x4A,0xA8,
0xFB,0xF0,0x00,0x04,0x65,0x6A,0xBA,0xCD,0xE8,0x00,0x00,0x01,0x6C,0xAA,0xAF,
0xBF,0xF8,0x00,0x02,0x92,0xB5,0xDF,0xA6,0xA8,0x00,0x00,0x00,0xB2,0x49,0x50,
0xFF,0xB8,0x00,0x01,0x39,0xD9,0x6F,0xAD,0xD4,0x00,0x00,0x00,0x4D,0x2A,0xA7,
0xF7,0xE8,0x00,0x02,0x8C,0x6D,0xA2,0xAA,0x50,0x00,0x00,0x00,0x32,0x8A,0xB2,
0xFF,0xF8,0x00,0x02,0xB2,0x54,0x0A,0x97,0xA8,0x00,0x00,0x00,0x1D,0x65,0x9A,
0xF5,0x78,0x00,0x01,0x1D,0x2A,0x0A,0x29,0x50,0x00,0x00,0x00,0x2A,0x94,0x65,
0xBF,0xDC,0x00,0x12,0xAB,0xD5,0x74,0x16,0xA4,0x00,0x00,0x00,0x08,0xA9,0xAA,
0xFF,0xFC,0x00,0x01,0xAA,0x5A,0x93,0x4A,0xA0,0x00,0x00,0x00,0x06,0x26,0x95,
0xFF,0xD8,0x00,0x10,0xBF,0x6A,0x98,0x6B,0x20,0x00,0x00,0x00,0x01,0x10,0xC5,
0xAD,0xFC,0x00,0x01,0xC9,0xB7,0x67,0x24,0x90,0x00,0x00,0x00,0x0A,0xCA,0x34,
0xFF,0x7E,0x00,0x00,0x66,0x58,0x95,0x5A,0xD0,0x00,0x00,0x00,0x03,0x2A,0xC9,
0xFF,0xBE,0x00,0x10,0x73,0x48,0x00,0x4B,0x00,0x00,0x00,0x00,0x01,0xA2,0x4A,
0xB7,0xDE,0x00,0x10,0x35,0x80,0x01,0x29,0xD0,0x00,0x00,0x00,0x01,0x51,0x49,
0xFF,0xED,0x00,0x18,0x5A,0x00,0x00,0x04,0x20,0x00,0x00,0x00,0x01,0x5C,0x24,
0xFD,0xFF,0x00,0x0C,0x2D,0x60,0x00,0x0B,0x80,0x00,0x00,0x00,0x00,0xA1,0x55,
0xDE,0xF7,0x00,0x0C,0x16,0xB4,0x80,0x00,0x80,0x00,0x00,0x00,0x00,0x54,0x82,
0xFF,0x7D,0x00,0x0E,0x0A,0x92,0xA4,0x1A,0x80,0x00,0x00,0x00,0x00,0x52,0x51,
0xEB,0xDF,0x80,0x0B,0x05,0x68,0x10,0x22,0x00,0x00,0x00,0x00,0x00,0x09,0x2C,
0xFF,0x77,0x00,0x16,0x85,0xB5,0x44,0x8C,0x00,0x00,0x00,0x00,0x00,0x06,0x42,
0x7F,0xFB,0x80,0x0B,0xC0,0xDD,0x42,0x62,0x00,0x00,0x00,0x00,0x00,0x01,0x22,
0xFB,0xFE,0x00,0x1A,0xA2,0x55,0x6B,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x11,
0xAF,0x6B,0x00,0x16,0xF0,0xAF,0xB4,0xA0,0x00,0x00,0x00,0x00,0x00,0x00,0x05,
0xFD,0xF4,0x00,0x4D,0xD8,0x29,0x4D,0x40,0x00,0x00,0x00,0x00,0x00,0x01,0x40,
0xEF,0x50,0x03,0x2B,0x6C,0x25,0x65,0x40,0x00,0x00,0x00,0x00,0x01,0x10,0x30,
0xF5,0x00,0x01,0x2D,0x77,0x15,0x34,0x00,0x00,0x00,0x00,0x00,0x00,0x88,0x0A,
0xBC,0x00,0x01,0x57,0xAD,0x82,0xCA,0x00,0x00,0x00,0x00,0x00,0x01,0xA6,0x09,
0x6A,0x00,0x00,0x9A,0xF6,0xA0,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x50,0x82,
0xAD,0x80,0x00,0x5F,0x5A,0xD8,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x16,0x52,
0xF4,0x80,0x00,0x2B,0x6E,0xEA,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x52,0xBA,
0xD8,0xC0,0x00,0x17,0xFB,0x2D,0xA0,0x00,0x00,0x00,0x00,0x00,0x00,0x98,0xDD,
0xF9,0x60,0x00,0x1E,0x95,0xD5,0x50,0x00,0x00,0x00,0x00,0x00,0x00,0x66,0x67,
0xFD,0xE0,0x00,0x0B,0xFD,0x75,0xD0,0x00,0x00,0x00,0x00,0x00,0x00,0x1B,0x3D,
0xFF,0xE0,0x00,0x2D,0xAF,0x5A,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x69,0x4D,
0xF9,0xA0,0x00,0x0F,0x7B,0xEF,0xA0,0x00,0x00,0x00,0x00,0x00,0x00,0x15,0x36,
0xFD,0xF0,0x00,0x05,0xF6,0xA9,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x2A,0x95,
0xFD,0xD0,0x00,0x02,0xDA,0xEE,0xA0,0x00,0x00,0x00,0x00,0x00,0x00,0x14,0x8A,
0xFE,0xF0,0x00,0x01,0x7D,0x76,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x0A,0x4B,
0xFE,0xD0,0x00,0x01,0x56,0xAB,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x28,
0xFC,0xE8,0x00,0x00,0xB9,0x6E,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0xCB,
0xFE,0x78,0x00,0x00,0x0D,0x32,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x64,
0xFF,0x78,0x00,0x00,0x2A,0xAE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x35,
0xFF,0x30,0x00,0x00,0x01,0x59,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x40,0x4A,
0xFF,0xB8,0x00,0x00,0x14,0xA6,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x11,
0xFF,0xDC,0x00,0x00,0x02,0x29,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x8C,
0xFF,0xDC,0x00,0x00,0x01,0x14,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x02,
0xFF,0x9A,0x00,0x00,0x00,0x8A,0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x48,
0xFF,0xC6,0x00,0x00,0x02,0x28,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x10,0x02,
0xFF,0xF1,0x00,0x00,0x00,0x06,0x80,0x00,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,
```
