#pragma once

#include "ops.h"

#define HASH_A		113
#define HASH_B		191
#define HASH_C		223
#define HASH_MOD	323

typedef BOOL (*hashtable)();

inline int gethash(const char* text)
{
	if (!text[0])
		return -1;
	if (!text[1])
		return -2;
	if (!text[2])
		return -3;
	return ((HASH_A * LOWER(text[0])) + (HASH_B * LOWER(text[1])) + (HASH_C * LOWER(text[2]))) % HASH_MOD;
}

opfxn badhash;

extern const hashtable hashfunctions[];