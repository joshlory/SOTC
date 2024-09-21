

//The folowing is modified to match "xff\0"-files, rather than "XFF2" files!:
      
struct t_xff0Hdr {
   unsigned char ident[4];    //00  "xff\0"  /   "xff2"
   unsigned int unk04;        //04   0   type, machine ? - never read   //File can contain multiple XFF headers for Tab7 (relocation stuff)   
   unsigned int nextHdr;    	//08   0   Pointer to another XFF header with Tab7 within file 

//Number of special sections = type+1; if type=0 => numOfSpecialSect=2
//used by strHash sub_1B4498
//if !=0 => typeProc = type+1 ; else typeProc = type(=0)+2
//special entries in the beginning of symTab??
// if ((SymTabNrEnt - (typeProc + tab20NrEnt)) == 0) some entry of communication struct is written
// else SymTabNrEnt = (SymTabNrEnt - (typeProc + tab20NrEnt))
// those are the first special entries in symTab
// This is "numberOfSpecialSect - 1" - this number does not include the zero at the start of SymTab!

   unsigned int SpecSectNr;	//0C   6=exe; 9=script/text? 0xF (iosKernel = ?) //type;
    // =0 in file
    
   //10 writen by DecodeSection_sub_100278 
   unsigned int entry;        //10   entry point function addr. Written on load, before that is =0
   //(about the following:) +0x00010000 ??
   unsigned int flSz; //stackRel;     //14  MAY ALSO BE "NEXT FILE START" Stack relative to start of file addr. (points right after the end of file) XXXX NOT: section header table offset from beginning of file
   // =0 in file
   //18 written by RelocateElfInfoHeader_sub_1004b8
   unsigned int stackAbs;     //18   MAY ALSO BE "NEXT FILE START" Stack absolute addr. (=0 before load) XXXX NOT: absolute section header offset in memory (before loading = 0)

   unsigned int expSymTabNrE; //1C   size of the following table [words] = [entries]   
   //vvvv +0x40010000   
   //20 The unk20Tab should be multiplied by 16 and added to symTab
   // (symTab + unk20EntryValue*16) are local entries for which to compute string hash value?? 
   //This table might specify whether to hash a name so that it can be linked - otherwise it will remain local.
   //in short - it specifies which funcs are exported (unk20EntValue *16 + symTab).
   //Number of each entry (1 word) in symTab, for the name string of which, 
   //hash will be computed for it to be externally exported.
	//Holds Exported and Imported symbols! 
	//Only simbols that are exclusively for internal use are not in this table! 

//WARNING: ABOVE IS INCORRECT: THIS IS TABLE OF UNEXPORTED SYMBOLS! Symbols with "sect"field (wrong name?) = 1 are exported, while those with 0 are not!
//this is more-of-a table of "internally-used symbols" 
//Table (only) of imported symbols.  Symbols with indexes in this table are not visible to external modules (if they originate from this module), and are visible to this module (only). 
//The remaining symbols (from symTab) are visible to external modules (if created by this module), but if among them there is an external function, it will not be visible for this module. 
//In the current implementation, the symbols of this table are those with "sect" == 0. 
 
   unsigned int expSymTab;    //20   growing numbers - 7, 8, 9, 0xC, 0xF, .. some are skipped

   unsigned int symTabNrE;    //24   size of the Symbol table [entries] (1 entry = 4 words = 16 bytes)    
   //vvvv +0x40010000 
   //handled (also) by RelocateSelfSymbol_sub_1018b8
   unsigned int SymTab;       //28   Symbol table offset (before loading = from start of file), after load = absolute 
   //vvvv +0x40010000 
   unsigned int SymTabStr;    //2C   Strings used by the entries in the Symbol Table
   //vvvv +0x40010000 
   unsigned int SectTab;      //30   Section header table? - "xff2-table" - see below 
   //vvvv +0x40010000 
   unsigned int symRelTab;    //34   Relative addr. of each entry in symTab based on (offset from the start) its section. some table of strange values - mostly middle numbers 
   unsigned int RelTabNrE;  	//38   Size in entries of the Relocation Table (contains 7-word structs, each of which points to two tables - foer addr and instr.
   //vvvv +0x40010000 
   //3C Tab7 seems to hold structs which specify how to relocated code
   //Handles (also) by RelocateCode_sub_1016e8
	//
   unsigned int relocTab;    	//3C   some table headers ... see "7-entry table"   "Tab7"  
   unsigned int SectNrE;    	//40   Number of Sections (entries)  //ssNameSz;  Special Sections Names Table Size [entries] - The zero section included.
   //vvvv +0x40010000  
//AKA xSectStrPnt_t
   unsigned int ssNamePt;     //44   Special Sections Names Table offsets (from the following word) 
   //vvvv +0x40010000 
   unsigned int ssNameBs;     //48   Base addr. for the special sections' strings (names)
   
   //from here relative to the start of file offseys start:
   unsigned int entry_Rel;       //4C  relative offset in code section of extry point function
   unsigned int expSymTab_Rel;   //50
   unsigned int SymTab_Rel;      //54
   unsigned int SymTabStr_Rel;   //58
   unsigned int SectTab_Rel;     //5C
   unsigned int symRelTab_Rel;   //60
   unsigned int relocTab_Rel;   	//64
   unsigned int ssNamePt_Rel;    //68
   unsigned int ssNameBs_Rel;    //6C
};




int xffFindSectNrByName(char *sectName, void *flBuf, u32 xffSz) {
   int i, j=0, k=0;
   struct xffHdr_t *xffHdr = flBuf;
  
  //Using a fixed buffer (maybe with malloc()), that contains the whole file.
  //Note that with the PS2's RAM limited to 32MB and how XFF files are processed,
  //it is unlikely that there exists an XFF file of more than 10MB... but this is only a speculation.
  
   u32 xffFlStart = (u32)flBuf;
   
   if (xffHdr->stackRel != xffSz) {
      //printf("\n ERR: stackRel = XFF file size  %08X != %08X  XFF file size  \n", xffHdr->stackRel, xffSz);   
      return -3;
   }
   struct xSectStrPnt_t *xSSPnt;
   xSSPnt = (void*)(xffFlStart + xffHdr->ssNamePt_Rel);
   if (xffHdr->ssNamePt_Rel >= xffSz) {
      //printf("\n ERR: ssNamePt outside file %08X >= %08X \n", xffHdr->ssNamePt_Rel, xffSz);   
      return -4;
   }
   //char *xSSNameStr = (void*)(xffFlStart + xffHdr->ssNameBs + xSSPnt[i].offs);
   #define xSSNameStrDirect(x) ((char*)(xffFlStart + xffHdr->ssNameBs_Rel + xSSPnt[(x)].offs))
    for (i=0; i < xffHdr->SectNrE; i++) {
        if ((xffHdr->ssNameBs_Rel + xSSPnt[i].offs) >= xffSz) {
           //printf("\n ERR: ssNameBs+off outside file \n");   
           return -5;
        }
        //if (strncmp(sectName, (char*)(xffHdr->ssNameBs_Rel + *(u32*)(xffBase + xffHdr->ssNamePt_Rel + 4*i)), 100) == 0) {
        if (strncmp(sectName, xSSNameStrDirect(i), 100) == 0) {
           j = i;
           k++;
        }
    }
    if (k > 1) {
       //printf("\n ERR: more than one (%d) section with name >%s< found! \n", k, sectName);
       return -2; //ERR
    } else if (k == 0) {
       //printf("\n No section with name >%s< found. \n", sectName);
       return -1;
    } else {
       //printf("\n Section with name >%s< found at %d . \n", sectName, j);
       return j;
    }
}


