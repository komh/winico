#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

class IconMgr{
   public:
      virtual void grabaIcono() = 0;
      virtual void cargaIcono() = 0;
   private:
      int identidad;
};


class WiconMgr:public IconMgr{
   public:
      WiconMgr(){
         pDatos = NULL;
         numImagenes = 0;
         iconoWindows = NULL;
      };
      void grabaIcono(){};      void cargaIcono(){};
      void grabaIcono(char* nombre);
      void cargaIcono(char* nombre) throw (IconError);
      void winIniIcon() throw (IconError);
      Os2IconMgr12* codecOs2Icon12();
   private:
      //Pointer to icon's data
      PBYTE pDatos;
      USHORT numImagenes;
      IconDir *iconoWindows;
};


class Os2IconMgr:public IconMgr{
   public:
      Os2IconMgr(){
         listaiconos = NULL;
      }
      void grabaIcono(){};
      void cargaIcono(){};
      int getNumImages(){return numImages;};
   protected:
      void llenaOffSets();
      int freeIconMem();
      ULONG sizeAllPaletas();
      ULONG firstOffSet();
      PBYTE centerMaskData(PBYTE data, const int tamanio);
      PBYTE centerImageData(PBYTE data, const int tamanio, int bits);
      int numImages;
   private:
      vector<Os2Icon> *listaiconos;
};

class Os2IconMgr12:public Os2IconMgr{
   public:
      Os2IconMgr12(){
      };
      void grabaIcono(char* nArchivo);
      void grabaImagenHeader(int i, char* nArchivo);
      void grabaImagenData(int i, char* nArchivo);
      void cargaIcono();
      void addImage(Os2Icon12 *warpIcon);
      void addImageGrande(Os2Icon12 *warpIconIn);
      void setNumImages();

   private:
      Os2Icon12* creaGrande(Os2Icon12 *warpIcon);
      int idIconMgr12;
      int freeIconMem();
      void llenaOffSets();
      ULONG sizeAllPaletas();
      ULONG firstOffSet();
      vector<Os2Icon12*> listaImagenes;
};

class Os2IconMgr20:public Os2IconMgr{
   public:
      Os2IconMgr20(){};
      void grabaIcono();
      void cargaIcono();
      ULONG sizeAllPaletas();
      ULONG firstOffSet();
      void llenaOffSets();
   private:
      vector<Os2Icon20> *listaiconos;
      int freeIconMem();
};

