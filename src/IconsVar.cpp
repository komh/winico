#include "IconsVar.hpp"

IconBIH::IconBIH(){
   cbFix       = 0;
   cx          = 0;
   cy          = 0;
   cPlanes     = 0;
   cBitCount   = 0;
}

void IconBIH::setIBIH(BITMAPINFOHEADER *bih){
   cbFix       = bih->cbFix;
   cx          = bih->cx;
   cy          = bih->cy;
   cPlanes     = bih->cPlanes;
   cBitCount   = bih->cBitCount;
}

void IconBIH::setIBIH(BITMAPINFOHEADER2 *bih2){
   cbFix       = bih2->cbFix;
   cx          = bih2->cx;
   cy          = bih2->cy;
   cPlanes     = bih2->cPlanes;
   cBitCount   = bih2->cBitCount;
}

IconBFH::IconBFH(){
   usType      = 0;
   cbSize      = 0;
   xHotspot    = 0;
   yHotspot    = 0;
   offBits     = 0;
}

void IconBFH::setIBFH(BITMAPFILEHEADER *bfh){
   usType      = bfh->usType;
   cbSize      = bfh->cbSize;
   xHotspot    = bfh->xHotspot;
   yHotspot    = bfh->yHotspot;
   offBits     = bfh->offBits;
}

void IconBFH::setIBFH(BITMAPFILEHEADER2 *bfh2){
   usType      = bfh2->usType;
   cbSize      = bfh2->cbSize;
   xHotspot    = bfh2->xHotspot;
   yHotspot    = bfh2->yHotspot;
   offBits     = bfh2->offBits;
}

IconAFH::IconAFH(){
   usType      = 0;
   cbSize      = 0;
   offNext     = 0;
   cxDisplay   = 0;
   cyDisplay   = 0;
}

void IconAFH::setIAFH(BITMAPARRAYFILEHEADER *bafh){
   usType      = bafh->usType;
   cbSize      = bafh->cbSize;
   offNext     = bafh->offNext;
   cxDisplay   = bafh->cxDisplay;
   cyDisplay   = bafh->cyDisplay;
}

void IconAFH::setIAFH(BITMAPARRAYFILEHEADER2 *bafh2){
   usType      = bafh2->usType;
   cbSize      = bafh2->cbSize;
   offNext     = bafh2->offNext;
   cxDisplay   = bafh2->cxDisplay;
   cyDisplay   = bafh2->cyDisplay;
}
