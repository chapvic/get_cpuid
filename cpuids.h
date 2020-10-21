#ifndef _CPUIDS_H
#define _CPUIDS_H

#ifndef _STDINT_H
#include <stdint.h>
#endif

#ifndef DUMMYSTRUCTNAME
#define DUMMYSTRUCTNAME
#endif

#ifndef DUMMYUNIONNAME
#define DUMMYUNIONNAME
#endif

#pragma pack(push,1)

// https://en.wikipedia.org/wiki/CPUID
// https://ru.wikipedia.org/wiki/CPUID

// -----------------------
// Generic CPUID structure
// -----------------------
typedef struct {
	union {
		struct {
			uint32_t EAX;
			uint32_t EBX;
			uint32_t ECX;
			uint32_t EDX;
		} DUMMYSTRUCTNAME;
		uint32_t Raw[4];
	} DUMMYUNIONNAME;
} CPUID_REGS;

// ------------------------------------
// Basic CPUID Information (EAX = 0x00)
// ------------------------------------
// EAX - Max. values for basic CPUID
// EBX - CPU vendor name (part 1)
// ECX - CPU vendor name (part 3)
// EDX - CPU vendor name (part 2)
// ------------------------------------
typedef struct {
	union {
		struct {
			uint32_t MaxBasicValue; // EAX
			uint32_t VendorName_1;  // EBX
			uint32_t VendorName_3;  // ECX
			uint32_t VendorName_2;  // EDX
		} DUMMYSTRUCTNAME;
		uint32_t Raw[4];
	} DUMMYUNIONNAME;
} CPUID_00, *P_CPUID_00;

