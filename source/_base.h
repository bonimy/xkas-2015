/* Common values, macros, and functions used throughout assembler. */

#pragma once

#ifndef __BASE_H__
#define __BASE_H__

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef	WIN32
#include <windows.h>

#ifdef _DEBUG
#define ASSUME(val)	assert(val)
#else
#define ASSUME(val) __assume(val)
#endif

/* Lunar Compress is only supported on windows machines.
	Eventually, we'll need to rewrite the library as open
	source to be portable. */
#define LUNAR_DLL

#else
#define ASSUME(val)	assert(val)

/* Linux machines use a different case-invariant string compare function name.
	We define the common name here to allow portability. */
#ifdef	linux
#define _stricmp strcasecmp
#endif

/* define win32 types used */
typedef unsigned char	byte;
typedef unsigned long   DWORD;
typedef int             BOOL;
typedef unsigned char   BYTE;
typedef unsigned short	WORD;

#ifndef	MAX_PATH
#ifdef	FILENAME_MAX
#define	MAX_PATH		FILENAME_MAX
#else
#define MAX_PATH		260
#endif
#endif

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif
#endif


#ifdef LUNAR_DLL
#include "../Lunar Compress/DLLCode/LunarDLL.h"
#endif

/* common values and macros */
#define NOTFOUND		-1
#define M_GETMAX(a,b)	((a)>(b)?(a):(b))
#define M_GETMIN(a,b)	((a)<(b)?(a):(b))

/* Define these macros as a measure for possible future unicode support */
#define UPPER(x)		upper[x]
#define LOWER(x)		lower[x]

/* array listing to create upper and lower case ASCII arrays */
#define next4(n)	n,			n+1,			n+2,			n+3
#define next16(n)	next4(n),	next4(n+4),		next4(n+8),		next4(n+12)
#define next64(n)	next16(n),	next16(n+16),	next16(n+32),	next16(n+48)
#define upr next16('A'), next4('Q'), next4('U'), 'Y', 'Z'
#define lwr next16('a'), next4('q'), next4('u'), 'y', 'z'

/* upper- and lower- case ASCII arrays */
static const char upper[] = { next64(0), 0x40, upr, 0x5B, next4(0x5C), 0x60, upr, 0x7B, next4(0x7C) };
static const char lower[] = { next64(0), 0x40, lwr, 0x5B, next4(0x5C), 0x60, lwr, 0x7B, next4(0x7C) };

#define __R2(n)	 n,     n + 2*(1<<5),     n + 1*(1<<5),     n + 3*(1<<5)
#define __R4(n) __R2(n), __R2(n + 2*(1<<4)), __R2(n + 1*(1<<4)), __R2(n + 3*(1<<4))
#define __R6(n) __R4(n), __R4(n + 2*(1<<2)), __R4(n + 1*(1<<2)), __R4(n + 3*(1<<2))
static const BYTE BitReverseTable256[] = { __R6(0), __R6(2), __R6(1), __R6(3) };

/* common code search procedure for string functions that ignore quoted text */
#define M_CHECKQUOTE1(statement) M_CHECKQUOTE4(i, str[i], i++, statement)
#define M_CHECKQUOTE2(increment, statement) M_CHECKQUOTE4(i, str[i], increment, statement);
#define M_CHECKQUOTE3(text, increment, statement) M_CHECKQUOTE4(i, text, increment, statement);
#define M_CHECKQUOTE4(index, text, increment, statement) \
	if (x == '\'' || x == '\"')\
	{\
		const int z = increment;\
		while (text ^ x && (statement))\
			increment;\
		if (!(statement))\
			index = z;\
	}

/* resize a value to the ceiling of its neartest base-2 value
	(e.g. val = 6 returns 8 and val = 45 returns 64 */
