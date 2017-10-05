#pragma once

#include "log.h"

#ifdef LUNAR_DLL

#define NOBANK	LC_NOBANK
#define LOROM	LC_LOROM
#define HIROM	LC_HIROM
#define	EXHIROM	LC_EXHIROM
#define EXLOROM	LC_EXLOROM
#define LOROM2	LC_LOROM_2
#define HIROM2	LC_HIROM_2

#define PC2SNES		LunarPCtoSNES
#define SNES2PC		LunarSNEStoPC
#else

#define NOBANK	0
#define LOROM	1
#define HIROM	2
#define	EXHIROM	4
#define EXLOROM	8
#endif

#define HEADERSIZE	0x200
#define MAXBANKS	0x100
#define MAXBANKSIZE	0x10000
#define MAXROMSIZE	((MAXBANKS*MAXBANKSIZE)+HEADERSIZE)

#define MAKERCODEADDRESS	0xFFB0	// Address of Maker code
#define GAMECODEADDRESS		0xFFB2	// Address of Game code
#define EXPRAMSIZEADDRESS	0xFFBD	// Address of Expansion RAM size
#define SPECIALVERADDRESS	0xFFBE	// Address of Special Version value
#define CARTTYPEADDRESS		0xFFBF	// Address of Cart Type value
#define ROMNAMEADDRESS		0xFFC0	// Address of ROM Name string
#define ROMNAMELENGTH		21		// Length of ROM Name string
#define MAPMODEADDRESS		0xFFD5	// Address of Map Mode value
#define ROMTYPEADDRESS		0xFFD6	// Address of ROM type value
#define ROMSIZEADDRESS		0xFFD7	// Address of ROM size code
#define ROMSIZEMIN			0x07	// Minimum valid ROM size
#define ROMSIZEMAX			0x0D	// Maximum valid ROM size
#define ROMSIZEBASE			0x400	// Used for calculating byte ROM size
#define	SRAMSIZEADDRESS		0xFFD8	// Address of SRAM size value
#define	DESTCODEADDRESS		0xFFD9	// Address of Destination code
#define FIXEDVALUEADRESS	0xFFDA	// Address of Fixed Value
#define VERSIONNUMADDRESS	0xFFDB	// Address of Version Number
#define COMPCHECKADDRESS	0xFFDC	// Address of Complement Checksum
#define CHECKSUMADDRESS		0xFFDE	// Address of Checksum

#define NATIVECOPVECTOR		0xFFE4	// Address of Native COP Vector
#define NATIVEBRKVECTOR		0xFFE6	// Address of Native BRK Vector
#define NATIVEABORTVECTOR	0xFFE8	// Address of Native ABORT Vector
#define NATIVENMIVECTOR		0xFFEA	// Address of Native NMI Vector
#define NATIVERESETVECTOR	0xFFEC	// Address of Native RESET Vector
#define NATIVEIRQVECTOR		0xFFEE	// Address ot Native IRQ Vector

#define EMUCOPVECTOR		0xFFF4	// Address of Emulation COP Vector
#define EMUBRKVECTOR		0xFFF6	// Address of Emulation BRK Vector
#define EMUABORTVECTOR		0xFFF8	// Address of Emulation ABORT Vector
#define EMUNMIVECTOR		0xFFFA	// Address of Emulation NMI Vector
#define EMURESETVECTOR		0xFFFC	// Address of Emulation RESET Vector
#define EMUIRQVECTOR		0xFFFE	// Address ot Emulation IRQ Vector

#define SRCROMCOPY			0x10000
#define PROGRAMSET			0x8000
#define SETBYSRCROM(value)	(value == SRCROMCOPY)
#define SETBYPROGRAM(value)	(value == PROGRAMSET)

#define EC_ROMNOTFOUND		1000
#define EC_ROMCANTCLOSE		1001
#define EC_ROMCANTACCESS	1010
#define EC_ROMUNKNOWNSIZE	1011
#define EC_ROMHEADERSIZE	1020
#define EC_ROMSIZETOOBIG	1021
#define EC_ROMCANTREAD		1030
#define EC_ROMBADFORMAT		1040
#define EC_ROMCANTOPENW		1050
#define EC_ROMWRITEFAIL		1051

struct rom_data
{
	/* the path of the rom */
	char path[MAX_PATH];

	/* the binary rom data */
	byte data[MAXROMSIZE];

	/* the actual size of the rom */
	int length;

	/* the size of the rom excluding the header size */
	int sfclength;

	/* rom has header */
	BOOL header;

	/* rom header has been programmatically set */
	BOOL header_set;

	/* lorom, hirom, exlorom, exhirom */
	int mode;

	/* mode has been programmatically set */
	BOOL mode_set;

	/* any code value from the designer */
	int makercode;

	/* makercode has been programmatically set */
	BOOL makercode_set;

	/* any code value from the designer */
	int gamecode;

	/* gamecode has been programmatically set */
	BOOL gamecode_set;

	/* enhancement chip ram size */
	int expramsize;

	/* expramsize has been programmatically set */
	BOOL expramsize_set;

	/* usually given to promotional games */
	int specialversion;

	/* specialversion has been programmatically set */
	BOOL specialversion_set;

	/* 0x00 denotes the standard snes cartridge */
	int carttype;

	/* carttype has been programmatically set */
	BOOL carttype_set;

	/* 21-character ASCII name */
	char name[ROMNAMELENGTH];

	/* name has been programmatically set */
	BOOL name_set;

