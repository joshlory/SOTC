#include <float.h>

typedef unsigned char 	u8;
typedef signed char 		s8;
typedef unsigned short 	u16;
typedef signed short 	s16;
typedef unsigned int 	u32;
typedef signed int 		s32;
typedef unsigned long long u64;
typedef signed long long 	s64;

//Volatile types are not really used in the converters (only used on the rael PS2).
typedef volatile unsigned char 	vu8;
typedef volatile signed char 		vs8;
typedef volatile unsigned short 	vu16;
typedef volatile signed short 	vs16;
typedef volatile unsigned int 	vu32;
typedef volatile signed int 		vs32;
typedef volatile unsigned long long vu64;
typedef volatile signed long long 	vs64;


struct t_v3s32 {
   s32 x;    
   s32 y;
   s32 z;    
};

struct t_v3s16 {
   s16 x;    
   s16 y;
   s16 z;    
};

struct t_v3fs { //float,  signle precision
	union {
	float	d[3];	//for accessing the xyz dimensions by indexing
	struct {
   float x;    
   float y;
   float z;
	};};
};


struct t_colRgbaUb { u8 r, g, b, a; };

struct t_colRgbaFl { float r, g, b, a; };



//#include <float.h>
//0x7F7FFFFF = 340282346638528860000000000000000000000.000000 = 3.402823e+038
//Don't use the exponent notation, as that value does not result in 0x7F7FFFFF (tested). The noraml float decimal notation is OK.
//#define FLT_MAX (340282346638528860000000000000000000000.000000)
#define MAX_FLOAT FLT_MAX
#define FLOAT_MAX FLT_MAX
/*
float s = MAX_FLOAT; // = 0x7F7FFFFF = 340282346638528860000000000000000000000.000000 = 3.402823e+038
float k = 3.402823e+038;
float d = 340282346638528860000000000000000000000.000000;
printf("\n %08X %e %e %e %08X  %08X ", *(u32*)&s, s, k, d, *(u32*)&k, *(u32*)&d);
*/
//FLT_MIN is the smallest positive float num. So use -FLT_MAX to get the smallest negative num.


//Used when converting s16 normalized to 1.0 to float and in reverse (with external saved scale):
//8000; //should convert it to float (arther than load that value in the register)
#define FLOAT_S16_UNITY_CONV (float)0x8000 //0x7FFF
//cannot use 0x8000, because multiplying it by 1.0 / -1.0 would result in sign-reversed numbers (overflow) in S16
//The correction for the -0x8000 = 0x8000 problem seems to have been done by changing the scale in CLB cH8. Add to the scale on each axis + ((float)0x0001 / (float)0x8000); before converting (using) it. This would guarantee that +1.0 will convert to 0x7FFF rather than incorrectly convert to 0x8000. The value 0x8000 would not appear. Looked in several original CLBs and it doesn't seem to appear in any. The highest I saw was 0x8001, which proves that this was the method used.  

//#define FLOAT_U16_UNITY_CONV (float)0x10000 //FFFF //because this is u16 and the s coeff should be 0xffff (or 0x10000 ?) rather than 0x7fff as for signed
//maybe there is another way the game does >>1 (arithmetic) u16 -> s16


//these require alignmment:
//The folowing three would fail for floats!!!
#define REVEND16(x) ( (((u16)(x) >>8) & 0xFF) | (((u16)(x) <<8) & 0xFF00) )
#define REVEND32(x) ( (((u32)(x) >>24) & 0xFF) | (((u32)(x) <<8) & 0xFF0000) | (((u32)(x) >>8) & 0xFF00) | (((u32)(x) <<24) & 0xFF000000) )
#define REVEND64(x) ( ((u64)REVEND32((u64)(x) & 0xFFFFFFFF)<<32) | (REVEND32(((u64)(x) >>32)) & 0xFFFFFFFF) )

//use the folowing for floats (the 32-bit one):
#define REVENDVAL16(x) ( *(u16*)&(x) = REVEND16(*(u16*)&(x)) )
#define REVENDVAL32(x) ( *(u32*)&(x) = REVEND32(*(u32*)&(x)) )
#define REVENDVAL64(x) ( *(u64*)&(x) = REVEND64(*(u64*)&(x)) )