int xffGetSectOffsByNr(u32 sectNr, void *flBuf, u32 xffSz, u32 *sectSz) {
   int i, j=0, k=0;
   struct xffHdr_t *xffHdr = flBuf;
   
   //The xffHdr->SpecSectNr should be used the folowing way:
   int tmpNrSect = xffHdr->SpecSectNr;
   if (tmpNrSect == 0) tmpNrSect = 2; //special case for some/all files
   else tmpNrSect++; // Zero section is not included
   
   if (tmpNrSect <= sectNr) { 
      printf("\n ERR: sectNr more than total nrSect 0x%X >= 0x%X \n", sectNr, xffHdr->SpecSectNr);
  //    return -1;      
   }
   
   u32 xffFlStart = (u32)flBuf;
   
   if ((xffHdr->SectTab_Rel + (xffHdr->SpecSectNr * sizeof(struct xSectHdr_t))) >= xffSz) {
      printf("\n ERR: SectHdr outside xff file \n");
      return -2;      
   } //oh, far too many checks...
   struct xSectHdr_t *sectHdr = (void*)(xffFlStart + xffHdr->SectTab_Rel);

   if ((sectHdr[sectNr].addr_Rel + sectHdr[sectNr].size) > xffSz) {
      printf("\n ERR: Section outside xff file relOffs = %08X  sz = %08X  endpos = %08X  flSz = %08X \n",\
      sectHdr[sectNr].addr_Rel, sectHdr[sectNr].size, (sectHdr[sectNr].addr_Rel + sectHdr[sectNr].size), xffSz);
      return -3;      
   }
   *sectSz = sectHdr[sectNr].size;
   return sectHdr[sectNr].addr_Rel; 
}

























/*
xff notes:
    Section numbers in the lowest printed (symbols) table correspond to the way sections 
    are ordered:
    order:             type    
    0 .zero_sect.       0
    1 .rodata           1
    2 .rel.rodata       9
    3 .rela.rodata      4
    4 .sdata            1
    ...
    So when the symTab shows that some symbol is in section 4  
    - this smeant the fourth section in the list = .sdata.
    
*/

int xffShowInfo(FILE* fdIn) {
//   #define INFO_BUF_SZ 0x90000
#define INFO_BUF_SZ 0xA0000
   //unsigned char buf[INFO_BUF_SZ];
   
  	fseek(fdIn, 0, SEEK_END);
	int xffFlSz = ftell(fdIn);
	
	u8 *buf = malloc(xffFlSz);
	if (buf == NULL) { printf("Failed to allocate buffer for XFF sz = %08X .", xffFlSz); goto xffExit; }
	//if (xffFlSz > INFO_BUF_SZ) { printf("XFF too large!"); goto xffExit; }
	fseek(fdIn, 0, SEEK_SET);
   fread(buf, 1, xffFlSz, fdIn);
    
   struct xffHdr_t *xffHdr = (void*)buf;
   
   
   printf("\nunk04=%08X NextHdr=%08X Entry_Rel=%08X Entry=%08X  ImportedSyms=%X  symRel= %X ", \
   xffHdr->unk04, xffHdr->nextHdr, xffHdr->entry_Rel, xffHdr->entry, xffHdr->expSymTabNrE, xffHdr->symRelTab_Rel);
    //         00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
   printf("\n\n    Stack    ImpSym   SymTab   StrTab   SectTab  ReloCTab ShStrPt  ShStrBs "); 
   printf("\nrel %8X %8X %8X %8X %8X %8X %8X %8X ", \
   xffHdr->stackRel, xffHdr->expSymTab_Rel, xffHdr->SymTab_Rel, xffHdr->SymTabStr_Rel, xffHdr->SectTab_Rel, xffHdr->relocTab_Rel, xffHdr->ssNamePt_Rel, xffHdr->ssNameBs_Rel);
   printf("\nabs %8X %8X %8X %8X %8X %8X %8X %8X  ", \
   xffHdr->stackAbs, xffHdr->expSymTab, xffHdr->SymTab, xffHdr->SymTabStr, xffHdr->SectTab, xffHdr->relocTab, xffHdr->ssNamePt, xffHdr->ssNameBs );
         int i, j, k;       
   
        //  printf("%08X %08X %08X ",buf, xffHdr->ssNameBs_Rel, *(u32*)(xffHdr->ssNamePt_Rel + i) ); 
   printf("\nSections= %d  ", xffHdr->SectNrE  ); 

   struct xSectHdr_t *sectHdr = (void*)(buf + xffHdr->SectTab_Rel);
   struct xSectHdr_t *sectHdrP = sectHdr;

      printf("\n\n  memAbs   fileAbs  size     align    type     flags    moved    addrR");

   for (i=0; i<xffHdr->SectNrE; i++) {
  
      printf("\n %X %s ", i, (buf + xffHdr->ssNameBs_Rel + *(u32*)(buf + xffHdr->ssNamePt_Rel + i*4))); 
  //           00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000   
      //printf("\n  memAbs   fileAbs  size     align    type     flags    moved    addrR");
      printf("\n %8X %8X %8X %8X %8X %8X %8X %8X ", \
      sectHdrP->memAddr_Abs, sectHdrP->fileAddr_Abs, sectHdrP->size, sectHdrP->align, sectHdrP->type, sectHdrP->flags, sectHdrP->moved, sectHdrP->addr_Rel);
      sectHdrP++;
   }
   
   struct xRelocEnt_t *relocTab = (void*)(buf + xffHdr->relocTab_Rel);
   struct xRelocEnt_t *relocTabP = relocTab;
   printf("\n\n RelocTab NREnt = %d ", xffHdr->RelTabNrE);
  //           00000000 00000000 00000000 00000000 00000000 00000000 00000000 
   printf("\n RelTabNr type     NrEnt    Sect     addrAbs  InstrAbs AddrRel  InstrRel");
   for (i=0; i<xffHdr->RelTabNrE; i++) { 
      printf("\n %8X %8X %8X %8X %8X %8X %8X %8X ", i, \
      relocTabP->type, relocTabP->nrEnt, relocTabP->sect, relocTabP->addrTyIx, relocTabP->instrTyIx, relocTabP->addrTyIx_Rel, relocTabP->instrTyIx_Rel );    
      relocTabP++;
   }    
 
   relocTabP = relocTab;   
   struct xRelocAddrEnt_t *relocAt;
   struct xRelocInstrEnt_t *relocIt;
   
   for (i=0; i<xffHdr->RelTabNrE; i++) { 
    //  printf("\n %8X %8X %8X %8X %8X %8X %8X ", \
    //  relocTabP->type, relocTabP->nrEnt, relocTabP->sect, relocTabP->addrTyIx, relocTabP->instrTyIx, relocTabP->addrTyIx_Rel, relocTabP->instrTyIx_Rel );    
      relocAt = (void*)(buf + relocTabP->addrTyIx_Rel);
      relocIt = (void*)(buf + relocTabP->instrTyIx_Rel);
      printf("\n RELOC TAB %d : ##################", i);
      //      0000 00000000 00000000  00000000 00000000 00000000 00000000 
      printf("\nNr    addr     tyIx      instr    tyIx");
      for (j=0; j<relocTabP->nrEnt; j++) {
          printf("\n%3X %08X %08X  %08X %08X  ", j, relocAt->addr, relocAt->tyIx, relocIt->instr, relocIt->tyIx );

          relocIt++;
          relocAt++;
      }

      relocTabP++;
   }    

   j=0; int l;
   struct xExpSymEnt_t *symImpTab = (void*)(buf + xffHdr->expSymTab_Rel); //IMPORTED!!!!
   struct xExpSymEnt_t *symImpTabP = symImpTab;
      
   struct xSymEnt_t *SymTab = (void*)(buf + xffHdr->SymTab_Rel);
   struct xSymEnt_t *SymTabP = SymTab;   
   struct xSymRelEnt_t *symRelTab = (void*)(buf + xffHdr->symRelTab_Rel);
   struct xSymRelEnt_t *symRelTabP =  symRelTab;
   
   printf("\n\n SymTab NrEnt= %d  SpecialSect = %d  ", xffHdr->symTabNrE, xffHdr->SpecSectNr );
  //         00000000 00000000 00000000 00000000 00000000 00000000 00000000 
   printf("\n nameOff  addr     size     info     unk0D    sect       Imp");
   for (i=0; i<xffHdr->symTabNrE; i++) {
        
      symImpTabP = symImpTab;    k = 0;
      for (l=0; l< xffHdr->expSymTabNrE; l++) { 
      if (i == symImpTabP->remapNr) { k =1;          
          
         break;
      }
      symImpTabP++;
      }
      
      printf("\n Ix=%x addRel=%08X  >%s< ", i, symRelTabP->addr, (void*)(buf + xffHdr->SymTabStr_Rel + SymTabP->nameOffs)); 
      printf("\n %8X %8X %8X %8X %8X %8X   %d", \
      SymTabP->nameOffs, SymTabP->addr, SymTabP->size, SymTabP->info, SymTabP->unk0D, SymTabP->sect, k);    
      SymTabP++;
      symRelTabP++; 
   }
   
   xffExit: 
free(buf);
  #if AUTOMODE != 1
	//waitUInp();
   //system("PAUSE");          
  #endif   
   return 0;
}