// --------------------------------------
// CPUID Feature Information (EAX = 0x01)
// --------------------------------------
typedef struct {
	union {
		struct {
			struct {
				uint32_t Stepping : 4;		// [0:3] Stepping
				uint32_t Model : 4;		// [4:7] Model
				uint32_t Family : 4;		// [8:11] Family
				uint32_t ProcessorType : 2;	// [12:13] Processor Type
				uint32_t __unused1 : 2;		// [14:15]
				uint32_t ExtendedModel : 4;	// [16:19] Extended Model
				uint32_t ExtendedFamily : 8;	// [20:27] Extended Family
				uint32_t __unused2 : 4;		// [28:31]
			} EAX;
			struct {
				uint32_t BrandIndex : 8;	// [0:7] Brand index. This number provides an entry into a brand string table that contains brand strings for IA-32 processors.
				uint32_t CLFLUSH_LineSize : 8;	// [8:15] CLFLUSH instruction cache line size. This number indicates the size of the cache line flushed by the CLFLUSH and CLFLUSHOPT
								// instructions in 8-byte increments. This field was introduced in the Pentium 4 processor.
								// (Value * 8 = cache line size in bytes)
				uint32_t LogicalProcessors : 8;	// [16:23] Maximum number of addressable IDs for logical processors in this physical package
								// The nearest power-of-2 integer that is not smaller than this value is the number of unique initial APIC IDs reserved for addressing different logical processors in a physical package.
								// Former use: Number of logical processors per physical processor; two for the Pentium 4 processor with Hyper-Threading Technology.
								// Valid if Hyper-threading feature flag is set. CPUID_01.EDX.HTT [bit 28] = 1
				uint32_t LocalAPIC_ID : 8;	// [24:31] Local APIC ID. The initial APIC-ID is used to identify the executing logical processor.
								// This number is the 8-bit ID that is assigned to the local APIC on the processor during power up. This field was introduced in the Pentium 4 processor.
								// It can also be identified via the cpuid 0BH leaf ( CPUID_0B.EDX[X2APIC_ID] )
			} EBX;
			struct {
				uint32_t SSE3 : 1;		// SSE3 New Instructions
				uint32_t PCLMULQDQ : 1;		// PCLMULQDQ Instruction
				uint32_t DTES64 : 1;		// 64-Bit Debug Store
				uint32_t MONITOR : 1;		// MONITOR/MWAIT
				uint32_t DS_CPL : 1;		// CPL Qualified Debug Store (Intel), Reserved (AMD)
				uint32_t VMX : 1;		// Virtual Machine Extensions (Intel), Reserved (AMD)
				uint32_t SMX : 1;		// Safer Mode Extensions (Intel), Reserved (AMD)
				uint32_t EIST : 1;		// Enhanced Intel SpeedStep Technology (Intel), Reserved (AMD)
				uint32_t TM2 : 1;		// Thermal Monitor 2 (Intel), Reserved (AMD)
				uint32_t SSSE3 : 1;		// Supplemental Streaming SIMD Extensions 3 (SSSE3)
				uint32_t CNXT_ID : 1;		// L1 context ID (Intel), Reserved (AMD)
				uint32_t SDBG : 1;		// Supports IA32_DEBUG_INTERFACE MSR for silicon debug (Intel), Reserved (AMD)
				uint32_t FMA : 1;		// 256-bit FMA extensions using YMM state (Intel), Reserved (AMD)
				uint32_t CMPXCHG16B : 1;	// CMPXCHG16B Available
				uint32_t XTPR : 1;		// xTPR Update Control - supports changing IA32_MISC_ENABLE [bit 23].
				uint32_t PDCM : 1;		// Perf/Debug Capability MSR - supports the performance and debug feature indication MSR IA32_PERF_CAPABILITIES
				uint32_t __unused1 : 1;
				uint32_t PCID : 1;		// Process-context Identifiers - supports PCIDs and that software may set CR4.PCIDE to 1
				uint32_t DCA : 1;		// Direct cache access (DCA) support (Intel), Reserved (AMD)
				uint32_t SSE4_1 : 1;		// Streaming SIMD Extensions 4.1
				uint32_t SSE4_2 : 1;		// Streaming SIMD Extensions 4.2
				uint32_t X2APIC : 1;		// x2APIC support (Intel), Reserved (AMD)
				uint32_t MOVBE : 1;		// MOVBE support (Intel), Reserved (AMD)
				uint32_t POPCNT : 1;		// POPCNT Instruction Support
				uint32_t TSC_Deadline : 1;	// Time Stamp Counter Deadline
				uint32_t AES : 1;		// AES support (Intel), Reserved (AMD)
				uint32_t XSAVE : 1;		// XSAVE support - supports the XSAVE/XRSTOR processor extended states feature, the XSETBV/XGETBV instructions, and XCR0 (Intel), Reserved (AMD)
				uint32_t OSXSAVE : 1;		// OSXSAVE support  - the OS has set CR4.OSXSAVE [bit 18] to enable XSETBV/XGETBV instructions to access XCR0 and to support processor extended state management using XSAVE/XRSTOR.(Intel), Reserved (AMD)
				uint32_t AVX : 1;		// 256-bit Intel advanced vector extensions (Intel), Reserved (AMD)
				uint32_t F16C : 1;		// 16-bit floating-point conversion instructions support
				uint32_t RDRAND : 1;		// RDRAND instruction support
				uint32_t HYPERVISOR : 1;	// Hypervisor present (always zero on physical CPUs)
			} ECX;
			struct {
				uint32_t FPU : 1;		// x87 FPU on Chip
				uint32_t VME : 1;		// Virtual-8086 Mode Enhancement
				uint32_t DE : 1;		// Debugging Extensions
				uint32_t PSE : 1;		// Page Size Extensions
				uint32_t TSC : 1;		// Time Stamp Counter (doesn't imply MSR=1)
				uint32_t MSR : 1;		// RDMSR and WRMSR Support
				uint32_t PAE : 1;		// Physical Address Extensions
				uint32_t MCE : 1;		// Machine Check Exception
				uint32_t CX8 : 1;		// CMPXCHG8B Instruction
				uint32_t APIC : 1;		// APIC on Chip
				uint32_t __unused1 : 1;
				uint32_t SEP : 1;		// SYSENTER and SYSEXIT
				uint32_t MTRR : 1;		// Memory Type Range Registers
				uint32_t PGE : 1;		// PTE Global Bit
				uint32_t MCA : 1;		// Machine Check Architecture
				uint32_t CMOV : 1;		// Conditional Move/Compare Instruction, if FPU=1 then also FCMOVcc/F(U)COMI(P)
				uint32_t PAT : 1;		// Page Attribute Table
				uint32_t PSE36 : 1;		// 36-bit Page Size Extension
				uint32_t PSN : 1;		// Processor Serial Number
				uint32_t CLFSH : 1;		// CLFLUSH instruction
				uint32_t __unused2 : 1;
				uint32_t DTES : 1;		// Debug Trace and EMON Store MSRs
				uint32_t ACPI : 1;		// Thermal Monitor and Clock Control
				uint32_t MMX : 1;		// MMX Technology
				uint32_t FXSR : 1;		// FXSAVE/FXRSTOR
				uint32_t SSE : 1;		// SSE Extensions
				uint32_t SSE2 : 1;		// SSE2 Extensions
				uint32_t SS : 1;		// Self Snoop
				uint32_t HTT : 1;		// Hyper Threading enabled
				uint32_t TM : 1;		// Thermal Monitor enabled
				uint32_t IA_64_JMPE : 1;	// IA-64, JMPE Jv, JMPE Ev
				uint32_t PBE : 1;		// Pending Break Enable
			} EDX;
		} DUMMYSTRUCTNAME;
		uint32_t Raw[4];
	} DUMMYUNIONNAME;
} CPUID_01, *P_CPUID_01;

// -------------------------------------------
// TLB/Cache/Prefetch Information (EAX = 0x02)
// -------------------------------------------
typedef CPUID_REGS CPUID_02, *P_CPUID_02;

