#ifndef _CPUID_H
#define _CPUID_H

#include <io.h>

void __cdecl cpuid(unsigned int leaf, unsigned int regs[]);
void __cdecl cpuidex(unsigned int leaf, unsigned int subleaf, unsigned int regs[]);

#endif