inline int mallocresize(const int val)
{
	int i = val - 1;
	i |= i >> (1 << 0);
	i |= i >> (1 << 1);
	i |= i >> (1 << 2);
	i |= i >> (1 << 3);
	i |= i >> (1 << 4);
#ifdef x64
	i |= i >> (1 << 5);
#endif
	return ++i;
}

inline void strlencpy(char *dest, const char *src, const int len = MAX_PATH)
{
	if ((int)strlen(src) < len)
		strcpy(dest, src);
	else
		memcpy(dest, src, len);
}

int strbegin(const char *str, const char key);
int strbegin(const char *str, const char *key);
int stribegin(const char *str, const char key);
int stribegin(const char *str, const char *key);

int strpos(const char *str, const char key);
int strpos(const char *str, const char *key, const int ssl, const int ksl);
int strpos(const char *str, const char *key);
int stripos(const char *str, const char key);
int stripos(const char *str, const char *key, const int ssl, const int ksl);
int stripos(const char *str, const char *key);

int strrpos(const char *str, const char key, const int ssl);
int strrpos(const char *str, const char key);
int strrpos(const char *str, const char *key, const int ssl, const int ksl);
int strrpos(const char *str, const char *key);
int strirpos(const char *str, const char key, const int ssl);
int strirpos(const char *str, const char key);
int strirpos(const char *str, const char *key, const int ssl, const int ksl);
int strirpos(const char *str, const char *key);

int strcount(const char *str, const char key);
int strcount(const char *str, const char *key, const int ssl, const int ksl);
int strcount(const char *str, const char *key);
int stricount(const char *str, const char key);
int stricount(const char *str, const char *key, const int ssl, const int ksl);
int stricount(const char *str, const char *key);

int strend(const char *str, const char key, const int ssl);
int strend(const char *str, const char key);
int strend(const char *str, const char *key, const int ssl, const int ksl);
int strend(const char *str, const char *key);
int striend(const char *str, const char key, const int ssl);
int striend(const char *str, const char key);
int striend(const char *str, const char *key, const int ssl, const int ksl);
int striend(const char *str, const char *key);

int strtrim(char *str, const int start, const int end);
int strltrim(char *str, const int start);
int strrtrim(char *str, const int end, const int ssl);
int strrtrim(char *str, const int end);

int strtrim(char *str, const char key);
int strtrim(char *str, const char *key, const int ksl);
int strtrim(char *str, const char *key);
int stritrim(char *str, const char key);
int stritrim(char *str, const char *key, const int ksl);
int stritrim(char *str, const char *key);

int strltrim(char *str, const char key, const int ssl);
int strltrim(char *str, const char key);
int strltrim(char *str, const char *key, const int ssl, const int ksl);
int strltrim(char *str, const char *key);
int striltrim(char *str, const char key, const int ssl);
int striltrim(char *str, const char key);
int striltrim(char *str, const char *key, const int ssl, const int ksl);
int striltrim(char *str, const char *key);

int strrtrim(char *str, const char key, const int ssl);
int strrtrim(char *str, const char key);
int strrtrim(char *str, const char *key, const int ssl, const int ksl);
int strrtrim(char *str, const char *key);
int strirtrim(char *str, const char key, const int ssl);
int strirtrim(char *str, const char key);
int strirtrim(char *str, const char *key, const int ssl, const int ksl);
int strirtrim(char *str, const char *key);

void strreplace(char *str, const char key, const char token);

int strbintonum(const char *str);
int strocttonum(const char *str);
int strdectonum(const char *str);
int strhextonum(const char *str);

int strisalpha(const char c);
int strislwr(const char c);
int strisupr(const char c);
int strisnum(const char c);
int strisbin(const char c);
int strisoct(const char c);
int strishex(const char c);
int strisdeftxt(const char c);
int strislbltxt(const char c);
int striswhite(const char c);

int strissquote(const char *str);
int strisdquote(const char *str);
int strisquote(const char *str);
int strisrep(const char *str, const char c);
	
int strisfullpath(const char *str, const int ssl);
int strisfullpath(const char *str);

#endif