#pragma once

#include "statement.h"

#define UPPERCHAR	'A':	case 'B':	case 'C':	case 'D':	case 'E':	case 'F':	case 'G':\
case 'H':	case 'I':	case 'J':	case 'K':	case 'L':	case 'M':	case 'N':	case 'O':\
case 'P':	case 'Q':	case 'R':	case 'S':	case 'T':	case 'U':	case 'V':	case 'W':\
case 'X':	case 'Y':	case 'Z'

#define LOWERCHAR	'a':	case 'b':	case 'c':	case 'd':	case 'e':	case 'f':	case 'g':\
case 'h':	case 'i':	case 'j':	case 'k':	case 'l':	case 'm':	case 'n':	case 'o':\
case 'p':	case 'q':	case 'r':	case 's':	case 't':	case 'u':	case 'v':	case 'w':\
case 'x':	case 'y':	case 'z'

#define NUMCHAR		'0':	case '1':	case '2':	case '3':	case '4':\
case '5':	case '6':	case '7':	case '8':	case '9'

#define ALPHACHAR	UPPERCHAR:	case LOWERCHAR
#define ALPHANUMCHAR	ALPHACHAR:	case NUMCHAR
#define HEXALPHAUPRCHAR	'A':	case 'B':	case 'C':	case 'D':	case 'E':	case 'F'
#define HEXALPHALWRCHAR	'a':	case 'b':	case 'c':	case 'd':	case 'e':	case 'f'
#define HEXALPHACHAR	HEXALPHAUPRCHAR:	case HEXALPHALWRCHAR
#define HEXCHAR			NUMCHAR:	case HEXALPHACHAR
#define BINARYCHAR		'0':	case '1'

#define WHITECHAR	'\t':	case '\x0B':	case '\x0C':	case ' '
#define NEWLINECHAR	'\r':	case '\n'
#define WINLINESTR	(!strbegin(SRCPCHAR, "\r\n"))
#define LINEJOINCHAR		','
#define LINECOMMENTCHAR		';'
#define BLOCKCOMMENTBEGIN	(!strcmp(SRCPCHAR, "/*"))
#define BLOCKCOMMENTEND		(!strcmp(SRCPCHAR, "*/"))
#define SEPARATORCHAR		':'
#define QUOTECHAR			'\'':	case '\"'

#define DEFINECHAR			'!'
#define DEFINESETCHAR		'='
#define DEFFIRSTCHAR	ALPHACHAR:	case '_':
#define DEFANYCHAR		DEFFIRSTCHAR:	case NUMCHAR

#ifdef UNICODE
#define WHITEWCHAR	 L'\t':		case L'\U000B':	case L'\U000C':	case L' ':		case L'\U00A0':\
case L'\U1680':	case L'\U2000':	case L'\U2001':	case L'\U2002':	case L'\U2003':\
case L'\U2004':	case L'\U2005':	case L'\U2006':	case L'\U2007':	case L'\U2008':\
case L'\U2009':	case L'\U200A':	case L'\U202F':	case L'\U205F': case L'\U3000':

#define NEWLINEWCHAR	L'\r':	case L'\n': case L'\U2028': case L'\U2029'
#endif

#define BEGINSTATEMENT beginstatement

#define PROCESSWHITE() {\
	if (ASMODE != AM_NEWLINE)\
		ASMODE = AM_NEWARG;\
	SRCINDEX++;\
	READMODE = RM_END;}

#define PROCESSNEWLINE() {\
	ASMODE = join ? AM_NEWARG : AM_NEWLINE;\
	if (WINLINESTR)\
		SRCINDEX++;\
	SRCINDEX++;\
	SRCBLOCK = 0;\
	SRCLINE++;\
	READMODE = RM_END;\
	join = FALSE;}

#define PROCESSNEWBLOCK() {\
	ASMODE = AM_NEWLINE;\
	SRCBLOCK++;}

extern BOOL instring;

void processwhite();
BOOL gettext(string *dest);
BOOL getqtext(string *dest);
void preprocessline();
void processincasm();

extern void assemblefile();