// ------------------------------------------------------------------------
// Deterministic Cache Parameters for Each Level (EAX = 0x04 with sub-leaf)
// ------------------------------------------------------------------------
typedef struct {
	union {
		struct {
			// Leaf 04H output depends on the initial value in ECX.*
			struct {
				uint32_t CacheType : 5;		// [0:4] Cache Type Field (0=null, 1=data, 2=code, 3=unified, 4...31=reserved)
				uint32_t CacheLevel : 3;	// [5:7] Cache Level (starts at 1).
				uint32_t SelfInitializing : 1;	// [8] Self Initializing cache level (does not need SW initialization).
				uint32_t FullyAssociative : 1;	// [9] Fully Associative cache.
				uint32_t __unused1 : 4;		// [10:13] Reserved.
				uint32_t ThreadsPerCache : 12;	// [14:25] Maximum number of addressable IDs for logical processors sharing this cache **, ***.
				uint32_t CoresPerPackage : 6;	// [26:31] Maximum number of addressable IDs for processor cores in the physical package **, ****, *****.
			} EAX;
			// NOTES:
			// *	 If ECX contains an invalid sub leaf index, EAX / EBX / ECX / EDX return 0. Sub-leaf index N + 1 is invalid if subleaf N returns EAX[4:0] as 0.
			// **	 Add one to the return value to get the result.
			// ***	 The nearest power-of-2 integer that is not smaller than(1 + EAX[25:14]) is the number of unique initial APIC IDs reserved for addressing different logical processors sharing this cache.
			// ****	 The nearest power-of-2 integer that is not smaller than(1 + EAX[31:26]) is the number of unique Core_IDs reserved for addressing different processor cores in a physical package. Core ID is a subset of bits of the initial APIC ID.
			// ***** The returned value is constant for valid initial values in ECX.Valid ECX values start from 0.
			struct {
				uint32_t SystemCoherencyLineSize : 12;	// [0:11] System Coherency Line Size **.
				uint32_t PhysicalLinePartitions : 10;	// [12:21] Physical Line partitions **.
				uint32_t WaysOfAssociativity : 10;	// [22:31] Ways of associativity **.
			} EBX;
			struct {
				uint32_t NumberOfSets : 32;		// [0:31] Number of Sets **.
			} ECX;
			struct {
				uint32_t WriteBack : 1;			// [1] Write-Back Invalidate/Invalidate.
									//     0 = WBINVD/INVD from threads sharing this cache acts upon lower level caches for threads sharing this cache.
									//     1 = WBINVD/INVD is not guaranteed to act upon lower level caches of non-originating threads sharing this cache.
				uint32_t CacheInclusiveness : 1;	// [2] Cache Inclusiveness (0 = Cache is not inclusive of lower cache levels. 1 = Cache is inclusive of lower cache levels).
				uint32_t ComplexCacheIndexing : 1;	//     Complex Cache Indexing (0 = Direct mapped cache. 1 = A complex function is used to index the cache, potentially using all address bits).
				uint32_t __unused1 : 30;		// [3:31] Reserved = 0.
			} EDX;
		} DUMMYSTRUCTNAME;
		uint32_t Raw[4];
	} DUMMYUNIONNAME;
} CPUID_04, *P_CPUID_04;

// ---------------------------------------
// MONITOR and MWAIT Features (EAX = 0x05)
// ---------------------------------------
typedef struct {
	union {
		struct {
			struct {
				uint32_t SmallestLineSize : 16;		// [0:15] Smallest monitor-line size in bytes (default is processor's monitor granularity).
				uint32_t __unused1 : 16;		// [16:31] Reserved = 0.
			} EAX;
			struct {
				uint32_t LargestLineSize : 16;		// [0:15] Largest monitor-line size in bytes (default is processor's monitor granularity).
				uint32_t __unused1 : 16;		// [16:31] Reserved = 0.
			} EBX;
			struct {
				uint32_t Enumeration : 1;		// [0] Enumeration of Monitor-Mwait extensions (beyond EAX and EBX registers) supported.
				uint32_t TreatingInterrupts : 1;	// [1] Supports treating interrupts as break-event for MWAIT, even when interrupts disabled.
				uint32_t __unused1 : 30;		// [2:31] Reserved.
			} ECX;
			struct {
				uint32_t C0 : 4;	// [0:3] Number of C0* sub C-states supported using MWAIT.
				uint32_t C1 : 4;	// [4:7] Number of C1* sub C-states supported using MWAIT.
				uint32_t C2 : 4;	// [8:11] Number of C2* sub C-states supported using MWAIT.
				uint32_t C3 : 4;	// [12:15] Number of C3* sub C-states supported using MWAIT.
				uint32_t C4 : 4;	// [16:19] Number of C4* sub C-states supported using MWAIT.
				uint32_t C5 : 4;	// [20:23] Number of C5* sub C-states supported using MWAIT.
				uint32_t C6 : 4;	// [24:27] Number of C6* sub C-states supported using MWAIT.
				uint32_t C7 : 4;	// [28:31] Number of C7* sub C-states supported using MWAIT.
			} EDX;
			// NOTE:
			// *  The definition of C0 through C7 states for MWAIT extension are processor-specific C-states, not ACPI Cstates.
		} DUMMYSTRUCTNAME;
		uint32_t Raw[4];
	} DUMMYUNIONNAME;
} CPUID_05, *P_CPUID_05;

