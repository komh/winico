#include <iostream>

#include "IconMgr.hpp"

using namespace std;

#define ICONO_20X20  20
#define ICONO_40X40  40

void WiconMgr::grabaIcono(char* fileName){
}

Os2IconMgr12* WiconMgr::codecOs2Icon12(){
   Os2IconMgr12 *iconoWarp = new Os2IconMgr12();
   //Se parte de la imagen mas peque¤a para que el WPS asuma la imagen mas grande al desplegarla
   for(int i=numImagenes-1; i >= 0;i--){
      IconDirEntry *entry = iconoWindows->getIdEntries()[i];
      int width = entry->getBWidth();
      IconImage *imagenWin = entry->getIconImage();

      cout << "Found image : "
           << width << "x" << width << "x" << imagenWin->getBitsXPixel()
           << ", ";

      switch(width){
         case 0:
            cout << "Not suppored !!!" << endl;
            break;

         default:{
            cout << "Converting..." << endl;

            Os2Icon12 *newIconWarp = new Os2Icon12(imagenWin);
            //Agrego al manager la imagen del icono
            iconoWarp->addImage(newIconWarp);
            //Dependiendo de si es una imagen de 16 o 32 se crea una imagen ya sea de 20 o 40
            if(width == 16 || width == 32)
               iconoWarp->addImageGrande(newIconWarp);
            break;
         }
      }
   }
   iconoWarp->setNumImages();
   return iconoWarp;
}

void WiconMgr::cargaIcono(char* fileName) throw (IconError){
   APIRET rc = 0;
   HFILE handleArchivo = 0L;
   FILESTATUS3 fileInfo = {{0}};
   ULONG bufSize = sizeof(FILESTATUS3);
   ULONG fileSize;
   ULONG accion = 0;
   PBYTE retorno = 0L;
   ULONG cbRead;
   rc = DosOpen(fileName,&handleArchivo,&accion,0L,
               FILE_NORMAL,
               FILE_OPEN,
               OPEN_SHARE_DENYNONE|OPEN_ACCESS_READONLY,
               0L);
   if(rc !=0){
      IconError error;
      error.function = "cargaIcono";
      error.file = __FILE__;
      error.line = __LINE__;
      error.msg = "Error opening the file";
      throw error;
   }
   else{
      rc = DosQueryFileInfo(handleArchivo,FIL_STANDARD,&fileInfo,bufSize);
      if(rc != 0){
         cout<<"Error al traer la informaci¢n del archivo" <<endl;
      }
      fileSize = fileInfo.cbFile;
      retorno = (PBYTE)malloc(sizeof(PBYTE)*fileSize);
      rc = DosRead(handleArchivo,retorno,fileSize,&cbRead);
      if(rc != 0){
         cout<<"Error al abrir el archivo" <<endl;
      }
   }
   rc = DosClose(handleArchivo);
   if(rc != 0){
      cout<<"Error al cerrar el archivo" <<endl;
   }
   this->pDatos = retorno;
}

void WiconMgr::winIniIcon() throw (IconError){
  PBYTE offset;
  PBYTE pData;
  PBYTE pIDEref;
  IconDir *picondir = new IconDir();
  picondir->setIdReserved((USHORT)*this->pDatos);
  picondir->setIdType((USHORT)*(pDatos+sizeof(USHORT)));
  if(picondir->getIdReserved() != 0 || picondir->getIdType() != 1){
      IconError error;
      error.function = "winIniIcon";
      error.file = __FILE__;
      error.line = __LINE__;
      error.msg = "Error, the file is not a Windows icon";
      throw error;
  }
  picondir->setIdCount((USHORT)*(pDatos+(2*sizeof(USHORT))));
  numImagenes = picondir->getIdCount();
  //Puntero de referencia base a donde comienza la secuencia de estructuras ICONDIRENTRY
  pIDEref = pDatos + 6;
  //Ciclo pricipal para inicializacion de objetos con datos del icono Windows
  for(int i=0;i<numImagenes;i++){
     offset = pIDEref + (i*16);
     IconDirEntry *picondirentry = new IconDirEntry(offset);
     pData = pDatos + picondirentry->getDwImageOffset();
     IconImage *piconimage = new IconImage(pData);
     picondirentry->setImageDta(piconimage);
     picondir->idEntries.insert(picondir->idEntries.end(),picondirentry);
   }
   iconoWindows = picondir;
}