int xffShowInfoSv(FILE* fdIn, FILE *infoFlPt) {

	infoFlPtGl = infoFlPt; //global... a bit hacky...

//   #define INFO_BUF_SZ 0x90000
#define INFO_BUF_SZ 0xA0000
   //unsigned char buf[INFO_BUF_SZ];
   
  	fseek(fdIn, 0, SEEK_END);
	int xffFlSz = ftell(fdIn);
	
	u8 *buf = malloc(xffFlSz);
	if (buf == NULL) { printf("Failed to allocate buffer for XFF sz = %08X .", xffFlSz); goto xffExit; }
	//if (xffFlSz > INFO_BUF_SZ) { inPrintf("XFF too large!"); goto xffExit; }
	fseek(fdIn, 0, SEEK_SET);
   fread(buf, 1, xffFlSz, fdIn);
    
   struct xffHdr_t *xffHdr = (void*)buf;
   
   
   inPrintf("\nunk04=%08X NextHdr=%08X Entry_Rel=%08X Entry=%08X  ImportedSyms=%X  symRel= %X ", \
   xffHdr->unk04, xffHdr->nextHdr, xffHdr->entry_Rel, xffHdr->entry, xffHdr->expSymTabNrE, xffHdr->symRelTab_Rel);
    //         00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
   inPrintf("\n\n    Stack    ImpSym   SymTab   StrTab   SectTab  ReloCTab ShStrPt  ShStrBs "); 
   inPrintf("\nrel %8X %8X %8X %8X %8X %8X %8X %8X ", \
   xffHdr->stackRel, xffHdr->expSymTab_Rel, xffHdr->SymTab_Rel, xffHdr->SymTabStr_Rel, xffHdr->SectTab_Rel, xffHdr->relocTab_Rel, xffHdr->ssNamePt_Rel, xffHdr->ssNameBs_Rel);
   inPrintf("\nabs %8X %8X %8X %8X %8X %8X %8X %8X  ", \
   xffHdr->stackAbs, xffHdr->expSymTab, xffHdr->SymTab, xffHdr->SymTabStr, xffHdr->SectTab, xffHdr->relocTab, xffHdr->ssNamePt, xffHdr->ssNameBs );
         int i, j, k;       
   
        //  inPrintf("%08X %08X %08X ",buf, xffHdr->ssNameBs_Rel, *(u32*)(xffHdr->ssNamePt_Rel + i) ); 
   inPrintf("\nSections= %d  ", xffHdr->SectNrE  ); 

   struct xSectHdr_t *sectHdr = (void*)(buf + xffHdr->SectTab_Rel);
   struct xSectHdr_t *sectHdrP = sectHdr;

      inPrintf("\n\n\n  memAbs   fileAbs  size     align    type     flags    moved    addrR");

   for (i=0; i<xffHdr->SectNrE; i++) {
  
      inPrintf("\n %X %s ", i, (buf + xffHdr->ssNameBs_Rel + *(u32*)(buf + xffHdr->ssNamePt_Rel + i*4))); 
  //           00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000   
      //inPrintf("\n  memAbs   fileAbs  size     align    type     flags    moved    addrR");
      inPrintf("\n %8X %8X %8X %8X %8X %8X %8X %8X ", \
      sectHdrP->memAddr_Abs, sectHdrP->fileAddr_Abs, sectHdrP->size, sectHdrP->align, sectHdrP->type, sectHdrP->flags, sectHdrP->moved, sectHdrP->addr_Rel);
      sectHdrP++;
   }
   
   struct xRelocEnt_t *relocTab = (void*)(buf + xffHdr->relocTab_Rel);
   struct xRelocEnt_t *relocTabP = relocTab;
   inPrintf("\n\n\n RelocTab NREnt = %d ", xffHdr->RelTabNrE);
  //           00000000 00000000 00000000 00000000 00000000 00000000 00000000 
   inPrintf("\n RelTabNr type     NrEnt    Sect     addrAbs  InstrAbs AddrRel  InstrRel");
   for (i=0; i<xffHdr->RelTabNrE; i++) { 
      inPrintf("\n %8X %8X %8X %8X %8X %8X %8X %8X ", i, \
      relocTabP->type, relocTabP->nrEnt, relocTabP->sect, relocTabP->addrTyIx, relocTabP->instrTyIx, relocTabP->addrTyIx_Rel, relocTabP->instrTyIx_Rel );    
      relocTabP++;
   }    
 
   relocTabP = relocTab;   
   struct xRelocAddrEnt_t *relocAt;
   struct xRelocInstrEnt_t *relocIt;
   
   for (i=0; i<xffHdr->RelTabNrE; i++) { 
    //  inPrintf("\n %8X %8X %8X %8X %8X %8X %8X ", \
    //  relocTabP->type, relocTabP->nrEnt, relocTabP->sect, relocTabP->addrTyIx, relocTabP->instrTyIx, relocTabP->addrTyIx_Rel, relocTabP->instrTyIx_Rel );    
      relocAt = (void*)(buf + relocTabP->addrTyIx_Rel);
      relocIt = (void*)(buf + relocTabP->instrTyIx_Rel);
      inPrintf("\n\n RELOC TAB %d : ##################", i);
      //      0000 00000000 00000000  00000000 00000000 00000000 00000000 
      inPrintf("\nNr    addr     tyIx      instr    tyIx");
      for (j=0; j<relocTabP->nrEnt; j++) {
          inPrintf("\n%3X %08X %08X  %08X %08X  ", j, relocAt->addr, relocAt->tyIx, relocIt->instr, relocIt->tyIx );

          relocIt++;
          relocAt++;
      }

      relocTabP++;
   }    

   j=0; int l;
   struct xExpSymEnt_t *symImpTab = (void*)(buf + xffHdr->expSymTab_Rel); //IMPORTED!!!!
   struct xExpSymEnt_t *symImpTabP = symImpTab;
      
   struct xSymEnt_t *SymTab = (void*)(buf + xffHdr->SymTab_Rel);
   struct xSymEnt_t *SymTabP = SymTab;   
   struct xSymRelEnt_t *symRelTab = (void*)(buf + xffHdr->symRelTab_Rel);
   struct xSymRelEnt_t *symRelTabP =  symRelTab;
   
   inPrintf("\n\n\n SymTab NrEnt= %d  SpecialSect = %d  ", xffHdr->symTabNrE, xffHdr->SpecSectNr );
  //         00000000 00000000 00000000 00000000 00000000 00000000 00000000 
   inPrintf("\n nameOff  addr     size     info     unk0D    sect       Imp");
   for (i=0; i<xffHdr->symTabNrE; i++) {
        
      symImpTabP = symImpTab;    k = 0;
      for (l=0; l< xffHdr->expSymTabNrE; l++) { 
      if (i == symImpTabP->remapNr) { k =1;          
          
         break;
      }
      symImpTabP++;
      }
      
      inPrintf("\n Ix=%x addRel=%08X  >%s< ", i, symRelTabP->addr, (void*)(buf + xffHdr->SymTabStr_Rel + SymTabP->nameOffs)); 
      inPrintf("\n %8X %8X %8X %8X %8X %8X   %d", \
      SymTabP->nameOffs, SymTabP->addr, SymTabP->size, SymTabP->info, SymTabP->unk0D, SymTabP->sect, k);    
      SymTabP++;
      symRelTabP++; 
   }
	inPrintf("\n\n\n"); 
   
   xffExit: 
free(buf);
  #if AUTOMODE != 1
 //  system("PAUSE");          
  #endif   
   return 0;
}









