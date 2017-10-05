#include "rom.h"

rom_data srcrom, destrom;

int rom_data::internalmakercode()
{
	return this->getw(MAKERCODEADDRESS);
}

int rom_data::internalgamecode()
{
	return this->getd(GAMECODEADDRESS);
}

int rom_data::internalexpramsize()
{
	return this->getb(EXPRAMSIZEADDRESS);
}

int rom_data::internalspecialversion()
{
	return this->getb(SPECIALVERADDRESS);
}

int rom_data::internalcarttype()
{
	return this->getb(CARTTYPEADDRESS);
}

void rom_data::internalname(char dest[ROMNAMELENGTH])
{
	memcpy(dest, this->data + this->snes2pc(ROMNAMEADDRESS), ROMNAMELENGTH);
}

int rom_data::internalmapmode()
{
	return this->getb(MAPMODEADDRESS);
}

int rom_data::internalromtype()
{
	return this->getb(ROMTYPEADDRESS);
}

int rom_data::internalsize()
{
	return this->getb(ROMSIZEADDRESS);
}

int rom_data::internalsramsize()
{
	return this->getb(SRAMSIZEADDRESS);
}

int rom_data::internaldestcode()
{
	return this->getb(DESTCODEADDRESS);
}

int rom_data::internalfixedvalue()
{
	return this->getb(FIXEDVALUEADRESS);
}

int rom_data::internalversionnum()
{
	return this->getb(VERSIONNUMADDRESS);
}

int rom_data::internalcomplementcheck()
{
	return this->getw(COMPCHECKADDRESS);
}

int rom_data::internalchecksum()
{
	return this->getw(CHECKSUMADDRESS);
}

int rom_data::internalnativecopvector()
{
	return this->getw(NATIVECOPVECTOR);
}

int rom_data::internalnativebrkvector()
{
	return this->getw(NATIVEBRKVECTOR);
}

int rom_data::internalnativeabortvector()
{
	return this->getw(NATIVEABORTVECTOR);
}

int rom_data::internalnativenmivector()
{
	return this->getw(NATIVENMIVECTOR);
}

int rom_data::internalnativeresetvector()
{
	return this->getw(NATIVERESETVECTOR);
}

int rom_data::internalnativeirqvector()
{
	return this->getw(NATIVEIRQVECTOR);
}
	
int rom_data::internalemucopvector()
{
	return this->getw(EMUCOPVECTOR);
}

int rom_data::internalemubrkvector()
{
	return this->getw(EMUBRKVECTOR);
}

int rom_data::internalemuabortvector()
{
	return this->getw(EMUABORTVECTOR);
}

int rom_data::internalemunmivector()
{
	return this->getw(EMUNMIVECTOR);
}

int rom_data::internalemuresetvector()
{
	return this->getw(EMURESETVECTOR);
}

int rom_data::internalemuirqvector()
{
	return this->getw(EMUIRQVECTOR);
}

int rom_data::isfastrom()
{
	return (this->internalmapmode() & 0x30) == 0x30;
}

int rom_data::ishirom()
{
	return this->internalmapmode() & 0x01;
}

int rom_data::getmode()
{
	/* try to find the right address mode
		check exrom modes first as first bank is usually mirrored */
	const int modes[] = { EXHIROM, EXLOROM, HIROM, LOROM, NOBANK };
	for (int i = 0; modes[i] != NOBANK; i++)
	{
		this->mode = modes[i];

		int checksum = this->internalchecksum();
		int complement = this->internalcomplementcheck();

		/* the checksum and its complement should match */
		if ((checksum ^ complement) == 0xFFFF)
		{
			BOOL match;

			/* now we check that the address mode is matching */
			switch (this->mode)
			{
			case LOROM:
				if (this->isfastrom())
					this->mode = LOROM2;
			case EXLOROM:
				match = !this->ishirom();
				break;

			case HIROM:
				if (this->isfastrom())
					this->mode = HIROM2;
			case EXHIROM:
				match = this->ishirom();
				break;
			}

			/* finally we check the internal size */
			if (match)
			{
				int sz = this->internalsize();
				if (sz < ROMSIZEMIN || sz > ROMSIZEMAX)
					continue;
				int size = ROMSIZEBASE << sz;
				if (this->sfclength > size || this->sfclength <= (size >> 1))
					continue;

				/* everything in the header is valid */
				return this->mode;
			}
		}
	}
	return NOBANK;
}