#define ROUND16(x) ( ( ((x) + 1) >>1) <<1 )


//Alignment-independant:
void REVENDVAL_f16(void *pt) {
   u8 *p = pt;
   u8 v;
   v = p[0]; p[0] = p[1]; p[1] = v;
   return;   
}

void REVENDVAL_f32(void *pt) {
   u8 *p = pt;
   u8 v;
   v = p[0]; p[0] = p[3]; p[3] = v;
   v = p[1]; p[1] = p[2]; p[2] = v;
   return;   
}

/*#define REVENDVAL16(x) REVENDVAL_f16(&(x)) 
#define REVENDVAL32(x) REVENDVAL_f32(&(x)) 
*/
//lwoSet... functions:
void RESetF4_f(void *pt, float val) {
   u8 *v = (void*)&val;
   u8 *p = pt;
   p[0] = v[3];
   p[1] = v[2];
   p[2] = v[1];
   p[3] = v[0];
   return;
}

void RESetU4_f(void *pt, u32 val) {
   u8 *v = (void*)&val;
   u8 *p = pt;
   p[0] = v[3];
   p[1] = v[2];
   p[2] = v[1];
   p[3] = v[0];
   return;
}

void RESetU2_f(void *pt, u16 val) {
   u8 *v = (void*)&val;
   u8 *p = pt;
   p[0] = v[1];
   p[1] = v[0];
   return;
}

void RESetI4_f(void *pt, int val) {
   u8 *v = (void*)&val;
   u8 *p = pt;
   p[0] = v[3];
   p[1] = v[2];
   p[2] = v[1];
   p[3] = v[0];
   return;
}

void RESetI2_f(void *pt, s16 val) {
   u8 *v = (void*)&val;
   u8 *p = pt;
   p[0] = v[1];
   p[1] = v[0];
   return;
}

#define RESetF4(pt, val) RESetF4_f(&(pt), (val))
#define RESetU4(pt, val) RESetU4_f(&(pt), (val))
#define RESetU2(pt, val) RESetU2_f(&(pt), (val))
#define RESetI4(pt, val) RESetI4_f(&(pt), (val))
#define RESetI2(pt, val) RESetI2_f(&(pt), (val))



float REGetF4_f(void *pt) {
   float val; u8 *v = (void*)&val;
   u8 *p = pt;
   v[0] = p[3];
   v[1] = p[2];
   v[2] = p[1];
   v[3] = p[0];
   return val;
}

u32 REGetU4_f(void *pt) {
   u32 val; u8 *v = (void*)&val;
   u8 *p = pt;
   v[0] = p[3];
   v[1] = p[2];
   v[2] = p[1];
   v[3] = p[0];
   return val;
}

u16 REGetU2_f(void *pt) {
   u16 val; u8 *v = (void*)&val;
   u8 *p = pt;
   v[0] = p[1];
   v[1] = p[0];
   return val;
}

s32 REGetI4_f(void *pt) {
   s32 val; u8 *v = (void*)&val;
   u8 *p = pt;
   v[0] = p[3];
   v[1] = p[2];
   v[2] = p[1];
   v[3] = p[0];
   return val;
}

s16 REGetI2_f(void *pt) {
	s16 val; u8 *v = (void*)&val;
   u8 *p = pt;
   v[0] = p[1];
   v[1] = p[0];
   return val;
}

#define REGetF4(pt) REGetF4_f(&(pt))
#define REGetU4(pt) REGetU4_f(&(pt))
#define REGetU2(pt) REGetU2_f(&(pt))
#define REGetI4(pt) REGetI4_f(&(pt))
#define REGetI2(pt) REGetI2_f(&(pt))






//http://graphics.stanford.edu/~seander/bithacks.html  bit-hacks


