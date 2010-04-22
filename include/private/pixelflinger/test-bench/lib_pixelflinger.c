#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/poll.h>
#include <time.h>
#include <errno.h>
#include <stdarg.h>
#include <sys/types.h>

//#define __QEMU__

#ifdef __QEMU__  

/* QEMU runs slow,so you can set this value less to save time. */
#define VALIDATE_TIMES 40000000
#define BENCHMARK_TIMES  40000000

#else /*real board*/

#define VALIDATE_TIMES 400000000
#define BENCHMARK_TIMES 400000000

#endif

#define gglMulx_VALIDATE_TIMES       4000000
#define gglMulAddx_VALIDATE_TIMES    4000000
#define gglMulSubx_VALIDATE_TIMES    4000000
#define gglMulii_VALIDATE_TIMES    4000000

#define gglMulx_BENCHMARK_TIMES BENCHMARK_TIMES
#define gglMulAddx_BENCHMARK_TIMES BENCHMARK_TIMES
#define gglMulSubx_BENCHMARK_TIMES BENCHMARK_TIMES

#define CONST           __attribute__((const))
#define ALWAYS_INLINE   __attribute__((always_inline))
typedef int32_t GGLfixed;



/*inline MIPS implementations*/
inline GGLfixed gglMulx_mips(GGLfixed a, GGLfixed b, int shift) CONST;
inline GGLfixed gglMulx_mips(GGLfixed a, GGLfixed b, int shift) {
    GGLfixed result,tmp,tmp1,tmp2;      

    if (__builtin_constant_p(shift)) {
        if (shift == 0) {
            asm ("mult %[a], %[b] \t\n"
              "mflo  %[res]   \t\n"
            : [res]"=&r"(result),[tmp]"=&r"(tmp)
            : [a]"r"(a),[b]"r"(b)
            : "%hi","%lo"
            );
        } else if (shift == 32)
        {
            asm ("mult %[a], %[b] \t\n"
            "li  %[tmp],1\t\n"
            "sll  %[tmp],%[tmp],0x1f\t\n"    
            "mflo %[res]   \t\n"
            "addu %[tmp1],%[tmp],%[res] \t\n" 
            "sltu %[tmp1],%[tmp1],%[tmp]\t\n"   /*obit*/
            "sra %[tmp],%[tmp],0x1f \t\n"   
            "mfhi  %[res]   \t\n"
            "addu %[res],%[res],%[tmp]\t\n"
            "addu %[res],%[res],%[tmp1]\t\n"
            : [res]"=&r"(result),[tmp]"=&r"(tmp),[tmp1]"=&r"(tmp1)
            : [a]"r"(a),[b]"r"(b),[shift]"I"(shift)
            : "%hi","%lo"
            );
        } else if ((shift >0) && (shift < 32))
        {
            asm ("mult %[a], %[b] \t\n"
            "li  %[tmp],1 \t\n"
            "sll  %[tmp],%[tmp],%[shiftm1] \t\n"    
            "mflo  %[res]   \t\n"
            "addu %[tmp1],%[tmp],%[res] \t\n" 
            "sltu %[tmp1],%[tmp1],%[tmp] \t\n"  /*obit?*/
            "addu  %[res],%[res],%[tmp] \t\n"    
            "mfhi  %[tmp]   \t\n"
            "addu  %[tmp],%[tmp],%[tmp1] \t\n" 
            "sll   %[tmp],%[tmp],%[lshift] \t\n" 
            "srl   %[res],%[res],%[rshift]    \t\n"
            "or    %[res],%[res],%[tmp] \t\n"  
            : [res]"=&r"(result),[tmp]"=&r"(tmp),[tmp1]"=&r"(tmp1),[tmp2]"=&r"(tmp2)
            : [a]"r"(a),[b]"r"(b),[lshift]"I"(32-shift),[rshift]"I"(shift),[shiftm1]"I"(shift-1)
            : "%hi","%lo"
            );
        } else {
            asm ("mult %[a], %[b] \t\n"
            "li  %[tmp],1 \t\n"
            "sll  %[tmp],%[tmp],%[shiftm1] \t\n"    
            "mflo  %[res]   \t\n"
            "addu %[tmp1],%[tmp],%[res] \t\n" 
            "sltu %[tmp1],%[tmp1],%[tmp] \t\n"  /*obit?*/
            "sra  %[tmp2],%[tmp],0x1f \t\n"
            "addu  %[res],%[res],%[tmp] \t\n"    
            "mfhi  %[tmp]   \t\n"
            "addu  %[tmp],%[tmp],%[tmp2] \t\n"  
            "addu  %[tmp],%[tmp],%[tmp1] \t\n"            /*tmp=hi*/
            "srl   %[tmp2],%[res],%[rshift]    \t\n"   
            "srav  %[res], %[tmp],%[rshift]\t\n"       
            "sll   %[tmp],%[tmp],1 \t\n" 
            "sll   %[tmp],%[tmp],%[norbits] \t\n"     
            "or    %[tmp],%[tmp],%[tmp2] \t\n"   
            "movz  %[res],%[tmp],%[bit5] \t\n"   
            : [res]"=&r"(result),[tmp]"=&r"(tmp),[tmp1]"=&r"(tmp1),[tmp2]"=&r"(tmp2)
            : [a]"r"(a),[b]"r"(b),[norbits]"I"(~(shift)),[rshift]"I"(shift),[shiftm1] "I"(shift-1),[bit5]"I"(shift & 0x20)
            : "%hi","%lo"
            );
        }
    } else {
        asm ("mult %[a], %[b] \t\n"
        "li  %[tmp],1 \t\n"
        "sll  %[tmp],%[tmp],%[shiftm1] \t\n"    
        "mflo  %[res]   \t\n"
        "addu %[tmp1],%[tmp],%[res] \t\n" 
        "sltu %[tmp1],%[tmp1],%[tmp] \t\n"  /*obit?*/
        "sra  %[tmp2],%[tmp],0x1f \t\n"
        "addu  %[res],%[res],%[tmp] \t\n"    
        "mfhi  %[tmp]   \t\n"
        "addu  %[tmp],%[tmp],%[tmp2] \t\n"  
        "addu  %[tmp],%[tmp],%[tmp1] \t\n"            /*tmp=hi*/
        "srl   %[tmp2],%[res],%[rshift]    \t\n"   
        "srav  %[res], %[tmp],%[rshift]\t\n"       
        "sll   %[tmp],%[tmp],1 \t\n" 
        "sll   %[tmp],%[tmp],%[norbits] \t\n"     
        "or    %[tmp],%[tmp],%[tmp2] \t\n"   
        "movz  %[res],%[tmp],%[bit5] \t\n"   
         : [res]"=&r"(result),[tmp]"=&r"(tmp),[tmp1]"=&r"(tmp1),[tmp2]"=&r"(tmp2)
         : [a]"r"(a),[b]"r"(b),[norbits]"r"(~(shift)),[rshift] "r"(shift),[shiftm1]"r"(shift-1),[bit5] "r"(shift & 0x20)
         : "%hi","%lo"
         );
        }

        return result;
}

