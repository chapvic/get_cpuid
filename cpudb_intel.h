#ifndef _CPUDB_INTEL_H
#define _CPUDB_INTEL_H

// ------------------------------------------------
// Source: https://en.wikichip.org/wiki/intel/cpuid
// ------------------------------------------------

static const char ARCH_80486[] = "80486";
static const char ARCH_P5[] = "P5";
static const char ARCH_P6[] = "P6";
static const char ARCH_Lakemont[] = "Lakemont";
static const char ARCH_Knights_Landing[] = "Knights Landing";
static const char ARCH_Knights_Mill[] = "Knights Mill";
static const char ARCH_Bonnell[] = "Bonnell";
static const char ARCH_Saltwell[] = "Saltwell";
static const char ARCH_Silvermont[] = "Silvermont";
static const char ARCH_Airmont[] = "Airmont";
static const char ARCH_Goldmont[] = "Goldmont";
static const char ARCH_Goldmont_Plus[] = "Goldmont Plus";
static const char ARCH_Tremont[] = "Tremont";
static const char ARCH_Penryn[] = "Penryn";
static const char ARCH_Nehalem[] = "Nehalem";
static const char ARCH_Westmere[] = "Westmere";
static const char ARCH_Sandy_Bridge[] = "Sandy Bridge";
static const char ARCH_Ivy_Bridge[] = "Ivy Bridge";
static const char ARCH_Haswell[] = "Haswell";
static const char ARCH_Broadwell[] = "Broadwell";
static const char ARCH_Skylake[] = "Skylake";
static const char ARCH_Cascade_Lake[] = "Cascade Lake";
static const char ARCH_Cooper_Lake[] = "Cooper Lake";
static const char ARCH_Ice_Lake[] = "Ice Lake";
static const char ARCH_Pentium_M[] = "Pentium M";
static const char ARCH_Modified_Pentium_M[] = "Modified Pentium M";
static const char ARCH_Core[] = "Core";
static const char ARCH_Kaby_Lake[] = "Kaby Lake";
static const char ARCH_Coffee_Lake[] = "Coffee Lake";
static const char ARCH_Cannon_Lake[] = "Cannon Lake";
static const char ARCH_Whiskey_Lake[] = "Whiskey Lake";
static const char ARCH_Amber_Lake[] = "Amber Lake";
static const char ARCH_Comet_Lake[] = "Comet Lake";
static const char ARCH_Tiger_Lake[] = "Tiger Lake";
static const char ARCH_Rocket_Lake[] = "Rocket Lake";
static const char ARCH_Alder_Lake[] = "Alder Lake";
static const char ARCH_Knights_Corner[] = "Knights Corner";
static const char ARCH_Knights_Ferry[] = "Knights Ferry";
static const char ARCH_Netburst[] = "Netburst";

