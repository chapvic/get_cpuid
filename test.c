#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#include "cpuid.h"

#ifndef DUMMYSTRUCTNAME
#define DUMMYSTRUCTNAME
#endif

#ifndef DUMMYUNIONNAME
#define DUMMYUNIONNAME
#endif

// ---------------------
// Basic CPUID structure
// ---------------------
typedef struct {
	union {
		struct {
			DWORD EAX;
			DWORD EBX;
			DWORD ECX;
			DWORD EDX;
		} DUMMYSTRUCTNAME;
		unsigned int Raw[4];
	} DUMMYUNIONNAME;
} CPUID_REGS;

static char* get_cpuname(CPUID_REGS regs) {
	static char cpuname[17];
	memset(cpuname, 0, 17);
	memcpy(cpuname, &regs.EBX, 4);
	memcpy(cpuname + 4, &regs.EDX, 4);
	memcpy(cpuname + 8, &regs.ECX, 4);
	return cpuname;
}


int main(int argc, char* argv[]) {
	unsigned leaf = 0, subleaf = 0;
	CPUID_REGS regs;
	printf("Execute cpuidex() with leaf=%u, subleaf=%u\n", leaf, subleaf);
	cpuid(0, regs.Raw);
	printf("Result:   Leaf: %u, Subleaf: %u, EAX=%08x, EBX=%08x, ECX=%08x, EDX=%08x\n",
		leaf, subleaf, regs.EAX, regs.EBX, regs.ECX, regs.EDX);
	printf("CPU Name: %s\n", get_cpuname(regs));
	return 0;
}
