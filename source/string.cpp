#include "string.h"

string::string()
{
	this->text = (char*)malloc(STRSTARTLEN + 1);
	this->capacity = STRSTARTLEN;
	*this->text = 0;
	this->length = 0;
}
string::string(const int size)
{
	this->capacity = mallocresize(size);
	this->text = (char*)malloc(this->capacity + 1);
	*this->text = 0;
	this->length = 0;
}
string::string(const char *str)
{
	this->length = strlen(str);
	this->capacity = mallocresize(this->length);
	this->text = (char*)malloc(this->capacity + 1);
	strcpy(this->text, str);
}
string::string(const char *str, const int start, const int end)
{
	this->length = end - start;
	this->capacity = mallocresize(this->length);
	this->text = (char*)malloc(this->capacity + 1);
	memcpy(this->text, str + start, this->length);
	this->text[this->length] = 0;
}
string::string(const string *str)
{
	this->length = str->length;
	this->capacity = mallocresize(this->length);
	this->text = (char*)malloc(this->capacity + 1);
	strcpy(this->text, str->text);
}
string::~string()
{
	free(this->text);
}

/* allocate the memory size of this->text */
void string::strmalloc(const int size)
{
	this->capacity = mallocresize(size);
	free(this->text);
	this->text = (char*)malloc(this->capacity + 1);
}
void string::strrealloc(const int size)
{
	this->capacity = mallocresize(size);
	this->text = (char*)realloc(this->text, this->capacity + 1);
}
	
/* sets str->text[pos] to c */
void strset(string *str, const int pos, const char c)
{
	if (pos > str->capacity)
		str->strrealloc(pos);
	str->text[pos] = c;
	if (!c && str->length > pos)
		str->length = pos;
	else if (c && pos >= str->length)
		str->text[str->length = (pos + 1)] = 0;
}

/* returns 0 if str and key have the same text */
int strcmp(const string *str, const char *key)
{
	return strcmp(str->text, key);
}
int strcmp(const string *str, const string *key)
{
	return strcmp(str->text, key->text);
}
int stricmp(const string *str, const char *key)
{
	return _stricmp(str->text, key);
}
int stricmp(const string *str, const string *key)
{
	return _stricmp(str->text, key->text);
}

/* copies key to str */
void strcpy(string *str, const char *key, const int ksl)
{
	if (ksl > str->capacity)
		str->strmalloc(ksl);
	memcpy(str->text, key, ksl);
	str->text[ksl] = 0;
	str->length = ksl;
}
void strcpy(string *str, const char *key)
{
	strcpy(str, key, strlen(key));
}
void strcpy(string *str, const string *key, const int ksl)
{
	strcpy(str, key->text, ksl);
}
void strcpy(string *str, const string *key)
{
	strcpy(str, key->text, key->length);
}

/* concatenates key to the end of str */
void strcat(string *str, const char key)
{
	str->text[str->length++] = key;
	if (str->length >= str->capacity)
		str->strrealloc(str->length);
	str->text[str->length] = 0;
}
void strcat(string *str, const char *key, const int ksl)
{
	const int length = str->length + ksl;
	if (length > str->capacity)
		str->strrealloc(length);
	memcpy(str->text + str->length, key, ksl);
	str->text[length] = 0;
	str->length = length;
}
void strcat(string *str, const char *key)
{
	strcat(str, key, strlen(key));
}
void strcat(string *str, const string *key)
{
	strcat(str, key->text, key->length);
}

/* inserts key intro str at index */
void strinsert(string *str, const char *key, const int ksl, const int index)
{
	const int len = str->length + ksl;
	if (len > str->capacity)
		str->strrealloc(len);
	memcpy(str->text + index + ksl, str->text + index, str->length - index);
	memcpy(str->text + index, key, ksl);
	str->text[len] = 0;
	str->length = len;
}
void strinsert(string *str, const char *key, const int index)
{
	strinsert(str, key, strlen(key), index);
}
void strinsert(string *str, const string *key, const int index)
{
	strinsert(str, key->text, key->length, index);
}

/* replaces all occurances of key in str with token */
void strreplace(string *str, const char key, const char token)
{
	strreplace(str->text, key, token);
}
void strreplace(string *str, const char *key, const char token, const int ksl)
{
	int i = 0, n = 0;
	char *c = str->text;
	while (c[n])
	{
		if (!strbegin(c + n, key))
		{
			c[i++] = token;
			n += ksl;
		}
		else
			c[i++] = c[n++];
	}
	c[str->length = i] = 0;
}
void strreplace(string *str, const char *key, const char token)
{
	strreplace(str, key, token, strlen(key));
}
void strreplace(string *str, const char key, const char *token, const int tsl)
{
	int i = str->length, n = 0;
	char *c = str->text;
	while (i--)
		if (c[i] == key)
			n++;
	if (!n)
		return;
	i = str->length;
	n = i + (n * (tsl - 1));
	str->length = n;
	if (n >= str->capacity)
		str->capacity = mallocresize(n + 1);
	while (i--)
	{
		if (c[i] == key)
		{
			n -= tsl;
			memcpy(c + n, token, tsl);
		}
		else
			c[--n] = c[i];
	}
	c[str->length] = 0;
}
void strreplace(string *str, const char key, const char *token)
{
	strreplace(str, key, token, strlen(token));
}
void strreplace(string *str, const char *key, const char *token, const int ksl, const int tsl)
{
	if (ksl >= tsl)
	{
		int i = 0, n = 0;
		char *c = str->text;
		while (c[n])
		{
			if (!strbegin(c + n, key))
			{
				memcpy(c + i, token, tsl);
				i += tsl;
				n += ksl;
			}
			else
				c[i++] = c[n++];
		}
		c[str->length = i] = 0;
	}
	else
	{
		const int dif = ksl - 1;
		int i = str->length;
		int *y = (int*)malloc(i * sizeof(int));
		int *t = y;
		char *c = str->text;
		while (i--)
		{
			if (!strbegin(c + i, key))
			{
				*(y++) = i + dif;
				i -= dif;
			}
		}
		if (t != y)
		{
			i = str->length;
			int n = i + ((y - t) * (tsl - ksl));
			str->length = n;
			if (n >= str->capacity)
				str->capacity = mallocresize(n + 1);
			y = t;
			while (i--)
			{
				if (i == *y)
				{
					y++;
					i -= dif;
					n -= tsl;
					memcpy(c + n, token, tsl);
				}
				else
					c[--n] = c[i];
			}
		}
		c[str->length] = 0;
		free(t);
	}
}
void strreplace(string *str, const char *key, const char *token)
{
	strreplace(str, key, token, strlen(key), strlen(token));
}