//Returns the section offset, or if <= 0, returns error.
//sectPt - output pointer to the section (optional) in RAM
//entPnt - output pointer to the entry point of the XFF in RAM 
//specify sectNm as ".data" / ".rodata".
int getXffSectByName(void **sectPtOut, int *sectSzOut, void **entPnt, void *xffFlBuf, int xffFlSz, char *sectNm, int verbose) {
	int ret = 0;
   int sectNr = xffFindSectNrByName(sectNm, xffFlBuf, xffFlSz);
   if (verbose > 0) printf("\n %s: %s section at %d index ", __func__, sectNm, sectNr);

   if (sectNr <= 0) {
      //printf("\n %s: ERR can't find section %s err= %d ", __func__, sectNm, sectNr);
		return -2;
   }

	int sectSz = 0;
   int sectOff = xffGetSectOffsByNr(sectNr, xffFlBuf, xffFlSz, &sectSz);
   if (sectOff <= 0) {
      //printf("\n %s: ERR while getting section offset & sz: err=%d ", __func__, sectOff);
      return -3;
   }
	if (sectSzOut != NULL) *sectSzOut = sectSz;
	if (sectPtOut != NULL) *sectPtOut = (void*)((u32)xffFlBuf + sectOff); //absolute section pointer in RAM
	void *sectPt = (void*)((u32)xffFlBuf + sectOff);

   struct xffHdr_t *xffHdr = xffFlBuf;
	if (entPnt != NULL) { //get the entry point as well and check if it is within this section
		*entPnt = (void*)((u32)sectPt + xffHdr->entry_Rel);
		if (xffHdr->entry_Rel >= sectSz) {
		   //printf("\n %s: ERR: entry point outside target section \n", __func__);
		   return -5;
		}
	}
   return sectOff;
}




//TODO: search for "reloc" in the game funcs and copy all the reloc funcs here, including a func to reloc a fixed XFF in RAM, so that its pointers can be freely used.

// XFF Functtions from the game. I have the feeling I have re-coded those before, but whatever.
//May need to rename them if this is ever linked with the game.

//ResolveRelocation_sub_1000d0
//This relocates a single relocation entry (so it needs to be called in a loop)
//XXX: can be called only after entry point header and sect tab and symTab relocation 
//Return: 0=fail / 1=success
//relocEnt is only one of the relocation table entries
//relocIx is the index in the addr/instr tables pointed to by relocEnt
int ResolveRelocation(void *xffBuf, struct t_xffRelocEnt *relocEnt, int relocIx) {
	int success = 0; //fai
	struct t_xffEntPntHdr *xffEp = xffBuf;
	int relTy = relocEnt->addr[relocIx].relType;
	int symIx = relocEnt->addr[relocIx].tgSymIx;
	int relOffs = relocEnt->addr[relocIx].addr;
	u32 *relAddr = (void*)((u32)xffEp->sectTab[relocEnt->sect].memPt + relOffs);
	void *tgtAddr = xffEp->symTab[symIx].addr;
	int addVal = relocEnt->inst[relocIx].inst;

	switch (relTy) {
		case 0: //do nothing
		break;

		case 2: //direct offset
			*relAddr = (u32)tgtAddr + addVal; 
		break;

		case 4: // jal / j reloc with target symbol in symTab
			*relAddr = (((u32)tgtAddr / 4) & 0x03FFFFFF) + addVal; 
		break;

		case 5: // high part of immediate lui, addi, etc. pair. XXX: this doesn't seem to support addiu and ori as the added value is alway signed.
			do{}while(0);
			//Skip over any more type-5 relocations following this one ... looks like a hack
			int oldRelocIx = relocIx;
			do {
				relocIx += 1;
				relTy = relocEnt->addr[relocIx].relType;
			} while (relTy == 5);
			//It is looking for the low-part reloc. so that it can compute the high part correctly to account for signed offsets.
			int loAddVal = 0;
			if (relTy == 6) { //the low part - addi / ori
				loAddVal = relocEnt->inst[relocIx].inst;
			} else {
				printf("\nld:\tWarning! Can't find low16 for hi16(relid:%d).", oldRelocIx);
				loAddVal = 0;
			}
			loAddVal = s32signExtS16(loAddVal); //convert to signed s32 from s16
			int a = (u32)tgtAddr + (addVal <<16);
			a += loAddVal; a = a >>15; a += 1; a = a>>1;
			*relAddr = (a & 0x0000FFFF) | (addVal & 0xFFFF0000); //addVal contains the instrucion part while a contains the high16 immediate part. 
		break;

		case 6: // immediate low 16 bits addi, ori, etc. reloc with target symbol in symTab
			*relAddr = ((u32)tgtAddr + addVal) & 0x0000FFFF;
			*relAddr |= addVal & 0xFFFF0000;
		break;

		case 1:
		case 3:
		default:
			printf("\n ld:\tFatal error!! unknown relocation type(%d) appeared. (ofs:%x)\n", relTy, relOffs);
			return 0; //fail
	};

	return 1; //success
}

/*
When the target is not in symTab, instead of taget symbol, the symbol corresponding to the section of the taget is used, and addVal holds the offset of the target in its section.
This is the case with structures without symbols. This is also the case with unnamed functions - the j/jal instruction hold the address/4 offset to the function from the start of the section. 

When the target is in symTab, its address (offset) from symTab is used and the offset in the inst tab can be either 0, or some other value if the relocation point is an instruction.

So in short - a relocation *always* dows this:
"At address relocAddr add to the values the (modified according to relocType) address of the taget symbol. The address of the target symbol is always given as a symbol from SymTab. When the target symbol itself is not in SymTab (not exported or imported), instead of its index in SymTab, the index of the section it belongs to is given and the "instr" value holds the its offset in its section already."

*/


