#include "strlist.h"

/* splits a string into a list using a given key */
void split(strlist *dest, const char key, const char *src)
{
	int i = 0, n = 0, z = 0;
	for (; src[i]; ++i)
	{
		if (src[i] == key)
		{
			strcpy(dest->get(n++), src + z, i - z);
			z = i + 1;
		}
	}
	strcpy(dest->get(n++), src + z, i - z);
	dest->count = n;
}
void split(strlist *dest, const char *key, const char *src, const int ssl)
{
	const int ksl = strlen(key);
	const int dif = ssl - ksl;
	int i = 0, n = 0, z = 0;
	for (; i <= dif; ++i)
	{
		if (!strbegin(src + i, key))
		{
			strcpy(dest->get(n++), src + z, i - z);
			i += ksl - 1;
			z = i + 1;
		}
	}
	strcpy(dest->get(n++), src + z, ssl - z);
	dest->count = n;
}
void split(strlist *dest, const char *key, const char *src)
{
	split(dest, key, src, strlen(src));
}
void split(strlist *dest, const char key, const string *src)
{
	split(dest, key, src->text);
}
void split(strlist *dest, const char *key, const string *src)
{
	split(dest, key, src->text, src->length);
}
void split(strlist *dest, const char key, strlist *src, const int src_num)
{
	split(dest, key, src->get(src_num));
}
void split(strlist *dest, const char *key, strlist *src, const int src_num)
{
	split(dest, key, src->get(src_num));
}
void split(strlist *dest, const char key, const int src_num)
{
	string *s = dest->get(src_num);
	char *src = (char*)malloc(s->length + 1);
	memcpy(src, s->text, s->length + 1);
	split(dest, key, src);
	free(src);
}
void split(strlist *dest, const char *key, const int src_num)
{
	string *s = dest->get(src_num);
	char *src = (char*)malloc(s->length + 1);
	memcpy(src, s->text, s->length + 1);
	split(dest, key, src, s->length);
	free(src);
}
void split_eq(strlist *dest, const char key, const char *src)
{
	int i = 0, n = 0, z = 0;
	for (; src[i]; ++i)
	{
		const char x = src[i];
		if (x == '\'' || x == '\"')
		{
			const int y = i++;
			while(src[i] ^ x && src[i])
				i++;
			if (i < 0)
				i = y;
		}
		if (src[i] == key)
		{
			strcpy(dest->get(n++), src + z, i - z);
			z = i + 1;
		}
	}
	strcpy(dest->get(n++), src + z, i - z);
	dest->count = n;
}
void split_eq(strlist *dest, const char *key, const char *src, const int ssl)
{
	const int ksl = strlen(key);
	const int dif = ssl - ksl;
	int i = 0, n = 0, z = 0;
	for (; i <= dif; ++i)
	{
		const char x = src[i];
		if (x == '\'' || x == '\"')
		{
			const int y = i++;
			while(src[i] ^ x && src[i])
				i++;
			if (i < 0)
				i = y;
		}
		if (!strbegin(src + i, key))
		{
			strcpy(dest->get(n++), src + z, i - z);
			i += ksl - 1;
			z = i + 1;
		}
	}
	strcpy(dest->get(n++), src + z, ssl - z);
	dest->count = n;
}
void split_eq(strlist *dest, const char *key, const char *src)
{
	split_eq(dest, key, src, strlen(src));
}
void split_eq(strlist *dest, const char key, const string *src)
{
	split_eq(dest, key, src->text);
}
void split_eq(strlist *dest, const char *key, const string *src)
{
	split_eq(dest, key, src->text, src->length);
}
void split_eq(strlist *dest, const char key, strlist *src, const int src_num)
{
	split_eq(dest, key, src->get(src_num));
}
void split_eq(strlist *dest, const char *key, strlist *src, const int src_num)
{
	split_eq(dest, key, src->get(src_num));
}
void split_eq(strlist *dest, const char key, const int src_num)
{
	string *s = dest->get(src_num);
	char *src = (char*)malloc(s->length + 1);
	memcpy(src, s->text, s->length + 1);
	split_eq(dest, key, src);
	free(src);
}
void split_eq(strlist *dest, const char *key, const int src_num)
{
	string *s = dest->get(src_num);
	char *src = (char*)malloc(s->length + 1);
	memcpy(src, s->text, s->length + 1);
	split_eq(dest, key, src);
	free(src);
}