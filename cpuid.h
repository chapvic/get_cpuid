#ifndef _CPUID_H
#define _CPUID_H

#ifdef _WIN32
#include <io.h>
#else
#define _GNU_SOURCE
#include <sched.h>
#pragma ms_struct on
#endif

#include "cpuids.h"

#ifndef _MSC_VER
#define __cdecl
#endif

#ifndef NULL
#define NULL (void*)0
#endif

/* Size of static array */
#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
#endif

#define CPU_VENDOR_STRING_LEN 12
#define CPU_BRAND_STRING_LEN  48

/* Vendors IDs */
#define CPU_VEN_AMD           0x00000001
#define CPU_VEN_INTEL         0x00000002
#define CPU_VEN_TRANSMETA     0x00000004
#define CPU_VEN_CYRIX         0x00000008
#define CPU_VEN_CENTAUR       0x00000010
#define CPU_VEN_NEXGEN        0x00000020
#define CPU_VEN_UMC           0x00000040
#define CPU_VEN_SIS           0x00000080
#define CPU_VEN_NSC           0x00000100
#define CPU_VEN_RISE          0x00000200
#define CPU_VEN_VORTEX        0x00000400
#define CPU_VEN_VIA           0x00000800

/* Old Vendors IDs */
#define CPU_VEN_AMD_OLD       0x00010000
#define CPU_VEN_TRANSMETA_OLD 0x00020000
 
/* VM Vendors IDs */
#define CPU_VEN_VMWARE        0x40100000
#define CPU_VEN_XEN           0x40200000
#define CPU_VEN_HYPER_V       0x40400000
#define CPU_VEN_PARALLELS     0x40800000

#pragma pack(push,1)

static struct _CPUID_VENDOR {
	uint32_t id;
	char name[CPU_VENDOR_STRING_LEN + 1];
} _cpuid_vendor[] = {
	/* Vendors */
	{ CPU_VEN_AMD, "AuthenticAMD" },
	{ CPU_VEN_INTEL, "GenuineIntel" },
	{ CPU_VEN_TRANSMETA, "GenuineTMx86" },
	{ CPU_VEN_CYRIX, "CyrixInstead" },
	{ CPU_VEN_CENTAUR, "CentaurHauls" },
	{ CPU_VEN_NEXGEN, "NexGenDriven" },
	{ CPU_VEN_UMC, "UMC UMC UMC " },
	{ CPU_VEN_SIS, "SiS SiS SiS " },
	{ CPU_VEN_NSC, "Geode by NSC" },
	{ CPU_VEN_RISE, "RiseRiseRise" },
	{ CPU_VEN_VORTEX, "Vortex86 SoC" },
	{ CPU_VEN_VIA, "VIA VIA VIA " },

	/* Old vendors */
	{ CPU_VEN_AMD_OLD, "AMDisbetter!" },      // early engineering samples of AMD K5 processor
	{ CPU_VEN_TRANSMETA_OLD,"TransmetaCPU" },
 
	/* VM vendors */
	{ CPU_VEN_VMWARE, "VMwareVMware" },
	{ CPU_VEN_XEN, "XenVMMXenVMM" },
	{ CPU_VEN_HYPER_V, "Microsoft Hv" },
	{ CPU_VEN_PARALLELS, " lrpepyh vr" }
};

static char * _cpu_processor_type[] = {
	"Original OEM processor",
	"Intel(R) OverDrive(R) processor",
	"Dual processor",
	"Intel(R) reserved"
};

typedef struct {
	uint32_t basic;
	uint32_t extended;
} CPU_MAX_VALUES;

// CPU vendor information
typedef struct {
	uint32_t id;
	char name[CPU_VENDOR_STRING_LEN + 1];
} CPU_VENDOR_INFO;

// CPU family, model & stepping information
typedef struct {
	uint8_t family;
	uint8_t model;
	uint8_t stepping;
} CPU_FMS;

// CPUID with EAX=1 (bitfields)
#define DUMMY_FEATURES
typedef struct {
	union {
		CPUID_01 Regs;
		uint32_t Signature : 24;
	} DUMMYSTRUCTNAME;
} CPU_FEATURES;

#pragma pack(pop)

/* Basic 'cpuid' wrapper functions */

void __cdecl cpuid(uint32_t leaf, uint32_t regs[]);
void __cdecl cpuidex(uint32_t leaf, uint32_t subleaf, uint32_t regs[]);


/* Advanced functions */

// Check if CPUID is available
int __cdecl is_cpuid_available();

// Get CPUID maximum values
CPU_MAX_VALUES * __cdecl cpu_max_values();

// Get CPU vendor information
CPU_VENDOR_INFO *  __cdecl cpu_vendor_info();

// Get CPU brand name string
char * __cdecl cpu_brand();

// Get CPU features
CPU_FEATURES * __cdecl cpu_features();

// Get CPU family, model and stepping information
CPU_FMS * __cdecl cpu_fms();

uint32_t __cdecl cpu_signature();

uint32_t __cdecl cpu_count();

// ----------------------
// CPU database functions
// ----------------------

typedef struct {
	uint32_t vendor;	// CPU vendor ID
	uint8_t family;		// CPUID family
	uint8_t ext_family;	// CPUID extended family
	uint8_t model;		// CPUID model
	uint8_t ext_model;	// CPUID extended model
	const char * arch;	// Microarchitecture
	const char * core;	// Core name(s)
	uint32_t process;	// Technology process (lithography) in nanometers
} CPUDB;

typedef struct {
	unsigned size;
	CPUDB * table;
} CPUDB_TABLE;

typedef struct {
	CPU_VENDOR_INFO vendor;			// CPU vendor information
	char brand[CPU_BRAND_STRING_LEN + 1];	// CPU brand name (identity string)
	uint8_t family;			// Calculated family
	uint8_t model;          	// Calculated model
	uint8_t stepping;		// Stepping
	char * arch;			// Microarchitecture
	char * core;			// Core name
	uint8_t process;		// Technology process (lithography) in nanometers
	CPU_FEATURES features;		// Basic CPU features list
	CPU_MAX_VALUES max_values;	// Maximum values for CPUID
} CPU_INFO;

CPU_INFO * __cdecl cpu_info();

#endif