inline GGLfixed gglMulAddx_mips(GGLfixed a, GGLfixed b, GGLfixed c, int shift) CONST;
inline GGLfixed gglMulAddx_mips(GGLfixed a, GGLfixed b, GGLfixed c, int shift) {
    GGLfixed result,t,tmp1,tmp2;
    
    if (__builtin_constant_p(shift)) {
        if (shift == 0) {
                 asm ("mult %[a], %[b] \t\n"
                 "mflo  %[lo]   \t\n"
                 "addu  %[lo],%[lo],%[c]    \t\n"
                 : [lo]"=&r"(result)
                 : [a]"r"(a),[b]"r"(b),[c]"r"(c)
                 : "%hi","%lo"
                 );
                } else if (shift == 32) {
                    asm ("mult %[a], %[b] \t\n"
                    "mfhi  %[lo]   \t\n"
                    "addu  %[lo],%[lo],%[c]    \t\n"
                    : [lo]"=&r"(result)
                    : [a]"r"(a),[b]"r"(b),[c]"r"(c)
                    : "%hi","%lo"
                    );
                } else if ((shift>0) && (shift<32)) {
                    asm ("mult %[a], %[b] \t\n"
                    "mflo  %[res]   \t\n"
                    "mfhi  %[t]   \t\n"
                    "srl   %[res],%[res],%[rshift]    \t\n"
                    "sll   %[t],%[t],%[lshift]     \t\n"
                    "or  %[res],%[res],%[t]    \t\n"
                    "addu  %[res],%[res],%[c]    \t\n"
                    : [res]"=&r"(result),[t]"=&r"(t)
                    : [a]"r"(a),[b]"r"(b),[c]"r"(c),[lshift]"I"(32-shift),[rshift]"I"(shift)
                    : "%hi","%lo"
                    );
                } else {
                    asm ("mult %[a], %[b] \t\n"
                    "nor %[tmp1],$zero,%[shift]\t\n"
                    "mflo  %[res]   \t\n"
                    "mfhi  %[t]   \t\n"
                    "srl   %[res],%[res],%[shift]    \t\n"
                    "sll   %[tmp2],%[t],1     \t\n"
                    "sllv  %[tmp2],%[tmp2],%[tmp1]     \t\n"
                    "or  %[tmp1],%[tmp2],%[res]    \t\n"
                    "srav  %[res],%[t],%[shift]     \t\n"
                    "andi %[tmp2],%[shift],0x20\t\n"
                    "movz %[res],%[tmp1],%[tmp2]\t\n"      
                    "addu  %[res],%[res],%[c]    \t\n"
                    : [res]"=&r"(result),[t]"=&r"(t),[tmp1]"=&r"(tmp1),[tmp2]"=&r"(tmp2)
                    : [a]"r"(a),[b]"r"(b),[c]"r"(c),[shift]"I"(shift)
                    : "%hi","%lo"
                    );
                }
            } else {
                asm ("mult %[a], %[b] \t\n"
                "nor %[tmp1],$zero,%[shift]\t\n"
                "mflo  %[res]   \t\n"
                "mfhi  %[t]   \t\n"
                "srl   %[res],%[res],%[shift]    \t\n"
                "sll   %[tmp2],%[t],1     \t\n"
                "sllv  %[tmp2],%[tmp2],%[tmp1]     \t\n"
                "or  %[tmp1],%[tmp2],%[res]    \t\n"
                "srav  %[res],%[t],%[shift]     \t\n"
                "andi %[tmp2],%[shift],0x20\t\n"
                "movz %[res],%[tmp1],%[tmp2]\t\n"      
                "addu  %[res],%[res],%[c]    \t\n"
                : [res]"=&r"(result),[t]"=&r"(t),[tmp1]"=&r"(tmp1),[tmp2]"=&r"(tmp2)
                : [a]"r"(a),[b]"r"(b),[c]"r"(c),[shift]"r"(shift)
                : "%hi","%lo"
                );
            }
            return result;
}