//Relocates the local symbols in an XFF and writes the DldSysUndefSymbol addr to all other.
//undefSym is a function that handles undefined symbols (only functions actually - not data)
int RelocateSelfSymbol(void *xffBuf, void *undefSym) { //_sub_1018b8    XXX: should be OK, but is UNTESTED!
	struct t_xffEntPntHdr *ep = xffBuf;
	int sc = ep->symTabNrE;
	struct t_xffSymEnt *se = ep->symTab;
	struct t_xffSymRelEnt *sr = ep->symRelTab;

	for (; sc > 0; sc--, se++, sr++) {
		u32 sect = se->sect;
		se->addr = undefSym;
		if (sect == 0) continue;
		if (sect == 0xFFF1) {
			se->addr = (void*)sr->offs;
			continue;
		}
		if (sect > 0xFEFF) continue;
		if (se->type >= 4) continue;
		//if (se->type < 0) continue;
		se->addr = (void*)((u32)ep->sectTab[se->sect].memPt + sr->offs);
	}
	return 1;
}


//Find the imported symbol in the common hashes tab, if present.
//int findImpSym( ) { //sub_1B4930
//internally references the hash tab
//also see AddStrHashKey_sub_1cb388; other hash funcs
//Was about to copy-write it for the DebugEnabler undefined data symbol reference naming on error screen, but gets way too complicated and better not make this feature unless really necessary.





//RelocateElfInfoHeader_sub_1004b8
void RelocateElfInfoHeader(struct t_xffEntPntHdr *xffEp) {
	u32 xffBaseAddr = (u32)xffEp;
	xffEp->sectTab = (void*)(xffBaseAddr + xffEp->sectTab_Rel);
	int i;
	//This is actually done with incr pointer and decr counter, but whatever
	for (i=0; i<xffEp->sectNrE; i++) {
		xffEp->sectTab[i].filePt = (void*)(xffBaseAddr + xffEp->sectTab[i].offs_Rel);
		if (xffEp->sectTab[i].size == 0) {
			xffEp->sectTab[i].filePt = NULL;
			xffEp->sectTab[i].offs_Rel = 0;
		} //XXX: workaround - resource files (like minotaur_A.skb) have the symTab relative offset of the .zero section not set and the previous data in RAM is visible there, just as the size of the symbol corresponding to the zero section.
	}
	xffEp->symTab = (void*)(xffBaseAddr + xffEp->symTab_Rel);
	xffEp->symRelTab = (void*)(xffBaseAddr + xffEp->symRelTab_Rel);
	xffEp->symTabStr = (void*)(xffBaseAddr + xffEp->symTabStr_Rel);
	xffEp->impSymIxs = (void*)(xffBaseAddr + xffEp->impSymIxs_Rel);
	xffEp->relocTab = (void*)(xffBaseAddr + xffEp->relocTab_Rel);
	xffEp->ssNamesBase = (void*)(xffBaseAddr + xffEp->ssNamesBase_Rel);
	xffEp->ssNamesOffs = (void*)(xffBaseAddr + xffEp->ssNamesOffs_Rel);
	//This is actually done with incr pointer and decr counter, but whatever
	for (i=0; i<xffEp->relocTabNrE; i++) {
		xffEp->relocTab[i].addr = (void*)(xffBaseAddr + xffEp->relocTab[i].addr_Rel);
		xffEp->relocTab[i].inst = (void*)(xffBaseAddr + xffEp->relocTab[i].inst_Rel);
	}
	xffEp->stack = (void*)(xffBaseAddr + xffEp->stack_Rel);
	return;
}



//void undefinedFunctionHandler(

//DecodeSection_sub_100278
//mallocMaxAlign() aligns to 0x100 bytes in the game.
//This handles only .text, .overlaydata and .bss (nobits) sections.
//.rodata, .data, .sdata are not handled by this. Maybe because sheet and resource files have only data, rodata and sdata sections, so they are relocated dynamically for memory deframgmentation?
void DecodeSection(void *xffBuf, void *(*mallocAlign)(int sz, int align), void *(*mallocMaxAlign)(int sz), void (*ldrDbgPrintf)(char *fmt, ...)) {
	struct t_xffEntPntHdr *xffEp = xffBuf;
	char *sectMovedTypes[] = {
		"normal use", // 0
		"out of align(alloc)", // 1 "\x1B[36m out of align(alloc) \x1B[m"
		"alloc flag(alloc)" // 2
	};
	char *sectDbgStr = NULL;

	int i;
	void *entPntSectBs = NULL;
	if (ldrDbgPrintf != NULL) ldrDbgPrintf("ld:\t\tdecode section\n");

	if (xffEp->sectNrE == 1) goto decSectExit;  

	//The zero section is not processed as it is all 0.
	for (i=1; i<xffEp->sectNrE; i++) {
		//these are actually incremented pointers, but indexing is easier to read.
		struct t_xffSectEnt *sect = &xffEp->sectTab[i];
		struct t_xffSsNmOffs *nmOffs = &xffEp->ssNamesOffs[i];

		sect->moved = 0;
		if (sect->size == 0) {
			sect->memPt = NULL;
		} else {
			if (sect->type == 0x8) { // nobit .bss section
				//Because nobits is not present in the file, it is always allocated
				if (sect->flags == 0) { //section is not copied and used as is in the file
					sect->memPt = mallocAlign(sect->size, sect->align);
					sect->moved = 1;
				} else {
					sect->memPt = mallocMaxAlign(sect->size);
					sect->moved = 2;
				}
				memset(sect->memPt, 0x00, sect->size);
				if (ldrDbgPrintf == NULL) goto decSectSkip;
				sectDbgStr = "\nld:\t%15s(nobit)  : 0x%08x(0x%08x) %s\n";


			//The following is coded a bit differently - .text is under <9, but whatever.
			} else if ((sect->type == 1) || (sect->type == 0x7FFFF420)) { // .text section
				if (sect->flags == 0) {
					//Check if the alignment is enough as is in the file:
					if (((u32)sect->filePt & (sect->align - 1)) != 0) {
						//Insufficient alignment, so alloicate
						sect->memPt = mallocAlign(sect->size, sect->align);
						memcpy(sect->memPt, sect->filePt, sect->size);
						sect->moved = 1;
					} else { //use the section as is in the file
						sect->memPt = sect->filePt;
					}
				} else {
					//Forced max alignment
					sect->memPt = mallocMaxAlign(sect->size);
					memcpy(sect->memPt, sect->filePt, sect->size);
					sect->moved = 2;
				}
				if (ldrDbgPrintf == NULL) goto decSectSkip;
				if (sect->type == 1) { // .text
					sectDbgStr = "\nld:\t%15s(progbit): 0x%08x(0x%08x) %s\n";
				} else { //VU code/data
					sectDbgStr = "\nld:\t%15s(overlaydata): 0x%08x(0x%08x) %s\n";
				}		
			} else if (sect->type < 9) { //other 'normal' sections
				goto decSectSkip;
			} else {
				goto decSectSkip;
			}
		}

		char *sectNm = &xffEp->ssNamesBase[nmOffs->nmOffs];
		//The moved-types are actually allocation types (or used in file as is).
		ldrDbgPrintf(sectDbgStr, sectNm, sect->memPt, sect->size, sectMovedTypes[sect->moved]);

		decSectSkip:
		if (entPntSectBs == NULL) entPntSectBs = sect->memPt;
	}

	decSectExit:
	xffEp->entryPnt = (void*)((u32)entPntSectBs + xffEp->entryPnt_Rel);
	return;
}




