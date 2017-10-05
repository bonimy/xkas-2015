#pragma once

#include "_base.h"

#define STRSTARTLEN 0x20

class string
{
public:
	char *text;
	int length, capacity;

	string();
	string(const int size);
	string(const char *str);
	string(const char *str, const int start, const int end);
	string(const string *str);
	~string();

	void strmalloc(const int size);
	void strrealloc(const int size);
};

void strset(string *str, const int pos = 0, const char c = 0);

int strcmp(const string *str, const char *key);
int strcmp(const string *str, const string *key);
int stricmp(const string *str, const char *key);
int stricmp(const string *str, const string *key);

void strcpy(string *str, const char *key, const int ksl);
void strcpy(string *str, const char *key);
void strcpy(string *str, const string *key, const int ksl);
void strcpy(string *str, const string *key);

void strcat(string *str, const char key);
void strcat(string *str, const char *key, const int ksl);
void strcat(string *str, const char *key);
void strcat(string *str, const string *key);

void strinsert(string *str, const char *key, const int ksl, const int index);
void strinsert(string *str, const char *key, const int index);
void strinsert(string *str, const string *key, const int index);

void strreplace(string *str, const char key, const char token);
void strreplace(string *str, const char *key, const char token, const int ksl);
void strreplace(string *str, const char *key, const char token);
void strreplace(string *str, const char key, const char *token, const int tsl);
void strreplace(string *str, const char key, const char *token);
void strreplace(string *str, const char *key, const char *token, const int ksl, const int tsl);
void strreplace(string *str, const char *key, const char *token);

inline int strpos(const string *str, const char key)
{
	return strpos(str->text, key);
}
inline int strpos(const string *str, const char *key)
{
	return strpos(str->text, key, str->length, strlen(key));
}
inline int strpos(const string *str, const string *key)
{
	return strpos(str->text, key->text, str->length, key->length);
}
inline int stripos(const string *str, const char key)
{
	return stripos(str->text, key);
}
inline int stripos(const string *str, const char *key)
{
	return stripos(str->text, key, str->length, strlen(key));
}
inline int stripos(const string *str, const string *key)
{
	return stripos(str->text, key->text, str->length, key->length);
}

inline int strrpos(const string *str, const char key)
{
	return strrpos(str->text, key, str->length);
}
inline int strrpos(const string *str, const char *key)
{
	return strrpos(str->text, key, str->length, strlen(key));
}
inline int strrpos(const string *str, const string *key)
{
	return strrpos(str->text, key->text, str->length, key->length);
}
inline int strirpos(const string *str, const char key)
{
	return strrpos(str->text, key, str->length);
}
inline int strirpos(const string *str, const char *key)
{
	return strirpos(str->text, key, str->length, strlen(key));
}
inline int strirpos(const string *str, const string *key)
{
	return strirpos(str->text, key->text, str->length, key->length);
}
	
inline int strcount(const string *str, const char key)
{
	return strcount(str->text, key);
}
inline int strcount(const string *str, const char *key, const int ksl)
{
	return strcount(str->text, key, str->length, ksl);
}
inline int strcount(const string *str, const char *key)
{
	return strcount(str->text, key);
}
inline int strcount(const string *str, const string *key)
{
	return strcount(str->text, key->text, str->length, key->length);
}
inline int stricount(const string *str, const char key)
{
	return stricount(str->text, key);
}
inline int stricount(const string *str, const char *key, const int ksl)
{
	return stricount(str->text, key, str->length, ksl);
}
inline int stricount(const string *str, const char *key)
{
	return stricount(str->text, key);
}
inline int stricount(const string *str, const string *key)
{
	return stricount(str->text, key->text, str->length, key->length);
}

inline int strbegin(const string *str, const char key)
{
	return strbegin(str->text, key);
}
inline int strbegin(const string *str, const char *key)
{
	return strbegin(str->text, key);
}
inline int strbegin(const string *str, const string *key)
{
	return strbegin(str->text, key->text);
}
inline int stribegin(const string *str, const char key)
{
	return stribegin(str->text, key);
}
inline int stribegin(const string *str, const char *key)
{
	return stribegin(str->text, key);
}
inline int stribegin(const string *str, const string *key)
{
	return stribegin(str->text, key->text);
}

