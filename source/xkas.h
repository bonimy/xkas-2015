#pragma once

#include "compress.h"
#include "vector.h"
#include "strlist.h"
#include "file.h"
#include "preprocessor.h"
#include "hash.h"
#include "define.h"
#include "rom.h"
#include "strmath.h"
#include "log.h"
#include "clargs.h"

#define SEP_BOF		0
#define SEP_WHITE	1
#define SEP_NEWLINE	2
#define SEP_BLOCK	3

#define MODE_READ			0
#define MODE_WHITE			1
#define MODE_NEWLINE		2
#define	MODE_LINECOMMENT	3
#define MODE_BLOCKCOMMENT	4
#define MODE_NEWBLOCK		5

void initialize();
void reset();
void assemble();
void assemblefile();
void initstatement();