//This is an imcomplete relocator - it only sets absolute addresses according to where the buffer to the XFF file is without allocating any additional space - for example for .bss(nobits) section or when the alignment requirements for a section are unmet. 
//XXX: Beware that if some section is not aligned in the file to 4 byte boundary (they usually are though), this can cause havoc on access to words, etc. But this would happen without relocation so it shouldn't be an issue.
int relocateXffLocalUse(void *xffBuf, int xffSz) {
	struct t_xffEntPntHdr *xffEp = xffBuf;
	RelocateElfInfoHeader(xffEp);
	int i;
	void *entPntSectBs = NULL;
	for (i=0; i<xffEp->sectNrE; i++) {
		xffEp->sectTab[i].memPt = xffEp->sectTab[i].filePt; //as it is constant in RAM
		if (entPntSectBs == NULL)
		if (xffEp->sectTab[i].size != 0) //XXX: workaround - resource files (like minotaur_A.skb) have the symTab relative offset of the .zero section not set and the previous data in RAM is visible there, just as the size of the symbol corresponding to the zero section. This prevents the zero section from being used. memAbs and fileAbs can't be used as they get set based on the relative offs.
			if (xffEp->sectTab[i].offs_Rel != 0)
				entPntSectBs = xffEp->sectTab[i].memPt; 
	}
	xffEp->entryPnt = (void*)((u32)entPntSectBs + xffEp->entryPnt_Rel);
	if (entPntSectBs == NULL) xffEp->entryPnt = NULL;	//XXX: added, just in case
	//reloc SymTab:
	for (i=0; i<xffEp->symTabNrE; i++) {
		struct t_xffSymEnt *sym = &xffEp->symTab[i];
		struct t_xffSymRelEnt *relSym = &xffEp->symRelTab[i];
		int sectIx = sym->sect;
		if (sectIx >= xffEp->sectNrE) { //== 0xFFF1) { //absolute
			sym->addr = NULL; //as we are not on PS2 (and we can't have abs addr) accessing this should just cause an exception
		} else {
			struct t_xffSectEnt *sect = &xffEp->sectTab[sectIx];
			sym->addr = (void*)((u32)sect->memPt + relSym->offs);
			//if ((relSym->offs + sym->size) > sect->size) { sym->addr = NULL; } //XXX: added: A symbol should not span past the end of the section it inhabits. - Mainly to fix the .zero section symbol, which has unset (old RAM data) size.
		}
	}

	for (i=0; i<xffEp->impSymIxsNrE; i++) {
		int sIx = xffEp->impSymIxs[i].stIx;
		struct t_xffSymEnt *sym = &xffEp->symTab[sIx];
		sym->addr = NULL; //imported symbols are not liked
	}

	for (i=0; i<xffEp->relocTabNrE; i++) {
		int r;
		for (r=0; r<xffEp->relocTab[i].nrEnt; r++) {
			ResolveRelocation(xffBuf, &xffEp->relocTab[i], r);
		}
	}
	return 0;
}



//This is done by path, so that if the file is very big, a buffer doesn't need to be allocated.
//return value
/*enum { //see fl_xffType.h 
	XFF_FL_TYPE_RESOURCE = 1,
	XFF_FL_TYPE_SHEET,
	XFF_FL_TYPE_EXECUTABLE,
};*/

//Errors above -10 mean that the file is an XFF file, but has/mightHave something wrong with its structure
//Returns: <0 err; ==0 not an XFF; 1=resource file / 2=Sheet/Executable file.

//if the size is unknown, set maxSz to the max input buffer sz.
//The buffer is assumed to be aligned to 4 bytes.
//Unlike xffChkIfXffFileByPath, this func does not require the size to be correct.
//TODO: consider adding arg flags to set exactly what to check for or different positive returns.
int xffChkIfXffFileByBuf(void *buf, int maxSz) {
	int flTy = -1;
	if (buf == NULL) return -1;
	struct t_xffEntPntHdr *xEpH = buf;
	struct t_xffEntPntHdr *ep = xEpH;
	if (xEpH == NULL) { return -2; }
	if (maxSz < sizeof(struct t_xffEntPntHdr)) { //file far too small or error reading
		flTy = -4; goto errExit;
	}
	if (xEpH->ident == XFF_RES_MAGIC_XFF) flTy = XFF_FL_TYPE_RESOURCE;
	else if (xEpH->ident == XFF_SHTEXE_MAGIC_XFF2) flTy = XFF_FL_TYPE_SHEET; //and also XFF_FL_TYPE_EXECUTABLE
	if (flTy < 0) { flTy = 0; goto errExit; } //not a sheet
	int flSz = xEpH->stack_Rel;
	if (maxSz < flSz) return -10;

	//Checking relative offsets - after the entryPoint and before the end of the file:
	//if (ep->entryPnt_Rel <= sizeof(struct t_xffEntPntHdr)) return -12; //the entry is in section, so don't check min
	if (ep->entryPnt_Rel >= flSz) return -13;
	if (ep->impSymIxs_Rel < sizeof(struct t_xffEntPntHdr)) return -14;
	if (ep->impSymIxs_Rel >= flSz) return -15;
	if (ep->symTab_Rel < sizeof(struct t_xffEntPntHdr)) return -16;
	if (ep->symTab_Rel >= flSz) return -17;
	if (ep->symTabStr_Rel < sizeof(struct t_xffEntPntHdr)) return -18;
	if (ep->symTabStr_Rel >= flSz) return -19;
	if (ep->sectTab_Rel < sizeof(struct t_xffEntPntHdr)) return -20;
	if (ep->sectTab_Rel >= flSz) return -21;
	if (ep->symRelTab_Rel < sizeof(struct t_xffEntPntHdr)) return -22;
	if (ep->symRelTab_Rel >= flSz) return -23;
	if (ep->relocTab_Rel < sizeof(struct t_xffEntPntHdr)) return -24;
	if (ep->relocTab_Rel >= flSz) return -25;
	if (ep->ssNamesOffs_Rel < sizeof(struct t_xffEntPntHdr)) return -26;
	if (ep->ssNamesOffs_Rel >= flSz) return -27;
	if (ep->ssNamesBase_Rel < sizeof(struct t_xffEntPntHdr)) return -28;
	if (ep->ssNamesBase_Rel >= flSz) return -29;

	//check align:
	if (ep->entryPnt_Rel & 0x3) return -40;
	if (ep->impSymIxs_Rel & 0x3) return -41;
	if (ep->symTab_Rel & 0x3) return -42;
	//if (ep->symTabStr_Rel & 0x3) return -43;  strings, so maybe it can be unaligned
	if (ep->sectTab_Rel & 0x3) return -44;
	if (ep->symRelTab_Rel & 0x3) return -45;
	if (ep->relocTab_Rel & 0x3) return -46;
	if (ep->ssNamesOffs_Rel & 0x3) return -47;
	//if (ep->ssNamesBase_Rel & 0x3) return -48;  strings, so maybe it can be unaligned

	//if (xEpH->specSectNrE == 0) { flTy = -11; goto errExit; } //not to be checked - can be 0 for some resourcess
	errExit:
	return flTy;
}

//TODO: Consider adding the above checks to the below - maybe the whole func + the already present stackRel check.