inline GGLfixed gglMulSubx_mips(GGLfixed a, GGLfixed b, GGLfixed c, int shift) CONST;
inline GGLfixed gglMulSubx_mips(GGLfixed a, GGLfixed b, GGLfixed c, int shift) {
    GGLfixed result,t,tmp1,tmp2;
    
    if (__builtin_constant_p(shift)) {
        if (shift == 0) {
                 asm ("mult %[a], %[b] \t\n"
                 "mflo  %[lo]   \t\n"
                 "subu  %[lo],%[lo],%[c]    \t\n"
                 : [lo]"=&r"(result)
                 : [a]"r"(a),[b]"r"(b),[c]"r"(c)
                 : "%hi","%lo"
                 );
                } else if (shift == 32) {
                    asm ("mult %[a], %[b] \t\n"
                    "mfhi  %[lo]   \t\n"
                    "subu  %[lo],%[lo],%[c]    \t\n"
                    : [lo]"=&r"(result)
                    : [a]"r"(a),[b]"r"(b),[c]"r"(c)
                    : "%hi","%lo"
                    );
                } else if ((shift>0) && (shift<32)) {
                    asm ("mult %[a], %[b] \t\n"
                    "mflo  %[res]   \t\n"
                    "mfhi  %[t]   \t\n"
                    "srl   %[res],%[res],%[rshift]    \t\n"
                    "sll   %[t],%[t],%[lshift]     \t\n"
                    "or  %[res],%[res],%[t]    \t\n"
                    "subu  %[res],%[res],%[c]    \t\n"
                    : [res]"=&r"(result),[t]"=&r"(t)
                    : [a]"r"(a),[b]"r"(b),[c]"r"(c),[lshift]"I"(32-shift),[rshift]"I"(shift)
                    : "%hi","%lo"
                    );
                } else {
                    asm ("mult %[a], %[b] \t\n"
                    "nor %[tmp1],$zero,%[shift]\t\n"
                     "mflo  %[res]   \t\n"
                     "mfhi  %[t]   \t\n"
                     "srl   %[res],%[res],%[shift]    \t\n"
                     "sll   %[tmp2],%[t],1     \t\n"
                     "sllv  %[tmp2],%[tmp2],%[tmp1]     \t\n"
                     "or  %[tmp1],%[tmp2],%[res]    \t\n"
                     "srav  %[res],%[t],%[shift]     \t\n"
                     "andi %[tmp2],%[shift],0x20\t\n"
                     "movz %[res],%[tmp1],%[tmp2]\t\n"      
                     "subu  %[res],%[res],%[c]    \t\n"
                     : [res]"=&r"(result),[t]"=&r"(t),[tmp1]"=&r"(tmp1),[tmp2]"=&r"(tmp2)
                     : [a]"r"(a),[b]"r"(b),[c]"r"(c),[shift]"I"(shift)
                     : "%hi","%lo"
                     );
                    } 
                } else {
                asm ("mult %[a], %[b] \t\n"
                "nor %[tmp1],$zero,%[shift]\t\n"
                "mflo  %[res]   \t\n"
                "mfhi  %[t]   \t\n"
                "srl   %[res],%[res],%[shift]    \t\n"
                "sll   %[tmp2],%[t],1     \t\n"
                "sllv  %[tmp2],%[tmp2],%[tmp1]     \t\n"
                "or  %[tmp1],%[tmp2],%[res]    \t\n"
                "srav  %[res],%[t],%[shift]     \t\n"
                "andi %[tmp2],%[shift],0x20\t\n"
                "movz %[res],%[tmp1],%[tmp2]\t\n"      
                "subu  %[res],%[res],%[c]    \t\n"
                : [res]"=&r"(result),[t]"=&r"(t),[tmp1]"=&r"(tmp1),[tmp2]"=&r"(tmp2)
                : [a]"r"(a),[b]"r"(b),[c]"r"(c),[shift]"r"(shift)
                : "%hi","%lo"
                );
            }
    return result;
}

