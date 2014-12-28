#include <os2.h>

class IconBIH{
   public:
      IconBIH();
      void setIBIH(BITMAPINFOHEADER *bih);
      void setIBIH(BITMAPINFOHEADER2 *bih2);
      ULONG getCx(){
         return cx;
      }
      ULONG getCy(){
         return cy;
      }
      USHORT getCPlanes(){
         return cPlanes;
      }
      USHORT getCBitCount(){
         return cBitCount;
      }
   private:
      ULONG cbFix;
      ULONG cx;
      ULONG cy;
      USHORT   cPlanes;
      USHORT   cBitCount;
};

class IconBFH{
   public:
      IconBFH();
      void setIBFH(BITMAPFILEHEADER *bfh);
      void setIBFH(BITMAPFILEHEADER2 *bfh2);
   private:
      USHORT      usType;
      ULONG       cbSize;
      SHORT       xHotspot;
      SHORT       yHotspot;
      USHORT      offBits;
};

class IconAFH{
   public:
      IconAFH();
      void setIAFH(BITMAPARRAYFILEHEADER *bafh);
      void setIAFH(BITMAPARRAYFILEHEADER2 *bafh2);
      USHORT getUsType(){
         return usType;
      }
   public:
      USHORT      usType;
      ULONG       cbSize;
      ULONG       offNext;
      USHORT      cxDisplay;
      USHORT      cyDisplay;
};
