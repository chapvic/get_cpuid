#include "cpuid.h"

#ifndef _MSC_VER

#define __asm_cpuid(leaf, a, b, c, d)			\
  __asm__ ("cpuid\n\t"					\
	   : "=a" (a), "=b" (b), "=c" (c), "=d" (d)	\
	   : "0" (leaf), "1" (0), "2" (0))

#define __asm_cpuidex(leaf, subleaf, a, b, c, d)	\
  __asm__ ("cpuid\n\t"					\
	   : "=a" (a), "=b" (b), "=c" (c), "=d" (d)	\
	   : "0" (leaf), "1" (0), "2" (subleaf))

static unsigned int __get_cpuid_max(unsigned int __ext, unsigned int *__sig) {
	unsigned int __eax, __ebx, __ecx, __edx;

#ifndef __x86_64__
  /* See if we can use cpuid.  On AMD64 we always can.  */
#if __GNUC__ >= 3
	__asm__("pushf{l|d}\n\t"
		"pushf{l|d}\n\t"
		"pop{l}\t%0\n\t"
		"mov{l}\t{%0, %1|%1, %0}\n\t"
		"xor{l}\t{%2, %0|%0, %2}\n\t"
		"push{l}\t%0\n\t"
		"popf{l|d}\n\t"
		"pushf{l|d}\n\t"
		"pop{l}\t%0\n\t"
		"popf{l|d}\n\t"
		: "=&r" (__eax), "=&r" (__ebx)
		: "i" (0x00200000));
#else
/* Host GCCs older than 3.0 weren't supporting Intel asm syntax
   nor alternatives in i386 code.  */
	__asm__("pushfl\n\t"
		"pushfl\n\t"
		"popl\t%0\n\t"
		"movl\t%0, %1\n\t"
		"xorl\t%2, %0\n\t"
		"pushl\t%0\n\t"
		"popfl\n\t"
		"pushfl\n\t"
		"popl\t%0\n\t"
		"popfl\n\t"
		: "=&r" (__eax), "=&r" (__ebx)
		: "i" (0x00200000));
#endif // __GNUC__ >= 3

	if (!((__eax ^ __ebx) & 0x00200000)) return 0;
#endif // !__x86_64__

/* Host supports cpuid.  Return highest supported cpuid input value.  */
	__asm_cpuid(__ext, __eax, __ebx, __ecx, __edx);
	if (__sig) *__sig = __ebx;
	return __eax;
}


/* Return cpuid data for requested cpuid level, as found in returned
   eax, ebx, ecx and edx registers.  The function checks if cpuid is
   supported and returns 1 for valid cpuid information or 0 for
   unsupported cpuid level.  All pointers are required to be non-null.  */

static int __get_cpuid(unsigned int __leaf,
	unsigned int *__eax, unsigned int *__ebx,
	unsigned int *__ecx, unsigned int *__edx)
{
	unsigned int __ext = __leaf & 0x80000000;
	if (__get_cpuid_max(__ext, 0) < __leaf) return 0;
	__asm_cpuid(__leaf, *__eax, *__ebx, *__ecx, *__edx);
	return 1;
}

static int __get_cpuidex(unsigned int __leaf, unsigned int __subleaf,
	unsigned int *__eax, unsigned int *__ebx,
	unsigned int *__ecx, unsigned int *__edx)
{
	unsigned int __ext = __leaf & 0x80000000;
	if (__get_cpuid_max(__ext, 0) < __leaf) return 0;
	__asm_cpuidex(__leaf, __subleaf, *__eax, *__ebx, *__ecx, *__edx);
	return 1;
}

#endif // !_MSC_VER

void __cdecl cpuid(unsigned int leaf, unsigned int regs[]) {
	memset(regs, 0, sizeof(unsigned int) * 4);
#ifndef _MSC_VER
	__get_cpuid(leaf, regs, regs+1, regs+2, regs+3);
#else
	__cpuid((int *)regs, leaf);
#endif // !_MSC_VER
}

void __cdecl cpuidex(unsigned int leaf, unsigned int subleaf, unsigned int regs[]) {
	memset(regs, 0, sizeof(unsigned int) * 4);
#ifndef _MSC_VER
	__get_cpuidex(leaf, subleaf, regs, regs+1, regs+2, regs+3);
#else
	__cpuidex((int *)regs, leaf, subleaf);
#endif // !_MSC_VER
}
