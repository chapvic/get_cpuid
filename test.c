#ifdef _WIN32
#include <windows.h>
#endif

#include "cpuid.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef DUMMYSTRUCTNAME
#define DUMMYSTRUCTNAME
#endif

#ifndef DUMMYUNIONNAME
#define DUMMYUNIONNAME
#endif

const char * PRINTF_MASK = "  Leaf=%02x -->> [ EAX=%08x, EBX=%08x, ECX=%08x, EDX=%08x ]\n";

int main(int argc, char* argv[]) {
	int avail = is_cpuid_available();
	printf("Is CPUID available = %s\n", avail ? "yes" : "no");
	if (!avail) return 1;

	CPU_INFO * info = cpu_info();

	CPUID_REGS r;
	puts("\nBasic CPUID raw data:");
	int i = 0;
	for (; i <= info->max_values.basic; i++) {
	    cpuid(i, r.Raw);
	    if (r.EAX > 0 || r.EBX > 0 || r.ECX > 0 || r.EDX > 0)
		printf(PRINTF_MASK, i, r.EAX, r.EBX, r.ECX, r.EDX);
	}

	puts("\nExtended CPUID raw data:");
	i = 0x80000000;
	for (; i <= info->max_values.extended; i++) {
	    cpuid(i, r.Raw);
	    if (r.EAX > 0 || r.EBX > 0 || r.ECX > 0 || r.EDX > 0)
		printf("  Leaf=%x -->> [ EAX=%08x, EBX=%08x, ECX=%08x, EDX=%08x ]\n", i, r.EAX, r.EBX, r.ECX, r.EDX);
	}

	puts("\nHypervisor CPUID raw data:");
	if(info->features.Regs.ECX.HYPERVISOR) {
	    i = 0x40000000;
	    cpuid(i, r.Raw);
	    int hv = r.EAX;
	    for (; i <= hv; i++) {
		cpuid(i, r.Raw);
		if (r.EAX > 0 || r.EBX > 0 || r.ECX > 0 || r.EDX > 0)
		    printf("  Leaf=%x -->> [ EAX=%08x, EBX=%08x, ECX=%08x, EDX=%08x ]\n", i, r.EAX, r.EBX, r.ECX, r.EDX);
	    }
	} else {
	    printf("  -- Hypervisor is not present!\n");
	}

	puts("\nCPUID information:");
	if (info) {
	    printf("  Vendor             : %s\n", info->vendor.name);
	    printf("  Brand name         : %s\n", info->brand);
	    if (info->arch) printf("  Codename           : %s\n", info->arch);
	    printf("  Core               : %s\n", info->core);
	    printf("  Lythography        : %d nm\n", info->process);
	    printf("  Signature          : %x\n", info->features.Signature);
	    printf("  Family             : %02xh (%d)\n", info->family, info->family);
	    printf("  Model              : %02xh (%d)\n", info->model, info->model);
	    printf("  Stepping           : %02xh (%d)\n", info->stepping, info->stepping);
	    printf("  Max CPUID          : basic = 0x%02X, extended = 0x%08X\n", info->max_values.basic, info->max_values.extended);
	    printf("  Hypervisor         : %s\n", info->features.Regs.ECX.HYPERVISOR ? "present" : "not present");
	    printf("  CPU sockets        : %d\n", cpu_count());
	    printf("  Physical cores     : %d\n", (info->features.Regs.EDX.HTT)?info->features.Regs.EBX.LogicalProcessors/2:info->features.Regs.EBX.LogicalProcessors);
	    printf("  Logical cores      : %d\n", info->features.Regs.EBX.LogicalProcessors);
	    printf("  Hyper Threading    : %s\n", info->features.Regs.EDX.HTT ? "enabled" : "disabled");
	}
}