inline GGLfixed gglMulx(GGLfixed a, GGLfixed b, int shift) CONST;
inline GGLfixed gglMulx(GGLfixed a, GGLfixed b, int shift) {
    return (GGLfixed)(((int64_t)(a)*b + (1<<(shift-1)))>>shift);
}
inline GGLfixed gglMulAddx(GGLfixed a, GGLfixed b, GGLfixed c, int shift) CONST;
inline GGLfixed gglMulAddx(GGLfixed a, GGLfixed b, GGLfixed c, int shift) {
    return (GGLfixed)(((int64_t)(a)*b)>>shift) + c;
}
inline GGLfixed gglMulSubx(GGLfixed a, GGLfixed b, GGLfixed c, int shift) CONST;
inline GGLfixed gglMulSubx(GGLfixed a, GGLfixed b, GGLfixed c, int shift) {
    return (GGLfixed)(((int64_t)(a)*b)>>shift) - c;
}

#define TEST_ASSERT_gglMulx(resc,resasm,a,b,shift) \
do { \
if (resc != resasm) \
	{\
		printf("resc 0x%x  resasm 0x%x a 0x%x b 0x%x shift 0x%x \n",resc,resasm,a,b,shift);\
		printf("FAILED \n"); \
		exit(-1);\
    }\
}\
while (0)

#define TEST_gglMulx(a,b,shift) \
do { \
	resc = gglMulx(a,b,shift); \
	resasm = gglMulx_mips(a,b,shift);\
	TEST_ASSERT_gglMulx(resc,resasm,a,b,shift);\
}\
while (0)

#define TEST_ASSERT_gglMulAddx(resc,resasm,a,b,c,shift) \
do { \
if (resc != resasm) \
	{\
		printf("resc 0x%x  resasm 0x%x a 0x%x b 0x%x c 0x%x shift 0x%x \n",resc,resasm,a,b,c,shift);\
		printf("FAILED \n"); \
		exit(-1);\
    }\
}\
while (0)

#define TEST_gglMulAddx(a,b,c,shift) \
do { \
	resc = gglMulAddx(a,b,c,shift); \
	resasm = gglMulAddx_mips(a,b,c,shift);\
	TEST_ASSERT_gglMulAddx(resc,resasm,a,b,c,shift);\
}\
while (0)

#define TEST_ASSERT_gglMulSubx(resc,resasm,a,b,c,shift) \
do { \
if (resc != resasm) \
	{\
		printf("resc 0x%x  resasm 0x%x a 0x%x b 0x%x c 0x%x shift 0x%x \n",resc,resasm,a,b,c,shift);\
		printf("FAILED \n"); \
		exit(-1);\
    }\
}\
while (0)

#define TEST_gglMulSubx(a,b,c,shift) \
do { \
	resc = gglMulSubx(a,b,c,shift); \
	resasm = gglMulSubx_mips(a,b,c,shift);\
	TEST_ASSERT_gglMulSubx(resc,resasm,a,b,c,shift);\
}\
while (0)

#define VALIDATION_START do { \
							printf("\n[validation start] %s\n",__FUNCTION__); \
							} while (0)
#define VALIDATION_END do { \
							printf("[validation pass] %s\n",__FUNCTION__); \
							} while (0)
							
