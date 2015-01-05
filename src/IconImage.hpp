#ifndef ICON_IMAGE_HPP
#define ICON_IMAGE_HPP

#include "BitmapHeader.hpp"
#include "RgbQuad.hpp"

class IconImage{
   public:
      IconImage();
      IconImage(PBYTE pImgData){
         icHeader = (BitmapHeader *)pImgData;
         //Calculates the number of bytes of this image
         numBytesInImg = ((icHeader->getBiHeight()/2)*icHeader->getBiWidth()*icHeader->getBiBitCount())/8;
         if(getBitsXPixel() != 24 && getBitsXPixel() != 32){
            icColors = (RgbQuad *)(pImgData + sizeof(BitmapHeader));
            icXor = (PBYTE)(pImgData + sizeof(BitmapHeader) + (ipow(2,icHeader->getBiBitCount()) * sizeof(RgbQuad)));
            //Set the pointer of the AND mask
            icAnd = (PBYTE)(pImgData + sizeof(BitmapHeader) + (ipow(2,icHeader->getBiBitCount()) * sizeof(RgbQuad)) + numBytesInImg);
         }
         else{
            icXor = (PBYTE)(pImgData + sizeof(BitmapHeader));
            icAnd = (PBYTE)(pImgData + sizeof(BitmapHeader) + numBytesInImg);
         }
         //Calculates the number of colors of this image
         numcolores = ipow(2,icHeader->getBiBitCount()*icHeader->getBiPlanes());
      }
      BitmapHeader* getBitmapHeader(){
         return icHeader;
      }
      RgbQuad* getIcColors(){
         return icColors;
      }
      PBYTE getIcXor(){
         return icXor;
      }
      PBYTE getIcAnd(){
         return icAnd;
      }
      int ipow(int b, int e){
         int p=b;
         while(--e)
            p*=b;
         return p;
      }
      int getNumColores(){
         int colorNumber = 0;
         if (numcolores == NULL){
            colorNumber = ipow(2,icHeader->getBiBitCount()*icHeader->getBiPlanes());
         }
         else
            colorNumber = numcolores;
         return colorNumber;
      }
      int getNumBytes(){
         int bytesNumber = 0;
         if(numBytesInImg == NULL){
            bytesNumber = ((icHeader->getBiHeight()/2)*icHeader->getBiWidth()*icHeader->getBiBitCount())/8;
         }
         else
            bytesNumber = numBytesInImg;
         return bytesNumber;
      }
      int getBitsXPixel(){
         return icHeader->getBiBitCount();
      }

   private:
      BitmapHeader *icHeader;
      RgbQuad  *icColors;
      PBYTE icXor;
      PBYTE icAnd;
      int numcolores;
      int numBytesInImg;
};

#endif
