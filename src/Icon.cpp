int Os2Icon::ipow(int b, int e){
   int p=b;
   while(--e)
      p*=b;
   return p;
}

void Os2Icon::setDataImage(PBYTE datos, int tamanio){
   pImgData = (PBYTE)malloc(tamanio);
   memcpy(pImgData, datos, tamanio);
}

void Os2Icon::setMaskData(PBYTE datos){
   maskSize = getSizeMaskImage();
   pMaskData = (PBYTE)calloc(maskSize*2,1);
   memset(pMaskData,0,maskSize);
   memcpy(pMaskData+maskSize,datos,maskSize);
}
ULONG Os2Icon::getSizeImage(){
   ULONG ret,res;
   int divisor,potencia;
   divisor = ibih->getCx()/4;
   if(ibih->getCBitCount() > 1){
      potencia = ibih->getCBitCount()/8;
      ret = ibih->getCx() * ibih->getCy() * potencia;
   }
   else{
      if(ibih->getCx()==20 || ibih->getCx()==40)
         ret = (ibih->getCx()/5) * (ibih->getCx()*2);
      else
         ret = (ibih->getCx()*ibih->getCy())/divisor;
   }
   return ret;
}

ULONG Os2Icon::getSizeMaskImage(){
   ULONG ret,res;
   switch(Mibih->getCx()){
      case 16:
         ret=64;
         break;
      case 20:
         ret=80;
         break;
      case 32:
         ret=128;
         break;
      case 40:
         ret=320;
         break;
      default:
         break;
   }
/*   if(Mibih->getCx()==16)
      ret=64;
      else
         if(Mibih->getCx()==20)
            ret=80;
            else
               if(Mibih->getCx()==32)
                  ret=128;
                  else
                     if(Mibih->getCx()==40)
                        ret=320;
*/
//   cout << "getSizeMaskImage: X=" << Mibih->getCx() << " ret=" << ret << endl;
   return ret;
}

ULONG Os2Icon::sizePaleta(){
   ULONG buffer;
   int porte;
   int numbits = getIbih()->getCPlanes()*getIbih()->getCBitCount();
   if(numbits != 24)
      porte = ipow(2,numbits);
   else
      porte = 0;
   buffer  = porte*sizeof(RGB);
   return buffer;
}

void Os2Icon12::convPal(RgbQuad *bpaleta, int colores){
   int i, j;
   pPaletaColor = (RGB*)malloc(colores*sizeof(RGB));
   for(i=0;i<colores;i++){
      pPaletaColor[i].bRed = bpaleta[i].getBlue();
      pPaletaColor[i].bGreen = bpaleta[i].getGreen();
      pPaletaColor[i].bBlue = bpaleta[i].getRed();
   }
}

IconBIH* Os2Icon::getIbih(){
   return ibih;
}

int Os2Icon12::setPalBW(){
   pPaletaBW = (RGB*)malloc(sizeof(RGB)*2);
   pPaletaBW[0].bBlue = 0x00;
   pPaletaBW[0].bGreen = 0x00;
   pPaletaBW[0].bRed = 0x00;
   pPaletaBW[1].bBlue = 0xff;
   pPaletaBW[1].bGreen  = 0xff;
   pPaletaBW[1].bRed = 0xff;

   return 0;
}

Os2Icon12::Os2Icon12(IconImage *imagenWin){
   bih = new BITMAPINFOHEADER;
   pArray = new BITMAPARRAYFILEHEADER;
   pHead = new BITMAPFILEHEADER;
   //No configuro la paleta de colores si es un icono de 24 bits
   if(imagenWin->getBitsXPixel() != 24)
      convPal(imagenWin->getIcColors(),imagenWin->getNumColores());
   setNumBitsColores(imagenWin->getBitsXPixel());
   setPalBW();
   setDataImage(imagenWin->getIcXor(),imagenWin->getNumBytes());
   setArray();
   setDatos(imagenWin);
   setXorAnd(imagenWin);
   setMaskData(imagenWin->getIcAnd());
}

ULONG Os2Icon12::getSizePicture(){
   ULONG size;
   int n1 = sizeof(BITMAPARRAYFILEHEADER);
   int n2 = sizeof(BITMAPFILEHEADER);
   int n3 = sizeof(RGB);
   size = n1+n2+(n3*2)+sizePaleta();
   return size;
}

int Os2Icon12::setXorAnd(IconImage *datos){
//   BITMAPFILEHEADER xheader = pArray->bfh;
   pArray->bfh.usType    = BFT_COLORICON;
   pArray->bfh.cbSize    = sizeof(BITMAPFILEHEADER);
   pArray->bfh.xHotspot  = datos->getBitmapHeader()->getBiWidth()/2;
   pArray->bfh.yHotspot  = datos->getBitmapHeader()->getBiHeight()/4;
   pArray->bfh.offBits   = 0;
   pArray->bfh.bmp.cbFix = sizeof(BITMAPINFOHEADER);
   pArray->bfh.bmp.cx    = datos->getBitmapHeader()->getBiWidth();
   pArray->bfh.bmp.cy    = datos->getBitmapHeader()->getBiHeight();
   pArray->bfh.bmp.cPlanes       = datos->getBitmapHeader()->getBiPlanes();
   pArray->bfh.bmp.cBitCount     = 1;
   Mibih->setIBIH(&pArray->bfh.bmp);
   return 0;
}

int Os2Icon12::setDatos(IconImage *datos){
   pHead->usType           =0x4943;
   pHead->cbSize           =sizeof(BITMAPFILEHEADER);
   pHead->xHotspot         =datos->getBitmapHeader()->getBiWidth()/2;
   pHead->yHotspot         =datos->getBitmapHeader()->getBiHeight()/4;
   pHead->offBits          =0;
   pHead->bmp.cbFix        =sizeof(BITMAPINFOHEADER);
   pHead->bmp.cx           =datos->getBitmapHeader()->getBiWidth();
   pHead->bmp.cy           =datos->getBitmapHeader()->getBiHeight()/2;
   pHead->bmp.cPlanes      =datos->getBitmapHeader()->getBiPlanes();
//   pHead->bmp.cBitCount    =datos->getBitmapHeader()->getBiBitCount();
   pHead->bmp.cBitCount    =datos->getBitsXPixel();
   ibih->setIBIH(&pHead->bmp);
   return 0;
}

int Os2Icon12::setArray(){
   pArray->usType       =0x4142;
   pArray->cbSize       =sizeof(BITMAPARRAYFILEHEADER);
   pArray->offNext      =1;
   pArray->cxDisplay    =0;
   pArray->cyDisplay    =0;
   return 0;
}

int Os2Icon12::getAlto(){
   return pHead->bmp.cy;
}

