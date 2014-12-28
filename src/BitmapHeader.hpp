#include <os2.h>

class BitmapHeader{

   ULONG    biSize;
   ULONG    biWidth;
   ULONG    biHeight;
   USHORT   biPlanes;
   USHORT   biBitCount;
   ULONG    biCompression;
   ULONG    biSizeImage;
   ULONG    biXPelsPerMeter;
   ULONG    biYPelsPerMeter;
   ULONG    biCirUsed;
   ULONG    biClrImportant;

   public:

      BitmapHeader(){
         biSize     =0;
         biWidth    =0;
         biHeight   =0;
         biPlanes   =0;
         biBitCount =0;
         biCompression  =0;
         biSizeImage    =0;
         biXPelsPerMeter=0;
         biYPelsPerMeter=0;
         biCirUsed      =0;
         biClrImportant =0;
      }

      // Setters

      void setBiSize(ULONG valor){
         biSize = valor;
         }
      void setBiWidth(ULONG valor){
         biWidth = valor;
         }
      void setBiHeight(ULONG valor){
         biHeight = valor;
         }
      void setBiPlanes(USHORT valor){
         biPlanes = valor;
         }
      void setBiBitCount(USHORT valor){
         biBitCount = valor;
         }
      void setBiCompression(ULONG valor){
         biCompression = valor;
         }
      void setBiSizeImage(ULONG valor){
         biSizeImage = valor;
         }
      void setBiXPelsPerMeter(ULONG valor){
         biXPelsPerMeter = valor;
         }
      void setBiYPelsPerMeter(ULONG valor){
         biYPelsPerMeter = valor;
         }
      void setBiCirUsed(ULONG valor){
         biCirUsed = valor;
         }
      void setBiClrImportant(ULONG valor){
         biClrImportant = valor;
         }

      //Getters

      ULONG getBiSize(){
         return biSize;
      }
      ULONG getBiWidth(){
         return biWidth;
      }
      ULONG getBiHeight(){
         return biHeight;
      }
      USHORT getBiPlanes(){
         return biPlanes;
      }
      USHORT getBiBitCount(){
         return biBitCount;
      }
      ULONG getBiCompression(){
         return biCompression;
      }
      ULONG getBiSizeImage(){
         return biSizeImage;
      }
      ULONG getBiXPelsPerMeter(){
         return biXPelsPerMeter;
      }
      ULONG getBiYPelsPerMeter(){
         return biYPelsPerMeter;
      }
      ULONG getBiCirUsed(){
         return biCirUsed;
      }
      ULONG getBiClrImportant(){
         return biClrImportant;
      }
   };