void Os2IconMgr12::grabaIcono(char* nArchivo){
   APIRET rc = 0;
   ULONG bwrote,accion;
   HFILE fileHandle;
   this->llenaOffSets();
   vector<Os2Icon12*>::iterator i = listaImagenes.begin();
   if (listaImagenes.size() == 0){
     printf("No images to save\n");
     exit(0);
   }
   rc = DosOpen(nArchivo,&fileHandle,&accion,0L,FILE_NORMAL,OPEN_ACTION_CREATE_IF_NEW,OPEN_SHARE_DENYNONE|OPEN_ACCESS_WRITEONLY,0L);
   if(rc!=0){
      printf("Error al crear el archivo para guardar el icono\n");
      exit(0);
   }
   else{
      while(i != listaImagenes.end()){
         if(getNumImages() > 1){
            rc = DosWrite(fileHandle,(*i)->getPArray(),sizeof(BITMAPARRAYFILEHEADER),&bwrote);
            if(rc!=0)
               printf("Error al escribir el encabezado de la imagen XOR-AND\n");
         }
         else{
            rc = DosWrite(fileHandle,&((*i)->getPArray()->bfh),sizeof(BITMAPFILEHEADER),&bwrote);
            if(rc!=0)
               printf("Error al escribir el encabezado de la imagen XOR-AND\n");
         }
         rc = DosWrite(fileHandle,(*i)->getPPaletaBW(0),sizeof(RGB)*2,&bwrote);
         if(rc!=0)
            printf("Error al grabar la paleta BN\n");
         rc = DosWrite(fileHandle,(*i)->getPHead(),sizeof(BITMAPFILEHEADER),&bwrote);
         if(rc!=0)
            printf("Error al grabar el encabezado del la imagen color\n");
         if((*i)->getBitsXPixel() != 24 && (*i)->getBitsXPixel() != 32){
            rc = DosWrite(fileHandle,(*i)->getPPaletaColor(),(*i)->sizePaleta(),&bwrote);
            if(rc!=0)
               printf("Error al grabar la paleta de la imagen color\n");
         }
         i++;
      }
      i = listaImagenes.begin();
      while(i != listaImagenes.end()){
         printf("Writing %dx%dx%d image...\n",
                (*i)->getAncho(), (*i)->getAlto(), (*i)->getBitsXPixel());

         rc = DosWrite(fileHandle,(*i)->getMaskData(),((*i)->getMaskSize()*2),&bwrote);
         if(rc!=0)
            printf("Error al grabar los datos de la mascara\n");
         rc = DosWrite(fileHandle,(*i)->getDataImage(),(*i)->getSizeImage(),&bwrote);
         if(rc!=0)
            printf("Error al grabar los datos de la imagen\n");
         i++;
      }
   }
   DosClose(fileHandle);
   freeIconMem();
}