inline int strend(const string *str, const char key)
{
	return strend(str->text, key, str->length);
}
inline int strend(const string *str, const char *key)
{
	return strend(str->text, key, str->length, strlen(key));
}
inline int strend(const string *str, const string *key)
{
	return strend(str->text, key->text, str->length, key->length);
}
inline int striend(const string *str, const char key)
{
	return striend(str->text, key, str->length);
}
inline int striend(const string *str, const char *key)
{
	return striend(str->text, key, str->length, strlen(key));
}
inline int striend(const string *str, const string *key)
{
	return striend(str->text, key->text, str->length, key->length);
}

inline void strtrim(string *str, const int start, const int end)
{
	str->length = strtrim(str->text, start, end);
}
inline void strltrim(string *str, const int start)
{
	str->length = strltrim(str->text, start);
}
inline void strrtrim(string *str, const int end)
{
	str->length = strrtrim(str->text, end, str->length);
}

inline void strtrim(string *str, const char key)
{
	str->length = strtrim(str->text, key);
}
inline void strtrim(string *str, const char *key)
{
	str->length = strtrim(str->text, key);
}
inline void strtrim(string *str, const string *key)
{
	str->length = strtrim(str->text, key->text, key->length);
}
inline void stritrim(string *str, const char key)
{
	str->length = stritrim(str->text, key);
}
inline void stritrim(string *str, const char *key)
{
	str->length = stritrim(str->text, key);
}
inline void stritrim(string *str, const string *key)
{
	str->length = stritrim(str->text, key->text, key->length);
}

inline void strltrim(string *str, const char key)
{
	str->length = strltrim(str->text, key, str->length);
}
inline void strltrim(string *str, const char *key)
{
	str->length = strltrim(str->text, key, str->length, strlen(key));
}
inline void strltrim(string *str, const string *key)
{
	str->length = strltrim(str->text, key->text, str->length, key->length);
}
inline void striltrim(string *str, const char key)
{
	str->length = striltrim(str->text, key, str->length);
}
inline void striltrim(string *str, const char *key)
{
	str->length = striltrim(str->text, key, str->length, strlen(key));
}
inline void striltrim(string *str, const string *key)
{
	str->length = striltrim(str->text, key->text, str->length, key->length);
}

inline void strrtrim(string *str, const char key)
{
	str->length = strrtrim(str->text, key, str->length);
}
inline void strrtrim(string *str, const char *key)
{
	str->length = strrtrim(str->text, key, str->length, strlen(key));
}
inline void strrtrim(string *str, const string *key)
{
	str->length = strrtrim(str->text, key->text, str->length, key->length);
}
inline void strirtrim(string *str, const char key)
{
	str->length = strirtrim(str->text, key, str->length);
}
inline void strirtrim(string *str, const char *key)
{
	str->length = strirtrim(str->text, key, str->length, strlen(key));
}
inline void strirtrim(string *str, const string *key)
{
	str->length = strirtrim(str->text, key->text, str->length, key->length);
}

inline int strbintonum(const string *str)
{
	return strbintonum(str->text);
}
inline int strocttonum(const string *str)
{
	return strocttonum(str->text);
}
inline int strdectonum(const string *str)
{
	return strdectonum(str->text);
}
inline int strhextonum(const string *str)
{
	return strhextonum(str->text);
}

inline int strissquote(const string *str)
{
	return *str->text == '\'' && str->text[str->length - 1] == '\'';
}
inline int strisdquote(const string *str)
{
	return *str->text == '\"' && str->text[str->length - 1] == '\"';
}
inline int strisquote(const string *str)
{
	return (*str->text == '\'' || *str->text == '\"') && str->text[str->length - 1] == *str->text;
}
inline int strisrep(const string *str, const char c)
{
	return strisrep(str->text, c);
}