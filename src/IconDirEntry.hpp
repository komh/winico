class IconDirEntry{
   BYTE  bWidth;
   BYTE  bHeight;
   BYTE  bColorCount;
   BYTE  bReserved;
   USHORT   wPlanes;
   USHORT   wBinCount;
   ULONG dwBytesInRes;
   ULONG dwImageOffset;
   IconImage *datosImagen;

   public:

      //Constructor

      IconDirEntry(){
         bWidth      = 0;
         bHeight     = 0;
         bColorCount = 0;
         bReserved   = 0;
         wPlanes     = 0;
         wBinCount   = 0;
         dwBytesInRes= 0;
         dwImageOffset=0;
         }

      IconDirEntry(PBYTE pValores){
         bWidth         = (BYTE)*pValores;
         bHeight        = (BYTE)*(pValores+1);
         bColorCount    = (BYTE)*(pValores+2);
         bReserved      = (BYTE)*(pValores+3);
         wPlanes        = *((USHORT *)(pValores+4));
         wBinCount      = *((USHORT *)(pValores+6));
         dwBytesInRes   = *((ULONG *)(pValores+8));
         dwImageOffset  = *((ULONG *)(pValores+12));
      }


      //Setters
      void setImageDta(IconImage *objeto){
         datosImagen = objeto;
      }

      //Getters

      BYTE getBWidth(){
         return bWidth;
      }
      ULONG getDwImageOffset(){
         return dwImageOffset;
      }
      IconImage *getIconImage(){
         return datosImagen;
      }
   };