void Os2IconMgr12::grabaImagenHeader(int i, char* nArchivo){
   APIRET rc = 0;
   ULONG bwrote,accion;
   HFILE fileHandle;
   vector<Os2Icon12*>::iterator j = listaImagenes.begin();
   rc = DosOpen(nArchivo,&fileHandle,&accion,0L,FILE_NORMAL,OPEN_ACTION_CREATE_IF_NEW,OPEN_SHARE_DENYNONE|OPEN_ACCESS_WRITEONLY,0L);
   // Avanza el puntero hasta la imagen que se desea grabar
   for(int index=0;index < i && index < getNumImages(); index++){
      j++;
   }
   if(getNumImages() > 1){
      rc = DosWrite(fileHandle,(*j)->getPArray(),sizeof(BITMAPARRAYFILEHEADER),&bwrote);
      if(rc!=0)
         printf("Error al escribir el encabezado de la imagen XOR-AND\n");
   }
   else{
      rc = DosWrite(fileHandle,&((*j)->getPArray()->bfh),sizeof(BITMAPFILEHEADER),&bwrote);
      if(rc!=0)
         printf("Error al escribir el encabezado de la imagen XOR-AND\n");
   }
   rc = DosWrite(fileHandle,(*j)->getPPaletaBW(0),sizeof(RGB)*2,&bwrote);
   if(rc!=0)
      printf("Error al grabar la paleta BN\n");
   rc = DosWrite(fileHandle,(*j)->getPHead(),sizeof(BITMAPFILEHEADER),&bwrote);
   if(rc!=0)
      printf("Error al grabar el encabezado del la imagen color\n");
   rc = DosWrite(fileHandle,(*j)->getPPaletaColor(),(*j)->sizePaleta(),&bwrote);
   if(rc!=0)
      printf("Error al grabar la paleta de la imagen color\n");

}

void Os2IconMgr12::grabaImagenData(int i, char* nArchivo){
   APIRET rc = 0;
   ULONG bwrote,accion;
   HFILE fileHandle;
   vector<Os2Icon12*>::iterator j = listaImagenes.begin();
   rc = DosOpen(nArchivo,&fileHandle,&accion,0L,FILE_NORMAL,OPEN_ACTION_CREATE_IF_NEW,OPEN_SHARE_DENYNONE|OPEN_ACCESS_WRITEONLY,0L);
   // Avanza el puntero hasta la imagen que se desea grabar
   for(int index=0;index < i && index < getNumImages(); index++){
      j++;
   }
   // Graba los datos de la imagen
   rc = DosWrite(fileHandle,(*j)->getMaskData(),((*j)->getMaskSize()*2),&bwrote);
   if(rc!=0)
      printf("Error al grabar los datos de la mascara\n");
   rc = DosWrite(fileHandle,(*j)->getDataImage(),(*j)->getSizeImage(),&bwrote);
   if(rc!=0)
      printf("Error al grabar los datos de la imagen\n");
}

void Os2IconMgr12::cargaIcono(){
}

int Os2IconMgr12::freeIconMem(){
   vector<Os2Icon12*>::iterator i = listaImagenes.begin();
   while(i != listaImagenes.end()){
      free(*i);
      i++;
   }
   return 0;
}

ULONG Os2IconMgr12::sizeAllPaletas(){
   ULONG acumula = 0;
   vector<Os2Icon12*>::iterator i = listaImagenes.begin();
   while(i != listaImagenes.end()){
      acumula = acumula + (*i)->sizePaleta();
      i++;
   }
   return acumula;
}

void Os2IconMgr12::addImage(Os2Icon12 *warpIcon){
   listaImagenes.insert(listaImagenes.end(), warpIcon);
}

ULONG Os2IconMgr12::firstOffSet(){
   int n1;
   int n2 = sizeof(BITMAPFILEHEADER);
   int n3 = sizeof(RGB);
   int nimages = listaImagenes.size();
   ULONG totPaleta = sizeAllPaletas();
   ULONG retorno;
   if(nimages == 1)
      n1 = sizeof(BITMAPFILEHEADER);
   else
      n1 = sizeof(BITMAPARRAYFILEHEADER);
   retorno = nimages*(n1+n2+(n3*2)) + totPaleta;
   return retorno;
}

void Os2IconMgr12::llenaOffSets(){
   vector<Os2Icon12*>::iterator i = listaImagenes.begin();
   int ant = 0;
   int acuNext = 0;
   int base = firstOffSet();
   int j = listaImagenes.size();
   int cont = 0;
   while(i != listaImagenes.end()){
      if(cont == j-1)
         (*i)->getPArray()->offNext = 0;
      else{
         (*i)->getPArray()->offNext = acuNext + (*i)->getSizePicture();
         acuNext = (*i)->getPArray()->offNext;
      }
      (*i)->getPArray()->bfh.offBits = base;
      (*i)->getIbih()->setIBIH(&((*i)->getPArray()->bfh.bmp));
      ant = (*i)->getMaskSize() * 2;
      (*i)->getPHead()->offBits = base + ant;
      (*i)->getIbih()->setIBIH(&((*i)->getPHead()->bmp));
      ant = ant + (*i)->getSizeImage();
      base = base + ant;
      cont++;
      i++;
   }
}

