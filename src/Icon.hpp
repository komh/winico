#define INCL_GPIBITMAPS
#define INCL_GPI
#include <os2.h>

struct IconError{
   const char* msg;
   const char* function;
   const char* file;
   unsigned long line;
};

class Icon{
   public:
      virtual int getAlto() = 0;
      virtual int getAncho() =  0;
   private:
      int identidad;
};


class WinIcon:public Icon{
   public:
      WinIcon(){}
      int getAlto();
      int getAncho();
   private:
      int nImagen;
};


class Os2Icon:public Icon{
   public:
      Os2Icon(){
         iafh = new IconAFH;
         ibfh = new IconBFH;
         ibih = new IconBIH;
         Mibih= new IconBIH;
      };
      int getAlto(){return 0;};
      int getAncho(){return 0;};
      int ipow(int b, int e);
      ULONG sizePaleta();
      ULONG getSizeImage();
      IconBIH* getIbih();
      void setDataImage(PBYTE datos, int tamanio);
      void setDataImage(PBYTE data){pImgData = data;};
      PBYTE getDataImage(){ return pImgData; };
      void setMaskData(PBYTE datos);
      PBYTE getMaskData(){ return pMaskData; };
      int getMaskSize(){return maskSize;};
      USHORT getBitsXPixel(){return ibih->getCBitCount();};
      int getNumBitsColores(){return numColores;};
      void setNumBitsColores(int bits){numColores = bits;};
      IconBIH *ibih;
      IconBIH *Mibih;
      IconBFH *ibfh;
      IconAFH *iafh;
   protected:
      int paletaSizeBW;
      int paletaSizeColor;
      int maskSize;
      bool fSoloONo;
      int dataSize;
   private:
      ULONG getSizeMaskImage();
      int numColores;
      PBYTE pImgData;
      PBYTE pMaskData;
};

class Os2Icon12:public Os2Icon{
   public:
      Os2Icon12(){
         bih = new BITMAPINFOHEADER;
         pArray = new BITMAPARRAYFILEHEADER;
         pHead = new BITMAPFILEHEADER;
      };
      Os2Icon12(IconImage *imagenWin);
      ULONG getSizePicture();
      RGB *getPPaletaBW(int i){ return pPaletaBW;};
      BITMAPARRAYFILEHEADER* getPArray(){  return pArray; };
      BITMAPFILEHEADER* getPHead(){ return pHead; };
      RGB *getPPaletaColor(){ return pPaletaColor;};
      int getAlto();
      int getAncho(){return pHead->bmp.cx;};
      void setPArray(BITMAPARRAYFILEHEADER *pArrayIn){pArray = pArrayIn;};
      void setPHead(BITMAPFILEHEADER *pHeadIn){pHead = pHeadIn;};
      void setPaletaBW(RGB *paletaIn){pPaletaBW = paletaIn;};
      void setPPaletaColor(RGB *paletaIn){pPaletaColor = paletaIn;};
   private:
      void convPal(RgbQuad *bpaleta, int colores);
      int setArray();
      int setXorAnd(IconImage *datos);
      int setPalBW();
      int setDatos(IconImage *datos);
      BITMAPARRAYFILEHEADER *pArray;
      BITMAPINFOHEADER *bih;
      BITMAPFILEHEADER *pHead;
      RGB *pPaletaBW;
      RGB *pPaletaColor;
};

class Os2Icon20:public Os2Icon{
   public:
      Os2Icon20(){
         bih = new BITMAPINFOHEADER2;
         pArray = new BITMAPARRAYFILEHEADER2;
         pHead = new BITMAPFILEHEADER2;
      };
      ULONG getSizePicture();
      RGB2 *getPPaletaBW(int i){ return pPaletaBW;};
      BITMAPARRAYFILEHEADER2* getPArray(){  return pArray; };
      BITMAPFILEHEADER2* getPHead(){ return pHead; };
      RGB2 *getPPaletaColor(){ return pPaletaColor;};
   private:
      void convPal(RgbQuad *bpaleta, int colores);
      int setArray();
      int setXorAnd(IconImage *datos);
      int setPalBW();
      int setDatos(IconImage *datos);
      BITMAPARRAYFILEHEADER2 *pArray;
      BITMAPINFOHEADER2 *bih;
      BITMAPFILEHEADER2 *pHead;
      RGB2 *pPaletaBW;
      RGB2 *pPaletaColor;

};