static CPUDB _cpudb_intel[] = {
	// Family 4
	{ CPU_VEN_INTEL, 4, 0, 0x1, 0, ARCH_80486, "80486DX", 800 },
	{ CPU_VEN_INTEL, 4, 0, 0x2, 0, ARCH_80486, "80486SX", 800 },
	{ CPU_VEN_INTEL, 4, 0, 0x3, 0, ARCH_80486, "80486DX2", 800 },
	{ CPU_VEN_INTEL, 4, 0, 0x4, 0, ARCH_80486, "80486SL", 800 },
	{ CPU_VEN_INTEL, 4, 0, 0x5, 0, ARCH_80486, 0, 800 },
	{ CPU_VEN_INTEL, 4, 0, 0x6, 0, ARCH_80486, 0, 800 },
	{ CPU_VEN_INTEL, 4, 0, 0x7, 0, ARCH_80486, 0, 800 },
	{ CPU_VEN_INTEL, 4, 0, 0x8, 0, ARCH_80486, "80486DX4", 600 },
	{ CPU_VEN_INTEL, 4, 0, 0x9, 0, ARCH_80486, 0, 800 },
	// Family 5
	{ CPU_VEN_INTEL, 5, 0, 0x1, 0, ARCH_P5, "P5, P54, P54CQS", 600 },
	{ CPU_VEN_INTEL, 5, 0, 0x2, 0, ARCH_P5, "P55CS", 600 },
	{ CPU_VEN_INTEL, 5, 0, 0x4, 0, ARCH_P5, "P55C", 600 },
	{ CPU_VEN_INTEL, 5, 0, 0x7, 0, ARCH_P5, "P55C (Mobile)", 600 },
	{ CPU_VEN_INTEL, 5, 0, 0x8, 0, ARCH_P5, "P55C (Mobile)", 600 },
	{ CPU_VEN_INTEL, 5, 0, 0x9, 0, ARCH_Lakemont, "Quark", 32 },
	{ CPU_VEN_INTEL, 5, 0, 0xA, 0, ARCH_Lakemont, "Quark", 32 },
	// Family 6 - MIC Architecture
	{ CPU_VEN_INTEL, 6, 0, 0x7, 0x5, ARCH_Knights_Landing, 0, 14 },
	{ CPU_VEN_INTEL, 6, 0, 0x5, 0x8, ARCH_Knights_Mill, 0, 14 },
	// Family 6 - Small cores
	{ CPU_VEN_INTEL, 6, 0, 0xC, 0x1, ARCH_Bonnell, "Silverthorne, Diamondville, Pineview", 45 },
	{ CPU_VEN_INTEL, 6, 0, 0x6, 0x2, ARCH_Bonnell, "Lincroft", 45 },
	{ CPU_VEN_INTEL, 6, 0, 0x7, 0x2, ARCH_Saltwell, "Penwell", 32 },
	{ CPU_VEN_INTEL, 6, 0, 0x5, 0x3, ARCH_Saltwell, "Cloverview", 32 },
	{ CPU_VEN_INTEL, 6, 0, 0x6, 0x3, ARCH_Saltwell, "Cedarview", 32 },
	{ CPU_VEN_INTEL, 6, 0, 0x7, 0x3, ARCH_Silvermont, "Bay Trail", 22 },
	{ CPU_VEN_INTEL, 6, 0, 0xA, 0x4, ARCH_Silvermont, "Tangier", 22 },
	{ CPU_VEN_INTEL, 6, 0, 0xD, 0x4, ARCH_Silvermont, "Avoton, Rangeley", 22 },
	{ CPU_VEN_INTEL, 6, 0, 0xA, 0x5, ARCH_Silvermont, "Anniedale", 22 },
	{ CPU_VEN_INTEL, 6, 0, 0xD, 0x5, ARCH_Silvermont, "SoFIA", 22 },
	{ CPU_VEN_INTEL, 6, 0, 0xC, 0x4, ARCH_Airmont, "Cherry Trail, Braswell", 14 },
	{ CPU_VEN_INTEL, 6, 0, 0xC, 0x5, ARCH_Goldmont, "Apollo Lake, Broxton", 14 },
	{ CPU_VEN_INTEL, 6, 0, 0xF, 0x5, ARCH_Goldmont, "Denverton", 14 },
	{ CPU_VEN_INTEL, 6, 0, 0xA, 0x7, ARCH_Goldmont_Plus, "Gemini Lake", 14 },
	{ CPU_VEN_INTEL, 6, 0, 0x6, 0x8, ARCH_Tremont, "Elkhart Lake", 10 },
	//
	// Family 6 - Big cores (server)
	// Intel's server big cores refers to Intel workstation and data center SoCs that ship in most enterprise desktops, workstations, and servers.
	//
	{ CPU_VEN_INTEL, 6, 0, 0xA, 0, ARCH_P6, 0, 250 },
	{ CPU_VEN_INTEL, 6, 0, 0x7, 0x1, ARCH_Penryn, "Harpertown, QC, Wolfdale, Yorkfield", 45 },
	{ CPU_VEN_INTEL, 6, 0, 0xD, 0x1, ARCH_Penryn, "Dunnington", 45 },
	{ CPU_VEN_INTEL, 6, 0, 0xA, 0x1, ARCH_Nehalem, "Bloomfield, EP, WS", 45 },
	{ CPU_VEN_INTEL, 6, 0, 0xE, 0x1, ARCH_Nehalem, "Lynnfield", 45 },
	{ CPU_VEN_INTEL, 6, 0, 0xE, 0x2, ARCH_Nehalem, "EX", 45 },
	{ CPU_VEN_INTEL, 6, 0, 0xF, 0x2, ARCH_Westmere, "EX", 32 },
	{ CPU_VEN_INTEL, 6, 0, 0xC, 0x2, ARCH_Westmere, "Gulftown, EP", 32 },
	{ CPU_VEN_INTEL, 6, 0, 0xD, 0x2, ARCH_Sandy_Bridge, "E, EN, EP", 32 },
	{ CPU_VEN_INTEL, 6, 0, 0xE, 0x3, ARCH_Ivy_Bridge, "E, EN, EP, EX", 22 },
	{ CPU_VEN_INTEL, 6, 0, 0xF, 0x3, ARCH_Haswell, "E, EP, EX", 22 },
	{ CPU_VEN_INTEL, 6, 0, 0x6, 0x5, ARCH_Broadwell, "DE, Hewitt Lake", 14 },
	{ CPU_VEN_INTEL, 6, 0, 0xF, 0x4, ARCH_Broadwell, "E, EP, EX", 14 },
// ------------------- dups 'model' & 'ext_model'
	{ CPU_VEN_INTEL, 6, 0, 0x5, 0x5, ARCH_Skylake, "SP, X, DE, W", 14 },
	{ CPU_VEN_INTEL, 6, 0, 0x5, 0x5, ARCH_Cascade_Lake, "SP, X, W", 14 },
	{ CPU_VEN_INTEL, 6, 0, 0x5, 0x5, ARCH_Cooper_Lake, 0, 14 },
// ------------------- <<<
	{ CPU_VEN_INTEL, 6, 0, 0xA, 0x6, ARCH_Ice_Lake, "DE", 10 },
	{ CPU_VEN_INTEL, 6, 0, 0xC, 0x6, ARCH_Ice_Lake, "SP", 10 },
//	{ CPU_VEN_INTEL, 6, 0, 0, 0, "Sapphire Rapids", "", 10 },
//	{ CPU_VEN_INTEL, 6, 0, 0, 0, "Granite Rapids", "", 7 },
//	{ CPU_VEN_INTEL, 6, 0, 0, 0, "Diamond Rapids", "", 7 },
	//
	// Family 6 - Big cores (client)
	// Intel's client big cores refers to Intel mainstream SoCs that ship in most tablets, latops, and desktop devices.
	//
	{ CPU_VEN_INTEL, 6, 0, 0x1, 0, ARCH_P6, 0, 350 },
	{ CPU_VEN_INTEL, 6, 0, 0x3, 0, ARCH_P6, 0, 350 },
	{ CPU_VEN_INTEL, 6, 0, 0x5, 0, ARCH_P6, 0, 350 },
	{ CPU_VEN_INTEL, 6, 0, 0x6, 0, ARCH_P6, 0, 350 },
	{ CPU_VEN_INTEL, 6, 0, 0x7, 0, ARCH_P6, "Katmai", 250 },
	{ CPU_VEN_INTEL, 6, 0, 0x8, 0, ARCH_P6, "Coppermine, Coppermine T", 250 },
	{ CPU_VEN_INTEL, 6, 0, 0xB, 0, ARCH_P6, "Tualatin", 250 },
	{ CPU_VEN_INTEL, 6, 0, 0x9, 0, ARCH_Pentium_M, "Banias", 130 },
	{ CPU_VEN_INTEL, 6, 0, 0xD, 0, ARCH_Pentium_M, "Dothan", 90 },
	{ CPU_VEN_INTEL, 6, 0, 0x5, 0x1, ARCH_Pentium_M, "Tolapai", 90 },
	{ CPU_VEN_INTEL, 6, 0, 0xE, 0, ARCH_Modified_Pentium_M, "Yonah", 65 },
	{ CPU_VEN_INTEL, 6, 0, 0xF, 0, ARCH_Core, "Merom", 65 },
	{ CPU_VEN_INTEL, 6, 0, 0x6, 0x1, ARCH_Core, "Merom L", 65 },
	{ CPU_VEN_INTEL, 6, 0, 0x7, 0x1, ARCH_Penryn, "Penryn, Wolfdale, Yorkfield", 45 },
	{ CPU_VEN_INTEL, 6, 0, 0xE, 0x1, ARCH_Nehalem, "Clarksfield", 45 },
	{ CPU_VEN_INTEL, 6, 0, 0xF, 0x1, ARCH_Nehalem, "Auburndale, Havendale", 45 },
	{ CPU_VEN_INTEL, 6, 0, 0x5, 0x2, ARCH_Westmere, "Arrandale, Clarkdale", 32 },
	{ CPU_VEN_INTEL, 6, 0, 0xA, 0x2, ARCH_Sandy_Bridge, "M, H", 32 },
	{ CPU_VEN_INTEL, 6, 0, 0xA, 0x3, ARCH_Ivy_Bridge, "M, H, Gladden", 22 },
	{ CPU_VEN_INTEL, 6, 0, 0xC, 0x3, ARCH_Haswell, "S", 22 },
	{ CPU_VEN_INTEL, 6, 0, 0x5, 0x4, ARCH_Haswell, "ULT", 22 },
	{ CPU_VEN_INTEL, 6, 0, 0x6, 0x4, ARCH_Haswell, "GT3E", 22 },
	{ CPU_VEN_INTEL, 6, 0, 0x7, 0x4, ARCH_Broadwell, "H", 14 },
	{ CPU_VEN_INTEL, 6, 0, 0xD, 0x3, ARCH_Broadwell, "U, Y, S", 14 },
	{ CPU_VEN_INTEL, 6, 0, 0x7, 0x4, ARCH_Broadwell, "C, W", 14 },
	{ CPU_VEN_INTEL, 6, 0, 0xE, 0x4, ARCH_Skylake, "Y, U", 14 },
	{ CPU_VEN_INTEL, 6, 0, 0xE, 0x5, ARCH_Skylake, "DT, H, S", 14 },
// ------------------- dups 'model' & 'ext_model'
	{ CPU_VEN_INTEL, 6, 0, 0xE, 0x8, ARCH_Kaby_Lake, "Y, U", 14 },
	{ CPU_VEN_INTEL, 6, 0, 0xE, 0x9, ARCH_Kaby_Lake, "DT, H, S, X", 14 },
	{ CPU_VEN_INTEL, 6, 0, 0xE, 0x8, ARCH_Coffee_Lake, "U", 14 },
	{ CPU_VEN_INTEL, 6, 0, 0xE, 0x9, ARCH_Coffee_Lake, "S, H, E", 14 },
// ------------------- <<<
	{ CPU_VEN_INTEL, 6, 0, 0x6, 0x6, ARCH_Cannon_Lake, "U", 10 },
// ------------------- dups 'model' & 'ext_model'
	{ CPU_VEN_INTEL, 6, 0, 0xE, 0x8, ARCH_Whiskey_Lake, "U", 14 },
	{ CPU_VEN_INTEL, 6, 0, 0xE, 0x8, ARCH_Amber_Lake, "Y", 14 },
	{ CPU_VEN_INTEL, 6, 0, 0xE, 0x8, ARCH_Comet_Lake, "U", 14 },
// ------------------- <<<
	{ CPU_VEN_INTEL, 6, 0, 0xE, 0x9, ARCH_Comet_Lake, "S, H", 14 },
	{ CPU_VEN_INTEL, 6, 0, 0xD, 0x7, ARCH_Ice_Lake, "Y", 10 },
	{ CPU_VEN_INTEL, 6, 0, 0xE, 0x7, ARCH_Ice_Lake, "U", 10 },
	{ CPU_VEN_INTEL, 6, 0, 0xD, 0x8, ARCH_Tiger_Lake, "H", 10 },
	{ CPU_VEN_INTEL, 6, 0, 0xC, 0x8, ARCH_Tiger_Lake, "U", 10 },
	{ CPU_VEN_INTEL, 6, 0, 0x7, 0xA, ARCH_Rocket_Lake, "S", 14 },
	{ CPU_VEN_INTEL, 6, 0, 0xA, 0x9, ARCH_Alder_Lake, "P", 10 },
	{ CPU_VEN_INTEL, 6, 0, 0x7, 0x9, ARCH_Alder_Lake, "S", 10 },
//	{ CPU_VEN_INTEL, 6, 0, 0, 0, "Raptor Lake", "", 10 },
//	{ CPU_VEN_INTEL, 6, 0, 0, 0, "Meteor Lake", "", 7 },
	//
	// Family 11
	//
	{ CPU_VEN_INTEL, 0xB, 0, 0, 0, ARCH_Knights_Corner, 0, 22 },
	{ CPU_VEN_INTEL, 0xB, 0, 0x1, 0, ARCH_Knights_Ferry, 0, 45 },
	//
	// Family 15
	//
	{ CPU_VEN_INTEL, 0xF, 0, 0x1, 0, ARCH_Netburst, "Willamette", 180 },
	{ CPU_VEN_INTEL, 0xF, 0, 0x2, 0, ARCH_Netburst, "Northwood", 130 },
	{ CPU_VEN_INTEL, 0xF, 0, 0x3, 0, ARCH_Netburst, "Prescott", 90 },
	{ CPU_VEN_INTEL, 0xF, 0, 0x4, 0, ARCH_Netburst, "Prescott", 90 },
	{ CPU_VEN_INTEL, 0xF, 0, 0x6, 0, ARCH_Netburst, 0, 90 },
};

#endif // !_CPUDB_INTEL_H