Os2Icon12* Os2IconMgr12::creaGrande(Os2Icon12 *warpIcon){
   RGB *paletaBW;
   BITMAPFILEHEADER *pBfhAux = new BITMAPFILEHEADER;
   BITMAPARRAYFILEHEADER *pArrayAux = new BITMAPARRAYFILEHEADER;
   Os2Icon12 *granWarpIcon = new Os2Icon12();
   paletaBW = (RGB*)malloc(sizeof(RGB)*2);
   paletaBW = warpIcon->getPPaletaBW(0);
   granWarpIcon->setNumBitsColores(warpIcon->getNumBitsColores());
   //EL array no cambia si se trata de una imagen de 16 o 32
   granWarpIcon->setPArray(warpIcon->getPArray());
   *pBfhAux = *warpIcon->getPHead();
   *pArrayAux = *granWarpIcon->getPArray();
   //Si se trata de una imagen de 16x16 seteo los encabezados de las
   //estructuras con los de una imagen de 20x20 y configuro los datos
   //para los nuevos tama¤os
   if(warpIcon->getAlto() == 16){
      //Inicializa los valores de la cabezera de la imagen en colores
      pBfhAux->usType = BFT_COLORICON;
      pBfhAux->cbSize =  sizeof(BITMAPFILEHEADER);
      pBfhAux->xHotspot = 10;
      pBfhAux->yHotspot = 10;
      pBfhAux->offBits = 0;
      pBfhAux->bmp.cbFix =  sizeof(BITMAPINFOHEADER);
      pBfhAux->bmp.cx = 20;
      pBfhAux->bmp.cy = 20;
      pBfhAux->bmp.cBitCount = warpIcon->getNumBitsColores();
      granWarpIcon->ibih->setIBIH(&pBfhAux->bmp);
      //Inicializa la cabezera para la imagen en blanco y negro incluyendo el encabezado para multiples imagenes
      pArrayAux->bfh.xHotspot = 10;
      pArrayAux->bfh.yHotspot = 10;
      pArrayAux->bfh.bmp.cx   = 20;
      pArrayAux->bfh.bmp.cy   = 40;
      granWarpIcon->Mibih->setIBIH(&pArrayAux->bfh.bmp);
      granWarpIcon->setMaskData(centerMaskData(warpIcon->getMaskData(),ICONO_20X20));
      granWarpIcon->setDataImage(centerImageData(warpIcon->getDataImage(),ICONO_20X20, warpIcon->getNumBitsColores()));
   }
   //Si se trata de una imagen de 32x32
   else if(warpIcon->getAlto() == 32){
      pBfhAux->xHotspot = 20;
      pBfhAux->yHotspot = 20;
      pBfhAux->bmp.cx = 40;
      pBfhAux->bmp.cy = 40;
      pBfhAux->bmp.cBitCount = warpIcon->getNumBitsColores();
      granWarpIcon->ibih->setIBIH(&pBfhAux->bmp);
      pArrayAux->bfh.xHotspot = 20;
      pArrayAux->bfh.yHotspot = 20;
      pArrayAux->bfh.bmp.cx   = 40;
      pArrayAux->bfh.bmp.cy   = 80;
      granWarpIcon->Mibih->setIBIH(&pArrayAux->bfh.bmp);
      granWarpIcon->setMaskData(centerMaskData(warpIcon->getMaskData(),ICONO_40X40));
      granWarpIcon->setDataImage(centerImageData(warpIcon->getDataImage(),ICONO_40X40, warpIcon->getNumBitsColores()));
   }
   //Asigna los valores a las variables de instancia
   granWarpIcon->setPHead(pBfhAux);
   granWarpIcon->setPArray(pArrayAux);
   granWarpIcon->setPaletaBW(paletaBW);
   granWarpIcon->setPPaletaColor(warpIcon->getPPaletaColor());
   return granWarpIcon;
}

