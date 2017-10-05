#pragma once

#include "vector.h"
#include "string.h"
#include "log.h"

/* command line (CL) argument strings */
#define CL_PRINTMESSAGES	"/pm"		/* print messages to stream */
#define CL_PRINTWARNINGS	"/pw"		/* print warnings to stream */
#define CL_PRINTERRORS		"/pe"		/* print errors to stream */
#define CL_MESSAGEFORMAT	"/mf:"		/* custom message format */
#define CL_WARNINGFORMAT	"/mw:"		/* custom warning format */
#define CL_ERRORFORMAT		"/me:"		/* custom error format */
#define CL_WARNINGASERROR	"/we:"		/* treat certain warnings as errors */
#define CL_DIRECTORY		"/dir:"		/* specify primary directory */
#define CL_MAINASMPATH		"/main:"	/* specify main asm path */
#define CL_SRCROMPATH		"/src:"		/* specify source rom path */
#define CL_DESTROMPATH		"/dest:"	/* specify destination rom path */
#define CL_LUNARCOMPRESS	"/lc"		/* use Lunar Compress.dll */
#define CL_DISABLEWARNINGS	"/dw:"		/* disable specific warnings */
#define CL_INCLUDEWARNINGS	"/iw:"		/* enable specific warnings */
#define	CL_EXEPATH			"/exe:"		/* patch using an external program */
#define CL_PRINTTEXT		"/print:"	/* print message(s) to stream */
#define CL_STRESCAPE		"/stcesc:"	/* use string escape sequences in code strings */
#define	CL_PRINTSTDERR		"/stderr"	/* print errors to standard error stream */
#define CL_PRINTSTDOUT		"/stdout"	/* print errors to standard output stream */

struct clargs
{
	BOOL printmessages, printwarnings, printerrors;
	string *messageformat, *warningformat, *errorformat;
	vector<int> errorwarnings, disablewarnings, includewarnings;

	char asmdir[MAX_PATH], asmpath[MAX_PATH];
	char srcpath[MAX_PATH], destpath[MAX_PATH];

	char exepath[MAX_PATH];

	BOOL strescape;
	BOOL printstderr,  printstdout;
};

extern clargs defargs;

void initdefargs();
int setdefargs(int argc, char **argv);
BOOL getcommandbool(const char* arg, const char* key, BOOL &command);
BOOL getcommandtext(const char* arg, const char* key, string* command);
BOOL getcommandpath(const char* arg, const char* key, char	command[MAX_PATH]);