void validate_gglMulx()
{
	GGLfixed resc,resasm,a,b,shift;
    int i;
        
    VALIDATION_START;
    
    shift = 0;

    printf("shift ==0 \n");
    
    srand(time(NULL));
    
    for (i=0;i<gglMulx_VALIDATE_TIMES;i++)
	{
	    a = rand();
        b = rand();
        TEST_gglMulx(a,b,0);
        
        a = rand();
        b = 0 - rand();
        TEST_gglMulx(a,b,0);
        
        a = 0 - rand();
        b = 0 - rand();
        TEST_gglMulx(a,b,0);
        
	}
	
	printf("shift == 32 \n");
	shift = 32; 
    for (i=0;i<gglMulx_VALIDATE_TIMES;i++)
	{
	    a = rand();
        b = rand();
        TEST_gglMulx(a,b,32);
        
        a = rand();
        b = 0 - rand();
        TEST_gglMulx(a,b,32);
        
        a = 0 - rand();
        b = 0 - rand();
        TEST_gglMulx(a,b,32);
        
	}
	
	printf("shift = [1,31] \n");
	printf("shift: ");
	for (shift=1;shift<=31;shift++)
	{
		printf("%d ",shift);
    	for (i=0;i<gglMulx_VALIDATE_TIMES;i++)
		{
	    	a = rand();
        	b = rand();
        	TEST_gglMulx(a,b,shift);
        
        	a = rand();
        	b = 0 - rand();
        	TEST_gglMulx(a,b,shift);
        	
        	a = 0 - rand();
        	b = 0 - rand();
        	TEST_gglMulx(a,b,shift);
        
		}
	}
	printf("\n");
	
	printf("random shift \n");
	for (i=0;i<gglMulx_VALIDATE_TIMES;i++)
	{
	   	
	    a = rand();
        b = rand();
        shift = rand();
        TEST_gglMulx(a,b,shift);
        
        a = rand();
        b = 0 - rand();
        shift = rand();
        TEST_gglMulx(a,b,shift);
        
        a = 0 - rand();
        b = 0 - rand();
        shift = rand();
        TEST_gglMulx(a,b,shift);
        
	}
	
	VALIDATION_END;
}

void validate_gglMulAddx()
{
	GGLfixed resc,resasm,a,b,c,shift;
    int i;
        
    VALIDATION_START;
    
    shift = 0;
    
    srand(time(NULL));

    printf("shift ==0 \n");
    for (i=0;i<gglMulAddx_VALIDATE_TIMES;i++)
	{
	    a = rand();
        b = rand();
        c = rand();
        TEST_gglMulAddx(a,b,c,0);
        
        a = rand();
        b = 0 - rand();
        c = rand();
        TEST_gglMulAddx(a,b,c,0);
        
        a = 0 - rand();
        b = 0 - rand();
        c = rand();
        TEST_gglMulAddx(a,b,c,0);
        
        a = 0 - rand();
        b = 0 - rand();
        c = 0 - rand();
        TEST_gglMulAddx(a,b,c,0);
        
	}
	
	printf("shift == 32 \n");
	shift = 32; 
    for (i=0;i<gglMulAddx_VALIDATE_TIMES;i++)
	{
	   	a = rand();
        b = rand();
        c = rand();
        TEST_gglMulAddx(a,b,c,32);
        
        a = rand();
        b = 0 - rand();
        c = rand();
        TEST_gglMulAddx(a,b,c,32);
        
        a = 0 - rand();
        b = 0 - rand();
        c = rand();
        TEST_gglMulAddx(a,b,c,32);
        
        a = 0 - rand();
        b = 0 - rand();
        c = 0 - rand();
        TEST_gglMulAddx(a,b,c,32);
        
	}
	
	printf("shift = [1,31]\n");
	printf("shift: ");
	for (shift=1;shift<=31;shift++)
	{
		
		printf("%d ",shift);
    	for (i=0;i<gglMulAddx_VALIDATE_TIMES;i++)
		{
	    	a = rand();
        	b = rand();
        	c = rand();
        	TEST_gglMulAddx(a,b,c,shift);
        
       		a = rand();
        	b = 0 - rand();
        	c = rand();
        	TEST_gglMulAddx(a,b,c,shift);
        
        	a = 0 - rand();
        	b = 0 - rand();
        	c = rand();
        	TEST_gglMulAddx(a,b,c,shift);
        
        	a = 0 - rand();
        	b = 0 - rand();
        	c = 0 - rand();
        	TEST_gglMulAddx(a,b,c,shift);
        
		}
	}
	printf(" \n");
	
	printf("random shift \n");
	for (i=0;i<gglMulAddx_VALIDATE_TIMES;i++)
	{
	    a = rand();
        b = rand();
        c = rand();
        shift = rand();
        TEST_gglMulAddx(a,b,c,shift);
        
       	a = rand();
        b = 0 - rand();
        c = rand();
        shift = rand();
        TEST_gglMulAddx(a,b,c,shift);
        
        a = 0 - rand();
        b = 0 - rand();
        c = rand();
        shift = rand();
        TEST_gglMulAddx(a,b,c,shift);
        
        a = 0 - rand();
        b = 0 - rand();
        c = 0 - rand();
        shift = rand();
        TEST_gglMulAddx(a,b,c,shift);
        
        
	}
	
	VALIDATION_END;
}

