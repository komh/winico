#include <iostream>
#include <fstream>

// declared in intro.cpp
int unoAuno(char *archivoin, char *archivout);
int todosIco(char *nuevoDir);
void error_exit(int errorcode);

int main(int argc, char *argv[]){
int retorno,i;
int flag = 0;
   if(argc == 3){
      for(i=0;i<argc;i++){
         if(!strnicmp(argv[i],"-d",2)){
            retorno = todosIco(argv[2]);
            flag = 1;
         }
      }
      if(flag == 0)
         retorno = unoAuno(argv[1],argv[2]);
   }
   else
      error_exit(-1);
   return 0;
}
