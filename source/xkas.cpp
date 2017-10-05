#include "xkas.h"

void reset()
{
	resetlogdata();
	resetasemblyfiles();
	
	ASMODE = AM_NEWLINE;
	READMODE = RM_BEGIN;
	ALLOWBLOCK = TRUE;
}

void initialize()
{
	initsrcrom(defargs.srcpath);
	initdestrom(defargs.destpath);
	initasmpath(defargs.asmpath, defargs.asmdir);
}

void assemble()
{
	reset();
	assemblefile();
}

void assemblefile()
{
	instring = FALSE;
	while (SRCCHAR)
	{
		processwhite();
skipwhite:
		switch (READMODE)
		{
		case RM_BEGIN:
			setstart();
			READMODE = RM_READ;
		case RM_READ:
			SRCINDEX++;
			SRCLENGTH++;
			break;
		case RM_END:
			INITASMARG();
			if (ARGLENGTH)
			{
				switch (LASTASMODE)
				{
				case AM_NEWLINE:
					if (SRCCHAR == '#')
					{
						SRCINDEX++;
						break;
					}
				case AM_NEWBLOCK:
					initstatement();
					break;
				case AM_NEWARG:
					processincasm();
					break;
				}
			}
			READMODE = RM_BEGIN;
			goto skipwhite;
		}
	}
	
	if (indefine)
		exitdefine();
	else
		returnfromfile();
}

#define SETROMDATA(key, dest, value, code, name) \
	(ARGCMP(key))\
	{\
		if (SETBYPROGRAM(destrom. ## dest ## _set))\
			return log(LOG_ERROR, TRUE, TRUE, code, name " already set");\
		destrom. ## dest = value;\
		destrom. ## dest ## _set = PROGRAMSET;\
	}

void initstatement()
{
	if (*ARGPCHAR == '!' && !lastdefine)
	{
		di = getdefine(arg);
		ARGMODE = ARG_DEFINE;
	}
	else if (ARGMODE == ARG_DEFINE)
	{
		if (ARGCMP("="))
		{
			ARGMODE = ARG_NEWDEFINE;
		}
		else
		{
			enterdefine();
			lastdefine = FALSE;
		}
	}
	else if (ARGMODE == ARG_NEWDEFINE)
	{
		strcpy(di->value, arg);
	}
	else if SETROMDATA("noheader", header, 0, 6000, "header")
	else if SETROMDATA("header", header, HEADERSIZE, 6000, "header")
	else if SETROMDATA("lorom", mode, LOROM, 6000, "mode")
	else if SETROMDATA("hirom", mode, HIROM, 6000, "mode")
	else if SETROMDATA("exlorom", mode, EXLOROM, 6000, "mode")
	else if SETROMDATA("exhirom", mode, EXHIROM, 6000, "mode")
	else if SETROMDATA("slowrom", fastrom, FALSE, 6000, "fastrom")
	else if SETROMDATA("fastrom", fastrom, TRUE, 6000, "fastrom")
	else if (ARGCMP("incsrc"))
	{
		ASMODE = AM_NEWARG;
		ARGMODE = ARG_INCSRC;
	}
	else if (ARGCMP("incbin"))
	{
		ASMODE = AM_NEWARG;
		ARGMODE = ARG_INCBIN;
	}
	else if (ARGCMP("macro"))
	{
		ASMODE = AM_NEWARG;
		ARGMODE = ARG_MACRO;
	}
	else if (ARGCMP("endmacro"))
	{

	}
	else
	{
		int hash = gethash(arg->text);
		if (hash >= 0)
			hashfunctions[hash]();
	}
}