//same return as the above
int xffChkIfXffFileByPath(char *path) {
	int flTy = -1;
	if (path == NULL) return -1;
	struct t_xffEntPntHdr *xEpH = mallocAndClr(sizeof(struct t_xffEntPntHdr));
	if (xEpH == NULL) { return -2; }
	//printf("\n %s: path >%s< ", __func__, path);
	FILE *flIn = fopen(path, "rb");
	if (flIn == NULL) { freeIfNotNull(xEpH); return -3; }

	int r = fread(xEpH, 1, sizeof(struct t_xffEntPntHdr), flIn);
	if (r < sizeof(struct t_xffEntPntHdr)) { //file far too small or error reading
		flTy = -4; goto errExit;
	}
	if (xEpH->ident == XFF_RES_MAGIC_XFF) flTy = XFF_FL_TYPE_RESOURCE;
	else if (xEpH->ident == XFF_SHTEXE_MAGIC_XFF2) flTy = XFF_FL_TYPE_SHEET; //and also XFF_FL_TYPE_EXECUTABLE
	if (flTy < 0) { flTy = 0; goto errExit; } //not a sheet
	fseek(flIn, 0, SEEK_END);
	int flInSz = ftell(flIn);
	if (xEpH->stack_Rel != flInSz) { flTy = -10; goto errExit; } //But is this always so?
	//if (xEpH->specSectNrE == 0) { flTy = -11; goto errExit; } //not to be checked - can be 0 for some resources

	errExit:
	freeIfNotNull(xEpH);
	fclose(flIn);
	return flTy;
}



//Returns a symbol of symTab, based on the offset - symDataOffs to its data. Usually used when looking for the entryPoint symbol.
//Can be used for XFFs that have not yet been relocated (by relocateXffLocalUse()) and for reloc'ed as well.
//symSect - section to which the symbol belongs - if NULL, then any section is used - beware that this may result in finding the wromng symbol.
//If symNm is not NULL, it is set to point to the name of the symbol
//startSymIx - starting symbol index - in case the caller compares the name of the symbol and needs to do multipe searches (not knowing the section). (set to 0 otherwise)
int xffFindSymIxByOffsNonReloc(char **symNm, struct t_xffSymEnt **symEnt, void *xffBuf, int xffSz, int symDataOffs, char *symSect, int startSymIx) {
	int symIx = -1;
   int sectNr = -1;
	if (symSect != NULL) sectNr = xffFindSectNrByName(symSect, xffBuf, xffSz);
	struct t_xffEntPntHdr *xEpH = xffBuf;
	struct t_xffSymEnt *symTab = (void*)((u32)xffBuf + xEpH->symTab_Rel);
	struct t_xffSymRelEnt *symRel = (void*)((u32)xffBuf + xEpH->symRelTab_Rel);
	char *symTabStr = (void*)((u32)xffBuf + xEpH-> symTabStr_Rel);
	int i;
	for (i=startSymIx; i<xEpH->symTabNrE; i++) {
		if (symRel[i].offs == symDataOffs) { //found
			if (sectNr >= 0) { //compare section
				if (sectNr != symTab[i].sect) continue; //mismatch
			}
			//else -> return the data for this sym
			if (symNm != NULL) *symNm = &symTabStr[symTab[i].nameOffs];
			if (symEnt != NULL) *symEnt = &symTab[i];
			symIx = i;
			break;
		}
	}
	return symIx;
}


//Much like the above, but uses the absolute, relocated address of the symbol.
//For this the XFF must be relocated.
//symSect can be NULL (and should usually be so), and startSymIx should usually be 0. 
int xffFindSymIxByPtReloc(char **symNm, struct t_xffSymEnt **symEnt, void *xffBuf, int xffSz, void *symDataPt, char *symSect, int startSymIx) {
	int symIx = -1;
   int sectNr = -1;
	if (symSect != NULL) sectNr = xffFindSectNrByName(symSect, xffBuf, xffSz);
	struct t_xffEntPntHdr *xEpH = xffBuf;
	struct t_xffSymEnt *symTab = (void*)((u32)xffBuf + xEpH->symTab_Rel);
	struct t_xffSymRelEnt *symRel = (void*)((u32)xffBuf + xEpH->symRelTab_Rel);
	char *symTabStr = (void*)((u32)xffBuf + xEpH-> symTabStr_Rel);
	int i;
	for (i=startSymIx; i<xEpH->symTabNrE; i++) {
		//if (symRel[i].offs == symDataOffs) { //found
		if (symTab[i].addr == symDataPt) { //found
			if (sectNr >= 0) { //compare section
				if (sectNr != symTab[i].sect) continue; //mismatch
			}
			//else -> return the data for this sym
			if (symNm != NULL) *symNm = &symTabStr[symTab[i].nameOffs];
			if (symEnt != NULL) *symEnt = &symTab[i];
			symIx = i;
			break;
		}
	}
	return symIx;
}


#if 0
//XXX: UNFINISHED:  This is too complicated, because there is no direct way to know the symbol to whuch the relocation would point to, from the input address. So better make a more specific fujnction - see below.
//Finds the address referencing (at which there is a pointer to) the given absolute address (dataPt). If none, returns NULL. relTabIx, relEntIx return the relocation entry that relocates this pointer.
//For this the XFF must be relocated.
void *xffFindRelocRefByPtReloc(int *relTabIx, int *relEntIx, struct t_xffSymEnt **symEnt, void *xffBuf, int xffSz, void *dataPt, char *symSect, int startSymIx) {
	int symIx = -1;
   int sectNr = -1;
	if (symSect != NULL) sectNr = xffFindSectNrByName(symSect, xffBuf, xffSz);
	struct t_xffEntPntHdr *xEpH = xffBuf;
	struct t_xffSymEnt *symTab = (void*)((u32)xffBuf + xEpH->symTab_Rel);
	struct t_xffSymRelEnt *symRel = (void*)((u32)xffBuf + xEpH->symRelTab_Rel);
	char *symTabStr = (void*)((u32)xffBuf + xEpH-> symTabStr_Rel);
	int i;
	for (i=startSymIx; i<xEpH->symTabNrE; i++) {
		//if (symRel[i].offs == symDataOffs) { //found
		if (symTab[i].addr == symDataPt) { //found
			if (sectNr >= 0) { //compare section
				if (sectNr != symTab[i].sect) continue; //mismatch
			}
			//else -> return the data for this sym
			if (symNm != NULL) *symNm = &symTabStr[symTab[i].nameOffs];
			if (symEnt != NULL) *symEnt = &symTab[i];
			symIx = i;
			break;
		}
	}
	return symIx;
}
#endif


//Checks if the addr in dataPt is a relocation target - i.e. a pointer.
//rlcTy is the type of relocation. Specify 2 for pointer addr reloc (the other types are for reloc done in code), or -1 for "don't check".
//For this the XFF must be relocated.
//Returns <= 0 on non-relocTgt and >= 1 on is reloc tgt.
int xffFindIfAddrIsRelocTgt(int *rlcTabIx, int *rlcEntIx, void *xffBuf, int xffSz, void *dataPt, char *symSect, int rlcTy) {
	if (dataPt == NULL) return -2;
	int isRlcTgt = 0;
   int sectNr = -1;
	struct t_xffEntPntHdr *xEpH = xffBuf;
	if (symSect != NULL) sectNr = xffFindSectNrByName(symSect, xffBuf, xffSz);
	//Because the XFF should already be relocated, using the absolute pointers:
	struct t_xffRelocEnt *relocMainTab = xEpH->relocTab;
	int i, j;
	for (i=0; i<xEpH->relocTabNrE; i++) { //go through the main reloc tabs - two for each sect
		struct t_xffRelocEnt *rt = &relocMainTab[i];
		if (sectNr >= 0) { //section-checking enabled
			if (rt->sect != sectNr) continue; //wrong section
		}
		struct t_xffSectEnt *sect = &xEpH->sectTab[rt->sect];
		u32 ptOffsInSect = (int)(dataPt - sect->memPt); //this can end-up wrong or negative
		for (j=0; j<rt->nrEnt; j++) {
			struct t_xffRelocAddrEnt *rAe = &rt->addr[j];
			struct t_xffRelocInstEnt *rIe = &rt->inst[j];
			if (rlcTy >= 0)
				if (rAe->relType != rlcTy) continue;
			if (ptOffsInSect == rAe->addr) { //found
				if (rlcTabIx != NULL) *rlcTabIx = i;
				if (rlcEntIx != NULL) *rlcEntIx = j;
				isRlcTgt = 1;
				break;
			}
		}
	}
	return isRlcTgt;
}