// ----------------------------------------------
// Thermal and Power Management Leaf (EAX = 0x06)
// ----------------------------------------------
typedef struct {
	union {
		struct {
			struct {
				uint32_t DTS : 1;	// [0] Digital temperature sensor is supported if set.
				uint32_t TBT : 1;	// [1] Intel Turbo Boost Technology Available (see description of IA32_MISC_ENABLE [38]).
				uint32_t ARAT : 1;	// [2] APIC-Timer-always-running feature is supported if set.
				uint32_t __unused1 : 1;	// [3] Reserved.
				uint32_t PLN : 1;	// [4] Power limit notification controls are supported if set.
				uint32_t ECMD : 1;	// [5] Clock modulation duty cycle extension is supported if set.
				uint32_t PTM : 1;	// [6] Package thermal management is supported if set.
				uint32_t HWP : 1;	// [7] HWP base registers (IA32_PM_ENABLE[bit 0], IA32_HWP_CAPABILITIES, IA32_HWP_REQUEST, IA32_HWP_STATUS) are supported if set.
				uint32_t HWP_N : 1;	// [8] HWP Notification. IA32_HWP_INTERRUPT MSR is supported if set.
				uint32_t HWP_AW : 1;	// [9] HWP Activity Window. IA32_HWP_REQUEST[bits 41:32] is supported if set.
				uint32_t HWP_EPP : 1;	// [10] HWP Energy Performance Preference. IA32_HWP_REQUEST[bits 31:24] is supported if set.
				uint32_t HWP_PLR : 1;	// [11] HWP Package Level Request. IA32_HWP_REQUEST_PKG MSR is supported if set.
				uint32_t __unused2 : 1;	// [12] Reserved.
				uint32_t HDC : 1;		// [13] HDC base registers IA32_PKG_HDC_CTL, IA32_PM_CTL1, IA32_THREAD_STALL MSRs are supported if set.
				uint32_t __unused3 : 18;	// [14:31] Reserved.
			} EAX;
			struct {
				uint32_t InterruptThresholds : 4;	// [0:3] Number of Interrupt Thresholds in Digital Thermal Sensor.
				uint32_t __unused1 : 28;		// [4:31] Reserved.
			} EBX;
			struct {
				uint32_t HWCF : 1;		// [0] Hardware Coordination Feedback Capability (Presence of IA32_MPERF and IA32_APERF). The capability to provide a measure of delivered processor performance(since last reset of the counters), as a percentage of the expected processor performance when running at the TSC frequency.
				uint32_t __unused1 : 2;		// [1:2] Reserved = 0.
				uint32_t PEB : 1;		// [3] The processor supports performance-energy bias preference if CPUID.06H:ECX.SETBH[bit 3] is set and it also implies the presence of a new architectural MSR called IA32_ENERGY_PERF_BIAS(1B0H).
				uint32_t __unused2 : 28;	// [4:31] Reserved = 0.
			} ECX;
			struct {
				uint32_t __unused1 : 32;	// [0:31] Reserved = 0.
			} EDX;
		} DUMMYSTRUCTNAME;
		uint32_t Raw[4];
	} DUMMYUNIONNAME;
} CPUID_06, *P_CPUID_06;

// ---------------------------------------------------------------------------------------
// Extended Feature Flags Enumeration Leaf (EAX = 0x07. Output depends on ECX input value)
// ---------------------------------------------------------------------------------------
typedef struct {
	union {
		struct {
			struct {
				uint32_t MaximumSubLeaves : 32;		// Reports the maximum input value for supported leaf 7 sub-leaves.
			} EAX;						// If ECX contains an invalid sub-leaf index, EAX/EBX/ECX/EDX return 0. Sub-leaf index N is invalid if N exceeds the value that sub-leaf 0 returns in EAX.
			struct {
				uint32_t FSGSBASE : 1;			// [0] Supports RDFSBASE/RDGSBASE/WRFSBASE/WRGSBASE if 1.
				uint32_t IA32_TSC_ADJUST_MSR : 1;	// [1] IA32_TSC_ADJUST MSR is supported if 1.
				uint32_t SGX : 1;			// [2] Supports Intel® Software Guard Extensions (Intel® SGX Extensions) if 1.
				uint32_t BMI1 : 1;		// [3]
				uint32_t HLE : 1;		// [4]
				uint32_t AVX2 : 1;		// [5]
				uint32_t FDP_EXCPTN_ONLY : 1;	// [6] x87 FPU Data Pointer updated only on x87 exceptions if 1.
				uint32_t SMEP : 1;		// [7] Supports Supervisor-Mode Execution Prevention if 1.
				uint32_t BMI2 : 1;		// [8]
				uint32_t EREP : 1;		// [9] Supports Enhanced REP MOVSB/STOSB if 1.
				uint32_t INVPCID : 1;		// [10] If 1, supports INVPCID instruction for system software that manages process-context identifiers.
				uint32_t RTM : 1;		// [11]
				uint32_t RDT_M : 1;		// [12] Supports Intel® Resource Director Technology (Intel® RDT) Monitoring capability if 1.
				uint32_t DFPU : 1;		// [13] Deprecates FPU CS and FPU DS values if 1.
				uint32_t MPX : 1;		// [14] Supports Intel® Memory Protection Extensions if 1.
				uint32_t RDT_A : 1;		// [15] Supports Intel® Resource Director Technology (Intel® RDT) Allocation capability if 1.
				uint32_t __unused1 : 2;		// [16:17] Reserved.
				uint32_t RDSEED : 1;		// [18]
				uint32_t ADX : 1;		// [19]
				uint32_t SMAP : 1;		// [20] Supports Supervisor-Mode Access Prevention (and the CLAC/STAC instructions) if 1.
				uint32_t __unused2 : 2;		// [21:22] Reserved.
				uint32_t CLFLUSHOPT : 1;	// [23]
				uint32_t CLWB : 1;		// [24]
				uint32_t IPT : 1;		// [25] Intel Processor Trace.
				uint32_t __unused3 : 3;		// [26:28] Reserved.
				uint32_t SHA : 1;		// [29] Supports Intel® Secure Hash Algorithm Extensions (Intel® SHA Extensions) if 1.
				uint32_t __unused4 : 2;		// [30:31] Reserved.
			} EBX;
			struct {
				uint32_t PREFETCHWT1 : 1;	// [0] Supports PREFETCHWT1.
				uint32_t __unused1 : 1;		// [1] Reserved.
				uint32_t UMIP : 1;		// [2] Supports user-mode instruction prevention if 1.
				uint32_t PKU : 1;		// [3] Supports protection keys for user-mode pages if 1.
				uint32_t OSPKE : 1;		// [4] If 1, OS has set CR4.PKE to enable protection keys (and the RDPKRU/WRPKRU instructions).
				uint32_t __unused2 : 12;	// [5:16] Reserved.
				uint32_t MAWAU : 5;		// [17:21] The value of MAWAU used by the BNDLDX and BNDSTX instructions in 64-bit mode.
				uint32_t RDPID : 1;		// [22] Supports Read Processor ID if 1.
				uint32_t __unused3 : 7;		// [23:29] Reserved.
				uint32_t SGX_LC : 1;		// [30] Supports SGX Launch Configuration if 1.
				uint32_t __unused4 : 1;		// [31] Reserved.
			} ECX;
			struct {
				uint32_t __unused1 : 32;	// [0:31] Reserved.
			} EDX;
		} DUMMYSTRUCTNAME;
		uint32_t Raw[4];
	} DUMMYUNIONNAME;
} CPUID_07, *P_CPUID_07;