//Bit order reversing: (not used for anything at the time of adding  - XXX: UNTESTED!, may not work correctly for signed)
//Taken directly from http://graphics.stanford.edu/~seander/bithacks.html
static const unsigned char LocBitReverseTable256[256] = 
{
#   define R2(n)     n,     n + 2*64,     n + 1*64,     n + 3*64
#   define R4(n) R2(n), R2(n + 2*16), R2(n + 1*16), R2(n + 3*16)
#   define R6(n) R4(n), R4(n + 2*4 ), R4(n + 1*4 ), R4(n + 3*4 )
    R6(0), R6(2), R6(1), R6(3)
};

//Using LUT
//Usually using a 4-bit LUT results in the highest performance on the PS2 
#define BITREV8LUT8(x) (LocBitReverseTable256[(x)])
#define BITREV16LUT8(x) ((BITREV8LUT8((x) &0xFF) <<8) | (BITREV8LUT8(((x) >>8) &0xFF) <<0))
#define BITREV32LUT8(x) ((BITREV8LUT8((x) &0xFF) <<24) | (BITREV8LUT8(((x) >>8) &0xFF) <<16) | (BITREV8LUT8(((x) >>16) &0xFF) <<8) | (BITREV8LUT8(((x) >>24) &0xFF) <<0) )

#define BITREVB(x) BITREV8LUT8((x))
#define BITREVH(x) BITREV32LUT8((x))
#define BITREVW(x) BITREV32LUT8((x))
/*
unsigned int v; // reverse 32-bit value, 8 bits at time
unsigned int c; // c will get v reversed
// Option 1:
c = (BitReverseTable256[v & 0xff] << 24) | (BitReverseTable256[(v >> 8) & 0xff] << 16) | (BitReverseTable256[(v >> 16) & 0xff] << 8) | (BitReverseTable256[(v >> 24) & 0xff]);
// Option 2:
unsigned char * p = (unsigned char *) &v; unsigned char * q = (unsigned char *) &c;
q[3] = BitReverseTable256[p[0]]; q[2] = BitReverseTable256[p[1]]; q[1] = BitReverseTable256[p[2]]; q[0] = BitReverseTable256[p[3]];
*/



#define MIN_CMP(a,b) (((a)<(b))?(a):(b))
#define MAX_CMP(a,b) (((a)>(b))?(a):(b))

#define LIM_MIN_MAX(a, min, max) ( ((a)>(max)) ?(max):( ((a)<(min)) ?(min):(a) ) ) 


//Sign extension of signed variables

//bits sets how many bits is the input variable
//#define s32signExt(val, bits) ((int)(val <<(32-bits)) / (1<<(32-bits))) //This results in the same as the input value  - maybe it gets optimized away 

//The following works correctly - when the right shift is done to a signed varibale, it is arithmetic:
//The bits arg should specify the total number of bits together with the sign bit, rather than the index of the sign bit.
#define s32signExt(val, bits) ((s32)((val) <<(32-(bits))) >>(32-(bits)))
//This doesn't work correctly for the high 32 bits, so if it is needed,it will be implemented but not for now.
#if 0
//This doesn't work when the field is in the lower 32 bits because we are on 32-bit arch. It seems to work on my new PC though - maybe 64-bit types are not emulated here.
#define s64signExt(val, bits) ((s64)((val) <<(64-(bits))) >>(64-(bits)))
#else
//untested #define s64signExt(val, bits) ((bits >32) ? ((s64)((val) <<(64-(bits))) >>(64-(bits))) : (((val) & (1<<(bits-1))) ? (s64)((val) | (0xFFFFFFFFFFFFFFFFul<<bits)) : (s64)(val)))
//The bits-1 in the second shift is important, else if we specify a bits value of 64 (no bits should get set) that will be made into no-shifting, resulting in 0xFFFF... getting ORed. 
//The second part is only to do masking, so that the effect is the same as the shifting-type sign-entension.
#define s64signExt(val, bits) (((val) & ((u64)1<<(bits-1))) ? (s64)((val) | ((s64)0xFFFFFFFFFFFFFFFFull<<(bits-1))) : ( (bits < 64) ? (s64)((val) & (~((s64)0xFFFFFFFFFFFFFFFFull<<bits))) : (val)) )
#endif