void validate_gglMulSubx()
{
	GGLfixed resc,resasm,a,b,c,shift;
    int i;
        
    VALIDATION_START;
    
    shift = 0;
    
 	srand(time(NULL));
 
    printf("shift ==0 \n");
    for (i=0;i<gglMulSubx_VALIDATE_TIMES;i++)
	{
		a = rand();
        b = rand();
        c = rand();
        TEST_gglMulSubx(a,b,c,0);
        
        a = rand();
        b = 0 - rand();
        c = rand();
        TEST_gglMulSubx(a,b,c,0);
        
        a = 0 - rand();
        b = 0 - rand();
        c = rand();
        TEST_gglMulSubx(a,b,c,0);
        
        a = 0 - rand();
        b = 0 - rand();
        c = 0 - rand();
        TEST_gglMulSubx(a,b,c,0);
        
	}
	
	printf("shift == 32 \n");
	shift = 32; 
    for (i=0;i<gglMulSubx_VALIDATE_TIMES;i++)
	{
	   a = rand();
        b = rand();
        c = rand();
        TEST_gglMulSubx(a,b,c,32);
        
        a = rand();
        b = 0 - rand();
        c = rand();
        TEST_gglMulSubx(a,b,c,32);
        
        a = 0 - rand();
        b = 0 - rand();
        c = rand();
        TEST_gglMulSubx(a,b,c,32);
        
        a = 0 - rand();
        b = 0 - rand();
        c = 0 - rand();
        TEST_gglMulSubx(a,b,c,32);
      
        
	}
	
	printf("shift = [1,31]\n");
	printf("shift: ");
	for (shift=1;shift<=31;shift++)
	{
		printf("%d ",shift);
    	for (i=0;i<gglMulSubx_VALIDATE_TIMES;i++)
		{
	    	a = rand();
        	b = rand();
        	c = rand();
        	TEST_gglMulSubx(a,b,c,shift);
        
       		a = rand();
        	b = 0 - rand();
        	c = rand();
        	TEST_gglMulSubx(a,b,c,shift);
        
        	a = 0 - rand();
        	b = 0 - rand();
        	c = rand();
        	TEST_gglMulSubx(a,b,c,shift);
        
        	a = 0 - rand();
        	b = 0 - rand();
        	c = 0 - rand();
        	TEST_gglMulSubx(a,b,c,shift);
        
		}
	}
	printf(" \n");
	
	printf("random shift \n");
	for (i=0;i<gglMulSubx_VALIDATE_TIMES;i++)
	{
	    a = rand();
        b = rand();
        c = rand();
        shift = rand();
        TEST_gglMulSubx(a,b,c,shift);
        
       	a = rand();
        b = 0 - rand();
        c = rand();
        shift = rand();
        TEST_gglMulSubx(a,b,c,shift);
        
        a = 0 - rand();
        b = 0 - rand();
        c = rand();
        shift = rand();
        TEST_gglMulSubx(a,b,c,shift);
        
        a = 0 - rand();
        b = 0 - rand();
        c = 0 - rand();
        shift = rand();
        TEST_gglMulSubx(a,b,c,shift);
        
        
	}
	
	VALIDATION_END;
}

#define BENCH_LOGO do { \
						printf("\n[benchmark] %s start \n",__FUNCTION__); \
					  } while(0);
					  
#define BENCH_ASM do { \
						printf("[ASM version] time used: %d seconds. START:%d END:%d DUMMY:%d \n",time_e-time_s,time_e,time_s,resc); \
					 } while(0);
					 
#define BENCH_C do { \
						printf("[C version:] time used: %d seconds. START:%d END:%d DUMMY:%d \n",time_e-time_s,time_e,time_s,resc); \
				  } while(0);
				  
#define BENCH_END do { \
						printf("[benchmark] %s end \n",__FUNCTION__); \
					} while(0);