// -------------------------------------------------
// Direct Cache Access Information Leaf (EAX = 0x09)
// -------------------------------------------------
typedef struct {
	union {
		struct {
			struct {
				uint32_t IA32_PLATFORM_DCA_CAP_MSR : 32;	// [0:31] Value of IA32_PLATFORM_DCA_CAP MSR (address 1F8H).
			} EAX;
			struct {
				uint32_t __unused1 : 32;			// [0:31] Reserved.
			} EBX;
			struct {
				uint32_t __unused1 : 32;			// [0:31] Reserved.
			} ECX;
			struct {
				uint32_t __unused1 : 32;			// [0:31] Reserved.
			} EDX;
		} DUMMYSTRUCTNAME;
		uint32_t Raw[4];
	} DUMMYUNIONNAME;
} CPUID_09, *P_CPUID_09;

// -----------------------------------------------------
// Architectural Performance Monitoring Leaf (EAX = 0AH)
// -----------------------------------------------------
typedef struct {
	union {
		struct {
			struct {
				uint32_t VersionID : 8;		// [0:7] Version ID of architectural performance monitoring.
				uint32_t GP_PMC : 8;		// [8:15] Number of general-purpose performance monitoring counter per logical processor.
				uint32_t BitWidth : 8;		// [16:23] Bit width of general-purpose, performance monitoring counter.
				uint32_t BitVectorLength : 8;	// [24:31] Length of EBX bit vector to enumerate architectural performance monitoring events.
			} EAX;
			struct {
				uint32_t CCE : 1;		// [0] Core cycle event not available if 1.
				uint32_t IRE : 1;		// [1] Instruction retired event not available if 1.
				uint32_t RCE : 1;		// [3] Reference cycles event not available if 1.
				uint32_t LLCRE : 1;		// [4] Last-level cache reference event not available if 1.
				uint32_t LLCME : 1;		// [5] Last-level cache misses event not available if 1.
				uint32_t BIRE : 1;		// [6] Branch instruction retired event not available if 1.
				uint32_t BMRE : 1;		// [7] Branch mispredict retired event not available if 1.
				uint32_t __unused1 : 25;	// Reserved = 0.
			} EBX;
			struct {
				uint32_t __unused1 : 32;	// [0:31] Reserved = 0.
			} ECX;
			struct {
				uint32_t FFPC_Count : 5;	// [0:4] Number of fixed-function performance counters (if Version ID > 1).
				uint32_t FFPC_BitWidth : 9;	// [5:12] Bit width of fixed-function performance counters (if Version ID > 1).
				uint32_t __unused1 : 19;	// [13:31] Reserved = 0.
			} EDX;
		} DUMMYSTRUCTNAME;
		uint32_t Raw[4];
	} DUMMYUNIONNAME;
} CPUID_0A, *P_CPUID_0A;

// ----------------------------------------------
// Extended Topology Enumeration Leaf (EAX = 0BH)
// ----------------------------------------------
// NOTES:
// Most of Leaf 0BH output depends on the initial value in ECX.
// The EDX output of leaf 0BH is always valid and does not vary with input value in ECX.
// Output value in ECX[7:0] always equals input value in ECX[7:0].
// For sub-leaves that return an invalid level-type of 0 in ECX[15:8]; EAX and EBX will return 0.
// If an input value N in ECX returns the invalid level-type of 0 in ECX[15:8], other input values with ECX > N also return 0 in ECX[15:8].
typedef struct {
	union {
		struct {
			struct {
				uint32_t ShiftRight : 5;		// [0:4] - Number of bits to shift right on x2APIC ID to get a unique topology ID of the next level type. All logical processors with the same next level ID share current level.
				uint32_t __unused1 : 27;		// [5:31] Reserved.
			} EAX;
			struct {
				uint32_t LogicalProcessors : 16;	// [0:15] Number of logical processors at this level type. The number reflects configuration as shipped by Intel**.
				uint32_t __unused1 : 16;		// [16:31] Reserved.
			} EBX;
			struct {
				uint32_t LevelNumber : 8;		// [0:7] Level number. Same value in ECX input.
				uint32_t LevelType : 8;			// [8:15] Level type***.
				uint32_t __unused1 : 16;		// [16:31] Reserved.
			} ECX;
			struct {
				uint32_t X2APIC_ID : 32;		// x2APIC ID the current logical processor.
			} EDX;
			// NOTES:
			// *   Software should use this field(EAX[4:0]) to enumerate processor topology of the system.
			// **  Software must not use EBX[15:0] to enumerate processor topology of the system. This value in this field(EBX[15:0]) is only intended for display/diagnostic purposes.
			//     The actual number of logical processors available to BIOS/OS/Applications may be different from the value of EBX[15:0], depending on software and platform hardware configurations.
			// *** The value of the "level type" field is not related to level numbers in any way, higher "level type" values do not mean higher levels.
			//     Level type field has the following encoding:
			//     0 : Invalid
			//     1 : SMT (hyperthreading)
			//     2 : Core
			//     3 - 255 : Reserved
		} DUMMYSTRUCTNAME;
		uint32_t Raw[4];
	} DUMMYUNIONNAME;
} CPUID_0B, *P_CPUID_0B;

