#pragma once

#include "file.h"

#define MODE_ARG		0
#define MODE_SRC		1

#define AM_NEWLINE		0
#define AM_NEWBLOCK		1
#define AM_NEWARG		2

#define RM_BEGIN	0
#define RM_READ		1
#define RM_END		2

#define ARG_INCSRC		0
#define ARG_INCBIN		1
#define ARG_DEFINE		2
#define ARG_NEWDEFINE	3
#define ARG_MACRO		4

extern int asmode;
extern int lastasmode;
extern int argmode;
extern int readmode;
extern int allowblock;
extern string *arg;

#define ASMODE		asmode
#define LASTASMODE	lastasmode
#define ARGMODE		argmode
#define READMODE	readmode
#define ALLOWBLOCK	allowblock

class statement_item
{
public:
	int command;
	int size;
	byte* data;
};

class codeblock : public list<statement_item>
{
public:
	int pc;
	int size;
};