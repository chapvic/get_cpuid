#ifdef _WIN32
#include <windows.h>
#endif

#include "cpuid.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _MSC_VER

#define __asm_cpuid(leaf, a, b, c, d)			\
  __asm__ ("cpuid\n\t"					\
	   : "=a" (a), "=b" (b), "=c" (c), "=d" (d)	\
	   : "0" (leaf), "1" (0), "2" (0))

#define __asm_cpuidex(leaf, subleaf, a, b, c, d)	\
  __asm__ ("cpuid\n\t"					\
	   : "=a" (a), "=b" (b), "=c" (c), "=d" (d)	\
	   : "0" (leaf), "1" (0), "2" (subleaf))

int __cdecl __get_cpuid_max(uint32_t __ext, uint32_t *__sig) {
	uint32_t __eax, __ebx, __ecx, __edx;

#ifndef __x86_64__
	/* See if we can use cpuid.  On AMD64 we always can. */
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
	/* Host GCCs older than 3.0 weren't supporting Intel asm syntax nor alternatives in i386 code.  */
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

int __cdecl __check_leaf_invalid(uint32_t __leaf) {
	return ((__get_cpuid_max(__leaf & 0x40000000, 0) < __leaf) &&
		(__get_cpuid_max(__leaf & 0x80000000, 0) < __leaf));
}

int __cdecl __get_cpuid(uint32_t __leaf,
	uint32_t *__eax, uint32_t *__ebx,
	uint32_t *__ecx, uint32_t *__edx)
{
	if (__check_leaf_invalid(__leaf)) return 0;
	__asm_cpuid(__leaf, *__eax, *__ebx, *__ecx, *__edx);
	return 1;
}

int __cdecl __get_cpuidex(uint32_t __leaf, uint32_t __subleaf,
	uint32_t *__eax, uint32_t *__ebx,
	uint32_t *__ecx, uint32_t *__edx)
{
	if (__check_leaf_invalid(__leaf)) return 0;
	__asm_cpuidex(__leaf, __subleaf, *__eax, *__ebx, *__ecx, *__edx);
	return 1;
}

#endif // !_MSC_VER

void __cdecl cpuid(uint32_t leaf, uint32_t regs[]) {
	memset(regs, 0, sizeof(uint32_t) * 4);
#ifndef _MSC_VER
	__get_cpuid(leaf, regs, regs+1, regs+2, regs+3);
#else
	__cpuid((int32_t *)regs, leaf);
#endif // !_MSC_VER
}

void __cdecl cpuidex(unsigned int leaf, unsigned int subleaf, unsigned int regs[]) {
	memset(regs, 0, sizeof(uint32_t) * 4);
#ifndef _MSC_VER
	__get_cpuidex(leaf, subleaf, regs, regs+1, regs+2, regs+3);
#else
	__cpuidex((int32_t *)regs, leaf, subleaf);
#endif // !_MSC_VER
}


/* Advanced functions */

// Check if CPUID is available
int __cdecl is_cpuid_available() {
#ifdef _MSC_VER
#if defined _WIN64 || defined WIN64 || defined AMD64 || defined __x86_64__ || defined _M_X64
	return 1;
#else
	__asm {
		pushfd                               // Save EFLAGS
		pushfd                               // Store EFLAGS
		xor dword ptr [esp],0x00200000       // Invert the ID bit in stored EFLAGS
		popfd                                // Load stored EFLAGS (with ID bit inverted)
		pushfd                               // Store EFLAGS again (ID bit may or may not be inverted)
		pop eax                              // eax = modified EFLAGS (ID bit may or may not be inverted)
		xor eax,[esp]                        // eax = whichever bits were changed
		popfd                                // Restore original EFLAGS
		and eax,0x00200000                   // eax = zero if ID bit can't be changed, else non-zero
		test eax,eax
		jz end
		mov eax,1
	end:	
	}
#endif // defined _WIN64 || defined WIN64 || defined AMD64 || defined __x86_64__ || defined _M_X64
#else
	return __get_cpuid_max(0, NULL) > 0;
#endif // _MSC_VER
}

// Get CPUID maximum extended value
CPU_MAX_VALUES * __cdecl cpu_max_values() {
	static CPU_MAX_VALUES values;
	CPUID_REGS regs;
	cpuid(0, regs.Raw);
	values.basic = regs.EAX;
	cpuid(0x80000000, regs.Raw);
	values.extended = regs.EAX;
	return &values;
}

// Get CPU vendor information
CPU_VENDOR_INFO * __cdecl cpu_vendor_info() {
	static uint32_t id_list[] = { 0, 1, 2, 3, 5, 6, 10, 13 };
	static CPU_VENDOR_INFO vi;
	CPUID_00 regs;
	for (int k = 0; k < ARRAY_SIZE(id_list); k++) {
		cpuid(id_list[k], regs.Raw);
		memcpy(vi.name, &regs.VendorName_1, 4);
		memcpy(vi.name + 4, &regs.VendorName_2, 4);
		memcpy(vi.name + 8, &regs.VendorName_3, 4);
		for (int i = 0; i < ARRAY_SIZE(_cpuid_vendor); i++) {
			if (memcmp(_cpuid_vendor[i].name, vi.name, 12) == 0) {
				vi.id = _cpuid_vendor[i].id;
				return &vi;
			}
		}
	}
	memset(vi.name, 0, 16);		// zero name string, if not detected
	return &vi;
}

// Get CPU brand name string
char * __cdecl cpu_brand() {
	static char brand[49];
	if (0x80000004 <= (cpu_max_values())->extended) {
		cpuid(0x80000002, (uint32_t *)&brand[0]);
		cpuid(0x80000003, (uint32_t *)&brand[16]);
		cpuid(0x80000004, (uint32_t *)&brand[32]);
	}
	return brand;
}

// Get CPU features
CPU_FEATURES * __cdecl cpu_features() {
	static CPU_FEATURES regs;
	cpuid(1, regs.Regs.Raw);
	// Fix CPU cores count if x2APIC is supported
	if (regs.Regs.ECX.X2APIC) {
	    CPUID_0B t;
	    uint32_t cores=0, ecx=0, loop=1;
	    while (loop) {
		cpuidex(11, ecx, t.Raw);
		if (t.ECX.LevelNumber != ecx) break;
		switch (t.ECX.LevelType) {
		    case 0: // Invalid
			loop=0;
			break;
		    case 2:
			cores += t.EBX.LogicalProcessors;
			break;
		}
		ecx++;
	    }
	    regs.Regs.EBX.LogicalProcessors=cores;
	}
	return &regs;
}

// Get CPU family, model and stepping information
CPU_FMS * __cdecl cpu_fms() {
	static CPU_FMS fms;
	CPU_FEATURES * ft = cpu_features();
	fms.family = ft->Regs.EAX.Family;
	fms.model = ft->Regs.EAX.Model;
	fms.stepping = ft->Regs.EAX.Stepping;
	if (fms.family == 0x06 || fms.family == 0x0F)
		fms.model |= (ft->Regs.EAX.ExtendedModel << 4);
	if (fms.family == 0x0F)
		fms.family += ft->Regs.EAX.ExtendedFamily;
	return &fms;
}

// Get CPU signature
uint32_t __cdecl cpu_signature() {
	CPUID_REGS regs;
	if (0x80000001 <= (cpu_max_values())->extended) {
		cpuid(0x80000001, regs.Raw);
		return regs.EAX;
	} else {
		return (cpu_features())->Signature;
	}
}

uint32_t __cdecl cpu_count() {
	uint32_t count = 0;
#ifdef _WIN32
	SYSTEM_INFO systeminfo;
	GetSystemInfo(&systeminfo);
	count = systeminfo.dwNumberOfProcessors;
	CPUID_01 regs;
	cpuid(1, regs.Raw);
	if (regs.EDX.HTT) count /= 2;
#else
	FILE *f;
	char * mask = "/sys/devices/system/cpu/cpu%d/topology/physical_package_id";
	char path[256];
	char pkg[1];
	memset(path, 256, 0);
	int cpu_index = 0;
	int last_package_id = 0;
	while (1) {
		sprintf(path, mask, cpu_index);
		f = fopen(path, "r");
		if (f) {
			fread(pkg, 1, 1, f);
			fclose(f);
			pkg[1] = 0;
			int pkg_id = atoi(pkg);
			if (pkg_id > last_package_id) {
				count++;
				last_package_id = pkg_id;
			}
		} else break;
		cpu_index++;
	}
	count++;
#endif
	return count;
}




// ----------------------
// CPU database functions
// ----------------------

#include "cpudb_amd.h"
#include "cpudb_intel.h"

static CPUDB_TABLE * cpudb_get_table(uint32_t vendor_id) {
	static CPUDB_TABLE table;
	if (vendor_id == CPU_VEN_AMD) {
		table.size = ARRAY_SIZE(_cpudb_amd);
		table.table = _cpudb_amd;
	} else if (vendor_id == CPU_VEN_INTEL) {
		table.size = ARRAY_SIZE(_cpudb_intel);
		table.table = _cpudb_intel;
	}
	return &table;
}

CPU_INFO * __cdecl cpu_info() {
	if (!is_cpuid_available()) return NULL;
	static CPU_INFO info;
	memcpy(&info.vendor, cpu_vendor_info(), sizeof(CPU_VENDOR_INFO));
	memcpy(&info.brand, cpu_brand(), CPU_BRAND_STRING_LEN);
	memcpy(&info.family, cpu_fms(), sizeof(CPU_FMS));
	memcpy(&info.features, cpu_features(), sizeof(CPU_FEATURES));
	memcpy(&info.max_values, cpu_max_values(), sizeof(CPU_MAX_VALUES));

	CPUDB_TABLE * t = cpudb_get_table(info.vendor.id);
	if (!t->size) return NULL;
	CPUID_01 regs;
	cpuid(1, regs.Raw);
	for (int i = 0; i < t->size; i++) {
		if ((info.vendor.id == t->table[i].vendor)
				&& (regs.EAX.Family == t->table[i].family)
				&& (regs.EAX.ExtendedFamily == t->table[i].ext_family)
				&& (regs.EAX.Model == t->table[i].model)
				&& (regs.EAX.ExtendedModel == t->table[i].ext_model)) {
			info.arch = (char *)t->table[i].arch;
			info.core = (char *)t->table[i].core;
			info.process = t->table[i].process;
			break;
		}
	}
	return &info;
}
