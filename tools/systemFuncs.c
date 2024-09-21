//System functions - wrappers for system functions for easy use:


#include <stdarg.h>

void waitUInp(void) {
   printf("\r\nPress Return key to continue... ");
   fflush(stdin);
   getc(stdin);
   return;
}


#define MACHK_DEBUG 0
#if MACHK_DEBUG == 1
#define machk(x) machkIn((x), (char*)__func__)
void *machkIn(u32 sz, char *callerFuncName) {
#else
void *machk(u32 sz) {
#endif
	#if MACHK_DEBUG == 1
	void *cp = __builtin_return_address(0);
	//void *cp = __builtin_return_address(0); //int level);
	//printf("\n %s: Caller %p  %08X  %s ", __func__, cp, sz, callerFuncName);
	if (sz == 0) printf("\n %s: Caller %p  %08X  %s ", __func__, cp, sz, callerFuncName);
	#endif
	if (sz == 0) printf("\n WARN: machk() attempted to alloc zero-sized area ");
	#if 0
	printf("\n %s: sz %08X ", __func__, sz);
	#endif
   void *buf = malloc(sz);
   if (buf == NULL) {
      printf("\n\n %s: ERR: Failed to allocate buffer sz = %08X \n", __func__, sz);
      //This shouldn't really happen, so we are not handling it in the program in any way.
   }
   return buf;
}

void *mfchk(void *buf) { //just in case function-changing or err-handfling is necessary
   free(buf);
   return buf;
}

void *msetchk(void *buf, u8 fillData, u32 sz) { //just in case function-changing or err-handfling is necessary
   return memset(buf, fillData, sz);     
}


//inverting memcpy - copies the data, but inverts it
void memcpyInv(void *dstI, void *srcI, int len) {
	u8 *dst = dstI, *src = srcI;
	if (dst < src) {
		for (; len > 0; len--) {
			*dst = ~(*src); dst++; src++;
		}
	} else { //if (src < dst) { or they match
		src = &src[len-1]; //copy in reverse
		dst = &dst[len-1];
		for (; len > 0; len--) {
			*dst = ~(*src); dst--; src--;
		}
	}
	return;
}


///////////////////////////////////////////
//
//	Malloc Statistics and Checks
//

//1=use lineNumber instead of callerAddr
#define MALLOCANDCLR_LINENR 1

#define MALLOC_STAT_A_MAGIC 0xCAFEC0DE

//two such are placed at the start and one at the end of the buffer, to facilitate an overwrite check.
struct t_mallocStatASE { //'sub-entry' - main purpose is overwrite check.
	//u32	magicA;				//used in overwrite check - as the next pointer would usually be NULL when no next entries exist.
	//XXX: WARNING: It is relied that next is at the very start of this and the above structs!
	struct t_mallocStatAEnt *next; //only single-direction linking 
	int	size;					//malloc size (without the structs at the start and at the end) - this is what the caller set to allocate
	//void	*mallocPt;		//pointer to the start of the allocated area, returned by malloc() - this is a bit pointless, as it is clalculated by this func.
	char	*callerFuncName;	
	void	*callerAddr;		//address, where the call to malloc() was; //Misusing for caller line number instead, as it is much easier to find the source that way.
};
//This struct is 0x4-byte aligned, so should be OK, but keeping the total size 0x10 for now.

//XXX: Maybe somehow add an index (ever-incrementing) to the allocs, so that each one can be referenced by its ID this way

//malloc statistics - linked list - each entry is placed before the allocated data.
struct t_mallocStatAEnt {
	//u32	ovwrChkA;	//overwrite check
	struct t_mallocStatASE data;
	struct t_mallocStatASE invData;	//contains the same data, as data, but inverted.
	u8	mem[];	//the actual returned buffer is here
	//u32	nextInv;	//the value of next, but inverted - used as an overwrite check
};
//Placing the above struct both at the start and at the end, to better determine whether an overwrite happened at the start or at the end.

struct t_mallocStatMainData { //global struct 
	struct t_mallocStatAEnt *mallocStatAHead;
	u32	totalAlloc;		//including the stat-structs - what the malloc() calls got
	u32	payldAlloc;		//only the usable space
	u32	totlAlcNrE;		//
	u32	totalAllocMax;	//the max ever reached
	u32	payldAllocMax;
	u32	totlAlcNrEMax;
};

struct t_mallocStatMainData mallocStatMdD = {
	.mallocStatAHead = NULL,
	.totalAlloc = 0, .payldAlloc = 0, .totlAlcNrE = 0,
	.totalAllocMax = 0, .payldAllocMax = 0, .totlAlcNrEMax = 0,
};
struct t_mallocStatMainData *mallocStatMd = &mallocStatMdD;


//This code is not very automated... - it relies on the fact that the struct is 0x10 in size. Chnaging that would require changes to it too!
 
//replace the call to malloc() with this
//callerName is static string and should never disappear while the program is running
void *mallocStatAAlloc(int size, void *callerAddr, char *callerName, u32 lineNr, int doClr) { //get output size based on input size
	#if 0
	printf("\n sz %08X  cllr %08X  %s: %d ", size, (u32)callerAddr, callerName, lineNr);
	#endif
	void *pt = NULL;
	if (size <= 0) {
		if (size < 0) {
			printf("\n %s: Sz <  0: sz %08X  caller %p  %s: %d ", __func__, size, callerAddr, callerName, lineNr);
		} else {
			printf("\n %s: Sz == 0: sz %08X  caller %p  %s: %d ", __func__, size, callerAddr, callerName, lineNr);
		}
		return NULL;
	}
	int szAlign = (size +3) & (~3); //align to 4 bytes
	int tSz = sizeof(struct t_mallocStatAEnt) + szAlign + sizeof(struct t_mallocStatAEnt); //total size
	void *tPt = malloc(tSz);
	if (tPt == NULL) {
		printf("\n %s: Failed to allocate: tSz %08X  sz %08X  caller %p  %s: %d ", __func__, tSz, size, callerAddr, callerName, lineNr);
		return NULL;
	}
	//Size statistics:
	mallocStatMd->payldAlloc += size; mallocStatMd->totalAlloc += tSz; mallocStatMd->totlAlcNrE++;
	if (mallocStatMd->payldAllocMax < mallocStatMd->payldAlloc) mallocStatMd->payldAllocMax = mallocStatMd->payldAlloc;
	if (mallocStatMd->totalAllocMax < mallocStatMd->totalAlloc) mallocStatMd->totalAllocMax = mallocStatMd->totalAlloc;
	if (mallocStatMd->totlAlcNrEMax < mallocStatMd->totlAlcNrE) mallocStatMd->totlAlcNrEMax = mallocStatMd->totlAlcNrE;

	if (doClr) memset(tPt, 0x00, tSz); //clear the buf	
	struct t_mallocStatAEnt *aSt = tPt;	//struct at the start
	void *outPt = aSt->mem;
	struct t_mallocStatAEnt *aEn = (void*)&aSt->mem[szAlign]; //just after the allocated buffer
	//Fill the data:
	//aSt->data.magicA = MALLOC_STAT_A_MAGIC;
	//aSt->data.mallocPt = tPt;
	aSt->data.next = mallocStatMd->mallocStatAHead; mallocStatMd->mallocStatAHead = aSt; //link at the head
	aSt->data.size = size; //szAlign; //of the output buffer
	aSt->data.callerFuncName = callerName;
	#if MALLOCANDCLR_LINENR != 0
	aSt->data.callerAddr = (void*)lineNr;
	#else	
	aSt->data.callerAddr = callerAddr;
	#endif
	memcpyInv(&aSt->invData, &aSt->data, sizeof(struct t_mallocStatASE)); //Now copy it to the inverted one
	memcpy(aEn, &aSt->data, sizeof(struct t_mallocStatAEnt)); //and to the one at the end

	#if 0
	int mallocStateChkAndPrtIfBad(void);
	mallocStateChkAndPrtIfBad();
	#endif
	return outPt;
}


//TODO: add different align options (global settings)

//buf is the pointer returned by mallocStatAAlloc()
//returns: 0=allOK / 1=overwrAtStart / 0x10=overwrAtEnd / 3=overwrBoth / bit 2 set - start data does not match the end data; An odd condition is if bit 2 is set, but bits 0,1 are clear - shouldn't happen.

//Returns: 0=allOK / bit-fields bits(values) (set): 1= st.A <> st.B  /  2= en.A <> en.B  /  0x10 = st.A <> en.B  /  0x20= en.A <> st.B  /  0x100= st.A <> en.A  /  0x200= st.B <> en.B
//See bit-fields
//It only prints if there is an error.
//int mallocStatACheck(void *buf, int doPrt) { //, int doFree) {
	//void *tPt = (u8*)buf[-sizeof(struct t_mallocStatAEnt)];
//	struct t_mallocStatAEnt *aSt = tPt;	//struct at the start
int mallocStatACheck(struct t_mallocStatAEnt *aSt, int doPrt) {
	if (aSt == NULL) return -1;
	int szAlign = (aSt->data.size +3) & (~3); //align to 4 bytes
	int tSz = sizeof(struct t_mallocStatAEnt) + szAlign + sizeof(struct t_mallocStatAEnt); //total size
	struct t_mallocStatAEnt *aEn = (void*)&aSt->mem[szAlign];
	//check:
	struct t_mallocStatASE stIdD, *stId = &stIdD, enIdD, *enId = &enIdD;
	memcpyInv(stId, &aSt->invData, sizeof(struct t_mallocStatASE));
	memcpyInv(enId, &aEn->invData, sizeof(struct t_mallocStatASE));
	int misMatch = 0;
	if (memcmp(stId, &aSt->data, sizeof(struct t_mallocStatASE)) != 0) misMatch |= 1; //start data mismatch	st.A <> st.B
	if (memcmp(enId, &aEn->data, sizeof(struct t_mallocStatASE)) != 0) misMatch |= 2; //end data mismatch		en.A <> en.B

	if (memcmp(&aSt->data, enId, sizeof(struct t_mallocStatASE)) != 0) misMatch |= 0x10;		//					st.A <> en.B
	if (memcmp(stId, &aEn->data, sizeof(struct t_mallocStatASE)) != 0) misMatch |= 0x20; 		//					en.A <> st.B

	if (memcmp(&aSt->data, &aEn->data, sizeof(struct t_mallocStatASE)) != 0) misMatch |= 0x100;	//				st.A <> en.A
	if (memcmp(stId, enId, sizeof(struct t_mallocStatASE)) != 0) misMatch |= 0x200;					//				st.B <> en.B

	//flag bit 0 shows the Start being overwritten; flag bit 1 shows the End being overwritten - those two are the most meaningful

	//if (memcmp(aSt, aEn, sizeof(struct t_mallocStatAEnt)) != 0) misMatch |= ; //mismatch between start and edn
	//if (doPrt == 0) return misMatch;
	//if (misMatch == 0) return misMatch;
	
	struct t_mallocStatASE *ents[6] = { &aSt->data, stId, &aEn->data, enId, &aSt->invData, &aEn->invData }; //also includes the original inverted structs - for easy printing
	int matches[4] = {0,0,0,0}; //for each of st.A, st.B, en.A, en.B - counts the matches between each and the others
	matches[0] = ((misMatch & 1) ? 0 : 1) + ((misMatch & 0x10) ? 0 : 1) + ((misMatch & 0x100) ? 0 : 1);   //st.A
	matches[1] = ((misMatch & 1) ? 0 : 1) + ((misMatch & 0x20) ? 0 : 1) + ((misMatch & 0x200) ? 0 : 1); 	//st.B
	matches[2] = ((misMatch & 2) ? 0 : 1) + ((misMatch & 0x20) ? 0 : 1) + ((misMatch & 0x100) ? 0 : 1);   //en.A
	matches[3] = ((misMatch & 2) ? 0 : 1) + ((misMatch & 0x10) ? 0 : 1) + ((misMatch & 0x200) ? 0 : 1); 	//en.B
	int mrIx = 0, i; //find the entry with the most matches
	for (i=1; i<CONST_ARR_NRE(matches); i++) {
		if (matches[mrIx] < matches[i]) mrIx = i;
	}
	struct t_mallocStatASE *relDt = ents[mrIx]; //most reliable data

	if (doPrt == 0) {
		//if (doFree) { free(tPt); }
		return misMatch;
	}
	if (misMatch == 0) {
		//if (doFree) { free(tPt); }
		return misMatch;
	}
	printf("\n");
	if (matches[mrIx] < 1) printf("\n No reliable match found! The data below may be wrong!"); 
	printf("\n Most reliable is %d with %d matches.", mrIx, matches[mrIx]);
	printf("\n Matches: 0_st.A %d  1_st.B %d  2_en.A %d  3_en.B %d ", matches[0], matches[1], matches[2], matches[3]);
	printf("\n misMatch %03X ", misMatch);
	#if __x86_64__ || _WIN64 //GCC 64 or Win 64
	printf("\n %s: ERR: Data mismatch: tBf %08llX  tSz %08X  bf %08llX  sz %08X  caller %p ", __func__, (u64)aSt, tSz, (u64)aSt->mem, relDt->size, relDt->callerAddr);
	#else
	printf("\n %s: ERR: Data mismatch: tBf %08X  tSz %08X  bf %08X  sz %08X  caller %p ", __func__, (u32)aSt, tSz, (u32)aSt->mem, relDt->size, relDt->callerAddr);
	#endif
	//print the structs:
	u32 *st[6] = { (void*)&aSt->data, (void*)stId, (void*)&aEn->data, (void*)enId, (void*)&aSt->invData, (void*)&aEn->invData }; 
	printf("\n st.A    %08X  %08X  %08X  %08X ", st[0][0], st[0][1], st[0][2], st[0][3]);
	printf("\n st.B    %08X  %08X  %08X  %08X ", st[1][0], st[1][1], st[1][2], st[1][3]);
	printf("\n st.BInv %08X  %08X  %08X  %08X ", st[4][0], st[4][1], st[4][2], st[4][3]);
	printf("\n");
	printf("\n en.A    %08X  %08X  %08X  %08X ", st[2][0], st[2][1], st[2][2], st[2][3]);
	printf("\n en.B    %08X  %08X  %08X  %08X ", st[3][0], st[3][1], st[3][2], st[3][3]);
	printf("\n en.Binv %08X  %08X  %08X  %08X ", st[5][0], st[5][1], st[5][2], st[5][3]);
	#if MALLOCANDCLR_LINENR != 0
	printf("  line %d ", (u32)relDt->callerAddr);
	#else
	printf("  cllr %p ",  relDt->callerAddr);
	#endif
	printf(" funcNm >%s<", relDt->callerFuncName); //printed separately in case it crashes

	//int i = sizeof(struct t_mallocStatASE) / sizeof(u32);
	//u32 *sd = &aSt->data, *id = invData, *ed = aEn;
	//for (; i>0; i++) {
	//	if (sd
	//}
	return misMatch; //OK
}


int mallocStatAChkList(int doPrt) {
	struct t_mallocStatAEnt **sl;
	int anyFault = 0;
	int isHead = 1;
	for (sl = &mallocStatMd->mallocStatAHead; *sl != NULL; sl = &(*sl)->data.next) {
		int misMatch = mallocStatACheck(*sl, 1);
		anyFault |= misMatch;
		//struct t_mallocStatAEnt *par = (void*)sl; //relying that 'next' is at the very start of the struct
		isHead = 0;
	}
	if (doPrt) if (anyFault == 0) printf("\n %s: No damaged malloc structures detected. ", __func__);
	return anyFault;
}


int mallocStateChkAndPrtIfBad(void) {
	int badStat = mallocStatAChkList(0);
	if (badStat != 0) {
		printf("\n damagedAllocDetected ");
		waitUInp();
		int mallocStatAPrtStat(void);
		mallocStatAPrtStat();
		waitUInp();
	}
	return badStat;
}


/*
struct t_mallocStatAEnt *mallocStatAUnlink(struct t_mallocStatAEnt *par, struct t_mallocStatAEnt *cr) { // struct t_mallocStatAEnt **sl) {
	//if (sl == NULL) return NULL; //shouldn't happen
	//struct t_mallocStatAEnt *cr = *sl;
	if (cr == NULL) return NULL;
	//Unlinking is done only from the data of st.A and the rest are updated from it
	if (par != NULL) {
		par->data.next = cr->data.next;
		*(u32*)&par->invData.next = ~(u32)cr->data.next;
		int szAlign = (par->data.size +3) & (~3); //align to 4 bytes
		struct t_mallocStatAEnt *parEd = &par->mem[szAlign];
		parEd->data.next = cr->data.next;
		*(u32*)&parEd->invData.next = ~(u32)cr->data.next;
	}
	return cr;
}*/

void mallocStatASetNext(struct t_mallocStatAEnt *par, struct t_mallocStatAEnt *next) {
	if (par == NULL) return;
	int szAlign = (par->data.size +3) & (~3); //align to 4 bytes
	struct t_mallocStatAEnt *parEd = (void*)&par->mem[szAlign];
	par->data.next = next;
	#if __x86_64__ || _WIN64 //GCC 64 or Win 64
	*(u64*)&par->invData.next = ~(u64)next;
	parEd->data.next = next;
	*(u64*)&parEd->invData.next = ~(u64)next;
	#else
	*(u32*)&par->invData.next = ~(u32)next;
	parEd->data.next = next;
	*(u32*)&parEd->invData.next = ~(u32)next;
	#endif
	return;
}


//When freeing a buffer, check all the links up to it with the check-func. Because the links are updated, this check will prevent masking overwrites or catching them too late.
void mallocStatAFree(void *buf) {
	#if 0
	printf("\n %s: buf %p", __func__, buf);
	#endif
	#if 0
	mallocStateChkAndPrtIfBad();
	#endif
	if (buf == NULL) return;
	void *tPt = &((u8*)buf)[-sizeof(struct t_mallocStatAEnt)];
	struct t_mallocStatAEnt **sl, *cr = tPt; // = &mallocStatMd->mallocStatAHead;
	int isHead = 1, found = 0;
	for (sl = &mallocStatMd->mallocStatAHead; *sl != NULL;) {
		//check the entries along the way.
		int misMatch = mallocStatACheck(*sl, 1); misMatch = misMatch; //suppress warnings
		struct t_mallocStatAEnt *par = (void*)sl; //relying that 'next' is at the very start of the struct
		if (*sl == cr) { //the current one has been found -> unlink it and free it
			if (isHead) mallocStatMd->mallocStatAHead = cr->data.next;
			else mallocStatASetNext(par, cr->data.next);
			//XXX: There is no early exit, so this will go through all entries on each free().
			sl = &cr->data.next; //the current entry has not been freed yet, so this is possible
			found++;
		} else sl = &(*sl)->data.next;

		isHead = 0;
	}
	if (found == 1) {
		int szAlign = (cr->data.size +3) & (~3); //align to 4 bytes
		int tSz = sizeof(struct t_mallocStatAEnt) + szAlign + sizeof(struct t_mallocStatAEnt);
		mallocStatMd->payldAlloc -= cr->data.size; mallocStatMd->totalAlloc -= tSz; mallocStatMd->totlAlcNrE--;
		free(tPt);
	} else {
		int szAlign = (cr->data.size +3) & (~3); //align to 4 bytes
		int tSz = sizeof(struct t_mallocStatAEnt) + szAlign + sizeof(struct t_mallocStatAEnt);
		printf("\n %s: Entry found NOT one time = %d ", __func__, found);
		#if __x86_64__ || _WIN64 //GCC 64 or Win 64
		printf("\n tBf %08llX tSz %08X  bf %08llX sz %08X", (u64)cr, tSz, (u64)cr->mem, cr->data.size);
		#else
		printf("\n tBf %08X tSz %08X  bf %08X sz %08X", (u32)cr, tSz, (u32)cr->mem, cr->data.size);
		#endif
		#if MALLOCANDCLR_LINENR != 0
		printf("  line %d ", (u32)cr->data.callerAddr);
		#else
		printf("  cllr %p ",  cr->data.callerAddr);
		#endif
		printf(" funcNm >%s<", cr->data.callerFuncName); //printed separately in case it crashes
		free(tPt);
	}
	return;
}


//common statistics
int mallocStatAPrtStat(void) {
	printf("\n %s:    count     payload                     total (inclStatStructs)", __func__);
	//intf("\n mallocStatAPrtStat:    count     payload                     total (inclStatStructs)", __func__);
	//			                         01234567  01234567  0123.56789A MB
	printf("\n Mem alloc'ed: maximum  %08X  %08X  % 11.6f MB    %08X  % 11.6f MB", mallocStatMd->totlAlcNrEMax, mallocStatMd->payldAllocMax, (float)mallocStatMd->payldAllocMax/(1024.0*1024.0), mallocStatMd->totalAllocMax, (float)mallocStatMd->totalAllocMax/(1024.0*1024.0));
	printf("\n Mem alloc'ed: current  %08X  %08X  % 11.6f MB    %08X  % 11.6f MB", mallocStatMd->totlAlcNrE, mallocStatMd->payldAlloc, (float)mallocStatMd->payldAlloc/(1024.0*1024.0), mallocStatMd->totalAlloc, (float)mallocStatMd->totalAlloc/(1024.0*1024.0));
	return 0;
}


//Print all allocations
int mallocStatAPrtAllocs(int allocBufSzMaxPrt) {
	printf("\n\n\n Printing all allocs: (last alloc'ed are prt first)\n ");
	mallocStatAPrtStat();
	printf("\n");
	struct t_mallocStatAEnt **sl, *cr = NULL;
	int nrAllocs = 0, isHead = 1;
	for (sl = &mallocStatMd->mallocStatAHead; *sl != NULL; sl = &(*sl)->data.next) {
		//check the entries along the way.
		int misMatch = mallocStatACheck(*sl, 1); misMatch = misMatch; //suppress warnings
		//struct t_mallocStatAEnt *par = (void*)sl; //relying that 'next' is at the very start of the structs
		cr = *sl;
		int szAlign = (cr->data.size +3) & (~3); //align to 4 bytes
		int tSz = sizeof(struct t_mallocStatAEnt) + szAlign + sizeof(struct t_mallocStatAEnt); //total size
		//printf("\n misMatch %03X ", misMatch);
		char *funcNm = "MSPA"; //__func__;
		#if __x86_64__ || _WIN64 //GCC 64 or Win 64
		printf("\n %s:ix %04X tBf %08llX tSz %08X  bf %08llX sz %08X", funcNm, nrAllocs, (u64)cr, tSz, (u64)cr->mem, cr->data.size);
		#else
		printf("\n %s:ix %04X tBf %08X tSz %08X  bf %08X sz %08X", funcNm, nrAllocs, (u32)cr, tSz, (u32)cr->mem, cr->data.size);
		#endif
		#if MALLOCANDCLR_LINENR != 0
		printf("  line %5d ", (u32)cr->data.callerAddr);
		#else
		printf("  cllr %p ",  cr->data.callerAddr);
		#endif
		printf(" funcNm >%s<", cr->data.callerFuncName); //printed separately in case it crashes
		printf("\n");
		if (allocBufSzMaxPrt > 0) {
			int sz = MIN_CMP(allocBufSzMaxPrt, cr->data.size);
			void hexePrtA(void *data, int sz, char *descr);
			hexePrtA(cr->mem, sz, "");
			printf("\n\n");
		}
		isHead = 0;
		nrAllocs++;
	}
	return nrAllocs;
}

/*

int mallocStatAChkList(int doPrt)	//call this among the code, where you doubt that something of the alloc structs might have been overwritten
//the free() func does the same, so it should detect if something got overwritten 
	mallocStatAPrtAllocs();	//call this at the end of the code, when all malloc()-s have been freed. It will list those that weren't freed.

The free-code also prints if a malloc is attempted to be freed more than once and does not free it in that case. 

	waitUInp();
*/



//https://stackoverflow.com/questions/16100090/how-can-we-know-the-caller-functions-name
//https://stackoverflow.com/questions/4983480/how-to-map-a-function-name-and-line-number-by-a-memory-address-in-c-language
//https://sourceware.org/binutils/docs/binutils/addr2line.html

//See funcs above. This gives a lot of useful info, but is very slow.
#define MALLOCANDCLR_STAT 0

//each malloc prints where it was called from - not too useful
#define MALLOCANDCLR_DEBUG 0


#if MALLOCANDCLR_STAT == 1

	void mallocStatAChkListPrtAllAllocs(int doPrt, int allocBufSzMaxPrt) {
		mallocStatAChkList(doPrt);
		mallocStatAPrtAllocs(allocBufSzMaxPrt);
	}

	#define mallocAndClr(x) mallocAndClrIn((x), (char*)__func__, __LINE__)
	void *mallocAndClrIn(int sz, char *callerFuncName, u32 lineNr) {
		void *cp = __builtin_return_address(0);

		void *bf = mallocStatAAlloc(sz, cp, callerFuncName, lineNr, 1);

		//void *cp = __builtin_return_address(0); //int level);
		//printf("\n %s: Caller %p  %08X  %s ", __func__, cp, sz, callerFuncName);
	  /* if (sz == 0) { //used in CLB structure creation
		   //printf("\n WARN: mallocAndClr() attempted to alloc zero-sized area ");
		   return NULL; //don't allocate zero-sized areas
		}
		void *bf = malloc(sz);
		if (bf != NULL) { memset(bf, 0x00, sz); 
		} else {
			//void *cp = __builtin_return_address(0);
			printf("\n ERR: mallocAndClr() failed to allocate %08X memory. Caller %p ", sz, cp);
		} */
		return bf;     
	}

	#define mallocAndChk(x) mallocAndChkIn((x), (char*)__func__, __LINE__)
	void *mallocAndChkIn(int sz, char *callerFuncName, u32 lineNr) {
		void *cp = __builtin_return_address(0);
		void *bf = mallocStatAAlloc(sz, cp, callerFuncName, lineNr, 0); //alloc without clearing
		return bf;     
	}

	int freeIfNotNull(void *bf) {
		mallocStatAFree(bf);
		//if (bf != NULL) free(bf);
		return 0;
	}

#else

	void mallocStatAChkListPrtAllAllocs(int doPrt, int allocBufSzMaxPrt) {}

	#if MALLOCANDCLR_DEBUG == 1
	#define mallocAndClr(x) mallocAndClrIn((x), (char*)__func__, __LINE__)
	void *mallocAndClrIn(int sz, char *callerFuncName, u32 lineNr) {
	#else
	void *mallocAndClr(int sz) {
	#endif
		void *cp = __builtin_return_address(0);
		#if MALLOCANDCLR_DEBUG == 1
		//void *cp = __builtin_return_address(0); //int level);
		printf("\n %s: Caller %p  %08X  %s: %d", __func__, cp, sz, callerFuncName, lineNr);
		#endif
		if (sz <= 0) { //used in CLB structure creation
		   //printf("\n WARN: mallocAndClr() attempted to alloc zero-sized area ");
		   return NULL; //don't allocate zero-sized areas
		}
		void *bf = malloc(sz);
		if (bf != NULL) { memset(bf, 0x00, sz); 
		} else {
			//void *cp = __builtin_return_address(0);
			printf("\n ERR: %s() failed to allocate %08X memory. Caller %p ", __func__, sz, cp);
		}
		return bf;     
	}

	#if MALLOCANDCLR_DEBUG == 1
	#define mallocAndChk(x) mallocAndChkIn((x), (char*)__func__, __LINE__)
	void *mallocAndChkIn(int sz, char *callerFuncName, u32 lineNr) {
	#else
	void *mallocAndChk(int sz) {
	#endif
		void *cp = __builtin_return_address(0);
		#if MALLOCANDCLR_DEBUG == 1
		//void *cp = __builtin_return_address(0); //int level);
		printf("\n %s: Caller %p  %08X  %s: %d", __func__, cp, sz, callerFuncName, lineNr);
		#endif
		if (sz <= 0) { //used in CLB structure creation
		   //printf("\n WARN: mallocAndClr() attempted to alloc zero-sized area ");
		   return NULL; //don't allocate zero-sized areas
		}
		void *bf = malloc(sz);
		if (bf != NULL) { //memset(bf, 0x00, sz); 
		} else {
			//void *cp = __builtin_return_address(0);
			printf("\n ERR: %s() failed to allocate %08X memory. Caller %p ", __func__, sz, cp);
		}  
		return bf;     
	}

	int freeIfNotNull(void *bf) {
		if (bf != NULL) free(bf);
		return 0;
	}

#endif








//0=valid / <0 = invalid
//Yes, it's been more than a year (or two) and I still haven't got around to coding this old func.
int chkValidPath(char *path) {



	return 0;
}


//going with the most flexible way
//Win & Linux (I didn't check Linux though, but those should be the bare minimum).
//These allowed chars, are in addition to lowcase and captital letters and digits
//#define COMMON_PATH_ALLOWED_CHARS "" //no ned for now
// >=1 =valid / <=0 = invalid; Returns the path length when valid.
//maxLen sets the maximum allowed string elngth. If maxLen < 0 => not checked.
//This only checks the string - it does not try to open a file.
//If any of excludeChars is encountered, the string is flagged as non-path.
//Permitted symbols (but letters and digits):  "_.\\/:-!" (The '!' was included as there are EditWork files with path including it (if I remember correctly.) "\\/:" are delimiters and are thus allowed.
//Win forbiddeb symbols: "<>:"/\|?*"
int chkIfValidPath(char *path, char *allowedChars, char *excludeChars, int minLen, int maxLen) {
	if (path == NULL) return -1;
	int sLen = strlen(path);
	if (maxLen >= 0) if (sLen > maxLen) return -2;
	if (minLen >= 0) if (sLen < minLen) return -3;
	int i;
	int reachedDelim = 0;	//passed after the first delimiter - no ':' allowed after it - "<device>:\\<path>".
	int prevDelim = 0;		//prev char was delimiter.
	for (i=0; i<sLen; i++) {
		char c = path[i];
		if ((c == '\\') || (c == '/')) { //don't tollerate two or more consecutive delimiters like "\\\\" or "//"
			if (prevDelim != 0) return -10;
			prevDelim = 1; reachedDelim = 1;
		} else prevDelim = 0;

		if (c == ':') {
			if (reachedDelim != 0) return -11;	//The ':' can appear only once, before all delimiters.
			reachedDelim = 1;
		}

		if (excludeChars != NULL)
			if (strchr(excludeChars, c) != NULL) return -5;
		if (((c >= '0') && (c <= '9')) ||
			 ((c >= 'A') && (c <= 'Z')) ||
			 ((c >= 'a') && (c <= 'z')) ||
			 (c == '_') || (c == '.') || (c == '\\') || (c == '/') || (c == ':') || (c == '-') || (c == '!')) {
			do{}while(0);
		} else if (allowedChars != NULL) {
			if (strchr(allowedChars, c) == NULL) return -6;
		} else return -4;
	}
	return sLen;
}



//Set *flBufOut to NULL to alloacte space, otherwise it will be used as output buffer if the size is enough!
//Don't forget to free it, even if an error is returned. It should be freed always when != NULL.
//*flSzOut sets the size of the output buffer (if it was aleady allocated) else set to 0.
//returns the total number of bytes read (compare to *flSzOut to make sure all were read) or <= 0 on error 
int flGetToBuf(int *flSzOut, void **flBufOut, char *flNm) { 
   FILE *flPt;
	int ret = 0, flSz = 0;

	if ((flBufOut == NULL) || (flSzOut == NULL) || (flNm == NULL)) { ret = -2; goto errExit; }
  	flPt = fopen(flNm, "rb");
   if (flPt == NULL) {
      //printf("\n %s: ERR: Failed to open for reading >%s< \n", __func__, flNm);
		ret = -1;
      goto errExit;
   }
   
   fseek(flPt, 0, SEEK_END);
   flSz = ftell(flPt);
   fseek(flPt, 0, SEEK_SET);
   //printf("\n File sz= %08X  >%s< \n", flSz, flNm);
	
	if ((*flBufOut == NULL) || (*flSzOut < flSz)) { //no buffer allocated or too small
   	*flBufOut = mallocAndClr(flSz+1); //the +1 is in case the file has zero-length
	}
	*flSzOut = flSz;
   if (*flBufOut == NULL) {
      printf("\n %s: ERR: malloc failed to alloc %08X. \n", __func__, flSz);
		ret = -4;
      goto errExit2;
   }
	ret = fread(*flBufOut, 1, flSz, flPt); //get whole file
	
	errExit2:
	fclose(flPt);
	errExit:
	return ret;
}


//with limited size - the ammount of read data is returned. Useful when not sure how big the file is. 
//If the return value is == szLim, then it is possible that the complete file was not read. Better use flSzOut to check that.
int flGetToBufLimSz(int *flSzOut, void **flBufOut, char *flNm, int szLim) {
   FILE *flPt;
	int ret = 0, flSz = 0;

	if ((flBufOut == NULL) || (flSzOut == NULL) || (flNm == NULL)) { ret = -2; goto errExit; }
  	flPt = fopen(flNm, "rb");
   if (flPt == NULL) {
      printf("\n %s: ERR: Failed to open for reading >%s< \n", __func__, flNm);
		ret = -1;
      goto errExit;
   }
   
   fseek(flPt, 0, SEEK_END);
   flSz = ftell(flPt);
   fseek(flPt, 0, SEEK_SET);
   //printf("\n File sz= %08X  >%s< \n", flSz, flNm);
	if (flSz > szLim) flSz = szLim;

	if ((*flBufOut == NULL) || (*flSzOut < flSz)) { //no buffer allocated or too small
   	*flBufOut = mallocAndClr(flSz+1); //the +1 is in case the file has zero-length
	}
	*flSzOut = flSz;
   if (*flBufOut == NULL) {
      printf("\n %s: ERR: malloc failed to alloc %08X. \n", __func__, flSz);
		ret = -4;
      goto errExit2;
   }
	ret = fread(*flBufOut, 1, flSz, flPt); //get whole file
	
	errExit2:
	fclose(flPt);
	errExit:
	return ret;
}





//This finds a non-existing file and creates it - witha  name in the form: <namePath><extension>, or when that exists: <namePath>_<number><extension>, where number is a decimal value from 01 to 99. When all such "slots" are taken, it continues with three-digit slots and so on. When all slots are taken, returns NULL (although with the three-digit extension taht shouldn't happen).
//The number of slots are determined by maxFiles - set to -1 to get unlimited number, but limited to 10000000 (actually 8 digits 99999999).
//If the name is longer than the locally allocated string, it exits.
//openArgs should usually be "wb" but can also be "r+b"(read and write), or "ab"(append)
//freeIx gives the index chosen, from which the sued name can be reconstructed by the caller)
//when flExistsCb() returns > 0, the file is overwritten; can be NULL. flExistsCb() ret: <0=noCreate / 0=noOverwrite(createNew) / >0=overwrite
FILE *flOpenNewOutFileB(char *namePath, char *extension, int *freeIx, int maxFiles, char *openArgs, int (*flExistsCb)(void *privData, char *existsPath, FILE *existsFp), void *privData) {
	FILE *flOt = NULL;
	char *flNm = mallocAndClr(strlen(namePath) + 1 + 8 + strlen(extension) + 1 + 10); // "_12345678", '\0' and 10 more just in case
	if (flNm == NULL) return NULL;
	if (maxFiles >= 100000000) maxFiles = 100000000;

   int i = 0;
   sprintf(flNm, "%s%s", namePath, extension);
   //printf("\n %s: Output file >%s<", __func__, flNm);
   flOt = fopen(flNm, "rb");
	if (flOt != NULL) {
		if (flExistsCb != NULL) {
			int doOverwr = flExistsCb(privData, flNm, flOt);
			if (doOverwr < 0) {	//don't create at all
				fclose(flOt);
				flOt = NULL;
				goto exit;
			} else if (doOverwr > 0) {
				fclose(flOt);
				flOt = fopen(flNm, openArgs);
				goto exit;
			}
		}
	}
   while (flOt != NULL) {
      fclose(flOt);
      i++;
      if (i >= maxFiles) {
         //printf("\n %s: ERR: Failed to find free file name >%s< ix < %d \n", __func__, flNm, maxFiles);
         flOt = NULL; goto exit; //return NULL;
      }
      sprintf(flNm, "%s_%02d%s", namePath, i, extension);
      flOt = fopen(flNm, "rb");
   }
   flOt = fopen(flNm, openArgs); //"wb");   
   if (flOt == NULL) {
      //printf("\n %s: ERR: Failed to open for writing file >%s< \n", __func__, flNm);
      goto exit; //return NULL;
   }
	exit:
   freeIfNotNull(flNm);
	if (freeIx != NULL) *freeIx = i;
	return flOt;
}

FILE *flOpenNewOutFile64B(char *namePath, char *extension, int *freeIx, int maxFiles, char *openArgs, int (*flExistsCb)(void *privData, char *existsPath, FILE *existsFp), void *privData) {
	FILE *flOt = NULL;
	char *flNm = mallocAndClr(strlen(namePath) + 1 + 8 + strlen(extension) + 1 + 10); // "_12345678", '\0' and 10 more just in case
	if (flNm == NULL) return NULL;
	if (maxFiles >= 100000000) maxFiles = 100000000;

   int i = 0;
   sprintf(flNm, "%s%s", namePath, extension);
   //printf("\n %s: Output file >%s<", __func__, flNm);
   flOt = fopen64(flNm, "rb");
	if (flOt != NULL) {
		if (flExistsCb != NULL) {
			int doOverwr = flExistsCb(privData, flNm, flOt);
			if (doOverwr < 0) {	//don't create at all
				fclose(flOt);
				flOt = NULL;
				goto exit;
			} else if (doOverwr > 0) {
				fclose(flOt);
				flOt = fopen64(flNm, openArgs);
				goto exit;
			}
		}
	}
   while (flOt != NULL) {
      fclose(flOt);
      i++;
      if (i >= maxFiles) {
         //printf("\n %s: ERR: Failed to find free file name >%s< ix < %d \n", __func__, flNm, maxFiles);
         flOt = NULL; goto exit; //return NULL;
      }
      sprintf(flNm, "%s_%02d%s", namePath, i, extension);
      flOt = fopen64(flNm, "rb");
   }
   flOt = fopen64(flNm, openArgs); //"wb");   
   if (flOt == NULL) {
      //printf("\n %s: ERR: Failed to open for writing file >%s< \n", __func__, flNm);
      goto exit; //return NULL;
   }
	exit:
   freeIfNotNull(flNm);
	if (freeIx != NULL) *freeIx = i;
	return flOt;
}


FILE *flOpenNewOutFile(char *namePath, char *extension, int *freeIx, int maxFiles, char *openArgs) {
	 return flOpenNewOutFileB(namePath, extension, freeIx, maxFiles, openArgs, NULL, NULL);
}

FILE *flOpenNewOutFile64(char *namePath, char *extension, int *freeIx, int maxFiles, char *openArgs) {
	 return flOpenNewOutFile64B(namePath, extension, freeIx, maxFiles, openArgs, NULL, NULL);
}



//Just copies a file from one path to another
//maxFls specifies how many files can be tried when the output file already exists
//This func returns the out file ix on sucess, or <0 on fail.
//If the input file was read incompletely, bit 31 of the result gets set (check by: if  (res < -10))
int cpyFileByPath(char *dst, char *src, int bufSz, int maxFls) {
	if (bufSz <= 0) return -1;
	u32 *buf = mallocAndChk(bufSz);
	if (buf == NULL) return -2;

	FILE *flIn = fopen(src, "rb");
	if (flIn == NULL) { freeIfNotNull(buf); return -3; }
	fseek(flIn, 0, SEEK_END);
	int flInSz = ftell(flIn);
	fseek(flIn, 0, SEEK_SET);

	int freeIx = 0;
	FILE *flOt = flOpenNewOutFile(dst, "", &freeIx, maxFls, "wb");
	if (flOt == NULL) { freeIfNotNull(buf); fclose(flIn); return -4; }
	//if (freeIx > 0) ret |= 0x100; //the output path was not met 
	int badRd = 0;
	while (flInSz > 0) {
		int rdLen = fread(buf, 1, bufSz, flIn);
		if (rdLen > 0) fwrite(buf, 1, rdLen, flOt);
		flInSz-=bufSz;
		if ((rdLen != bufSz) && (flInSz >= 0)) badRd = 1;
	}

	freeIfNotNull(buf);
	fclose(flIn);
	fclose(flOt);
	return freeIx | (badRd <<31);
}


//Copy data of the set length, at the current file pointers from src to dst.
//should also work for 64-bit pointers. 
int cpyFileDataByFP(FILE *dst, FILE *src, s64 length, int bufSz) {
	if ((src == NULL) || (dst == NULL)) return -3;
	if (bufSz <= 0) return -1;
	u32 *buf = mallocAndChk(bufSz);
	if (buf == NULL) return -2;
	int badRd = 0;
	while (length > 0) {
		int rdLen = fread(buf, 1, bufSz, src);
		if (rdLen > 0) fwrite(buf, 1, (u32)MIN_CMP((u64)rdLen, length), dst);
		length-=bufSz;
		if ((rdLen != bufSz) && (length >= 0)) badRd = 1;
	}
	freeIfNotNull(buf);
	return (badRd <<31);
}



//TODO: move all the file access and directory funcs to a separate file sysFileIo.c

#include <dirent.h>
#include <sys/types.h>

#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>

/*stat struct:
time_t    st_atime   Time of last access. 
time_t    st_mtime   Time of last data modification. 
time_t    st_ctime   Time of last status change. 
times in seconds since Epoch ... on my...
*/


//Code to compare the time-stamps of two groups of files. The idea is to have an input files group and output files group. If any of the input files is older than the earliest output file, the func returns that the output files need to be updated.
//struct t_flCmpTimeStampA {}; //better make it simple
//The idea of this func is to reduce disc usage(wear), by not writing files that are already up-to-date. When not possible to apply it at the starting code of the converter, it can be applied at the output file building code.
//return: <0=err / 0=noUpdateNecessary / 1=updateNecessary(alsoSetONIdentocalDates)
//To decide whether to update, compare the return with 0: if it matches => noUpd / else update (on input newer or on fault).
//Only saving changes the modification date - changing the name does not change the modification date.
//inpFlGrp and outFlGrp are arrays of string pointers for the input and output files respectively and inpFlNrE, outFlNrE are their NrE
//They can be either allocated strings or on stack or in rodata - they are not modified. If they are allocated, it the responcibility of the caller to free them.
int flCmpTimeStamps(char *inpFlGrp[], int inpFlNrE, char *outFlGrp[], int outFlNrE) {
	int i;
	if (inpFlGrp == NULL) return -4;
	if (outFlGrp == NULL) return -8;
	//Find the latest-modified among the input files and the earliest-modified from the output files.
	int noInpFl = 1, noOutFl = 1;
	struct stat sa;
	u64 maxVl = 0xFFFFFFFF | (0xFFFFFFFFll <<32);
	u64 iLmSl, oLmSl, lmCr; //Selected and current lsast modification times since Epoch, in seconds.
	int imrc = -1, olrc = -1; //indexes in the file-path arrays: input most recently changed file and output least recently changed file
	iLmSl = 0;
	for (i=0; i<inpFlNrE; i++) {
		lmCr = 0; //looking for the highest value among the input files
		char *path = inpFlGrp[i];
		if (path != NULL) if (stat(path, &sa) == 0) {
			lmCr = sa.st_mtime; noInpFl = 0;
			if (iLmSl <= lmCr) { iLmSl = lmCr; imrc = i; }
		}
	}
	oLmSl = maxVl;
	for (i=0; i<outFlNrE; i++) {
		lmCr = maxVl; //looking for the lowest value among the input files
		char *path = outFlGrp[i];
		if (path != NULL) if (stat(path, &sa) == 0) {
			lmCr = sa.st_mtime; noOutFl = 0;
			if (oLmSl >= lmCr) { oLmSl = lmCr; olrc = i; }
		}
	}
	if (imrc < 0) noInpFl = 1;
	if (olrc < 0) noOutFl = 1;
	int ret = (noInpFl <<0) | (noOutFl <<1);
	if (ret != 0) return -ret;
	if (iLmSl >= oLmSl) {	//if the latest-modified input file was modified after the earliest-modified output file, the files have to be updated
		return 1;
	}
	return 0;
}



//outputs only the part of the input string after the last '/' or '\'
//Optionally it gives the length of the file name without the extension, which enables separating the extension, wither by mallocing separate string or by writing \0 over the the '.'.
//The dot is included in the ext length.
char *flPathGetFlNmAndExt(int *flNmNoExtLenO, int *extLenO, char *flPath) {
	int i = 0, flNmNeLen;
	if (flPath == NULL) return NULL;
	char *flNm = flPath;
	while (flPath[i] != '\0') {
		if ((flPath[i] == '\\') || (flPath[i] == '/')) {
			flNm = &flPath[i+1];
		}
		i++;
	}
	//if (flNmNoExtLenO != NULL) {
		flNmNeLen = -1;
		i = 0;
		while (flNm[i] != '\0') {
			if (flNm[i] == '.') flNmNeLen = i;
			i++;
		}
		if (flNmNeLen == -1) flNmNeLen = i; //wasn't set, so no '.', so no ext.
		if (flNmNoExtLenO != NULL) *flNmNoExtLenO = flNmNeLen;
		if (extLenO != NULL) *extLenO = i - flNmNeLen;
	//}
	return flNm;
}
/* Not done - may not be necessary:
//The file name here is allocated so it needs to be freed
char *flPathGetAllocFlNmAndSeparateExt(char *ext, char *flPath) {
	int i = 0;
	flNm = flPath;
	while (flPath[i] != '\0') {
		if ((flPath[i] == '\\') || (flPath[i] == '/')) {
			flNm = &flPath[i+1];
		}
		i++;
	}
	return flNm;
}*/


//compares the extension - whatever is found after the last delimiter(/\), after the last dot. If there is not extension in the string, but there is in the agrs - mistamtch.
//returns >=0 (1) on match; <0 on mismatch and on err
//If the name ends with a '\' or '/' there will be mismatch
//if ext is NULL, no comparing is done
//if ext is "", and the input string has an extension longer than 0 chars, then - mismatch.
//The dot is included in the extension length.
int flPathCmpExt(char *flPath, char *ext) {
	if (flPath == NULL) return -1;
	if (ext == NULL) return 1; //no-check "match"
	int flNmNoExtLen = 0, extLen = 0;
	char *flNm = flPathGetFlNmAndExt(&flNmNoExtLen, &extLen, flPath); 
	if (extLen != strlen(ext)) return -3; //cmp ext len
	if (strcmp(&flNm[flNmNoExtLen], ext) != 0) return -4; //compare ext
	return 1; //match
}




//Like sprintf, but allocates the output string of the necessary length and returns it. To be freed with free().
//In theory a more optiomal/faster way would be to use alloca() in a func for temporary use, but this is more universal.
#define SPRTFALLOC_MALLOC_DBG 0
#if SPRTFALLOC_MALLOC_DBG == 1
#define sprtfAlloc(...) sprtfAllocIn((char*)__func__, __VA_ARGS__)
char *sprtfAllocIn(char *callerFuncName, const char *format, ...) {
	void *cp = __builtin_return_address(0);
#else
char *sprtfAlloc(const char *format, ...) {
#endif
	va_list args, argsB;
	va_start(args, format);
	va_copy(argsB, args);
	int len = vsnprintf(NULL, 0, format, args);
	va_end(args);
	len += 1; //the return of vsnprintf() does not count the NULL terminator, while the input does, so this is necessary
	#if SPRTFALLOC_MALLOC_DBG == 1
	void *buf = mallocStatAAlloc(len, cp, callerFuncName);
	#else
	char *buf = mallocAndClr(len); //could add one more just in case
	#endif
	//va_start(args, format);
	if (buf != NULL) {
		vsnprintf(buf, len, format, argsB);
	}
	va_end(argsB);
	return buf;
}


//Connects the two strings in a new, aloocated string
char *strConAlloc(char *a, char *b) {
	if ((a == NULL) && (b == NULL)) return NULL;
	if (a == NULL) a = "";
	if (b == NULL) b = "";
	char *otStr = mallocAndClr(strlen(a) + strlen(b) + 1);
	strcat(otStr, a);
	strcat(otStr, b);
	return otStr;
}

//Like strncpy(), but allocates the output string:
//Note that strncpy() won't add a null char if the input string is longer than len, but this will. 
char *strNCpyAlloc(char *a, int len) {
	if (a == NULL) return NULL;
	if (len < 0) return NULL;
	char *otStr = mallocAndClr(len + 1);
	strncpy(otStr, a, len);
	otStr[len] = '\0';
	return otStr;
}

//Extends string a, with the length of the contents of string b and after that with c, with extension lengt for string c, set by the smallest among the length of string c and cLen.
//Should only be used on allocs made with allocAndClr().
void strNCatAlloc(char **a, char *b, char *c, int cLen) {
	if ((a == NULL) && (b == NULL) && (c == NULL)) return;
	//if (cLen < 0) return;
	int allocOptimal = 0;
	if (cLen < 0) { //used to switch to 'optimal' allocation - untested if any good
		cLen = -cLen;
		allocOptimal = 1;
	}

	int bLn = strlenNl(b); if (bLn < 0) bLn = 0;
	int cl = strlenNl(c);
	int cLn = MIN_CMP(cl, cLen); if (cLn < 0) cLn = 0;
	int eLn = bLn + cLn;
	if (*a == NULL) { //no out string alloc'ed, so alloc a new one
		*a = mallocAndClr(eLn + 1);
		if (bLn > 0) memcpy(*a, b, bLn);
		if (cLn > 0) memcpy(&(*a)[bLn], c, cLn);
		(*a)[eLn] = '\0'; //The parentheses are necessary.
	} else {
		if (eLn == 0) return; //no change, as there is nothing to add.
		int aLn = strlen(*a);
		int nLn = aLn+eLn+1;

		void *tempSpaceSave = NULL;
		if (allocOptimal) {
			tempSpaceSave = mallocAndClr(nLn+0x100); //in case the allocations are done sequentially (many calls to strNCatAlloc()) we skip some mem, to reduce fragmentation.
		}

		char *nA = mallocAndClr(nLn); //alloc space for the new string once
		if (aLn > 0) memcpy(nA, *a, aLn);
		strncpy(&nA[aLn], b, bLn);
		strncpy(&nA[aLn+bLn], c, cLn);
		nA[aLn+eLn] = '\0'; //add term zero
		freeIfNotNull(*a);
		//*a = NULL;

		if (allocOptimal) {
			//Now optionally move the new string to the old pos in memory, freeing the temporary pos:
			freeIfNotNull(tempSpaceSave);
			char *nB = mallocAndClr(nLn);
			memcpy(nB, nA, nLn); //should have the terminating zero already
			freeIfNotNull(nA);
			nA = nB;
		}
		*a = nA;
	}
	return;
}

//This is a handy function for allocating a string of tabs useful when printing a hierarchy structure
//Set extrStr to NULL (or extrLen to 0) to not use external string. If an external string is used, NULL is returned. If the external string is too short, a string is allocated and returned.
char *mkeAllocTabsOffs(char *extrStr, int extrSLen, int depth, char *tab) {
	int len = strlen(tab) * depth + 1;
	if (extrSLen < len) extrStr = NULL;
	char *str = extrStr;
	if (str == NULL) str = mallocAndClr(len);
	int i;
	for (i=0; i<depth; i++) strcat(str, tab);
	if (extrStr != NULL) return NULL;
	else return str;
}


//TODO: move all the file access and directory funcs to a separate file sysFileIo.c
#if 0
#include <dirent.h>
#include <sys/types.h>

#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

//unused - some types are not packed...
struct t_dirent {
    ino_t d_ino; /* inode number */
    off_t d_off; /* offset to the next dirent */
    unsigned short d_reclen; /* length of this record */
    unsigned char d_type; /* type of file */
    char d_name[256]; /* filename */
};


//https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c

//returns > 0 when it is a dir
int chkIfIsDir(char *path) {
   int isDir = 0;
   struct stat statbuf;
   if (stat(path, &statbuf) == 0) isDir = S_ISDIR(statbuf.st_mode);
   else isDir = -1;
   return isDir;
}


//https://stackoverflow.com/questions/18100097/portable-way-to-check-if-directory-exists-windows-linux-c
//Checks if a path is a file or directory.
//return: >0  S_IFREG=regularFile, S_IFDIR=directory;  0  dir does not exist OR exists but not a dir; <0  an error occurred (errno is also set)
//The return is masked to only return the file-type:
#if 0
#define	S_IFMT	 0170000		/* type of file */  - type-mask

#define	S_IFIFO	 0010000		/* named pipe (fifo) */
#define	S_IFCHR	 0020000		/* character special */
#define	S_IFDIR	 0040000		/* directory */
#define	S_IFBLK	 0060000		/* block special */
#define	S_IFREG	 0100000		/* regular */
#define	S_IFLNK	 0120000		/* symbolic link */
#define	S_IFSOCK  0140000		/* socket */
#endif

//XXX: This func will return -2 if the path ends in a delimiter '\\'.So make sure it doesn't.
//https://unix.superglobalmegacorp.com/Net2/newsrc/sys/stat.h.html
int pathGetPathType(char *path) {
	struct stat info;
	int statRC = stat(path, &info);
	if (statRC != 0) {
		if (errno == ENOENT)  { return -2; } //something along the path does not exist
		if (errno == ENOTDIR) { return -3; } //something in path prefix is not a dir
		return -4;
	}
	//S_IFREG / S_IFDIR
	return info.st_mode & S_IFMT;
}


//Ignore End Delimiter - removes the end-delimiter if there is some so as to prevent the func returning err on valid path with end delimiter.
int pathGetPathTypeIED(char *path) {
	int sl = strlen(path);
	sl -= 1;
	char ed = path[sl];
	if ((ed == '\\') || (ed == '/')) {
		path[sl] = '\0'; //remove the delimiter at the end
	}
	int res = pathGetPathType(path);

	if (path[sl] != ed) path[sl] = ed;
	return res;
}


//#include <windows.h>
//CreateDirectory();

#include <conio.h>
#include <process.h>
#include <dir.h>
//mkdir();


int makeDir(char *path) {
   int ret;
   //ret = CreateDirectory(path, NULL);
   ret = mkdir(path);
   return ret;    
}








//Some string-oriented funcs, useful for text files parsing:

//may need to rename these funcs late:


//If any of the characters in *s matches c, it returns 1, otherwise 0.
//Comparing stops on \0 and the \0 is not compared
int chkCharStrMatch(char c, char *s) {
	while (*s != '\0') { if (c == *s) return 1; s++; }
	return 0;
}

//As above, but also compares to '\0', so if c == '\0' the comparison will return 1 always
int chkCharStrMatchN(char c, char *s) {
	do { if (c == *s) return 1; } while (*s++ != '\0');
	return 0;
}


//String limited to number of chars copy, configurabe input delimiter, removing spaces leaving only one space
//Example: " some   Test string   ," if the ',' is specified as a delimiter will be copied as: "some Test string\0"
//can use the number of chars limit to prevent overwriting the destination. 
//THIS IS CHANGED: NOT: To detect that the copying was limited by that limit, the original necessary output string length (without counting the \0, is returned.
//Instead when the copying is limited by the number of chars, 1 is returned, othweise - 0.
//maxOutLen does not count the zero delimiter - set to -1 to not copy any chars (incl the zero delim) or set to -2 or less to not use a limit. 
//foldSyms = " ;" would "fold" all ' ' and ';' inside the string to a single instance of those symbpls, and any instance at the ends of the string would be folded to no symbols - removed. Note a sequence "  ;;;Some  ;  ; ;;  string;;;   ;" would result in: ";Some ; ; ; string; ". Useful when converting C combinations of identifiesrs with spaces.
//EDIT: the foldSyms function is canged to convert them all to space, so the result of the example will be "Some string". It can also be used to fold both intervals and tabs to intervals. Usual use " \t".
//inDelims sets the input delimiters. For CSV file - ",\r\n".
//\0 shows end of string and is not used in the symbols to fold. \0 is allways an input and output delimiter.
//Any inDelims in a row are converted to a single space. Any inDelims at the start or end of the entire string are removed.
//maxLen: <=-2 no limit; ==-1 - no chars; 0-> only the terminating zero; >= 1 - only counts the actual string characters.
int strncpyDlmSpc(char *dst, char *src, int maxLen, char *foldSyms, char *inDelims) {
	if ((dst == NULL) || (src == NULL)) return -3;
	if (maxLen == -1) return 2; //copying so limited, it didn't even copy the terminating zero
	int stFlg = -1;
	while (chkCharStrMatchN(*src, inDelims) == 0) {
		//notice - equal comparing, so an input of -2 would never equal 0, unless a VERY long string and s32 overflows.
		if (maxLen == 0) { if (stFlg == 0) dst--; *dst = '\0'; return 1; } //copying limited
		if (chkCharStrMatch(*src, foldSyms) == 0) { //normal char => copy it 
			*dst++ = *src;
			maxLen--;
			stFlg = 1;
		} else {
			if (stFlg > 0) { *dst++ = ' '; maxLen--; } //*src; //copy the first char after normal chars too as an interval
			stFlg = 0; 
		}
		src++;
	}
	if (stFlg == 0) dst--; //remove the last char, if it is a folded symbol
	*dst = '\0'; // place the terminating zero
	return 0;
}


//EDIT: Both are processed assuming the delimiters in inDelims, including '\0'. NOT: Processes both input strings similarly to the above - dst must be zero-terminated,
//while src can use any of the terminators specified in inDelims.
//foldSyms processing is applied to both strings while comparing them, similarly to the above.
//reurns 0 on macth, 1 on mismatch and < 0 on err  
//maxLen is synchronized to dst and not sync'ed to src.
//Any number of folded symbols is assumed to equal any combination other folded symbols.
//folded symbols at the very start and end are not compared, so the following strings match with folds=" \t", delims="\n,"
//" \t struct\t t_someStuctType ,"  "struct t_someStuctType"

int strncmpDlmSpc(char *dst, char *src, int maxLen, char *foldSyms, char *inDelims) {
	if ((dst == NULL) || (src == NULL)) return -3;
	if (maxLen == -1) return 2; //comparing so limited, it didn't even copy the terminating zero
	int sFSym = 0;
	int dFSym = 0;
	int stFlg = 0;
	while (1) {    
		//notice - equal comparing, so an input of -2 would never equal 0, unless a VERY long string and s32 overflows.
		//If it survived this far, then they match:
		if (maxLen == 0) { return 0; }

		sFSym = 0; dFSym = 0;
		//Skip through all folded symbols in each
		while (chkCharStrMatch(*src, foldSyms) != 0) { //folded symbol
			//in reality none of the folded symbols should match the delimiter symbols, in which case the following check is unneeded
			if (chkCharStrMatchN(*src, inDelims) != 0) return 1; //mismatch
			src++;
			sFSym = 1;
		}
		while (chkCharStrMatch(*dst, foldSyms) != 0) { //folded symbol
			//in reality none of the folded symbols should match the delimiter symbols, in which case the following check is unneeded
			if (chkCharStrMatchN(*dst, inDelims) != 0) return 1; //mismatch
			dst++; maxLen--;
			if (maxLen == 0) { return 0; }
			dFSym = 1;
		}
		
		int si = chkCharStrMatchN(*src, inDelims);
		int di = chkCharStrMatchN(*dst, inDelims);
		//printf("\n si di %d %d ", si, di);
		if (si != di) return 1; //one end-delimiter was reached, but the other was not => mismatch
		else if (si == 1) return 0; //both match and are end-delimiters, so exit signalling match

		if (stFlg == 0) { //in the folded symbols are at the very start => don't compare it
         stFlg = 1; //no longer at the start
      } else {
		   if (sFSym != dFSym) { return 1; } //mismatch
      }
		//Now the current symbol should be a normal char
		//printf("\n norm sym %c ?= %c ", *src, *dst);
		if (*src++ != *dst++) { return 1; } //mismatch
		maxLen--;
		if (maxLen == 0) { return 0; }
	}
	return 0;
}

#if 0
//incorrect code - doesn't handle single fold syms at the start correctly
int strncmpDlmSpc(char *dst, char *src, int maxLen, char *foldSyms, char *inDelims) {
	if ((dst == NULL) || (src == NULL)) return -3;
	if (maxLen == -1) return 2; //comparing so limited, it didn't even compare the terminating zero
	int sFSym = 0;
	int dFSym = 0;
	int stFlg = 1;
	while (1) {
		int si = chkCharStrMatchN(*src, inDelims);
		int di = chkCharStrMatchN(*dst, inDelims);
		if (si != di) return 1; //one end-delimiter was reached, but the other was not => mismatch
		else if (si == 1) return 0; //both match and are end-delimiters, so exit signalling match
      if (sFSym != dFSym) { return 1; }
      
		//notice - equal comparing, so an input of -2 would never equal 0, unless a VERY long string and s32 overflows.
		//If it survived this far, then they match:
		if (maxLen == 0) { return 0; }

		sFSym = 0; dFSym = 0;
		//Skip through all folded symbols in each
		while (chkCharStrMatch(*src, foldSyms) != 0) { //folded symbol
			//in reality none of the folded symbols should match the delimiter symbols, in which case the following check is unneeded
			if (chkCharStrMatchN(*src, inDelims) != 0) return 1; //mismatch
			src++;
			sFSym = 1;
		}
		while (chkCharStrMatch(*dst, foldSyms) != 0) { //folded symbol
			//in reality none of the folded symbols should match the delimiter symbols, in which case the following check is unneeded
			if (chkCharStrMatchN(*dst, inDelims) != 0) return 1; //mismatch
			dst++; maxLen--;
			if (maxLen == 0) { return 0; }
			dFSym = 1;
		}
		if (stFlg == 0) { //in the folded symbols are at the very start => don't compare it
		   if (sFSym != dFSym) { return 1; } //mismatch
		   stFlg = 1; //no longer at the start
      }
		//Now the current symbol should be a normal char
		
		//printf("\n norm sym %c ?= %c ", *src, *dst);
		if (*src++ != *dst++) { return 1; } //mismatch
		maxLen--;
		if (maxLen == 0) { return 0; }
		
		sFSym = 0; dFSym = 0;
		//Skip through all folded symbols in each
		while (chkCharStrMatch(*src, foldSyms) != 0) { //folded symbol
			//in reality none of the folded symbols should match the delimiter symbols, in which case the following check is unneeded
			if (chkCharStrMatchN(*src, inDelims) != 0) return 1; //mismatch
			src++;
			sFSym = 1;
		}
		while (chkCharStrMatch(*dst, foldSyms) != 0) { //folded symbol
			//in reality none of the folded symbols should match the delimiter symbols, in which case the following check is unneeded
			if (chkCharStrMatchN(*dst, inDelims) != 0) return 1; //mismatch
			dst++; maxLen--;
			if (maxLen == 0) { return 0; }
			dFSym = 1;
		}
		//if (sFSym != dFSym) { return 1; } //mismatch - checked on start, 
		//after checking for end-delims, so that one string can have foldSyms at the end, 
		//and still match to another that hasn't got any
	}
	return 0;
}
#endif


//This may be considered an odd function - it counts all the symbols in a string, 
//without counting those specified in foldSyms, with the exceptions specified in strncpyDlmSpc()
//and stops comparing when any of the delimiters specifoed is encountered.
//So basically it gives the length of the output string strncpyDlmSpc() would give.
//if countinng reaches endPtr, the counting stops and the function returns the current count.
int strlenDlmSpc(char *src, char *foldSyms, char *inDelims, char *endPtr) {
	int cnt = 0;
	if (src == NULL) return -3;
	int stFlg = 0;
	while (chkCharStrMatchN(*src, inDelims) == 0) {
		if (src >= endPtr) return cnt;
		if (chkCharStrMatch(*src, foldSyms) == 0) { //normal char => copy it 
			cnt++;
			stFlg = 1;
		} else {
			if (stFlg) { cnt++; } //count the first char after normal chars too as an interval
			stFlg = 0; 
		}
		src++;
	}
	if ((stFlg == 0) && (cnt > 0)) cnt--; //remove the last char, if it is a folded symbol
	return cnt;
}


//TODO: maybe make variants of these without end pointers:

//returns a pointer to the first occurance of char c in the string, or NULL if not found.
char *strchrDlm(char *src, char c, char *inDelims, char *endPtr) {
	if (src == NULL) return NULL;
	while (chkCharStrMatchN(*src, inDelims) == 0) {
		if (src >= endPtr) return NULL;
		if (*src == c) return src; //match
		src++;
	}
	return NULL; //not found
}



//allocates the necessary space and copies to it the given string after processing it like strncpyDlmSpc(). 
//The output string is '\0'-terminated.
#define STRCPYALLOCDLYSPC_MALLOC_DBG 0
#if STRCPYALLOCDLYSPC_MALLOC_DBG == 1
#define strcpyAllocDlmSpc(x,y,z,w) strcpyAllocDlmSpcIn((char*)__func__, (x), (y), (z), (w))
char *strcpyAllocDlmSpcIn(char *callerFuncName, char *src, char *foldSyms, char *inDelims, char *endPtr) {
	void *cp = __builtin_return_address(0);
#else
char *strcpyAllocDlmSpc(char *src, char *foldSyms, char *inDelims, char *endPtr) {
#endif
	if (src == NULL) return NULL;
	int l = strlenDlmSpc(src, foldSyms, inDelims, endPtr);
	if (l < 0) return NULL;
	//l;// += 1; //terminating zero
	#if STRCPYALLOCDLYSPC_MALLOC_DBG == 1
	void *pt = mallocStatAAlloc(l + 1, cp, callerFuncName);
	#else
	char *pt = mallocAndClr(l+1);
	#endif
	if (pt == NULL) return NULL;
	strncpyDlmSpc(pt, src, l, foldSyms, inDelims); //here l only specifies the text characters and doesn't count the terminating zero
	return pt;
}

//This is a more accurate func - it always returns (allocates) a non-NULL buffer (unless allocation fails), because there can be emty CSV fields after the current line has ended, which makes csvGetNextVal() and others return NULL, so this will get NULL as input when it should return simply an empty field.
char *strcpyAlwAllocDlmSpc(char *src, char *foldSyms, char *inDelims, char *endPtr) {
	if (src == NULL) {
		char *pt = mallocAndClr(4);
		if (pt == NULL)
		*pt = '\0';
		return pt;
	}
	int l = strlenDlmSpc(src, foldSyms, inDelims, endPtr);
	if (l < 0) return NULL;
	//l;// += 1; //terminating zero
	char *pt = mallocAndClr(l+1);
	if (pt == NULL) return NULL;
	strncpyDlmSpc(pt, src, l, foldSyms, inDelims); //here l only specifies the text characters and doesn't count the terminating zero
	return pt;
}

//XXX: there is also isxdigit()
//checks if the given string contains only decomal digits
//space characters set by foldSyms are skiped and not checked - still can eturn true with them inside.
int isOnlyDecDigitsDlmSpc(char *src, char *foldSyms, char *inDelims, char *endPtr) {
	if (src == NULL) return -3;
	while (chkCharStrMatchN(*src, inDelims) == 0) {
		if (src >= endPtr) return 1;
		if (chkCharStrMatch(*src, foldSyms) == 0) { //normal char => check it
			if (!isdigit(*src)) return 0; //found non-digit symbol
		}
		src++;
	}
	return 1; //all are digits XXX: bit there could be separators between them
}




//returns the next equal or higher power of two - for alignment
//align - specifies maximum alignment - if 0 - no max. - value in bytes (usually 4 for 32-bit systems). Must be a power of 2.
u32 getNextEqGtPowTwo(u32 val, int align) {
	/* what was I writing..? u32 v = 1;
	while (val > v) {
		if (align > 0) if (v >= align) break;
		v = v <<1;
	}
	return v;
	*/
	return (val + (align -1)) & (~(align -1));
}


//Returns the value that needs to be added to v, for it to be aligned to the next boundry specified by align.
//Only specify powers of two for align.
u32 getAlignVal(u32 v, u32 align) {
	#if 1
	//uses the lowest bit of align for align value
	int i = 0;
	for (i=0; i<32; i++) {
		if (align & (1<<i)) { align = 1<<i; break; }
	}
	#endif
	u32 mask = align -1;
	v &= mask;
	if (v == 0) return 0;
	else return align - v;
}


int getFlSzByPath(char *path) {
   int ret = 0;
	if (path == NULL) return -1;
	//printf("\n %s: >%s< ", __func__, path);
	//waitUInp();
	//printf("\n fopen ");
	FILE *flPt = fopen(path, "rb");
	//printf("\n flpt %08X ", (u32)flPt);
   if (flPt == NULL) return -1;
   fseek(flPt, 0, SEEK_END);
   ret = ftell(flPt);
   fclose(flPt);
   return ret;
}     



//Change all the directory delimiters to a specified character.
//Changes both '\' and '/'.
int dirChangeAllDelim(char *path, char delim) {
	if (path == NULL) return -1;
	char *p = path;
	while (*p != '\0') {
		if ((*p == '\\') || (*p == '/')) { *p = delim; } 
		p++;
	}
	return 0;
}



//Makes the directories (depth listed) in (the string) pathB, (placed) under pathA. It doesn't make any of the dirs in pathA.
//Basically concatenates pathB after pathA and in this so created path, creates any missing directories.
//Either pathA or pathB can be NULL.
//If pathA is NULL, all the non-existing dirs in pathB will be created.
//If pathB is NULL, nothing is done.
//pathOt can be used to get the allocated string containing the concatenated pathA, pathB (has to be freed by the caller). If it is NULL, the it is freed internally.
//maxDirs - sets the maximum depth in directories (from pathB) to be created. If set to 0 (Not to -1!), this returns the total number of directories in pathB, regardless how many of them already exist. If set to -1, then debug info is printed.
//Returns the total number of directories created (but if some of them existed, they are also counted). If maxDirs is less than the dirs in pathB, then maxDirs will be returned.
//Input directories can be specified with either '\\' or '/' delimiter (converts it internally).
//No delimiter is added betwen pathA and pathB, so take care to add one if necessary.
//Only the directories in pathB, followed by "\\", are created. So if pathB contains only directories, for the last one of them to be created, it has to end with "\\". 
int dirMakePathLimit(char **pathOt, char *pathA, char *pathB, int maxDirs) {
	int nrMadeDirs = 0;
	int lenA = 0, lenB = 0;
	char *pA = "\0", *pB = "\0"; //init to empty strings
	if (pathA != NULL) { lenA = strlen(pathA); pA = pathA; }
	if (pathB != NULL) { lenB = strlen(pathB); pB = pathB; } else { return -1; }
	int lenT = lenA + lenB; 
	#if 0
	//Disabled to allow files with no name - only extension perhaps somehow... XXX: Is this safe? (For some blender exported anims with cut names so their names end-up empty.)
	if (lenT <= 0) return -2; //bad args
	#endif
	lenT += 4; //in case delimiter is added between the two
	char *path = mallocAndClr(lenT);
	if (path == NULL) return -3;
	//if (pathA != NULL) strcat(path, pathA);
	//if (pathB != NULL) strcat(path, pathB);
	//char *delim = "\0"; //for now auto-delimiter is unsupported - seems cleaner, better be configurable - with yet another string arg.
	//sprintf(path, "%s%s%s", pA, delim, pB);
	sprintf(path, "%s%s", pA, pB);
	char *a = &path[0], *b = &path[lenA];
	dirChangeAllDelim(path, '\\'); //change to win-delim
	char *c = b, *oc = b; //curent char and old char
	while (*c != '\0') {
		if (*c == '\\') {
			*c = '\0';
			int l = strlen(oc);
			if (l > 0) {
				if (maxDirs == -1) printf("\n Found dir: >%s< dirs %08X ", path, nrMadeDirs);
				if (maxDirs != 0) {
					if ((nrMadeDirs >= maxDirs) && (maxDirs > 0)) break; //before creating another dir
					if (maxDirs == -1) printf("\n Making dir: >%s<  dirs %08X ", path, nrMadeDirs);
					if (maxDirs > 0) makeDir(path);
				}
				nrMadeDirs++;
			}
			*c = '\\';
			oc = c+1;
		}
		c++;
	}
	if (pathOt != NULL) *pathOt = path; else freeIfNotNull(path);
	return nrMadeDirs;
}


enum {
	RMVFILE_INACT = 0,
	RMVFILE_REMOVE = 1,
	RMVFILE_SIMULATE,
	RMVFILE_MAX
};
//the file is removed only if ctrlFlag == 1
//ctrlFlag: 2: only simulate and print the file that would otherwise be removed 
int removeFile(char *path, int ctrlFlag, int verbose) {
	int ret = 0;
	if (ctrlFlag == RMVFILE_SIMULATE) printf("\n WARNING: Will remove >%s< ", path);
	if (ctrlFlag == RMVFILE_REMOVE) {
		if (verbose > 0) printf("\n REMOVING: >%s< ", path);
		ret = remove(path);
		if (ret < 0) ret = -errno;
		if (verbose > 0) printf("  result 0/errno %d ", ret);
	}
	return ret;
}




//TODO: Currently I can't code this well - i don't have good ideas, so it is made only so that it mostly works.

//Open an output file - creates directories to it; creates it or overwrites an existing one according to settings:
//
//Replace by time stamp modification date enabled:
//Checks if the specified output file exists and if so, compares its modification date with the earliest of the files of inpFlGrp. If the earliest-modified of inpFlGrp[] was modified at the same time or after the existing output file, then the output file is deleted and a new one is created. If the input file last modfication was done before the creation of the (already-existting) output file, then nothing is done (no output file is created, nothing is removed).
//Else if file-overwriting is enabled, the output file is always overwritten.
//Else if simulation is enabled, then the code only prints what it would overwrite, without actually creating any output files.
//Else if new-file-creation is enabled, an incrementing index is added to the filename, just before the extendion, which is incremented until a file with matching name doen not exist. This is done to maxFiles limit.
//If the output directory does not exist, and create-output-dirs is not enabled, then no output file is created. Else the function creates all the folders in the file-path.
//When replacing an already existing file, the old file is first removed and then the new one is created.

//pathSt (can be NULL or emty string) is concatenated with pathEn to crete the full path. Only directories listed in pathEn are created.
//Directory creation stops when maxDirs are created (or when all directories in the path hierarchy have been created). If a directory exists, it is not created.
//To prevent directory creation, set maxDirs to 0. Setting maxDirs to -1 makes it print the directories it would create, without creating them.

//cfg:
enum {
	//FONOROF_MKE_PATH_DIRS = 1<<0,
	FONOROF_OUTFL_MASK	= 0xF<<0,
	FONOROF_OUTFL_NO_ACT	= 0<<0,
	FONOROF_OUTFL_NEW 	= 1<<0,	//Creates a new one by adding an index (limited to maxFiles) if it exists.
	FONOROF_OUTFL_OVERWR = 2<<0,	//Always overwrite the output file.
	FONOROF_OUTFL_OVRTIM = 3<<0,	//Overwrite (remove, create / new) only if its (the old file) last modification date is before the lastes modification date of any of inpFlGrp[].
	FONOROF_OUTFL_SIM 	= 4<<0,	//simulate overwriting and print was would have been overwritten without removing anything or creating any output file.

	FONOROF_NEED_UPD 		= 1<<8,	//set when flCmpTimeStamps() returns non-zero; this is only used in the return of flChkNewOrReplOutFile() - if this is not set, then there is no need to continue making the output file
};

//XXX: If any of  pathSt and pathEn, extension, openArgs are NULL, the output func should replace them (in a local copy of this struct) with its own, so they don't need to be set if they are not known at the time this struct is first created.
//Usually this struct is mainly used to carry flOutCfg, otFlDoUpd(sometimes), inFlGrp, inFlNrE and the file & dir creation settings - maxDirs, maxFls.
struct t_fonorof {
	int	retOt;		//output return value from flOpenNewOrReplOutFile()
	char	*pathSt;		//start part of the path - none of the directories in this string will be created
	char	*pathEn;		//path, name (directories in this string will be created)
	char	*extension;	

	s8		flOutCfg;	//cfg to flOpenNewOrReplOutFile() (systemFuncs.c): FONOROF_OUTFL_NEW, FONOROF_OUTFL_OVERWR, FONOROF_OUTFL_OVRTIM, FONOROF_OUTFL_SIM
	s8		otFlDoUpd;	//set when the output file has to be updated 
	s16	rfu;
	char	**inpFlGrp;	//lists all input files (accessible paths) - used to check their last-modification dates. When the latest of these is after the modification date of the old output file, it is created (if set so by flOutCfg). Can be NULL. This is freed by the free func, so set it to NULL in this struct if you need it afterwards or it is on stack!
	int	inpFlNrE;	//nrE of inFlsTab; can be 0

	int	maxDirs;		//maximum number of directories to create (depth) 0=createNone; -1=debug; default - set to 20

	int	freeIx;		//index of the file, when overwriting is disabled; set by flChkOpenNewOrReplOutFile()
	int	maxFls;		//maximum number of files to create when using indices (not overwriting)
	char	*openArgs;	//args to use for the open func - usually "r+b" or "w+b"
	int	verbose;		//0= print mtime outFl update info / <0 don't print
};

void fonorofFree(struct t_fonorof *f) {
	if (f == NULL) return;
	int i;
	freeIfNotNull(f->pathSt);		f->pathEn = NULL;
	freeIfNotNull(f->pathEn);		f->pathEn = NULL;
	freeIfNotNull(f->extension);	f->extension = NULL;
	if (f->inpFlGrp != NULL) {
		for (i=0; i<f->inpFlNrE; i++) freeIfNotNull(f->inpFlGrp[i]);
	}
	freeIfNotNull(f->inpFlGrp);	f->inpFlGrp = NULL;
	freeIfNotNull(f->openArgs);	f->openArgs = NULL;
	freeIfNotNull(f);
	return;
}

/*
default init code example:
	struct t_fonorof *fn = mallocAndClr(sizeof(struct t_fonorof));
	//or 	struct t_fonorof fnD, *fn = &fnD; memset(fn, 0x00, sizeof(struct t_fonorof));
	fn->flOutCfg = FONOROF_OUTFL_NEW;
	fn->maxDirs = 20;
	fn->maxFls = 100;

	printf() //program manual
	fonorofPrtArgsDesc("-w");
	...	//args parsing
	case 'w': //output file write config
		i++;
		fonorofOutFlCfg2fn(fn, argv[i]); // new / overwrite / ovrwmtime / simulate
		break;
	...

	char *inpFlGrp[2]; //variant, using struct on stack
	inpFlGrp[0] = fbxFilePathNm;
	inpFlGrp[1] = skbFilePathNm;
	fn->inpFlGrp = inpFlGrp;
	fn->inpFlNrE = CONST_ARR_NRE(inpFlGrp);

	//Optional:
	fn->pathEn = ntoFlPath;
	fn->extension = pathExt;
	int doCrtOutFl = flChkNewOrReplOutFile(fn);
	if ((doCrtOutFl & FONOROF_NEED_UPD) == 0) {	//don't overwrite
		goto errExit2; //skip conversion and output file creation
	}


	//main conversion code

	struct t_xffMainHdrCfg *xffCfg;
	xffCfg->cfg->fonorof = fn;
	//OR 
	FILE *flOt = flOpenNewOrReplOutFileFn(fn);

	//output file building

	fn->pathEn = NULL; fn->extension = NULL; //if used
	fn->inpFlGrp = NULL; fn->inpFlNrE = 0; //as they are on stack (and the actual strings come from elsewhere), so they shouldn't be freed by this
	fonorofFree(fn);
	
//if none of the above is done and xffCfg->cfg->fonorof is NULL, the XFF-builder code sould work just as it did originally - create a new file with index added if an old one exists.
	
*/


//describes the string args to fonorofOutFlCfg2fn
//The option code is usually  "-w". 	fonorofPrtArgsDesc("-w");
void fonorofPrtArgsDesc(char *optCode) {
	 //fonorofArgDescStr = 
	printf("\n  %s new        If the output file exsists, an incrementing index is added to the created one (default).", optCode);
	printf("\n  %s overwrite  The output file is overwriten (without asking for confirmation)", optCode);
	printf("\n  %s ovrwmtime  The output file is overwriten only if it is older than any of the input files, else no output file is created.", optCode);
	printf("\n  %s simulate   Same as \"overwrite\" but only prints what would be removed without doing anything.", optCode);
	//printf("\n -w overwrite  Forces overwriting of all output sheet files (without confirmation). Use with care! ");
	//printf("\n -w simulate  Only prints the paths of (without removing) the files that will be removed by the \"-w overwrite\". Best run this once to make sure no important file will be removed by the overwrite option.");
	return;
}

//used to decode the -w option of the input args
// new / overwrite / ovrwmtime / simulate
int fonorofOutFlCfg2fn(struct t_fonorof *fn, char *str) {
	if (str == NULL) return -1;
	if (strcmp(str, "new") == 0) fn->flOutCfg = FONOROF_OUTFL_NEW; //default
	else if (strcmp(str, "overwrite") == 0) fn->flOutCfg = FONOROF_OUTFL_OVERWR;
	else if (strcmp(str, "ovrwmtime") == 0) fn->flOutCfg = FONOROF_OUTFL_OVRTIM;
	else if (strcmp(str, "simulate") == 0) fn->flOutCfg = FONOROF_OUTFL_SIM;
	return 0;
}

FILE *flOpenNewOrReplOutFileFn(struct t_fonorof *fn) {
	if (fn == NULL) return NULL;
	int r = 0, ret = 0, outFlCfg = fn->flOutCfg & FONOROF_OUTFL_MASK;
	FILE *flPt = NULL;
	char *pathNm = NULL;
	r = dirMakePathLimit(&pathNm, fn->pathSt, fn->pathEn, fn->maxDirs);
	if (pathNm == NULL) { ret = -10; goto errExit; }
	
	char *flNm = strConAlloc(pathNm, fn->extension);
	if (flNm == NULL) { ret = -12; goto errExit2; }

	int rmvFlg = RMVFILE_INACT; fn->otFlDoUpd = 0;
	int maxFls = 1;
	switch (outFlCfg) {
		case FONOROF_OUTFL_NEW: maxFls = fn->maxFls; rmvFlg = RMVFILE_INACT; fn->otFlDoUpd = 1; break;
		case FONOROF_OUTFL_OVERWR: rmvFlg = RMVFILE_REMOVE; fn->otFlDoUpd = 1; break;
		case FONOROF_OUTFL_OVRTIM:
			fn->otFlDoUpd = flCmpTimeStamps(fn->inpFlGrp, fn->inpFlNrE, &flNm, 1);
			rmvFlg = (fn->otFlDoUpd == 0) ? RMVFILE_INACT : RMVFILE_REMOVE;
			break;
		case FONOROF_OUTFL_SIM: rmvFlg = RMVFILE_SIMULATE; break;
	};

	r = removeFile(flNm, rmvFlg, 0);
	if (fn->verbose >= 0)
	//if ((-r) != ENOENT) 
	if (r < 0) printf("\n Couldn't remove file errno %d  >%s<", -r, flNm);
	freeIfNotNull(flNm);
	
	if (outFlCfg != FONOROF_OUTFL_SIM) {
	if (fn->otFlDoUpd != 0) {
		if (fn->verbose >= 0) if (outFlCfg == FONOROF_OUTFL_OVRTIM) printf("\n OtFl -OLD (overwrie)  >%s%s<.", pathNm, fn->extension); // printf("\n OutFl - updating (writing) >%s%s<.", pathNm, fn->extension);
		flPt = flOpenNewOutFile(pathNm, fn->extension, &fn->freeIx, maxFls, fn->openArgs);
	} else {
		if (fn->verbose >= 0) if (outFlCfg == FONOROF_OUTFL_OVRTIM) printf("\n OtFl -RECENT (no act) >%s%s<.", pathNm, fn->extension); //printf("\n OutFl is recent enough (no act) >%s%s<.", pathNm, fn->extension);
	}
	}

	errExit2:
	freeIfNotNull(pathNm);
	errExit:
	fn->retOt = ret;
	return flPt;
}

//cfg is the same as for the above
//Checks whether according to settings and file presence and modification date, to create a new output file, overwrite the old one, or do nothing.
int flChkNewOrReplOutFile(struct t_fonorof *fn) {
	if (fn == NULL) return -1;
	if (fn->pathEn == NULL) return -1;
	int ret = 0, outFlCfg = fn->flOutCfg & FONOROF_OUTFL_MASK;
	char *pathSt = fn->pathSt; if (pathSt == NULL) pathSt = "";
	char *pathEn = fn->pathEn; if (pathEn == NULL) pathEn = "";
	char *extension = fn->extension; if (extension == NULL) extension = "";
	char *flNm = sprtfAlloc("%s%s%s", pathSt, pathEn, extension);
	if (flNm == NULL) { ret = -12; goto errExit; }

	int rmvFlg = RMVFILE_INACT; fn->otFlDoUpd = 0; //, needUpdOutFl = 0;
	switch (outFlCfg) {
		case FONOROF_OUTFL_NEW: fn->otFlDoUpd = 1; break;
		case FONOROF_OUTFL_OVERWR: fn->otFlDoUpd = 1; break;
		case FONOROF_OUTFL_OVRTIM:
			fn->otFlDoUpd = flCmpTimeStamps(fn->inpFlGrp, fn->inpFlNrE, &flNm, 1);
			break;
		case FONOROF_OUTFL_SIM: break;
	};

	if (outFlCfg != FONOROF_OUTFL_SIM) {
	if (fn->otFlDoUpd != 0) {
		//if (fn->verbose >= 0) if (outFlCfg == FONOROF_OUTFL_OVRTIM) printf("\n OtFl -OLD (overwrie)  >%s<.", flNm); // printf("\n OutFl - updating (writing) >%s%s<.", pathNm, fn->extension);
	} else {
		if (fn->verbose >= 0) if (outFlCfg == FONOROF_OUTFL_OVRTIM) printf("\n OtFl -RECENT (no act) >%s<.", flNm); //printf("\n OutFl is recent enough (no act) >%s%s<.", pathNm, fn->extension);
	}
	} else ret |= FONOROF_NEED_UPD; //else code will skip building output file when simulating

	ret |= outFlCfg | ((fn->otFlDoUpd != 0) ? FONOROF_NEED_UPD : 0);
	
	freeIfNotNull(flNm);
	errExit:
	return ret;
}

//flChkRet is the return of flChkNewOrReplOutFile()
FILE *flChkOpenNewOrReplOutFile(struct t_fonorof *fn) {
	if (fn == NULL) return NULL;
	if (fn->otFlDoUpd < 0) return NULL;
	int r = 0, ret = 0, outFlCfg = fn->flOutCfg & FONOROF_OUTFL_MASK;
	FILE *flPt = NULL; char *pathNm = NULL;
	r = dirMakePathLimit(&pathNm, fn->pathSt, fn->pathEn, fn->maxDirs);
	if (pathNm == NULL) { ret = -10; goto errExit; }
	
	char *flNm = strConAlloc(pathNm, fn->extension);
	if (flNm == NULL) { ret = -12; goto errExit2; }

	int rmvFlg = RMVFILE_INACT, needUpdOutFl = 0;
	int maxFls = 1;
	switch (outFlCfg) {
		case FONOROF_OUTFL_NEW: maxFls = fn->maxFls; rmvFlg = RMVFILE_INACT; needUpdOutFl = 1; break;
		case FONOROF_OUTFL_OVERWR: rmvFlg = RMVFILE_REMOVE; needUpdOutFl = 1; break;
		case FONOROF_OUTFL_OVRTIM:
			//needUpdOutFl = ((flChkRet & FONOROF_NEED_UPD) != 0);
			needUpdOutFl = (fn->otFlDoUpd != 0);
			rmvFlg = (needUpdOutFl == 0) ? RMVFILE_INACT : RMVFILE_REMOVE;
			break;
		case FONOROF_OUTFL_SIM: rmvFlg = RMVFILE_SIMULATE; break;
	};

	r = removeFile(flNm, rmvFlg, 0);
	if (fn->verbose >= 0)
	//if ((-r) != ENOENT) 
	if (r < 0) printf("\n Couldn't remove file errno %d  >%s<", -r, flNm);
	freeIfNotNull(flNm);

	if (outFlCfg != FONOROF_OUTFL_SIM) {
	if (needUpdOutFl != 0) {
		if (fn->verbose >= 0) if (outFlCfg == FONOROF_OUTFL_OVRTIM) printf("\n OutFl writing >%s%s<.", pathNm, fn->extension);
		flPt = flOpenNewOutFile(pathNm, fn->extension, &fn->freeIx, fn->maxFls, fn->openArgs);
	} else {
		if (fn->verbose >= 0) if (outFlCfg == FONOROF_OUTFL_OVRTIM) printf("\n OutFl recent enough => not updating >%s%s<.", pathNm, fn->extension);
	}
	}

	errExit2:
	freeIfNotNull(pathNm);
	errExit:
	fn->retOt = ret;
	return flPt;
}

#if 0
//ret returns status info. Can be NULL. 
FILE *flOpenNewOrReplOutFile(int *retOt, char *pathSt, char *pathEn, int maxDirs, char *extension, int *freeIx, int maxFiles, char *openArgs, char *inpFlGrp[], int inpFlNrE, int cfg) {
	int r = 0, ret = 0, outFlCfg = cfg & FONOROF_OUTFL_MASK;
	FILE *flPt = NULL;
	char *pathNm = NULL;
	r = dirMakePathLimit(&pathNm, pathSt, pathEn, maxDirs);
	if (pathNm == NULL) { ret = -10; goto errExit; }
	
	char *flNm = strConAlloc(pathNm, extension);
	if (flNm == NULL) { ret = -12; goto errExit2; }

	int rmvFlg = RMVFILE_INACT, needUpdOutFl = 0;
	switch (outFlCfg) {
		case FONOROF_OUTFL_NEW: rmvFlg = RMVFILE_INACT; needUpdOutFl = 1; break;
		case FONOROF_OUTFL_OVERWR: rmvFlg = RMVFILE_REMOVE; needUpdOutFl = 1; break;
		case FONOROF_OUTFL_OVRTIM:
			needUpdOutFl = flCmpTimeStamps(inpFlGrp, inpFlNrE, &flNm, 1);
			rmvFlg = (needUpdOutFl == 0) ? RMVFILE_INACT : RMVFILE_REMOVE;
			break;
		case FONOROF_OUTFL_SIM: rmvFlg = RMVFILE_SIMULATE; break;
	};

	r = removeFile(flNm, rmvFlg, 0);
	freeIfNotNull(flNm);

	if (needUpdOutFl != 0) {
		flPt = flOpenNewOutFile(pathNm, extension, freeIx, maxFiles, openArgs);
	}

	errExit2:
	freeIfNotNull(pathNm);
	errExit:
	if (retOt != NULL) *retOt = ret;
	return flPt;
}


/*
standard usage:
cfg = FONOROF_OUTFL_NEW FONOROF_OUTFL_OVERWR  FONOROF_OUTFL_OVRTIM FONOROF_OUTFL_SIM
FILE *flOpenNewOrReplOutFile(NULL, NULL, char *pathEn, 20, char *extension, NULL, 100, "w+b", char *inpFlGrp[], int inpFlNrE, cfg);
*/


//cfg is the same as for the above
//Checks whether according to settings and file presence and modification date, to create a new output file, overwrite the old one, or do nothing.
int flChkNewOrReplOutFile(char *pathNm, char *extension, char *inpFlGrp[], int inpFlNrE, int cfg) {
	int ret = 0, outFlCfg = cfg & FONOROF_OUTFL_MASK;
	char *flNm = strConAlloc(pathNm, extension);
	if (flNm == NULL) { ret = -12; goto errExit; }

	int rmvFlg = RMVFILE_INACT, needUpdOutFl = 0;
	switch (outFlCfg) {
		case FONOROF_OUTFL_NEW: break;
		case FONOROF_OUTFL_OVERWR: break;
		case FONOROF_OUTFL_OVRTIM:
			needUpdOutFl = flCmpTimeStamps(inpFlGrp, inpFlNrE, &flNm, 1);
			break;
		case FONOROF_OUTFL_SIM: break;
	};

	ret |= outFlCfg | ((needUpdOutFl != 0) ? FONOROF_NEED_UPD : 0);
	freeIfNotNull(flNm);
	errExit:
	return ret;
}

//flChkRet is the return of flChkNewOrReplOutFile()
FILE *flChkOpenNewOrReplOutFile(int *retOt, char *pathNm, int maxDirs, char *extension, int *freeIx, int maxFiles, char *openArgs, int flChkRet) {
	if (flChkRet < 0) return NULL;
	int r = 0, ret = 0, outFlCfg = flChkRet & FONOROF_OUTFL_MASK;
	FILE *flPt = NULL;
	r = dirMakePathLimit(NULL, NULL, pathNm, maxDirs);
	if (pathNm == NULL) { ret = -10; goto errExit; }
	
	char *flNm = strConAlloc(pathNm, extension);
	if (flNm == NULL) { ret = -12; goto errExit2; }

	int rmvFlg = RMVFILE_INACT, needUpdOutFl = 0;
	switch (outFlCfg) {
		case FONOROF_OUTFL_NEW: rmvFlg = RMVFILE_INACT; needUpdOutFl = 1; break;
		case FONOROF_OUTFL_OVERWR: rmvFlg = RMVFILE_REMOVE; needUpdOutFl = 1; break;
		case FONOROF_OUTFL_OVRTIM:
			needUpdOutFl = ((flChkRet & FONOROF_NEED_UPD) != 0);
			rmvFlg = (needUpdOutFl == 0) ? RMVFILE_INACT : RMVFILE_REMOVE;
			break;
		case FONOROF_OUTFL_SIM: rmvFlg = RMVFILE_SIMULATE; break;
	};

	r = removeFile(flNm, rmvFlg, 0);
	freeIfNotNull(flNm);

	if (needUpdOutFl != 0) {
		flPt = flOpenNewOutFile(pathNm, extension, freeIx, maxFiles, openArgs);
	}

	errExit2:
	freeIfNotNull(pathNm);
	errExit:
	if (retOt != NULL) *retOt = ret;
	return flPt;
}
#endif
















//returns pointer to the first char, when any of matchChar, after multiple skipChars.
//If after multiple of skipChar a matchChar is not found, NULL is returned.
//The searching ends upon reaching a char among endChar or the address endPt.
//Do NOT use the same char in both matchChar and skipChar.
//More commonly only matchChar or skipChar would be used.
//any of the input params can be NULL
//matchChar, skipChar, endChar are all null-terminated; Because endChar is always null-terminated, the null-terminator is always used if endChar is not NULL. If a null-char shouldn't be a terminator, use endPt.
//endChar, endPt have higher precedence over matchChar has higher priority than skipChar
//lastChar gives a pointer to the char at which the function returned
//XXX: matchChar has been changed to have orecedence over endChar, so that one can exit the loop successfully at endChar, if matchChar has the same chars
char *getFirstChar(char **lastChar, char *str, char *matchChar, char *skipChar, char *endChar, char *endPt) {
	if (str == NULL) return NULL;
	char *pt = str;
	char c = '\0'; //
	char *r = NULL;
	while (1) {
		if (lastChar != NULL) *lastChar = pt;
		#if 1
		if (endPt != NULL) if (pt >= endPt) return NULL;
		#else
		if (pt == endPt) return NULL;
		#endif
		c = *pt;
		if (matchChar != NULL) {
			r = strchr(matchChar, c);
			if (r != NULL) return pt;
		}
		if (endChar != NULL) {
			r = strchr(endChar, c);
			if (r != NULL) return NULL;
		}
		if (skipChar != NULL) {
			r = strchr(skipChar, c);
			if (r == NULL) {
				if (matchChar == NULL) return pt;
				else return NULL;
			}
		}
		pt++;
	}
	return pt;
}
//the above can be done like this:
//char *getFirstChar(char **lastChar, char *str, " \t", "+-0123456789", " \t", char *endPt) 



//returns !=0 if it is integer representation, else it is probably float
//ends comparing on '\0' or endPt whichever comes first
//For hex numbers this can return either, so only use for decimal integer numbers
int isIntNr(char *n, char *endPt) {
	//int isInt = 1;
	while (*n != '\0') {
		char c = *n;
		if (endPt != NULL) { if (n >= endPt) break; }
		if (strchr("+-0123456789", c) == NULL) return 0;
		n++;
	}
	return 1; //is int
}



//If the input string is a directory and not a file, it concatenates its name to the already existing path to form a sheet-file path.
//Usually used for sheet files. 
//Example: if "F:\\whateverPath\\ColObjDefI2_COL0_F96BEBF7" is passed and it is a directory, 
//it will output "F:\\whateverPath\\ColObjDefI2_COL0_F96BEBF7\\ColObjDefI2_COL0_F96BEBF7.csv" (assuming dirDelim = "\\" and extension = ".csv").
//dirDelim should be "\\" for Windows and "/" for Linux.
//extension should be "" for binary sheets and ".csv" for CSV sheets. 
char *pathDirToPathAlloc(int *isDir, char *inPath, char *dirDelim, char *extension) {
	if (inPath == NULL) return NULL;
	char *flPathNm = NULL;
	if (isDir != NULL) *isDir = 0;
	if (chkIfIsDir(inPath) > 0) {
		if (isDir != NULL) *isDir = 1;
		char *dirNm = flPathGetFlNmAndExt(NULL, NULL, inPath);
		if (extension == NULL) extension = ""; //just in case
		flPathNm = sprtfAlloc("%s%s%s%s", inPath, dirDelim, dirNm, extension);
	} else {
		flPathNm = sprtfAlloc("%s", inPath); //a file, directly in the folder
	}
	return flPathNm;
}




//A pointer is used for the input value so that any variable type is supported. Byte access is used only. For s8/u8, bits=8; for s/u64 - 64, etc. 
//The bits are counted from the LSb. 
int getSetBits(void *vlIn, int bits) {
	int sb = 0, i;
	u8 *v = (u8*)vlIn;
	int bi = 0; //byte index
	for (i=0; i<bits; i++) {
		bi = i >>3;		
		if (((v[bi] >>(i & 7)) & 1) != 0) sb++;
	}
	return sb;
}


//These wrappers support NULL pointers - if any of the pointers is NULL, they return mismatch.
int strcmpNl(const char *a, const char *b) {
	if (a == NULL) return -0x7FFFFFFF;
	if (b == NULL) return 0x7FFFFFFF;
	return strcmp(a, b);
}

int strncmpNl(const char *a, const char *b, size_t num) {
	if (a == NULL) return -0x7FFFFFFF;
	if (b == NULL) return 0x7FFFFFFF;
	return strncmp(a, b, num);
}

int strlenNl(const char *a) {
	if (a == NULL) return -1;
	return strlen(a);
}


//Compares the string Ending to the last chars of string Str. Ending has to be shorter or equal to Str for the comparison to succeed at all. This is useful when checking if a file's extension is a certain one.
//XXX: if the second string is of zero length, the result will be match (0)! 
int strCmpEnd(const char *str, const char *ending) {
	if (str == NULL) return -0x7FFFFFFF;
	if (ending == NULL) return 0x7FFFFFFF;
	int la = strlen(str), lb = strlen(ending);
	la -= lb;
	if (la < 0) return 0x7FFFFFFE; //Mismatch, as the string to look-in is shorter.
	return strcmp(&str[la], ending);
}


//Finds the iter-th occurance of any of the chars of the string srch in the str string.
//iter (occurance): 0=first(fromTheStart), 1=second, etc.; -1=first(fromTheEnd), -2=second(fromTheEnd), etc.
//If not found, returns NULL pointer.
char *strChrFnd(char *str, char *srch, int iter) {
	char *fnd = NULL;
	char *s = NULL;
	if (iter >= 0) {
		for (s = str; *s != '\0'; s++) { 
			char *f = strchr(srch, *s);
			if (f != NULL) {
				if (iter > 0) iter--;
				else { fnd = s; break; }
			}
		}
	} else {
		int l = strlen(str); s = &str[l-1]; iter = (-iter) -1;
		for (; l > 0; l--, s--) {
			char *f = strchr(srch, *s);
			if (f != NULL) {
				if (iter > 0) iter--;
				else { fnd = s; break; }
			}
		}
	}
	return fnd;
}


//Memory blocks swapping swapMems. Such funcs for quats and u32/floats exist in quat.c.
//For u32/float - see switchFloat() in quat.c.
//I could make one like this for u32, etc., but supporting unaligned access is more universal.
//XXX: It is assumed that the two memory ranges do NOT overlap, though there is a check for that too.
int switchMems(void *a, void *b, int len) {
	if (len <= 0) return -1;
	if (a == NULL) return -2;
	if (b == NULL) return -3;
	char *ac = a, *bc = b;
	//check for overlap
	if (((ac <= bc) && (&ac[len-1] >= bc)) || ((bc <= ac) && (&bc[len-1] >= ac))) { //overlap
		u8 *buf = mallocAndChk(len);
		if (buf == NULL) return -4;
		memcpy(buf, a, len);
		memcpy(a, b, len);
		memcpy(b, buf, len);
		freeIfNotNull(buf);
	} else {
		//byte-by-byte, so that no additional buf is used
		int l = len; char t;
		for (; l>0; l--) {
			t = *ac; *ac = *bc; *bc = t; 
			ac++; bc++;
		}
	}
	return 0;
}


//Removes the first match of character sequence of *strRmv from *strSrc.
//ret: pointer to where strRmv was in strSrc
//A zero length strRmv will always match at the first char pos. This is avoided in the code.
char *strRemoveNl(char *strSrc, char *strRmv) {
	if (strSrc == NULL) return NULL;
	if (strRmv == NULL) return NULL;
	#if 0
	char *matchPt = strstr(strSrc, strRmv);
	if (matchPt == NULL) return NULL;
	int sls = strlen(matchPt);
	int slr = strlen(strRmv);
	memmove(matchPt, &matchPt[slr], sls - srl);
	return matchPt;
	#else
	char *s, *sc, *r, cr = *strRmv;
	for (s = strSrc;; s++) {
		char cs = *s;
		if (cs == '\0') break;
		
		if (cs == cr) //optimization and makes sure at least one char matches
		for (r = strRmv+1, sc = s+1; ; r++, sc++) {
			char crc = *r;
			if (crc == '\0') { //match, so copy the string after that, overwriting the removed str
				char *matchPt = s;
				for (; ; s++, sc++) {
					char c = *sc;
					*s = c;
					if (c == '\0') return matchPt;
				}
			}
			if (*sc != crc) break;
		}
	}
	return NULL;
	#endif
}



////////////////////////////////////////
//
//	Simple Performance Counters
//

#include <time.h>

struct t_perfCntA {
	clock_t start;
	clock_t end;
	double duration;
	u8		started;
	u8		ended;
	char id[10];	//can place a string here
};


//maybe also add a capability to have multiple timers and detect the sequence in which they started and ended; or multiple events per timer

struct t_perfCntA *perfCntAInit(char *id) {
	struct t_perfCntA *pc = mallocAndClr(sizeof(struct t_perfCntA));
	if (pc == NULL) return NULL;
	if (id != NULL) {
		int slen = sizeof(pc->id) -1;
		memset(pc->id, ' ', slen);
		strncpy(pc->id, id, slen); pc->id[slen] = '\0';
	}
	return pc;
}

void perfCntAExit(struct t_perfCntA *pc) {
	freeIfNotNull(pc);
}

void perfCntASetId(struct t_perfCntA *pc, char *id) {
	if (pc == NULL) return;
	if (id != NULL) {
		int slen = sizeof(pc->id) -1;
		memset(pc->id, ' ', slen);
		strncpy(pc->id, id, slen); pc->id[slen] = '\0';
	}
}

inline void perfCntAStart(struct t_perfCntA *pc) {
	if (pc == NULL) return;
	pc->start = clock();
	pc->started = 1;
}

inline void perfCntASetIdAndStart(struct t_perfCntA *pc, char *id) {
	perfCntASetId(pc, id);
	perfCntAStart(pc);
}

inline void perfCntAFinish(struct t_perfCntA *pc) {
	if (pc == NULL) return;
	pc->end = clock();
	pc->ended = 1;
}

double perfCntAGetDurationSec(struct t_perfCntA *pc) {
	if (pc == NULL) return -3;
	pc->duration = ((double)pc->end - (double)pc->start) / (double)CLOCKS_PER_SEC; //in seconds
	if (pc->started == 0) pc->duration = -1;
	if (pc->ended == 0) pc->duration = -2;
	return pc->duration;
}

//The duration is printed next to the string (id) of the entry that is before the code, the duration of which is measured. 
void perfCntAPrint(struct t_perfCntA *pc) {
	if (pc == NULL) return;
	double d = perfCntAGetDurationSec(pc);
	printf("\n PerfCnt %-9s: %9.4f   start %9.4f   end %9.4f  st%d en%d", pc->id, pc->duration, (double)pc->start, (double)pc->end, pc->started, pc->ended);
	return;
}

//Stop, print and restart.
//The id refers to the next time period.
void perfCntAStPrintRst(struct t_perfCntA *pc, char *id) {
	if (pc == NULL) return;
	perfCntAFinish(pc);
	perfCntAPrint(pc);
	if (id != NULL) {
		int slen = sizeof(pc->id) -1;
		memset(pc->id, ' ', slen);
		strncpy(pc->id, id, strlen(id)); pc->id[slen] = '\0';
	}
	perfCntAStart(pc);
}


/*
//Example:
struct t_perfCntA *pcA = perfCntAInit("Cnt1");

perfCntAStart(pcA);

perfCntAFinish(pcA);

perfCntAPrint(pcA);

perfCntAExit(pcA);


struct t_perfCntA *pcA = perfCntAInit("Cnt1");
perfCntAStPrintRst(pcA);
perfCntAExit(pcA);

*/


//converts a buffer (of a text file usually) to null-terminated strings - each line is converted to a null-term string. \r ir \r\n marks a single file end. This is used with getNextBfStrLine 
//termChars sets the characters that will be converted to \0; \0 is kept \0
//Using the usual safe way insted - conv the first of \r\n. //NOT: //If two identocal term-chars are found one after another, the second one is not conv
int bfToTermStrLines(char *buf, char *termChars, char *bufEnd) {
	char *c = buf;
	//if (termChars == NULL) termChars = "\r\n";
	char *prevTermChar = NULL;
	while (c < bufEnd) {
		//if (strchr(termChars, *c) != NULL) { //found a term char
		//	if (
		//}
		if (c[0] == '\r') {
			*c = '\0';
			if (c[1] == '\n') { c++; } //skip the \n, so that getNextBfStrLine() won't think there are two strings here
		} else if (c[0] == '\n') { *c = '\0'; }
		c++;
	}
	return 0;
}

//
//This gets a pointer to the next null-terminated string in a buffer. Each \0 marks the end of a string. Any \r \n at the start of a string are skipped (as many as there are until the first other char). \0\0 means two zero-length lines, so this will have to be called again to get the third line.
//lnStartSkipSyms (set to NULL for default) set the symbols to be skipped at the start of the line - usually "\r\n"
//lnEndMarkSyms (set to NULL for default) set the line ending marling symbols. '\0' is always assumed such symbol
//bufEnd points to just after the last char of the buf. On a zero-size buf, bufEnd points to the start of the buf.
char *getNextBfStrLine(char *prevLine, char *lnStartSkipSyms, char *lnEndMarkSyms, char *bufEnd) {
	if (prevLine == NULL) return NULL;
	if (lnEndMarkSyms == NULL) lnEndMarkSyms = "\0";
	if (lnStartSkipSyms == NULL) lnStartSkipSyms = "\r\n";
	char *c = prevLine;
	while (*c != '\0') {
		if (strchr(lnStartSkipSyms, *c) != NULL) break; //found
		if (c >= bufEnd) return NULL; //reached the end
		c++;
	}
	//now *c points to the term zero or other term char
	c++;
	if (c >= bufEnd) return NULL; //reached the end
	while (strchr(lnStartSkipSyms, *c) != NULL) { // (*c == '\r') || (*c == '\n')) { //skip any \r \n
		if (c >= bufEnd) return NULL; //reached the end
		c++;
	}
	return c;
}



//based on the radix, checks if the given character is a digit of that radix
//returns 0 if not and 1 if so.
int isRadixDigit(char c, int radix) {
	int v = c;
	if (v < '0') return 0; //not
	v -= '0';
	if (c <= '9') {
		if (v < radix) return 1; //OK
		else return 0;
	}
	if (c < 'A') return 0; //not a number
	int r = radix - 10;	
	if (c >= 'a') v = c - 'a';
	else v = c - 'A';
	if (v < r) return 1;
	return 0;
}


//hex "editor" print
void hexePrtA(void *data, int sz, char *descr) {
	int i; u8 *d = data;
	if (descr == NULL) descr = "";
	u64 bd[3]; bd[2] = 0ull; char *st = (char*)bd;
	printf("\n %08X: sz %08X  %s", (u32)d, sz, descr);
	if (d == NULL) return;
	int lSz = (sz + 0xF) & ~0xF;
	for (i=0;; i++) {
		//if (((u32)d & 0xF) == 0)
		if ((i & 0xF) == 0)
		{
			if (i != 0) {
				printf(">%s<", st);
				bd[0] = 0ull; bd[1] = 0ull;
			}
			if (i >= lSz) break;
			printf("\n %08X:", (u32)d);
		}
		if (i >= lSz) break;
		//if (((u32)d & 7) == 0)
		if ((i & 7) == 0)
			printf(" ");
		//if ((i & 3) == 0)
		//	printf(" ");
		u8 c = '.';
		if (i < sz) c = *d;
		char b = *(char*)&c;
		if ((b < ' ') || (b > '~')) b = '.';
		if (i < sz) printf("%02X ", c);
		else { b = ' '; printf("   "); }
		st[i&0xF] = b;
		d++;
	}
}







/////////////////////////////////////////////
//
//	Walk a directory structure hierarchically:
//

enum {
	DIRPRTSUBHIERA_ENTTY_BGN = -1001,
	DIRPRTSUBHIERA_ENTTY_END = -1002,
};

struct t_dirPrtSubHierAEnt {
	//This struct and all its fields are only valid until the user func returns (unless otherwise noted).
	DIR	*dirPt; //This shouldn't reallt be accessed but better have it.
	struct dirent *dirEntry;

	struct t_dirPrtSubHierAEnt *parentDir;
	int	depth;			
	int	ixInParent;		//Sequential index of the element in the parent.
								//After all files in a folder have been processed, the callback is called with ixInParent=maxCount and entType = DIRPRTSUBHIERA_ENTTY_END;
	char	*parentPath;	//ends in a delimiter
	char	*entName;		//no delimiter at start, includes extension if there is one
	char	*entPathNm;		// = parentPath with entName added to it
	int	entType;			//return of pathGetPathType() - can be S_IFREG and so on - used to detect if a file or folder
};

struct t_dirPrtSubHierAMd {
	char	*startPathOrig;	//the path in the call to dirPrtSubHierarchyA()
	char	*startPathConv;	//Converted and added end delimiter.
	int	maxDepth;			//the maxDepth in the call to dirPrtSubHierarchyA() Set to <0 for infinite.
	//int	doCbForCurDir;		//Not supported - always skipped: If non-zero, then the callback is called for the curent '.' directory too; else is skipped. The current and parent dirs are only added to the t_dirPrtSubHierAEnt.ixInParent counting if the corresponding doCbForCurDir/doCbForParDir is enabled.
	//int	doCbForParDir;
	int	(*userCbFunc)(struct t_dirPrtSubHierAMd *md);
	void	*privData;

	//Current data (temporary):
	//int	curIxInParent;
	struct t_dirPrtSubHierAEnt *curEnt;	//currently-processed entry; This should basically never be NULL when the callback is called.
};


//Recursive inner func of dirPrtSubHierarchyA():
//Assumes dirPath has correct for this OS delimiters and ends in a delimiter.
int dirPrtSubHierarchyRcrA(struct t_dirPrtSubHierAMd *md, struct t_dirPrtSubHierAEnt *parEnt, char *dirPath, int depth) {
	if (depth == md->maxDepth) return;
	struct t_dirPrtSubHierAEnt entD, *ent = &entD;
	struct t_dirPrtSubHierAEnt *prevEnt = md->curEnt; //This should match parEnt, but having it separate.
	md->curEnt = ent;
	ent->parentPath = dirPath;
	ent->depth = depth;
	ent->ixInParent = 0; //used as a counter too

	struct dirent *entry;
	DIR *dir = opendir(dirPath);
	ent->dirPt = dir;

	if (md->userCbFunc != NULL) {
		ent->dirEntry = NULL;
		ent->entName = NULL;
		ent->entPathNm = NULL;
		ent->entType = DIRPRTSUBHIERA_ENTTY_BGN;
		md->userCbFunc(md);
	}

	if (dir != NULL) {	//Go through all files:
		while ((entry = readdir(dir)) != NULL) {
			ent->dirEntry = entry;
			ent->entName = entry->d_name;
			//printf("\n % 3d: >%s<", ent->ixInParent, ent->entName);
			int isCurOrPar = 0;
			if (ent->entName[0] == '.') {	//skip "." and ".." dirs
				if ((ent->entName[1] == '\0') || ((ent->entName[1] == '.') && (ent->entName[2] == '\0'))) {
					isCurOrPar = 1;
				}
			}

			int skipProcNext = 0;
			if (isCurOrPar == 0) {
				ent->entPathNm = strConAlloc(ent->parentPath, ent->entName);
				ent->entType = pathGetPathType(ent->entPathNm);

				if (ent->entType == S_IFDIR) {  //directory:
					freeIfNotNull(ent->entPathNm); ent->entPathNm = NULL;
					ent->entPathNm = sprtfAlloc("%s%s\\", ent->parentPath, ent->entName);
				}

				if (md->userCbFunc != NULL) {
					skipProcNext = md->userCbFunc(md);
				}

				if (ent->entType == S_IFDIR) { //process entries in the dir:
					if (skipProcNext > -1) {
						dirPrtSubHierarchyRcrA(md, ent, ent->entPathNm, depth+1);
					}
				}

				freeIfNotNull(ent->entPathNm); ent->entPathNm = NULL;
			}

			ent->ixInParent++;
			if (skipProcNext <= -2) {
				break; //skip next
			}
		}
	}

	//Call at end:
	if (md->userCbFunc != NULL) {
		ent->dirEntry = NULL;
		ent->entName = NULL;
		ent->entPathNm = NULL;
		ent->entType = DIRPRTSUBHIERA_ENTTY_END;
		md->userCbFunc(md);
	}

	if (dir != NULL) closedir(dir);
	ent->dirPt = NULL;

	md->curEnt = prevEnt; //for the caller
	return ent->ixInParent;
}


//Print the contents of the current folder and all beneath it:
//maxDepth: 1=only print in current.
//UserCallbackFunc return val: -1=skipProcessingSubFoldersOfThis / -2=skipProcessingOtherFolders/FilesNextTo(after)This; -2 will make the subDir count wrong though.
int dirPrtSubHierarchyA(char *dirPath, int maxDepth, int (*userCbFunc)(struct t_dirPrtSubHierAMd *md), void *privData) {
	if (strlenNl(dirPath) <= 0) return -1;
	struct t_dirPrtSubHierAMd mdD, *md = &mdD;
	md->startPathOrig = dirPath;
	md->userCbFunc = userCbFunc;
	md->privData = privData;
	md->maxDepth = maxDepth;

	int dpSl = strlen(dirPath);
	char *endDelim = "";
	if ((dirPath[dpSl-1] != '\\') && (dirPath[dpSl-1] != '/')) endDelim = "\\";
	md->startPathConv = sprtfAlloc("%s%s", dirPath, endDelim);
	dirChangeAllDelim(md->startPathConv, '\\');

	int nrFiles = dirPrtSubHierarchyRcrA(md, NULL, md->startPathConv, 0);

	freeIfNotNull(md->startPathConv);
	return nrFiles;
}


#if 0
//Exmaple usage to print the structure:
int tstDirHierWalk(struct t_dirPrtSubHierAMd *md) {
	int fullPath = 0;
	struct t_dirPrtSubHierAEnt *ent = md->curEnt;
	//md->privData;
	//inPrintf("\n %d ", ent->entType);
	char *initOffsStr = "\n  ";
	#if 1
	//Additional offset when exiting dirs:
	if (ent->entType == DIRPRTSUBHIERA_ENTTY_END) {
		if (fullPath == 0) {
			char *tabs = mkeAllocTabsOffs(NULL, 0, ent->depth+1, "|  ");
			inPrintf("%s%s", initOffsStr, tabs);
			freeIfNotNull(tabs);
		}
	}
	#endif
	if ((ent->depth == 0) && (ent->entType == DIRPRTSUBHIERA_ENTTY_BGN)) {
		if (fullPath == 0) {
			inPrintf("%s%s", initOffsStr, ent->parentPath);
		}
	}
	if (ent->entType < 0) return 0; //skip bgn and end.
	char *tabs = mkeAllocTabsOffs(NULL, 0, ent->depth+1, "|  ");

	if (fullPath) {
		if (ent->entType != S_IFDIR) {
			inPrintf("%s", ent->entPathNm);
		}
	} else {
		inPrintf("%s%s%s", initOffsStr, tabs, ent->entName);
	}
	//waitUInp();

	freeIfNotNull(tabs);
	return 0;
}
#endif

















