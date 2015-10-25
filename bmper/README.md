## Bmper for manipulating bitmaps
###Assembly development for c.h.i.p. computer

This is an example of an assembly program for the c.h.i.p. computer to manipulate one of the simplest possible file formats still in use today: the bitmap file.
A bitmap file is a sequence of numbers representing the color codes for a rectangular matrix of points. If used in a screen for example, it will represent the pixel colors in an image to be shown.
This example will probably run unmodified on any ARM system having a Linux kernel such as a Raspberry Pi or an Android phone or tablet.

####Program definition
The first thing to do is to define how the program will operate: It will be a console application that follows the Unix KISS principle: it does a simple, well defined task that can be chained together with other tools to perform more complex operations.
Our application gets a filename, verify that the file corresponds to a bitmap in order to perform some task upon it and then, optionally, store the result on a different named file and exit after the task is completed. If no output file is defined, the result will be piped to the standard output.
```bash
# bmper -g in.bmp out.bmp
```
If no task is specified, the program will read the bitmap file and will give information about it. If no file is specified, the program will output a help message.
On all cases, the program should exit gracefully.

####Command line arguments
Our program must start getting the arguments from the system command line.
The arguments are stored as zero terminated strings in memory. One pointer to each argument will be stored in the stack, the topmost being the argument count.
After the arguments count, there is the pointer to the command invocation string.

####File header
There is a file header with information about the file itself. A signature, how big it is, etc.
```asm
struct BITMAPFILEHEADER
  bfType      dw ?
  bfSize      dd ?
  bfReserved1 dw ?
  bfReserved2 dw ?
  bfOffBits   dd ?
ends
```
####Bitmap info header
After the file header, there is a bunch of numbers that serve to decode the bitmap information: The size of the point matrix, how the colors get encoded, and so on. There is a complete explanation on [Wikipedia](https://en.wikipedia.org/wiki/BMP_file_format).
```asm
struct BITMAPINFOHEADER
  biSize          dd ?
  biWidth         dd ?
  biHeight        dd ?
  biPlanes        dw ?
  biBitCount      dw ?
  biCompression   dd ?
  biSizeImage     dd ?
  biXPelsPerMeter dd ?
  biYPelsPerMeter dd ?
  biClrUsed       dd ?
  biClrImportant  dd ?
ends
```

[Return home](https://github.com/pelaillo/chip_asm)