int rom_data::snes2pc(int snes)
{
	return SNES2PC(snes, this->mode, this->header);
}

int rom_data::getb(int snes)
{
	int pc = this->snes2pc(snes);
	return this->data[pc];
}

int rom_data::getw(int snes)
{
	int pc = this->snes2pc(snes);
	return this->data[pc] | (this->data[pc + 1] << 8);
}

int rom_data::getl(int snes)
{
	int pc = this->snes2pc(snes);
	return this->data[pc] | (this->data[pc + 1] << 8) | (this->data[pc + 2] << 0x10);
}

int rom_data::getd(int snes)
{
	int pc = this->snes2pc(snes);
	return this->data[pc] | (this->data[pc + 1] << 8) | (this->data[pc + 2] << 0x10) | (this->data[pc + 3] << 0x18);
}

int rom_data::computechecksum()
{
	int sum = 0;
	for (int i = this->header; i < this->length; i++)
		sum += this->data[i];
	return sum & 0xFFFF;
}

void rom_data::write()
{
	FILE *fd = fopen(this->path, "wb");
	if (!fd)
		return log(LOG_ERROR, FALSE, FALSE, EC_ROMCANTOPENW, "%s could not be opened for writing", this->path);
	if (fwrite(this->data, 1, this->length, fd) != this->length)
		return log(LOG_ERROR, FALSE, FALSE, EC_ROMWRITEFAIL, "%s could not be written to successfully", this->path);
	if (fclose(fd))
		return log(LOG_WARNING, FALSE, FALSE, EC_ROMCANTCLOSE, "%s could not be closed", this->path);
}

/* get the source rom data */
void initsrcrom(const char *path)
{
	/* clear rom path and data */
	*srcrom.path = 0;
	memset(srcrom.data, 0, MAXROMSIZE);

	/* get src rom data if a file was given */
	if (path && *path)
	{
		/* open file */
		FILE *fd = fopen(path, "rb");
		if (!fd)
			return log(LOG_ERROR, FALSE, FALSE, EC_ROMNOTFOUND, "%s could not be opened for reading", path);

		/* set position to end of file */
		if (fseek(fd, 0, SEEK_END))
			return log(LOG_ERROR, FALSE, FALSE, EC_ROMCANTACCESS, "%s could not be accessed", path);

		/* get file size */
		if ((srcrom.length = ftell(fd)) == -1)
			return log(LOG_ERROR, FALSE, FALSE, EC_ROMUNKNOWNSIZE, "could not get file size of %s", path);

		/* get and validate header size */
		srcrom.header = srcrom.length & 0x7FFF;
		if (srcrom.header && srcrom.header != HEADERSIZE)
			return log(LOG_ERROR, FALSE, FALSE, EC_ROMHEADERSIZE, "%s has an invalid header size", path);

		/* validate file szie */
		srcrom.sfclength = srcrom.length - srcrom.header;
		if (srcrom.sfclength > MAXROMSIZE - HEADERSIZE)
			return log(LOG_ERROR, FALSE, FALSE, EC_ROMSIZETOOBIG, "%s exceeds maximum binary size", path);

		/* get rom data */
		rewind(fd);
		if (fread(srcrom.data, 1, srcrom.length, fd) != srcrom.length)
			return log(LOG_ERROR, FALSE, FALSE, EC_ROMCANTREAD, "could not read %s", path);

		/* close file */
		if (fclose(fd))
			log(LOG_WARNING, FALSE, FALSE, EC_ROMCANTCLOSE, "%s could not be closed", path);	// Don't set as an error as this shouldn't affect patching

		/* validate address mode */
		if ((srcrom.mode = srcrom.getmode()) == NOBANK)
			return log(LOG_ERROR, FALSE, FALSE, EC_ROMBADFORMAT, "%s does not have a valid internal header (cannot not verify address mode)");
	
		/* get path */
		strcpy(srcrom.path, path);
	}
}