void bench_gglMulx()
{
	int i;
	GGLfixed resc=0,a,b,shift;
	uint32_t time_s,time_e;

    
    BENCH_LOGO;
    
    srand(0);
    a=(int)(((RAND_MAX+1.0))*rand()/(RAND_MAX+1.0));
    b=(int)(((RAND_MAX+1.0))*rand()/(RAND_MAX+1.0));  
    
    printf("shift == 0 \n");
    time_s = time(NULL);
	for (i=0;i<gglMulx_BENCHMARK_TIMES;i++)
	{
		a++;
		b++;
		/* we use return value res to stop gcc 
		   eliminating this function call
		*/
        resc += gglMulx_mips(a,b,0);
	}
	time_e = time(NULL);
	BENCH_ASM;
	    
	time_s = time(NULL);
	for (i=0;i<gglMulx_BENCHMARK_TIMES;i++)
	{
        a++;
		b++;
		resc += gglMulx(a,b,0);
	}
	time_e = time(NULL);
    BENCH_C;
    
    
    
    
    
    printf("shift == 32 \n");
    time_s = time(NULL);
	for (i=0;i<gglMulx_BENCHMARK_TIMES;i++)
	{
		a++;
		b++;
		/* we use return value res to stop gcc 
		   eliminating this function call
		*/
        resc += gglMulx_mips(a,b,32);
	}
	time_e = time(NULL);
	BENCH_ASM;
	    
	time_s = time(NULL);
	for (i=0;i<gglMulx_BENCHMARK_TIMES;i++)
	{
       a++;
	   b++;
	   resc += gglMulx(a,b,32);
	}
	time_e = time(NULL);
    BENCH_C;
    
    printf("shift == 16 \n");
    time_s = time(NULL);
	for (i=0;i<gglMulx_BENCHMARK_TIMES;i++)
	{
		a++;
		b++;
		/* we use return value res to stop gcc 
		   eliminating this function call
		*/
        resc += gglMulx_mips(a,b,16);
	}
	time_e = time(NULL);
	BENCH_ASM;
	    
	time_s = time(NULL);
	for (i=0;i<gglMulx_BENCHMARK_TIMES;i++)
	{
        a++;
		b++;
		resc += gglMulx(a,b,16);
	}
	time_e = time(NULL);
    BENCH_C;
    
    
    srand(0);
    a=(int)(((RAND_MAX+1.0))*rand()/(RAND_MAX+1.0));
    b=(int)(((RAND_MAX+1.0))*rand()/(RAND_MAX+1.0)); 
    printf("random shift  \n");
    time_s = time(NULL);
	for (i=0;i<gglMulx_BENCHMARK_TIMES;i++)
	{
		a++;
		b++;
		shift++;
		/* we use return value res to stop gcc 
		   eliminating this function call
		*/
        resc += gglMulx_mips(a,b,shift);
	}
	time_e = time(NULL);
	BENCH_ASM;
	    
	time_s = time(NULL);
	for (i=0;i<gglMulx_BENCHMARK_TIMES;i++)
	{
        a++;
		b++;
		shift++;
		resc += gglMulx(a,b,shift);
	}
	time_e = time(NULL);
    BENCH_C;
    
	BENCH_END;	
	
}

void bench_gglMulAddx()
{
	int i;
	GGLfixed resc=0,a,b,c,shift;
	uint32_t time_s,time_e;

    
    BENCH_LOGO;
    
    srand(0);
    a=(int)(((RAND_MAX+1.0))*rand()/(RAND_MAX+1.0));
    b=(int)(((RAND_MAX+1.0))*rand()/(RAND_MAX+1.0));  
    c=(int)(((RAND_MAX+1.0))*rand()/(RAND_MAX+1.0));  
    
    printf("shift == 0 \n");
    time_s = time(NULL);
	for (i=0;i<gglMulAddx_BENCHMARK_TIMES;i++)
	{
		a++;
		b++;
		c++;
		/* we use return value res to stop gcc 
		   eliminating this function call
		*/
        resc += gglMulAddx_mips(a,b,c,0);
	}
	time_e = time(NULL);
	BENCH_ASM;
	    
	time_s = time(NULL);
	for (i=0;i<gglMulAddx_BENCHMARK_TIMES;i++)
	{
        a++;
		b++;
		c++;
		resc += gglMulAddx(a,b,c,0);
	}
	time_e = time(NULL);
    BENCH_C;
    
    printf("shift == 32 \n");
    time_s = time(NULL);
	for (i=0;i<gglMulAddx_BENCHMARK_TIMES;i++)
	{
		a++;
		b++;
		c++;
		/* we use return value res to stop gcc 
		   eliminating this function call
		*/
        resc += gglMulAddx_mips(a,b,c,32);
	}
	time_e = time(NULL);
	BENCH_ASM;
	    
	time_s = time(NULL);
	for (i=0;i<gglMulAddx_BENCHMARK_TIMES;i++)
	{
        a++;
		b++;
		c++;
		resc += gglMulAddx(a,b,c,32);
	}
	time_e = time(NULL);
    BENCH_C;
    
    printf("shift == 16\n");
    time_s = time(NULL);
	for (i=0;i<gglMulAddx_BENCHMARK_TIMES;i++)
	{
		a++;
		b++;
		c++;
		/* we use return value res to stop gcc 
		   eliminating this function call
		*/
        resc += gglMulAddx_mips(a,b,c,16);
	}
	time_e = time(NULL);
	BENCH_ASM;
	    
	time_s = time(NULL);
	for (i=0;i<gglMulAddx_BENCHMARK_TIMES;i++)
	{
        a++;
		b++;
		c++;
		resc += gglMulAddx(a,b,c,16);
	}
	time_e = time(NULL);
    BENCH_C;
    
    srand(0);
    a=(int)(((RAND_MAX+1.0))*rand()/(RAND_MAX+1.0));
    b=(int)(((RAND_MAX+1.0))*rand()/(RAND_MAX+1.0));  
    c=(int)(((RAND_MAX+1.0))*rand()/(RAND_MAX+1.0));  
    shift=(int)(((RAND_MAX+1.0))*rand()/(RAND_MAX+1.0));  
    
    printf("random shift\n");
    time_s = time(NULL);
	for (i=0;i<gglMulAddx_BENCHMARK_TIMES;i++)
	{
		a++;
		b++;
		c++;
		shift++;
		/* we use return value res to stop gcc 
		   eliminating this function call
		*/
        resc += gglMulAddx_mips(a,b,c,shift);
	}
	time_e = time(NULL);
	BENCH_ASM;
	    
	time_s = time(NULL);
	for (i=0;i<gglMulAddx_BENCHMARK_TIMES;i++)
	{
        a++;
		b++;
		c++;
		shift++;
		resc += gglMulAddx(a,b,c,shift);
	}
	time_e = time(NULL);
    BENCH_C;
    
    
}