void Os2IconMgr12::addImageGrande(Os2Icon12 *warpIconIn){
   Os2Icon12 *granImagen = this->creaGrande(warpIconIn);
   //Agrego la imagen a la lista
   this->addImage(granImagen);
}

void Os2IconMgr12::setNumImages(){
   numImages = listaImagenes.size();
}

PBYTE Os2IconMgr::centerMaskData(PBYTE data, const int tamanio){
   int delta,i,j,largoScan,smallSize;
   PBYTE scanor;
   PBYTE scands;
   PBYTE scanax;
   PBYTE scandsX;
   PBYTE retorno;
   BYTE aux1 = 0;
   BYTE aux2;
   if(tamanio == ICONO_20X20){
      delta = 2;
      retorno = (PBYTE)malloc(80);
      memset(retorno,255,80);
      scanor = (PBYTE)malloc(4);
      scands = (PBYTE)malloc(4);
      scanor = (PBYTE)data+64;
      smallSize = 16;
      aux2 = 192;
   }
   else if(tamanio == ICONO_40X40){
      delta = 4;
      retorno = (PBYTE)malloc(320);
      memset(retorno,255,320);
      scanor = (PBYTE)malloc(4);
      scanax = (PBYTE)malloc(4);
      scands = (PBYTE)malloc(8);
      scanor = (PBYTE)data+128;
      smallSize = 32;
      aux2=240;
   }
   largoScan = delta * 2;
   scands = retorno + largoScan * delta;
   i = 0;
   j=0;
   while(i < smallSize){
      memcpy(scands, scanor, 4);
      scandsX = scands;
      if(tamanio == ICONO_40X40){
         while(j<5){
            aux1 = *scandsX & 15;
            *scandsX = (*scandsX >> 4) & 15;
            *scandsX = *scandsX | aux2;
            aux2 = (aux1 << 4) & 240;
            scandsX++;
            j++;
         }
         j=0;
         aux1=0;
         aux2=240;
         scandsX--;
         *scandsX = *scandsX | 15;
      }
      else{
         while(j<3){
            aux1 = *scandsX & 3;
            *scandsX = (*scandsX >> 2) & 63;
            *scandsX = *scandsX | aux2;
            aux2 = (aux1 << 6) & 192;
            scandsX++;
            j++;
         }
         j=0;
         aux1=0;
         aux2=192;
         scandsX--;
         *scandsX = *scandsX | 63;
      }
      scands = scands + largoScan;
      scanor = scanor + 4;
      i++;
   }
   return retorno;
}

PBYTE Os2IconMgr::centerImageData(PBYTE data, const int tamanio, int bits){
   int delta,i,largoScan,largoScanOr,ppc,numScans;
   PBYTE scanor;
   PBYTE scands;
   PBYTE retorno;
   if(bits==24 || bits==32)
      ppc=bits/8;
   else
      ppc=1;
   if(tamanio == ICONO_20X20){
      delta = 2;
      numScans=16;
      largoScan = 20*ppc;
      largoScanOr = 16*ppc;
      retorno = (PBYTE)malloc(400*ppc);
      // El color de fondo es el mismo del primer dato (si no fuera fondo, la imagen saldra corrupta)
      memset(retorno,*data,400*ppc);
   }
   else if(tamanio == ICONO_40X40){
      delta = 4;
      numScans=32;
      largoScan = 40*ppc;
      largoScanOr = 32*ppc;
      retorno = (PBYTE)malloc(1600*ppc);
      // El color de fondo es el mismo del primer dato (si no fuera fondo, la imagen saldra corrupta)
      memset(retorno,*data,1600*ppc);
   }
   scands = retorno + largoScan * delta;
   scanor = data;
   i=0;
   while(i < numScans){
      scands = scands + delta*ppc;
      memcpy(scands,scanor,largoScanOr);
      scands = scands + delta*ppc + largoScanOr;
      scanor = scanor + largoScanOr;
      i++;
   }
   return retorno;
}