/*
Test code:
int sha = 5+32, shb = 4+32, shc = 6+32;
printf(" >>> %016llX  %016llX  %016llX  ", s64signExt(0x10ull, 5), s64signExt(0x10ull, 4), s64signExt(0x10ull, 6));
printf(" >>> %016llX  %016llX  %016llX  ", s64signExt(0x1000000000ull, sha), s64signExt(0x1000000000ull, shb), s64signExt(0x1000000000ull, shc));
int shd = 64; //63;
printf(" >>> %016llX  %016llX  %016llX  ", s64signExt(0xF000000000000000ull, shd), s64signExt(0x8000000000000000ull, shd), s64signExt(0x4000000000000000ull, shd));
waitUInp();
*/

//Some more commonly used variants:
#define s32signExtS8(a) (s32signExt((a), 8))
#define s32signExtS8val(a) ((a) = s32signExt((a), 8))
#define s32signExtS16(a) (s32signExt((a), 16))
#define s32signExtS16val(a) ((a) = s32signExt((a), 16))

//Gets the Number of entries of a constant array like   char *arr[] = { "someString", "another string ", " yet anothStr" }; or array of structs or whatever.
#define CONST_ARR_NRE(a) (sizeof((a)) / sizeof(*(a)))
//Gets the entry size when given an array of entries:
#define CONST_ARR_ENTSZ(a) (sizeof(*(a)))


//Get the base pointer of a struct by a pointer to a field of it:
//example:
//struct t_someStct { u32 fldA, u32 fldB, u32 fldC; };
//struct t_someStct st;
//struct t_someStct *stp = STCT_GET_BASE_BY_FLD(t_someStct, fldB, &st.fldB);
//#define BACK_OFFS_OF_STCT()
#define STCT_GET_BASE_BY_FLD(stctTy, fldNm, fldPt) ((stctTy*)&((u8*)(fldPt))[-offsetof(stctTy, fldNm)])


//Gets a struct field by its type and offset.
//Returns a pointer to the field: Put an asterisk '*' before this macro (when in use) to get the actual data field. STCT_GET_FLD_BY_TYOF - was the name
#define STCT_GET_FLDA(stctP, fldTy, offs) ( (fldTy*) (&((u8*)(stctP))[(offs)]) )



//these macros should work for u8,u16,u32,u64 (and their signed counterparts) (tested mostly)
 
//start= start bit; len= length in bits
//shifts to align to bit 0 and masks
#define GET_BITFIELD(x, start, len) (((x) >>(start)) & ((1<<(len))-1))

//This should be OR-ed with other such to make-up a value of multiple bit-fields
//When using this for u64, x has to be cast to long lonh (u64/s64) like this: SET_BITFIELD((s64)x, start, len)
#define SET_BITFIELD(x, start, len) (((x) & ((1<<(len))-1)) <<(start))


//absolte value
//Just don't forget to cast the input as the required signed type and if u64 (long long) the input literal val needs "ll" at the end ((long long)0xFFFFFFFFFFFFFFFEll)
//Note that the absoluteValur (negative) of 0x80000000 is also 0x80000000 (in s32), and the same goes for all other data types. 
#define ABS_VAL(x) (((x) < 0) ? -(x) : (x))


#if 0
//XXX: TODO: add to the xff builder to be able to specify the align by reading it from the struct placed.
//Getting alignments of data:
//https://stackoverflow.com/questions/28460987/c-get-type-alignment-portably
#define alignof(type) offsetof(struct { char c; type d; }, d)
//https://stackoverflow.com/a/17800462/1956010
#define alignof(type) ((size_t)&((struct { char c; type d; } *)0)->d)
//https://stackoverflow.com/questions/6440021/compiler-support-of-gnu-statement-expression
#define alignof(type) ({ \
    struct s { char c; type d; }; \
    offsetof(struct s, d); \
})
//C11 _Alignof()

#if __STDC_VERSION__ >= 201112L
    /* C11 */
#else
    /* not C11 */
#endif

#endif



