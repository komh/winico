class RgbQuad{

   BYTE  red;
   BYTE  green;
   BYTE  blue;
   BYTE  reserved;

   public:

   //Constructor

      RgbQuad(){
         red   = 0;
         green = 0;
         blue  = 0;
         reserved = 0;
         }

   //Getters

      BYTE getRed(){
         return red;
      }
      BYTE getGreen(){
         return green;
      }
      BYTE getBlue(){
         return blue;
      }
      BYTE getReserved(){
         return reserved;
      }
};