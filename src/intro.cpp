#define INCL_GPI
#define INCL_DOSERRORS
#include <os2.h>

#include <iostream>

#include "Icon.hpp"
#include "IconMgr.hpp"

using namespace std;

// forward declaration
int checkType(char *archivo);
void error_exit(int errorcode);

void printError(IconError& error){
   cout << " " << error.function << endl << " " << error.file << '(' << error.line << ')'
   << endl << " \"" << error.msg << "\"" << endl;
}

int unoAuno(char *archivoin, char *archivout){
   try{
      if(checkType(archivoin)==1){
         WiconMgr *windowMgr = new WiconMgr();
         windowMgr->cargaIcono(archivoin);
         windowMgr->winIniIcon();
         Os2IconMgr12  *warpMgr = windowMgr->codecOs2Icon12();
         warpMgr->grabaIcono(archivout);
         cout<< "Icon converted"<<endl;
      }
      else
         error_exit(-7);
      }
   catch(IconError e){
      printError(e);
   }
   return 0;
}
/************************************************************************************************************/


int todosIco(char *nuevoDir){
HDIR dirhandle=HDIR_SYSTEM;
FILEFINDBUF3 findbuffer={0};
ULONG relargobuf=sizeof(FILEFINDBUF3);
ULONG fcontador=1;
APIRET rc=0;
ULONG numDrive = 0;
ULONG largoDir = 0;
BYTE dirActual[256] = "";
CHAR dirNew[256] = "";
PEAOP2 pEABuf = NULL;

   try{
      largoDir = (ULONG)sizeof(dirActual);
      rc=DosQueryCurrentDir(numDrive, dirActual, &largoDir);
      if(rc!=0)
         error_exit(-3);

      pEABuf = NULL;
      strcpy(dirNew,nuevoDir);

      rc=DosCreateDir(dirNew, pEABuf);
      if(rc!=0)
         error_exit(-4);

      rc=DosFindFirst("*.ico",&dirhandle,FILE_NORMAL,&findbuffer,relargobuf,&fcontador,FIL_STANDARD);
      if(rc!=0)
         error_exit(-5);

      else{
         WiconMgr *windowMgr = new WiconMgr();
         windowMgr->cargaIcono(findbuffer.achName);
         windowMgr->winIniIcon();
         Os2IconMgr12  *warpMgr = windowMgr->codecOs2Icon12();

         rc=DosSetCurrentDir(dirNew);
         if(rc!=0)
            error_exit(-6);

         warpMgr->grabaIcono(findbuffer.achName);

         rc=DosSetCurrentDir("..");
         if(rc!=0)
            error_exit(-6);
      }


      while(rc!=18){
         fcontador=1;
         rc=DosFindNext(dirhandle,&findbuffer,relargobuf,&fcontador);
         if(rc!=18){
            WiconMgr *windowMgr = new WiconMgr();
            windowMgr->cargaIcono(findbuffer.achName);
            windowMgr->winIniIcon();
            Os2IconMgr12  *warpMgr = windowMgr->codecOs2Icon12();

            rc=DosSetCurrentDir(dirNew);
            if(rc!=0)
               error_exit(-6);

            warpMgr->grabaIcono(findbuffer.achName);

            rc=DosSetCurrentDir("..");
            if(rc!=0)
               error_exit(-6);
         }
      }
   }
   catch(IconError& error){
      printError(error);
   }
   return 0;
}

/*********************************************************************************************/

int checkType(char *archivo){
   int largo = strlen(archivo);
   char *ext = "ico";
   char ver[3+1];
   int i=largo-1;
   while(i >=0){
      if(archivo[i] == '.' && i + 3 < largo){
         ver[0] = archivo[i+1];
         ver[1] = archivo[i+2];
         ver[2] = archivo[i+3];
         ver[3] = '\0';
         break;
      }
      i--;
   }
   if((strcmp(ext,ver)!=0) || (i < 0))
      return -1;
   else
      return 1;
}

void error_exit(int errorcode){
   switch(errorcode){
      case -1:
         printf("Usage: WINICO Winfilename OS2filename\n");
         printf("       WINICO [-d] dirname\n");
         break;
      case -2:
         printf("DosOpen error\n");
         break;
      case -3:
         printf("DosQueryCurrentDir error\n");
         break;
      case -4:
         printf("DosCreateDir error\n");
         break;
      case -5:
         printf("DosFindFirst error\n");
         break;
      case -6:
         printf("DosSetCurrentDir error\n");
         break;
      case -7:
         printf("Wrong file format\n");
         break;
      default:
         exit(errorcode);
   }
   exit(0);
}

