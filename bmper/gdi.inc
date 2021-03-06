; GDI: Graphics Display Interface

include 'macro/armstruc.inc'

struct BITMAPFILEHEADER
  bfType      dw ?
  bfSize      dd ?
  bfReserved1 dw ?
  bfReserved2 dw ?
  bfOffBits   dd ?
ends

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