// -------------------------------------------------------------------
// Processor Extended State Enumeration Main Leaf (EAX = 0DH, ECX = 0)
// -------------------------------------------------------------------
// NOTES: Leaf 0DH main leaf (ECX=0).
typedef struct {
	union {
		struct {
			struct {
				uint32_t X87 : 1;		// [0] x87 state.
				uint32_t SSE : 1;		// [1] SSE state.
				uint32_t AVX : 1;		// [2] AVX state.
				uint32_t MPX : 2;		// [3:4] MPX state.
				uint32_t AVX512 : 3;		// [5:7] AVX-512 state.
				uint32_t IA32_XSS : 1;		// [8] Used for IA32_XSS.
				uint32_t PKRU : 1;		// [9] PKRU state.
				uint32_t __unused1 : 22;	// [10-31] Reserved.
			} EAX;					// Bits 0-31: Reports the supported bits of the lower 32 bits of XCR0. XCR0[n] can be set to 1 only if EAX[n] is 1.
			struct {
				uint32_t XCR0_Max : 32;		// [0:31] Maximum size (bytes, from the beginning of the XSAVE/XRSTOR save area) required by enabled features in XCR0. May be different than ECX if some features at the end of the XSAVE save area are not enabled.
			} EBX;
			struct {
				uint32_t XCR0_MaxAll : 32;	// [0:31] Maximum size (bytes, from the beginning of the XSAVE/XRSTOR save area) of the XSAVE/XRSTOR save area required by all supported features in the processor, i.e., all the valid bit fields in XCR0.
			} ECX;
			struct {
				uint32_t XCR0_BitsUpper : 32;	// [0:31] Reports the supported bits of the upper 32 bits of XCR0. XCR0[n+32] can be set to 1 only if EDX[n] is 1. Otherwise is reserved.
			} EDX;
		} DUMMYSTRUCTNAME;
		uint32_t Raw[4];
	} DUMMYUNIONNAME;
} CPUID_0D_0, *P_CPUID_0D_0;

// ------------------------------------------------------------------
// Processor Extended State Enumeration Sub-leaf (EAX = 0DH, ECX = 1)
// ------------------------------------------------------------------
typedef struct {
	union {
		struct {
			struct {
				uint32_t XSAVEOPT : 1;		// [0] XSAVEOPT is available.
				uint32_t XSAVEC : 1;		// [1] Supports XSAVEC and the compacted form of XRSTOR if set.
				uint32_t XGETBV : 1;		// [2] Supports XGETBV with ECX = 1 if set.
				uint32_t XSR : 2;		// [3] Supports XSAVES/XRSTORS and IA32_XSS if set.
				uint32_t __unused1 : 27;	// [4-31] Reserved.
			} EAX;
			struct {
				uint32_t XSAVE_Size : 32;	// [0:31] The size in bytes of the XSAVE area containing all states enabled by XCRO | IA32_XSS.
			} EBX;
			struct {
				uint32_t XCR0_1 : 8;		// [0:7] Used for XCR0.
				uint32_t PT : 1;		// [8] PT state.
				uint32_t XCR0_2 : 1;		// [9] Used for XCR0.
				uint32_t __unused1 : 22;	// [10:31] Reserved.
			} ECX;					// Reports the supported bits of the lower 32 bits of the IA32_XSS MSR. IA32_XSS[n] can be set to 1 only if ECX[n] is 1.
			struct {
				uint32_t IA32_XSS_BitsUpper : 32;	// Reports the supported bits of the upper 32 bits of the IA32_XSS MSR. IA32_XSS[n+32] can be set to 1 only if EDX[n] is 1.  Otherwise is reserved.
			} EDX;
		} DUMMYSTRUCTNAME;
		uint32_t Raw[4];
	} DUMMYUNIONNAME;
} CPUID_0D_1, *P_CPUID_0D_1;

// --------------------------------------------------------------------------
// Processor Extended State Enumeration Sub-leafs (EAX = 0DH, ECX = n, n > 1)
// -------------------------------------------------------------------------- 
// NOTES:
// Leaf 0DH output depends on the initial value in ECX.
// Each sub-leaf index(starting at position 2) is supported if it corresponds to a supported bit in either the XCR0 register or the IA32_XSS MSR.
// * If ECX contains an invalid sub-leaf index, EAX/EBX/ECX/EDX return 0. Sub-leaf n(0 ? n ? 31) is invalid if sub-leaf 0 returns 0 in EAX[n] and sub-leaf 1 returns 0 in ECX[n]. Sub-leaf n(32 ? n ? 63) is invalid if sub-leaf 0 returns 0 in EDX[n-32] and sub-leaf 1 returns 0 in EDX[n-32].
typedef struct {
	union {
		struct {
			uint32_t EAX;				// The size in bytes (from the offset specified in EBX) of the save area for an extended state feature associated with a valid sub-leaf index, N.
			uint32_t EBX;				// The offset in bytes of this extended state component’s save area from the beginning of the XSAVE/XRSTOR area. This field reports 0 if the sub-leaf index, N, does not map to a valid bit in the XCR0 register*.
			struct {
				uint32_t IA32_XSS : 1;		// Set if the bit N (corresponding to the sub-leaf index) is supported in the IA32_XSS MSR; it is clear if bit N is instead supported in XCR0.
				uint32_t XSAVE_CompactArea : 1;	// Set if, when the compacted format of an XSAVE area is used, this extended state component located on the next 64-byte boundary following the preceding state component(otherwise, it is located immediately following the preceding state component).
				uint32_t __unused1 : 30;	// Reserved.
			} ECX;					// This field reports 0 if the sub-leaf index, N, is invalid*.
			uint32_t EDX;				// This field reports 0 if the sub-leaf index, N, is invalid*; otherwise it is reserved.
		} DUMMYSTRUCTNAME;
		uint32_t Raw[4];
	} DUMMYUNIONNAME;
} CPUID_0D_N, *P_CPUID_0D_N;

