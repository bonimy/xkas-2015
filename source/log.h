#pragma once

#include "strlist.h"

#define LOG_MESSAGE		0	// messages output by the compiler or the assembly file
#define LOG_ERROR		1	// compile time errors (compilation will not be applied)
#define LOG_WARNING		2	// compile time warnings (does not hinder compilation)
#define LOG_FATALERROR	3	// fatal error (compilation will terminate immediately)

#define LOG_MESSAGEKEY	"$(message)"
#define LOG_FILEKEY		"$(filenum)"
#define LOG_LINEKEY		"$(linenum)"
#define LOG_CODEKEY		"$(codenum)"
#define LOG_COMMANDKEY	"$(command)"

#define LOG_FILEPREFIX	"<file>"
#define LOG_FILESUFFIX	"</file>"
#define LOG_CODEPREFIX	"<code>"
#define LOG_CODESUFFIX	"</code>"
#define LOG_CMDPREFIX	"<command>"
#define LOG_CMDSUFFIX	"</command>"

extern strlist	*errors, *warnings, *messages;
extern string	*messageformat, *errorformat, *warningformat;

extern BOOL	printerrors,
			printwarnings,
			printmessages;

void log(const int dest, const BOOL show, const BOOL infile, const int code, const char *text, ...);
void resetlogdata();