void bench_gglMulSubx()
{
	int i;
	GGLfixed resc=0,a,b,c,shift;
	uint32_t time_s,time_e;

    
    BENCH_LOGO;
    
    srand(0);
    a=(int)(((RAND_MAX+1.0))*rand()/(RAND_MAX+1.0));
    b=(int)(((RAND_MAX+1.0))*rand()/(RAND_MAX+1.0));  
    c=(int)(((RAND_MAX+1.0))*rand()/(RAND_MAX+1.0));  
    
    printf("shift == 0 \n");
    time_s = time(NULL);
	for (i=0;i<gglMulSubx_BENCHMARK_TIMES;i++)
	{
		a++;
		b++;
		c++;
		/* we use return value res to stop gcc 
		   eliminating this function call
		*/
        resc += gglMulSubx_mips(a,b,c,0);
	}
	time_e = time(NULL);
	BENCH_ASM;
	    
	time_s = time(NULL);
	for (i=0;i<gglMulSubx_BENCHMARK_TIMES;i++)
	{
        a++;
		b++;
		c++;
		resc += gglMulSubx(a,b,c,0);
	}
	time_e = time(NULL);
    BENCH_C;
    
    printf("shift == 32 \n");
    time_s = time(NULL);
	for (i=0;i<gglMulSubx_BENCHMARK_TIMES;i++)
	{
		a++;
		b++;
		c++;
		/* we use return value res to stop gcc 
		   eliminating this function call
		*/
        resc += gglMulSubx_mips(a,b,c,32);
	}
	time_e = time(NULL);
	BENCH_ASM;
	    
	time_s = time(NULL);
	for (i=0;i<gglMulSubx_BENCHMARK_TIMES;i++)
	{
        a++;
		b++;
		c++;
		resc += gglMulSubx(a,b,c,32);
	}
	time_e = time(NULL);
    BENCH_C;
    
    printf("shift == 16\n");
    time_s = time(NULL);
	for (i=0;i<gglMulSubx_BENCHMARK_TIMES;i++)
	{
		a++;
		b++;
		c++;
		/* we use return value res to stop gcc 
		   eliminating this function call
		*/
        resc += gglMulSubx_mips(a,b,c,16);
	}
	time_e = time(NULL);
	BENCH_ASM;
	    
	time_s = time(NULL);
	for (i=0;i<gglMulSubx_BENCHMARK_TIMES;i++)
	{
        a++;
		b++;
		c++;
		resc += gglMulSubx(a,b,c,16);
	}
	time_e = time(NULL);
    BENCH_C;
    
    srand(0);
    a=(int)(((RAND_MAX+1.0))*rand()/(RAND_MAX+1.0));
    b=(int)(((RAND_MAX+1.0))*rand()/(RAND_MAX+1.0));  
    c=(int)(((RAND_MAX+1.0))*rand()/(RAND_MAX+1.0));  
    shift=(int)(((RAND_MAX+1.0))*rand()/(RAND_MAX+1.0));  
    
    printf("random shift\n");
    time_s = time(NULL);
	for (i=0;i<gglMulSubx_BENCHMARK_TIMES;i++)
	{
		a++;
		b++;
		c++;
		shift++;
		/* we use return value res to stop gcc 
		   eliminating this function call
		*/
        resc += gglMulSubx_mips(a,b,c,shift);
	}
	time_e = time(NULL);
	BENCH_ASM;
	    
	time_s = time(NULL);
	for (i=0;i<gglMulSubx_BENCHMARK_TIMES;i++)
	{
        a++;
		b++;
		c++;
		shift++;
		resc += gglMulSubx(a,b,c,shift);
	}
	time_e = time(NULL);
    BENCH_C;    
}

int main()
{

	/* validation */
	validate_gglMulx();
	validate_gglMulAddx();
	validate_gglMulSubx();
	
	/* benchmark */
	bench_gglMulx();
	bench_gglMulAddx();
	bench_gglMulSubx();
	
	return 1;
}