void initdestrom(const char *path)
{
	if (path)
		strcpy(destrom.path, path);
	memset(destrom.data, 0, MAXROMSIZE);

	if (*srcrom.path)
	{
		memcpy(destrom.data, srcrom.data, srcrom.length);

		destrom.length		= srcrom.length;
		destrom.sfclength	= srcrom.sfclength;
		destrom.header		= srcrom.header;
		destrom.mode		= srcrom.mode;

		destrom.makercode		= srcrom.internalmakercode();
		destrom.gamecode		= srcrom.internalgamecode();
		destrom.expramsize		= srcrom.internalexpramsize();
		destrom.specialversion	= srcrom.internalspecialversion();
		destrom.carttype		= srcrom.internalcarttype();

		srcrom.internalname(destrom.name);
		destrom.mapmode		= srcrom.internalmapmode();
		destrom.fastrom		= srcrom.isfastrom();
		destrom.romtype		= srcrom.internalromtype();
		destrom.size		= srcrom.internalsize();
		destrom.sramsize	= srcrom.internalsramsize();
		destrom.destcode	= srcrom.internaldestcode();

		destrom.nativecopvector		= srcrom.internalnativecopvector();
		destrom.nativebrkvector		= srcrom.internalnativebrkvector();
		destrom.nativeabortvector	= srcrom.internalnativeabortvector();
		destrom.nativenmivector		= srcrom.internalnativenmivector();
		destrom.nativeresetvector	= srcrom.internalnativeresetvector();
		destrom.nativeirqvector		= srcrom.internalnativeirqvector();

		destrom.emucopvector	= srcrom.internalemucopvector();
		destrom.emubrkvector	= srcrom.internalemubrkvector();
		destrom.emuabortvector	= srcrom.internalemuabortvector();
		destrom.emunmivector	= srcrom.internalemunmivector();
		destrom.emuresetvector	= srcrom.internalemuresetvector();
		destrom.emuirqvector	= srcrom.internalemuirqvector();
		
		destrom.header_set =
		destrom.mode_set =
		destrom.makercode_set =
		destrom.gamecode_set =
		destrom.gamecode_set =
		destrom.expramsize_set =
		destrom.specialversion_set =
		destrom.carttype_set =
		destrom.name_set =
		destrom.mapmode_set =
		destrom.fastrom_set =
		destrom.romtype_set =
		destrom.size_set =
		destrom.sramsize_set =
		destrom.destcode_set =
		destrom.fixedvalue_set =
		destrom.versionnum_set =
		destrom.nativecopvector_set =
		destrom.nativebrkvector_set =
		destrom.nativeabortvector_set =
		destrom.nativenmivector_set =
		destrom.nativeresetvector_set =
		destrom.nativeirqvector_set =
		destrom.emucopvector_set =
		destrom.emubrkvector_set =
		destrom.emuabortvector_set =
		destrom.emunmivector_set =
		destrom.emuresetvector_set =
		destrom.emuirqvector_set = SRCROMCOPY;
	}
	else
	{
		destrom.length		=
		destrom.sfclength	=
		destrom.header		= 0;
		destrom.mode		= NOBANK;

		destrom.makercode		= 
		destrom.gamecode		= 
		destrom.expramsize		= 
		destrom.specialversion	= 
		destrom.carttype		= 0;

		memset(destrom.name, 0, ROMNAMELENGTH);
		destrom.mapmode		= 
		destrom.fastrom		= 
		destrom.romtype		= 
		destrom.size		= 
		destrom.sramsize	= 
		destrom.destcode	= 0;

		destrom.nativecopvector		= 
		destrom.nativebrkvector		= 
		destrom.nativeabortvector	= 
		destrom.nativenmivector		= 
		destrom.nativeresetvector	= 
		destrom.nativeirqvector		= 0;

		destrom.emucopvector	= 
		destrom.emubrkvector	= 
		destrom.emuabortvector	= 
		destrom.emunmivector	= 
		destrom.emuresetvector	= 
		destrom.emuirqvector	= 0;
		
		destrom.header_set =
		destrom.mode_set =
		destrom.makercode_set =
		destrom.gamecode_set =
		destrom.gamecode_set =
		destrom.expramsize_set =
		destrom.specialversion_set =
		destrom.carttype_set =
		destrom.name_set =
		destrom.mapmode_set =
		destrom.fastrom_set =
		destrom.romtype_set =
		destrom.size_set =
		destrom.sramsize_set =
		destrom.destcode_set =
		destrom.fixedvalue_set =
		destrom.versionnum_set =
		destrom.nativecopvector_set =
		destrom.nativebrkvector_set =
		destrom.nativeabortvector_set =
		destrom.nativenmivector_set =
		destrom.nativeresetvector_set =
		destrom.nativeirqvector_set =
		destrom.emucopvector_set =
		destrom.emubrkvector_set =
		destrom.emuabortvector_set =
		destrom.emunmivector_set =
		destrom.emuresetvector_set =
		destrom.emuirqvector_set = FALSE;
	}
}