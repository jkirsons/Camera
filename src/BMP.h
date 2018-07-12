#pragma once

//assuming pixel lines have multiples of 4 bytes sizes
class BMP
{

  static void setChar(void *buffer, int pos, char ch)
  {
    *(char*)(((uint8_t*)buffer)+pos) = ch;
  }

  static void setLong(void *buffer, int pos, long l)
  {
    *(long*)(((uint8_t*)buffer)+pos) = l;
  }
  
  static void setShort(void *buffer, int pos, short s)
  {
    *(short*)(((uint8_t*)buffer)+pos) = s;
  }
  
public:  
  static const int headerSize = 54 + 256*4;
  
  static void construct16BitHeader(void *buffer, long xres, long yres)
  {
    setChar(buffer, 0, 'B');
    setChar(buffer, 1, 'M');

    long bytesPerLine = xres;// * 2;
    setLong(buffer, 2, bytesPerLine * yres  + 54 + 256*4); //filesize
    setLong(buffer, 6, 0);
    
    setLong(buffer, 10, 54 + 256*4); //offset

    setLong(buffer, 14, 40); //header size
    setLong(buffer, 18, xres);
    setLong(buffer, 22, yres);
    setShort(buffer, 26, 1); //planes
    setShort(buffer, 28, 8); //bits

    setLong(buffer, 30, 0); //compression 3 = bit fields
    setLong(buffer, 38, 0); //x pix per meter
    setLong(buffer, 42, 0); //y pix per meter

    setLong(buffer, 46, 0); //biClrUsed
    setLong(buffer, 50, 0); //biClrImportant
    for(int i = 0; i <= 0xFF; i++)
    {
      setLong(buffer, 54+i*4+0, i); 
      setLong(buffer, 54+i*4+1, i); 
      setLong(buffer, 54+i*4+2, i); 
      setLong(buffer, 54+i*4+3, 0);    
    }
    

  }
};


