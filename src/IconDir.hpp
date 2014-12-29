#ifndef ICON_DIR_HPP
#define ICON_DIR_HPP

#include "IconDirEntry.hpp"

class IconDir{

   USHORT   idReserved;
   USHORT   idType;
   USHORT   idCount;

   public:

      //Constructor

      IconDir(){
         idReserved = 0;
         idType     = 0;
         idCount    = 0;
         }

      //Getters

      USHORT getIdReserved(){
         return idReserved;
      }
      USHORT getIdType(){
         return idType;
      }
      USHORT getIdCount(){
         return idCount;
      }
      std::vector<IconDirEntry*> getIdEntries(){
         return idEntries;
      }

      //Setters

      void setIdReserved(USHORT valor){
         idReserved = valor;
         }
      void setIdType(USHORT valor){
         idType = valor;
         }
      void setIdCount(USHORT valor){
         idCount = valor;
         }

      std::vector<IconDirEntry*> idEntries;

};

#endif
