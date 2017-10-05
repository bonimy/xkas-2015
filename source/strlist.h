#pragma once

#include "list.h"
#include "string.h"

class strlist : public list<string>
{
};
	
void split(strlist *dest, const char key, const char *src);
void split(strlist *dest, const char *key, const char *src, const int ssl);
void split(strlist *dest, const char *key, const char *src);
void split(strlist *dest, const char key, const string *src);
void split(strlist *dest, const char *key, const string *src);
void split(strlist *dest, const char key, strlist *src, const int src_num = 0);
void split(strlist *dest, const char *key, strlist *src, const int src_num = 0);
void split(strlist *dest, const char key, const int src_num = 0);
void split(strlist *dest, const char *key, const int src_num = 0);
void split_eq(strlist *dest, const char key, const char *src);
void split_eq(strlist *dest, const char *key, const char *src, const int ssl);
void split_eq(strlist *dest, const char *key, const char *src);
void split_eq(strlist *dest, const char key, const string *src);
void split_eq(strlist *dest, const char *key, const string *src);
void split_eq(strlist *dest, const char key, strlist *src, const int src_num = 0);
void split_eq(strlist *dest, const char *key, strlist *src, const int src_num = 0);
void split_eq(strlist *dest, const char key, const int src_num = 0);
void split_eq(strlist *dest, const char *key, const int src_num = 0);