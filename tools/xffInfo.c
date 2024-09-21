#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>



#include "commonDataTypes.h"
#include "systemFuncs.c"
#include "flInfoPrint.c"

#include "xffType.h"
#include "fl_xffType.h"
#include "xffFuncs.c"


int main(int argc, char *argv[]) {
   infoConsNoVisible = 1; //printing everything to console makes it very slow for big files.

   if (argc != 2) {
      printf("\n ERR: A single argument with the name of the file is necessary. ");
      goto errExit;
   }
      
   #define xffFlNm argv[1]
   
   FILE *xffFlPt, *infoFlPt;
   int i, j, k;
   //char nmStr[256] = {0};
   char nmStr[0x1000] = {0};

   xffFlPt = fopen(xffFlNm, "rb");
   if (xffFlPt == NULL) {
      printf("\n ERR: Failed to open for raeding NMO >%s< \n", xffFlNm);
      goto errExit;
   }
   
   i = 0;
   #if DONT_MAKE_INFOFL == 0
   sprintf(nmStr, "%s.xff_spec.txt", xffFlNm);
   infoFlPt = fopen(nmStr, "rb");
   while (infoFlPt != NULL) {
      fclose(infoFlPt);
      i++;
      if (i > 99) {
         printf("\n ERR: Failed to find free INFO file name %s \n", nmStr);
         goto errExit2;
      }
      sprintf(nmStr, "%s_%02d.spec.txt", xffFlNm, i);
      infoFlPt = fopen(nmStr, "rb");
   }
   infoFlPt = fopen(nmStr, "wb");   
   if (infoFlPt == NULL) {
      printf("\n ERR: Failed to open for writing INFO file %s \n", nmStr);
      goto errExit2;
   }

  #endif


  xffShowInfoSv(xffFlPt, infoFlPt);  
  

  //goto normExit;

   errExit3:
   #if DONT_MAKE_INFOFL == 0
   fclose(infoFlPt); 
   #endif
   errExit2:
   fclose(xffFlPt);        
   errExit:
   
   printf("\n Completed. ");   
   system("PAUSE");
  //normExit:
 	
  return 0;
}
