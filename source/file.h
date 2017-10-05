#pragma once

#include "vector.h"
#include "log.h"
#include "statement.h"

#define FILE_LIMIT 0x200

#define ARGLENGTH	(arg->length)
#define SRCSTART	(fi.start)
#define SRCINDEX	(fi.index)
#define SRCLENGTH	(fi.length)
#define SRCLINE		(fi.linenum)
#define SRCBLOCK	(fi.blocknum)
#define SRCPSTART	(fi.data + SRCSTART)
#define SRCPCHAR	(fi.data + SRCINDEX)
#define SRCCHAR		(*SRCPCHAR)
#define SRCNEXTCHAR	(SRCPCHAR[1])

#define SETLENGTH()		(fi->length = fi->index - fi->start)
#define INITASMARG()	(strcat(arg, SRCPSTART, SRCLENGTH))
#define ARGCMP(key)		(!stricmp(arg, key))
#define ARGPCHAR		(arg->text)

struct file_item
{
	char name[MAX_PATH];
	char *data;
	int size;
	int start, length, index, linenum, blocknum;
	file_item *pfile;

	file_item() : data(NULL), pfile(NULL) { *name = 0; }
	~file_item();
};

extern char	asmpath[MAX_PATH];
extern char asmdir[MAX_PATH];
extern int	dirlen;

extern file_item fi, *pfi;

void initasmpath(const char *path, const char *dir);
void loadasmfile(const char *path);
void getrealpath(const char *path, char *realpath);
int getfilenumber(const char* path);
void returnfromfile();
void resetasemblyfiles();
void setstart();