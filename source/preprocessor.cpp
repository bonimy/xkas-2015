#include "preprocessor.h"

/* If the assembler is processing a string literal, this value will
be the character literal of the quote used (single or double quote
character). Otherwise, it is FALSE.*/
BOOL instring;

/* Updates the assembler position so that whitespace is
	properly ignored. If this function is called when
	the assembler is at a whitespace character, then its
	position will be to the next non-whitespace character
	and all line, block, and etc. info will be updated
	to reflect the change. */
void processwhite()
{
	LASTASMODE = ASMODE;	// Remember the last assembly mode.
	BOOL join = FALSE;
loop:
	if (instring)	// Determine if the assembler is currently in a literal string.
	{
		while (SRCCHAR)	// Go through string
		{
			switch (SRCCHAR)
			{
			case 0:
			case NEWLINECHAR:		// Log error if end of file/line is reached without terminating quote.
				PROCESSNEWLINE();	
				ALLOWBLOCK = TRUE;
				log(LOG_ERROR, TRUE, TRUE, 0, "string has no terminating quote");
				instring = FALSE;
				return;
			case QUOTECHAR:
				if (SRCCHAR == instring)	// Terminate string literal once matching quote character is found.
					instring = FALSE;
			default:
				return;						// Do not process white-space in string literals.
			}
		}
	}

	while (SRCCHAR)
	{
		switch (SRCCHAR)
		{
		case QUOTECHAR:			
			instring = SRCCHAR;
			return;
		case WHITECHAR:			
			PROCESSWHITE();
			ALLOWBLOCK = TRUE;
			break;
		case NEWLINECHAR:		
			PROCESSNEWLINE();
			ALLOWBLOCK = TRUE;
			break;
		case LINEJOINCHAR:
			SRCINDEX++;
			READMODE = RM_END;
			join = TRUE;
			break;
		case LINECOMMENTCHAR:
			SRCINDEX++;
			while (SRCCHAR)
			{
				switch(SRCCHAR)
				{
				case NEWLINECHAR:
					PROCESSNEWLINE();
					ALLOWBLOCK = TRUE;
					goto loop;
				default:
					SRCINDEX++;
					break;
				}
			}
			break;
		case SEPARATORCHAR:
			if (!ALLOWBLOCK || SRCNEXTCHAR == SRCCHAR)
				return;
			SRCINDEX++;
			switch (SRCCHAR)
			{
			case WHITECHAR:
			case NEWLINECHAR:
			case LINECOMMENTCHAR:
				PROCESSNEWBLOCK();
				break;
			default:
				if (BLOCKCOMMENTBEGIN)
				{
					PROCESSNEWBLOCK();
					break;
				}
				ALLOWBLOCK = FALSE;
				return log(LOG_ERROR, TRUE, TRUE, 0, "block separator must have white space after it (scope resolution operator typo?)");
			}
			break;
		default:
			if (BLOCKCOMMENTBEGIN)
			{
				SRCINDEX += 2;
				ASMODE = AM_NEWARG;
				READMODE = RM_END;
				while (SRCCHAR)
				{
					switch(SRCCHAR)
					{
					case NEWLINECHAR:
						PROCESSNEWLINE();
						break;
					default:
						if (BLOCKCOMMENTEND)
						{
							SRCINDEX += 2;
							ALLOWBLOCK = TRUE;
							goto loop;
						}
						SRCINDEX++;
						break;
					}
				}
				log(LOG_ERROR, TRUE, TRUE, 0, "block comment has no end tag");
				return;
			}
			return;
		}
	}
	READMODE = RM_END;
}

BOOL processtext(string *dest)
{
	switch (SRCCHAR)
	{
	case QUOTECHAR:
		return getqtext(dest);
	default:
		return gettext(dest);
	}
}

/* gets text until whitespace appears */
BOOL gettext(string *dest)
{
	setstart();
	while (SRCCHAR)
	{
		processwhite();
		//if (LASTCHAR != 'A')
		{
			strcpy(dest, SRCPSTART, SRCLENGTH);
			return TRUE;
		}
		//else
		{
			SRCINDEX++;
			SRCLENGTH++;
		}
	}
	return FALSE;
}

/* gets text surrounded by quotes */
BOOL getqtext(string *dest)
{
	char x = SRCCHAR;
	fi.index++;
	setstart();
	while (SRCCHAR)
	{
		switch (SRCCHAR)
		{
		case NEWLINECHAR:
			//processnewline();
			log(LOG_ERROR, TRUE, TRUE, 0, "string not terminated");
			return FALSE;
		default:
			if (SRCCHAR == x)
			{
				if (dest)
					strcpy(dest, SRCPSTART, SRCLENGTH);
				return TRUE;
			}
			SRCINDEX++;
			break;
		}
	}
	log(LOG_ERROR, TRUE, TRUE, 0, "could not get string");
	return FALSE;
}

void preprocessline()
{
	if (ARGCMP("define"))
	{

	}
}

/* includes an asm file */
void processincasm()
{
	loadasmfile(ARGPCHAR);
	assemblefile();
}