// ---------------------------------------------------------------------------------------------------
// Intel Resource Director Technology (Intel RDT) Monitoring Enumeration Sub-leaf (EAX = 0FH, ECX = 0)
// ---------------------------------------------------------------------------------------------------
typedef CPUID_REGS CPUID_0F_0, *P_CPUID_0F_0;

// ----------------------------------------------------------------------------------
// L3 Cache Intel RDT Monitoring Capability Enumeration Sub-leaf (EAX = 0FH, ECX = 1)
// ----------------------------------------------------------------------------------
typedef CPUID_REGS CPUID_0F_1, *P_CPUID_0F_1;

// ---------------------------------------------------------------------------------------------------
// Intel Resource Director Technology (Intel RDT) Allocation Enumeration Sub-leaf (EAX = 10H, ECX = 0)
// ---------------------------------------------------------------------------------------------------
typedef CPUID_REGS CPUID_10_0, *P_CPUID_10_0;

// --------------------------------------------------------------------------------
// L3 Cache Allocation Technology Enumeration Sub-leaf (EAX = 10H, ECX = ResID = 1)
// --------------------------------------------------------------------------------
typedef CPUID_REGS CPUID_10_1, *P_CPUID_10_1;

// --------------------------------------------------------------------------------
// L2 Cache Allocation Technology Enumeration Sub-leaf (EAX = 10H, ECX = ResID = 2)
// --------------------------------------------------------------------------------
typedef CPUID_REGS CPUID_10_2, *P_CPUID_10_2;

// -----------------------------------------------------------------------------
// Memory Bandwidth Allocation Enumeration Sub-leaf (EAX = 10H, ECX = ResID = 3)
// -----------------------------------------------------------------------------
typedef CPUID_REGS CPUID_10_3, *P_CPUID_10_3;

// ----------------------------------------------------------------------
// Intel SGX Capability Enumeration Leaf, sub-leaf 0 (EAX = 12H, ECX = 0)
// ----------------------------------------------------------------------
typedef CPUID_REGS CPUID_12_0, *P_CPUID_12_0;

// ----------------------------------------------------------------------
// Intel SGX Attributes Enumeration Leaf, sub-leaf 1 (EAX = 12H, ECX = 1)
// ----------------------------------------------------------------------
typedef CPUID_REGS CPUID_12_1, *P_CPUID_12_1;

// -------------------------------------------------------------------------
// Intel SGX EPC Enumeration Leaf, sub-leaves (EAX = 12H, ECX = 2 or higher)
// -------------------------------------------------------------------------
typedef CPUID_REGS CPUID_12_N, *P_CPUID_12_N;

// ----------------------------------------------------------------
// Intel Processor Trace Enumeration Main Leaf (EAX = 14H, ECX = 0)
// ----------------------------------------------------------------
typedef CPUID_REGS CPUID_14_0, *P_CPUID_14_0;

// ---------------------------------------------------------------
// Intel Processor Trace Enumeration Sub-leaf (EAX = 14H, ECX = 1)
// ---------------------------------------------------------------
typedef CPUID_REGS CPUID_14_1, *P_CPUID_14_1;

// ------------------------------------------------------------------------------
// Time Stamp Counter and Nominal Core Crystal Clock Information Leaf (EAX = 15H)
// ------------------------------------------------------------------------------
typedef CPUID_REGS CPUID_15, *P_CPUID_15;

// ------------------------------------------------
// Processor Frequency Information Leaf (EAX = 15H)
// ------------------------------------------------
typedef CPUID_REGS CPUID_16, *P_CPUID_16;

// --------------------------------------------------------------------------
// System-On-Chip Vendor Attribute Enumeration Main Leaf (EAX = 17H, ECX = 0)
// --------------------------------------------------------------------------
typedef CPUID_REGS CPUID_17_0, *P_CPUID_17_0;

// ----------------------------------------------------------------------------
// System-On-Chip Vendor Attribute Enumeration Sub-leaf (EAX = 17H, ECX = 1..3)
// ----------------------------------------------------------------------------
typedef CPUID_REGS CPUID_17_N, *P_CPUID_17_N;

// ----------------------------------------------------------------------------------------
// System-On-Chip Vendor Attribute Enumeration Sub-leaves (EAX = 17H, ECX > MaxSOCID_Index)
// ----------------------------------------------------------------------------------------
// EAX Reserved = 0.
// EBX Reserved = 0.
// ECX Reserved = 0.
// EDX Reserved = 0.
// ----------------------------------------------------------------------------------------
typedef CPUID_REGS CPUID_17_X, *P_CPUID_17_X;



// -----------------------------------
// Extended Function CPUID Information
// -----------------------------------
typedef struct {
	union {
		struct {
			uint32_t MaxExtendedValue;	// Maximum Input Value for Extended Function CPUID Information.
			/*
			uint32_t EBX;	// Reserved.
			uint32_t ECX;	// Reserved.
			uint32_t EDX;	// Reserved.
			*/
		} DUMMYSTRUCTNAME;
		uint32_t Raw[4];
	} DUMMYUNIONNAME;
} CPUID_80, P_CPUID_80;