//This finds a named symbol that is a structure, at which at a set offset there is a pointer to an address given in dataPt.
//All named symbols get exported (right?). NOT: If exported is 1, then this will look only for symbols that get exported.
//offs sets the offset in the symbol where the pointer is stored. The offset should be 4-byte aligned and so should the symbol, otherwise this will crash.
//This does not use the relocation tables at all. It simply compares values.
//XXX: WARNING: because of the above, this can give false-positive results for values matchinbg the address (dataPt) given!
//For this the XFF must be relocated.
int xffFindNamedSymPointerToAddrReloc(char **symNm, struct t_xffSymEnt **symEnt, void *xffBuf, int xffSz, void *dataPt, char *symSect, int startSymIx, int offs) {
	if (dataPt == NULL) return -2;
	int symIx = -1;
   int sectNr = -1;
	if (symSect != NULL) sectNr = xffFindSectNrByName(symSect, xffBuf, xffSz);
	struct t_xffEntPntHdr *xEpH = xffBuf;
	struct t_xffSymEnt *symTab = (void*)((u32)xffBuf + xEpH->symTab_Rel);
	struct t_xffSymRelEnt *symRel = (void*)((u32)xffBuf + xEpH->symRelTab_Rel);
	char *symTabStr = (void*)((u32)xffBuf + xEpH-> symTabStr_Rel);
	int i;
	for (i=startSymIx; i<xEpH->symTabNrE; i++) {
		char *crSymNm = &symTabStr[symTab[i].nameOffs];
		if (strlen(crSymNm) <= 0) continue; //only named symbols
		if (sectNr >= 0) { //compare section
			if (sectNr != symTab[i].sect) continue; //mismatch
		}
		//u32 *pt = (u32*)((u32)symTab[i].addr + offs);
		u32 *pt = symTab[i].addr;
		if (pt == NULL) continue;
		pt = &pt[offs>>2];
		//This is necessary, because if this addr does NOT contain a relocated pointer, dereferencing it can go anywgere and crash.
		int isRelocTgt = xffFindIfAddrIsRelocTgt(NULL, NULL, xffBuf, xffSz, pt, symSect, 2);
		if (isRelocTgt <= 0) continue;
		
		if (((void*)*pt) == dataPt) { //found
			if (symNm != NULL) *symNm = &symTabStr[symTab[i].nameOffs];
			if (symEnt != NULL) *symEnt = &symTab[i];
			symIx = i;
			break;
		}
	}
	return symIx;
}



//If the dataPt data is a named symbol, the symbol index is returned, else < 0. 
int xffFindNamedSymOfData(char **symNm, struct t_xffSymEnt **symEnt, void *xffBuf, int xffSz, void *dataPt, char *symSect, int startSymIx) {
	if (dataPt == NULL) return -2;
	int symIx = -1;
   int sectNr = -1;
	if (symSect != NULL) sectNr = xffFindSectNrByName(symSect, xffBuf, xffSz);
	struct t_xffEntPntHdr *xEpH = xffBuf;
	struct t_xffSymEnt *symTab = (void*)((u32)xffBuf + xEpH->symTab_Rel);
	char *symTabStr = (void*)((u32)xffBuf + xEpH-> symTabStr_Rel);
	int i;
	for (i=startSymIx; i<xEpH->symTabNrE; i++) {
		char *crSymNm = &symTabStr[symTab[i].nameOffs];
		if (strlen(crSymNm) <= 0) continue; //only named symbols
		if (sectNr >= 0) { //compare section
			if (sectNr != symTab[i].sect) continue; //mismatch
		}
		//u32 *pt = (u32*)((u32)symTab[i].addr + offs);
		u32 *pt = symTab[i].addr;
		if (pt == NULL) continue;
		if (((void*)pt) == dataPt) { //found
			if (symNm != NULL) *symNm = &symTabStr[symTab[i].nameOffs];
			if (symEnt != NULL) *symEnt = &symTab[i];
			symIx = i;
			break;
		}
	}
	return symIx;
}




#if 0
//did this by mistake; incomplete. Might have written a complete one once
//xff get entPnt pre reloc isysGetXffEntryPointPreRelocation
void *xeppr(struct t_xffEntPntHdr *xffBuf) {
	void *ep = NULL;
	if (ep->sectNrE <= 1) return ep;
	struct t_xffSectEnt *sects = (u32)xffBuf + (u32)xffBuf->sectTab_Rel; 
	xffBuf->sectTab = sects;
	int i = 1; struct t_xffSectEnt *sc = sects++; //get skip the .zero sect
	for (; i < ep->sectNrE; i++, sc++) {
		sc->filePt = (u32)xffBuf + (u32)sc->offs_Rel;
		if (sc->size == 0) continue;
		if (sc->type == 8) { //nobits
			dprtf("\n nobits sect of sz 0");
			//iosJumpRecoverPoint(""); //_sub_1b3de8
		}
		if ((sc->type == 1) || (sc->type == 0x7FFFF420)) { //progbits or sth
//oh this won't work for resources
		}
			dprtf("\n sectSz 0");
			//iosJumpRecoverPoint(""); //_sub_1b3de8
		}
	}
	return ep;
}
#endif




//Find the symbol to which dataPt points to. Note that if the symbol is a sepcialSect, then the symNm is NULL.
//Only for alreday relocated XFFs.
//This is mainly used to find the names of external (imported) symbols.
//This assumes that the relocation is full addres reference (pointer) but the reloc type is not checked.
int xffFindNamedSymWhichRelocTgtPointsToRlc(char **symNm, struct t_xffSymEnt **symEnt, void *xffBuf, int xffSz, void *dataPt, char *symSect, int startSymIx, int rlcTy) {
	if (dataPt == NULL) return -2;

	//Find the relocEnt which relocates at the dataPt target addr:
	int rlcTabIx = -1, rlcEntIx = -1; 
	int isRlcTgt = xffFindIfAddrIsRelocTgt(&rlcTabIx, &rlcEntIx, xffBuf, xffSz, dataPt, symSect, rlcTy);
	if (rlcEntIx < 0) return -5;

   int sectNr = -1;
	struct t_xffEntPntHdr *xEpH = xffBuf;
	if (symSect != NULL) sectNr = xffFindSectNrByName(symSect, xffBuf, xffSz);
	//Because the XFF should already be relocated, using the absolute pointers:
	struct t_xffRelocEnt *relocMainTab = xEpH->relocTab;
	struct t_xffRelocEnt *rt = &relocMainTab[rlcTabIx];
	struct t_xffSectEnt *sect = &xEpH->sectTab[rt->sect];
	struct t_xffRelocAddrEnt *rAe = &rt->addr[rlcEntIx];
	struct t_xffRelocInstEnt *rIe = &rt->inst[rlcEntIx];
	int tgSymIx = rAe->tgSymIx;
	if (tgSymIx < 0) return -7;

	struct t_xffSymEnt *symTab = (void*)((u32)xffBuf + xEpH->symTab_Rel);
	struct t_xffSymRelEnt *symRel = (void*)((u32)xffBuf + xEpH->symRelTab_Rel);
	char *symTabStr = (void*)((u32)xffBuf + xEpH-> symTabStr_Rel);

	if (symNm != NULL) *symNm = &symTabStr[symTab[tgSymIx].nameOffs];
	if (symEnt != NULL) *symEnt = &symTab[tgSymIx];
	return tgSymIx;
}
















