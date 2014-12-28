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
      vector<IconDirEntry*> getIdEntries(){
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

      vector<IconDirEntry*> idEntries;

};