	/* fastrom, hirom, and enchancement chip flags */
	int mapmode;

	/* mapmode has been programmatically set */
	BOOL mapmode_set;

	/* fastrom mode */
	BOOL fastrom;

	/* fastrom has been programmatically set */
	BOOL fastrom_set;

	/* inclusions of ram, sram, and/or enchancement chips */
	int romtype;

	/* romtype has been programmatically set */
	BOOL romtype_set;

	/* a code value of the desired rom size */
	int size;

	/* size has been programmatically set */
	BOOL size_set;

	/* a code value of the desired sram size */
	int sramsize;

	/* sramsize has been programmatically set */
	BOOL sramsize_set;

	/* a code value of where the product will be sold */
	int destcode;

	/* destcode has been programmatically set */
	BOOL destcode_set;

	/* should be 0x33 */
	int fixedvalue;

	/* fixedvalue has been programmatically set */
	BOOL fixedvalue_set;

	/* version number */
	int versionnum;

	/* versionnum has been programmatically set */
	BOOL versionnum_set;

	/* native cop vector*/
	int nativecopvector;

	/* nativecopvector has been programmatically set */
	BOOL nativecopvector_set;

	/* native brk vector*/
	int nativebrkvector;

	/* nativebrkvector has been programmatically set */
	BOOL nativebrkvector_set;

	/* native abort vector*/
	int nativeabortvector;

	/* nativeabortvector has been programmatically set */
	BOOL nativeabortvector_set;

	/* native nmi vector*/
	int nativenmivector;

	/* nativenmivector has been programmatically set */
	BOOL nativenmivector_set;

	/* native reset vector*/
	int nativeresetvector;

	/* nativeresetvector has been programmatically set */
	BOOL nativeresetvector_set;

	/* native irq vector*/
	int nativeirqvector;

	/* nativeirqvector has been programmatically set */
	BOOL nativeirqvector_set;

	/* emulation cop vector*/
	int emucopvector;

	/* emucopvector has been programmatically set */
	BOOL emucopvector_set;

	/* emulation brk vector*/
	int emubrkvector;

	/* emubrkvector has been programmatically set */
	BOOL emubrkvector_set;

	/* emulation abort vector*/
	int emuabortvector;

	/* emuabortvector has been programmatically set */
	BOOL emuabortvector_set;

	/* emulation nmi vector*/
	int emunmivector;

	/* emunmivector has been programmatically set */
	BOOL emunmivector_set;

	/* emulation reset vector*/
	int emuresetvector;

	/* emuresetvector has been programmatically set */
	BOOL emuresetvector_set;

	/* emulation irq vector*/
	int emuirqvector;

	/* emuirqvector has been programmatically set */
	BOOL emuirqvector_set;

	/* gets the maker code from the rom data */
	int internalmakercode();

	/* gets the game code from the rom data */
	int internalgamecode();

	/* gets the expansion ram size from the rom data */
	int internalexpramsize();

	/* gets the special version value from the rom data */
	int internalspecialversion();

	/* gets the cartridge type form the rom data */
	int internalcarttype();

	/* gets the name from the rom data */
	void internalname(char dest[ROMNAMELENGTH]);

	/* gets the map mode form the rom data */
	int internalmapmode();

	/* gets the type from the rom data */
	int internalromtype();

	/* gets the size from the rom data */
	int internalsize();

	/* gets the sram size from the rom data */
	int internalsramsize();

	/* gets the destination code from the rom data */
	int internaldestcode();

	/* gets the fixed value from the rom data */
	int internalfixedvalue();

	/* gets the version number form the rom data */
	int internalversionnum();

	/* gets the complement checksum from the rom data */
	int internalcomplementcheck();

	/* gets the checksum from the rom data */
	int internalchecksum();

	/* gets the native cop vector from the rom data */
	int internalnativecopvector();

	/* gets the native brk vector from the rom data */
	int internalnativebrkvector();

	/* gets the native abort vector from the rom data */
	int internalnativeabortvector();

	/* gets the native nmi vector from the rom data */
	int internalnativenmivector();

	/* gets the native reset vector from the rom data */
	int internalnativeresetvector();

	/* gets the native irq vector from the rom data */
	int internalnativeirqvector();
	
	/* gets the emulation cop vector from the rom data */
	int internalemucopvector();

	/* gets the emulation brk vector from the rom data */
	int internalemubrkvector();

	/* gets the emulation abort vector from the rom data */
	int internalemuabortvector();

	/* gets the emulation nmi vector from the rom data */
	int internalemunmivector();

	/* gets the emulation reset vector from the rom data */
	int internalemuresetvector();

	/* gets the emulation irq vector from the rom data */
	int internalemuirqvector();

	/* gets the fastrom flag from the map mode */
	int isfastrom();

	/* gets the hirom flag from the map mode */
	int ishirom();
	
	/* lorom, lorom2, hirom, hirom2, exlorom, exhirom */
	int getmode();

	/* get a pc address from a snes address */
	int snes2pc(int snes);
	
	/* get a byte at the snes address */
	int getb(int snes);

	/* get a work at the snes address */
	int getw(int snes);

	/* get a 24-bit int at the snes address */
	int getl(int snes);

	/* get a 32-bit int at the snes address */
	int getd(int snes);

	/* computes the actual checksum of the rom data */
	int computechecksum();

	/* write the rom data back to the file */
	void write();
};

extern rom_data destrom;

/* initializes the source rom */
void initsrcrom(const char *path);

/* initializes the dest rom */
void initdestrom(const char *path);