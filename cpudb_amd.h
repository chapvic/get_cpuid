#ifndef _CPUDB_AMD_H
#define _CPUDB_AMD_H

// ----------------------------------------------
// Source: https://en.wikichip.org/wiki/amd/cpuid
// ----------------------------------------------

static const char ARCH_Bobcat[] = "Bobcat";
static const char ARCH_Bulldozer[] = "Bulldozer";
static const char ARCH_Piledriver[] = "Piledriver";
static const char ARCH_Steamroller[] = "Steamroller";
static const char ARCH_Excavator[] = "Excavator";
static const char ARCH_Jaguar[] = "Jaguar";
static const char ARCH_Puma[] = "Puma";
static const char ARCH_Zen[] = "Zen";
static const char ARCH_ZenPlus[] = "Zen+";
static const char ARCH_Zen2[] = "Zen 2";
static const char ARCH_Zen3[] = "Zen 3";

static CPUDB _cpudb_amd[] = {
	// Family 20 (uncomplete)
	// { CPU_VEN_AMD, 0xF, 0x5, ?, 0, ARCH_Bobcat, "Desna, Ontario, Zacate", 0 },

	// Family 21
	//{ CPU_VEN_AMD, 0xF, 0x6, ?, 0, ARCH_Bulldozer, "Zurich, Valencia", 32 },
	{ CPU_VEN_AMD, 0xF, 0x6, 0x1, 0, ARCH_Bulldozer, "Zambezi, Interlagos", 32 },
	//{ CPU_VEN_AMD, 0xF, 0x6, ?, 0x1, ARCH_Piledriver, "Richland, Vishera, Delhi, Seoul, Abu Dhabi", 32 },
	{ CPU_VEN_AMD, 0xF, 0x6, 0x1, 0x1, ARCH_Piledriver, "Trinity", 32 },
	//{ CPU_VEN_AMD, 0xF, 0x6, ?, 0x3, ARCH_Steamroller, "Bald Eagle", 28 },
	{ CPU_VEN_AMD, 0xF, 0x6, 0, 0x3, ARCH_Steamroller, "Kaveri", 28 },
	{ CPU_VEN_AMD, 0xF, 0x6, 0x8, 0x3, ARCH_Steamroller, "Godavari", 28 },
	//{ CPU_VEN_AMD, 0xF, 0x6, ?, ?, ARCH_Excavator, "Brown Falcon, Prairie Falcon", 28 },
	{ CPU_VEN_AMD, 0xF, 0x6, 0, 0x6, ARCH_Excavator, "Carrizo", 28 },
	{ CPU_VEN_AMD, 0xF, 0x6, 0x5, 0x6, ARCH_Excavator, "Bristol Ridge", 28 },
	{ CPU_VEN_AMD, 0xF, 0x6, 0, 0x7, ARCH_Excavator, "Stoney Ridge", 28 },
};

#endif // !_CPUDB_AMD_H
