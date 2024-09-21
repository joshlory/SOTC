
FILE *infoFlPtGl = NULL;

int infoConsNoVisible = 0;

#define inPrintf infoPrintf

void infoPrintf(const char *format, ...)
{
	char tmpStrBuf[0x1000];
    va_list args;
    va_start(args, format);

    vsprintf(tmpStrBuf, format, args);

    va_end(args);

	if (infoConsNoVisible == 0) printf("%s", tmpStrBuf);
	if (infoFlPtGl != NULL) {
	   fwrite(tmpStrBuf, 1, strlen(tmpStrBuf), infoFlPtGl);
	}
}


void printBuf(void *bufIn, int count, int width) { //width is in bytes: 1 / 2 / 4
   int i;
   unsigned char *buf = bufIn;
   //With little-endiab byte-odering!
   inPrintf("\n");
   if ((width != 1) && (width != 2) && (width != 4)) {
      inPrintf("\n ERR: bad width %d \n", width); 
      return;  
   }
   if (((u32)buf & (width-1)) != 0) {
      inPrintf("\n ERR: Print of unalligned buf %08X , width = %d ", (u32)buf, width); 
      //(u32)buf = (u32)buf & (~3);  
   }
   
   for (i=0; i<count; i+=width) {
      if ((i % 0x10) == 0) inPrintf("\n %04X : ", i);
      if ((i % 0x8) == 0) inPrintf("  ");
      if (width == 1) {
         inPrintf(" %02X%02X %02X%02X", buf[i+0], buf[i+1], buf[i+2], buf[i+3]); 
         i+=3;
      } else if (width == 2) {
         inPrintf(" %02X%02X ", buf[i+1], buf[i]);
      } else {
        inPrintf(" %02X%02X%02X%02X ", buf[i+3], buf[i+2], buf[i+1], buf[i]);
      }
   }
   inPrintf("\n");   
   return;
}


char prtHexByte2Char(u8 b) {
	char c = b;
	if (b < ' ') c = '.';
	else if (b > '~') c = '.';
	return c;
}

//print data as in hex editor; no alignment; 0x10 bytes on a line
void prtHexBuf(u32 addr, void *bufIn, int count) {
   int i, j;
   u8 *b = bufIn;
   for (i=0; i<count; i++) {
      if ((i % 0x10) == 0) inPrintf("\n %08X  %04X: ", addr+i, i);
      if ((i % 0x8) == 0) inPrintf("  ");
		inPrintf(" %02X", b[i]); 
		if ((i & 0xF) == 0xF) {
			inPrintf("   | "); 
			for (j=0; j<0x10; j++) {
				inPrintf("%c", prtHexByte2Char(b[(i&(~0xF)) +j])); 			
			}
			inPrintf(" |"); 
		}
   }
	int c = count & 0xF;
	if (c != 0) {
		for (i=0; i<(0x10-c); i++) inPrintf("   "); 
		inPrintf("   | "); 
		for (j=0; j<c; j++) {
			inPrintf("%c", prtHexByte2Char(b[(count&(~0xF)) +j])); 			
		}
		for (i=0; i<(0x10-c); i++) inPrintf(" "); 
			inPrintf(" |"); 
	}

   inPrintf("\n");   
   return;  
}