typedef struct {
	union {
		struct {
			uint32_t EAX;				// Extended Processor Signature and Feature Bits.
			uint32_t EBX;				// Reserved.
			struct {
				uint32_t LAHF_SAHF : 1;		// LAHF/SAHF available in 64-bit mode
				uint32_t CMPL : 1;		// Core multi-processing legacy mode (CmpLegacy) (AMD), Reserved (Intel)
				uint32_t SVM : 1;		// Secure Virtual Machine (AMD), Reserved (Intel)
				uint32_t XAPICS : 1;		// Extended APIC Register Space (AMD), Reserved (Intel)
				uint32_t MOVCR8 : 1;		// LOCK MOV CR0 means MOV CR8 (AMD), Reserved (Intel)
				uint32_t LZCNT : 1;		// LZCNT Support (AMD), Reserved (Intel)
				uint32_t SSE4A : 1;		// SSE4A instruction support (EXTRQ, INSERTQ, MOVNTSD, MOVNTSS) (AMD), Reserved (Intel)
				uint32_t MSSE : 1;		// Misaligned SSE Support Mode Available (AMD), Reserved (Intel)
				uint32_t PF : 1;		// PREFETCH and PREFETCHW support (AMD), Reserved (Intel)
				uint32_t __unused1 : 3;		//
				uint32_t SKINITDEV : 1;		// SKINIT and DEV support (AMD), Reserved (Intel)
				uint32_t __unused2 : 19;	//
			} ECX;
			struct {
				uint32_t __unused1 : 11;	//
				uint32_t SYSCALL : 1;		// SYSCALL/SYSRET available in 64-bit mode
				uint32_t __unused2 : 8;		//
				uint32_t XD : 1;		// Execute Disable Bit available
				uint32_t __unused3 : 1;		//
				uint32_t ExtMMX : 1;		// Extensions to MMX instructions (AMD), Reserved (Intel)
				uint32_t __unused4 : 2;		//
				uint32_t FFXSR : 1;		// FXSAVE and FXRSTOR instruction optimizations (AMD), Reserved (Intel)
				uint32_t P1GB : 1;		// 1GB page support (AMD), Reserved (Intel)
				uint32_t RDTSCP : 1;		// RDTSCP Instruction (AMD), Reserved (Intel)
				uint32_t __unused5 : 1;		//
				uint32_t EM64T : 1;		// 64-bit Technology available
				uint32_t Is3DNowExt : 1;	// AMD Extensions to 3DNow! (AMD), Reserved (Intel)
				uint32_t Is3DNow : 1;		// 3DNow! Instructions (AMD), Reserved (Intel)
			} EDX;
		} DUMMYSTRUCTNAME;
		uint32_t Raw[4];
	} DUMMYUNIONNAME;
} CPUID_81, P_CPUID_81;

// -----------------------------------
// NOTES:
// * L2 associativity field encodings:
//     00H - Disabled.
//     01H - Direct mapped.
//     02H - 2-way.
//     04H - 4-way.
//     06H - 8-way.
//     08H - 16-way.
//     0FH - Fully associative.
// -----------------------------------
typedef struct {
	union {
		struct {
			uint32_t EAX;	// Reserved = 0.
			uint32_t EBX;	// Reserved = 0.
			struct {
				uint32_t CLS : 8;	// [0:7] Cache Line size in bytes.
				uint32_t __unused1 : 4;	// [8:11] Reserved.
				uint32_t L2AF : 4;	// [12:15] L2 Associativity field *.
				uint32_t CS : 16;
			} ECX;
			uint32_t EDX;	// Reserved = 0.
		} DUMMYSTRUCTNAME;
		uint32_t Raw[4];
	} DUMMYUNIONNAME;
} CPUID_86, P_CPUID_86;

typedef struct {
	union {
		struct {
			uint32_t EAX;	// Reserved = 0.
			uint32_t EBX;	// Reserved = 0.
			uint32_t ECX;	// Reserved = 0.
			struct {
				uint32_t __unused1 : 8;		// [0:7] Reserved = 0.
				uint32_t ITSC : 1;		// [8] Invariant TSC (Time Stamp Counter) available if 1.
				uint32_t __unused2 : 23;	// [9:31] Reserved = 0.
			} EDX;
		} DUMMYSTRUCTNAME;
		uint32_t Raw[4];
	} DUMMYUNIONNAME;
} CPUID_87, P_CPUID_87;

// ----------------------------------------------------------------------------------------------------------------------
// NOTES:
// * If CPUID.80000008H:EAX[0:7] is supported, the maximum physical address number supported should come from this field.
// ----------------------------------------------------------------------------------------------------------------------
typedef struct {
	union {
		struct {
			// Linear/Physical Address size.
			struct {
				uint32_t PAB : 8;		// [0:7] # Physical Address Bits *.
				uint32_t LAB : 8;		// [8:15] # Linear Address Bits.
				uint32_t __unused1 : 16;	// Reserved = 0.
			} EAX;
			uint32_t EBX;	// Reserved = 0.
			uint32_t ECX;	// Reserved = 0.
			uint32_t EDX;	// Reserved = 0.
		} DUMMYSTRUCTNAME;
		uint32_t Raw[4];
	} DUMMYUNIONNAME;
} CPUID_88, P_CPUID_88;

#pragma pack(pop)

#endif // !_CPUIDS_H
