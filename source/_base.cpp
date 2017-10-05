#include "_base.h"

/* returns 0 if str begins with key */
int strbegin(const char *str, const char key)
{
	return *str ^ key;
}
int strbegin(const char *str, const char *key)
{
	for (int i = 0; key[i]; i++)
		if (strbegin(str + i, key[i]))
			return 1;
	return 0;
}
int stribegin(const char *str, const char key)
{
	return UPPER(*str) ^ UPPER(key);
}
int stribegin(const char *str, const char *key)
{
	for (int i = 0; key[i]; i++)
		if (stribegin(str + i, key[i]))
			return 1;
	return 0;
}

/* returns the first occurrance of key in str */
int strpos(const char *str, const char key)
{
	for (int i = 0; str[i]; i++)
		if (!strbegin(str + i, key))
			return i;
	return NOTFOUND;
}
int strpos(const char *str, const char *key, const int ssl, const int ksl)
{
	const int dif = ssl - ksl;
	for (int i = 0; i <= dif; i++)
		if (!memcmp(str + i, key, ksl))
			return i;
	return NOTFOUND;
}
int strpos(const char *str, const char *key)
{
	return strpos(str, key, strlen(str), strlen(key));
}
int stripos(const char *str, const char key)
{
	const char y = UPPER(key);
	for (int i = 0; str[i]; i++)
		if (UPPER(str[i]) == y)
			return i;
	return NOTFOUND;
}
int stripos(const char *str, const char *key, const int ssl, const int ksl)
{
	const int dif = ssl - ksl;
	for (int i = 0; i <= dif; i++)
		if (!stribegin(str + i, key))
			return i;
	return NOTFOUND;
}
int stripos(const char *str, const char *key)
{
	return stripos(str, key, strlen(str), strlen(key));
}

/* returns the last occurrance of key in str */
int strrpos(const char *str, const char key, const int ssl)
{
	for (int i = ssl; i--; )
		if (str[i] == key)
			return i;
	return NOTFOUND;
}
int strrpos(const char *str, const char key)
{
	return strrpos(str, key, strlen(str));
}
int strrpos(const char *str, const char *key, const int ssl, const int ksl)
{
	for (int i = ssl - ksl; i >= 0; i--)
		if (!memcmp(str + i, key, ksl))
			return i;
	return NOTFOUND;
}
int strrpos(const char *str, const char *key)
{
	return strrpos(str, key, strlen(str), strlen(key));
}
int strirpos(const char *str, const char key, const int ssl)
{
	const char y = UPPER(key);
	for (int i = ssl; i--; )
		if (UPPER(str[i]) == y)
			return i;
	return NOTFOUND;
}
int strirpos(const char *str, const char key)
{
	return strirpos(str, key, strlen(str));
}
int strirpos(const char *str, const char *key, const int ssl, const int ksl)
{
	for (int i = ssl - ksl; i >= 0; i--)
		if (!stribegin(str + i, key))
			return i;
	return NOTFOUND;
}
int strirpos(const char *str, const char *key)
{
	return strirpos(str, key, strlen(str), strlen(key));
}

/* returns the number of occurances of key in str */
int strcount(const char *str, const char key)
{
	int n = 0;
	for (int i = 0; str[i]; i++)
		if (str[i] == key)
			n++;
	return n;
}
int strcount(const char *str, const char *key, const int ssl, const int ksl)
{
	const int dif = ssl - ksl;
	int n = 0;
	for (int i = 0; i <= dif; i++)
		if (!strbegin(str + i, key))
			n++;
	return n;
}
int strcount(const char *str, const char *key)
{
	return strcount(str, key, strlen(str), strlen(key));
}
int stricount(const char *str, const char key)
{
	const char y = UPPER(key);
	int n = 0;
	for (int i = 0; str[i]; i++)
		if (UPPER(str[i]) == y)
			n++;
	return n;
}
int stricount(const char *str, const char *key, const int ssl, const int ksl)
{
	const int dif = ssl - ksl;
	int n = 0;
	for (int i = 0; i <= dif; i++)
		if (!stribegin(str + i, key))
			n++;
	return n;
}
int stricount(const char *str, const char *key)
{
	return stricount(str, key, strlen(str), strlen(key));
}

/* checks if str ends with key */
int strend(const char *str, const char key, const int ssl)
{
	return str[ssl - 1] ^ key;
}
int strend(const char *str, const char key)
{
	return strend(str, key, strlen(str));
}
int strend(const char *str, const char *key, const int ssl, const int ksl)
{
	return memcmp(str + (ssl - ksl), key, ksl);
}
int strend(const char *str, const char *key)
{
	return strend(str, key, strlen(str), strlen(key));
}
int striend(const char *str, const char key, const int ssl)
{
	return stribegin(str + (ssl - 1), key);
}
int striend(const char *str, const char key)
{
	return striend(str, key, strlen(str));
}
int striend(const char *str, const char *key, const int ssl, const int ksl)
{
	return stribegin(str + (ssl - ksl), key);
}
int striend(const char *str, const char *key)
{
	return striend(str, key, strlen(str), strlen(key));
}

/* removes all characters between start and end in str */
int strtrim(char *str, const int start, const int end)
{
	int i1 = start, i2 = end;
	while (str[i2])
		str[i1++] = str[i2++];
	str[i1] = 0;
	return i1;
}
int strltrim(char *str, const int start)
{
	int i = 0;
	for (char* c = str + start; c[i]; i++)
		str[i] = c[i];
	str[i] = 0;
	return i;
}
int strrtrim(char *str, const int end, const int ssl)
{
	const int dif = ssl - end;
	str[dif] = 0;
	return dif;
}
int strrtrim(char *str, const int end)
{
	return strrtrim(str, end, strlen(str));
}

/* removes all instances of key from str and
	returns the new length */
int strtrim(char *str, const char key)
{
	int n = 0;
	for (int i = 0; str[i]; i++)
		if (str[i] ^ key)
			str[n++] = str[i];
	str[n] = 0;
	return n;
}
int strtrim(char *str, const char *key, const int ksl)
{
	int n = 0;
	for (int i = 0; str[i]; )
		if (memcmp(str + i, key, ksl))
			str[n++] = str[i++];
		else
			i += ksl;
	str[n] = 0;
	return n;
}
int strtrim(char *str, const char *key)
{
	return strtrim(str, key, strlen(key));
}
int stritrim(char *str, const char key)
{
	const char y = UPPER(key);
	int n = 0;
	for (int i = 0; str[i]; i++)
		if (UPPER(str[i]) ^ y)
			str[n++] = str[i];
	str[n] = 0;
	return n;
}
int stritrim(char *str, const char *key, const int ksl)
{
	int n = 0;
	for (int i = 0; str[i]; )
		if (stribegin(str + i, key))
			str[n++] = str[i++];
		else
			i += ksl;
	str[n] = 0;
	return n;
}
int stritrim(char *str, const char *key)
{
	return stritrim(str, key, strlen(key));
}

/* removes key from beginning of str (if it exists)
	and returns the modified length of str */
int strltrim(char *str, const char key, const int ssl)
{
	if (*str ^ key)
		return ssl;
	const int len = ssl - 1;
	memcpy(str, str + 1, len);
	str[len] = 0;
	return len;
}
int strltrim(char *str, const char key)
{
	return strltrim(str, key, strlen(str));
}
int strltrim(char *str, const char *key, const int ssl, const int ksl)
{
	if (!memcmp(str, key, ksl))
		return ssl;
	const int len = ssl - ksl;
	memcpy(str, str + ksl, len);
	str[len] = 0;
	return len;
}
int strltrim(char *str, const char *key)
{
	return strltrim(str, key, strlen(str), strlen(key));
}
int striltrim(char *str, const char key, const int ssl)
{
	if (UPPER(*str) ^ UPPER(key))
		return ssl;
	const int len = ssl - 1;
	memcpy(str, str + 1, len);
	str[len] = 0;
	return len;
}
int striltrim(char *str, const char key)
{
	return striltrim(str, key, strlen(str));
}
int striltrim(char *str, const char *key, const int ssl, const int ksl)
{
	if (stribegin(str, key))
		return ssl;
	const int len = ssl - ksl;
	memcpy(str, str + ksl, len);
	str[len] = 0;
	return len;
}
int striltrim(char *str, const char *key)
{
	return striltrim(str, key, strlen(str), strlen(key));
}

/* removes key from the end of str (if it exists)
	and returns the modified length of str */
int strrtrim(char *str, const char key, const int ssl)
{
	const int len = ssl - 1;
	if (str[len] ^ key)
		return ssl;
	str[len] = 0;
	return len;
}
int strrtrim(char *str, const char key)
{
	return strrtrim(str, key, strlen(str));
}
int strrtrim(char *str, const char *key, const int ssl, const int ksl)
{
	const int len = ssl - ksl;
	if (memcmp(str + len, key, ksl))
		return ssl;
	str[len] = 0;
	return len;
}
int strrtrim(char *str, const char *key)
{
	return strrtrim(str, key, strlen(str), strlen(key));
}
int strirtrim(char *str, const char key, const int ssl)
{
	const int len = ssl - 1;
	if (UPPER(str[len]) ^ UPPER(key))
		return ssl;
	str[len] = 0;
	return len;
}
int strirtrim(char *str, const char key)
{
	return strirtrim(str, key, strlen(str));
}
int strirtrim(char *str, const char *key, const int ssl, const int ksl)
{
	const int len = ssl - ksl;
	if (stribegin(str + len, key))
		return ssl;
	str[len] = 0;
	return len;
}
int strirtrim(char *str, const char *key)
{
	return strirtrim(str, key, strlen(str), strlen(key));
}

/* replaces all instances of key with token */
void strreplace(char *str, const char key, const char token)
{
	for (int i = 0; str[i]; i++)
		if (str[i] == key)
			str[i] = token;
}

/* parses str as an integer value */
int strbintonum(const char *str)
{
	int r = 0;
	for (int i = 0, x = *str; x; x = str[++i])
	{
		if (x == '1')
			r |= 1;
		else if (x != '0')
			return r;
		r <<= 1;
	}
	return r;
}
int strocttonum(const char *str)
{
	int r = 0;
	for (int i = 0, x = *str; x; x = str[++i])
	{
		if (x >= '0' && x <= '7')
			r |= x - '0';
		else
			return r;
		r <<= 3;
	}
	return r;
}
int strdectonum(const char *str)
{
	int r = 0;
	for (int i = 0, x = *str; x; x = str[++i])
	{
		if (x >= '0' && x <= '9')
			r += x - '0';
		else
			return r;
		r *= 10;
	}
	return r;
}
int strhextonum(const char *str)
{
	int r = 0;
	for (int i = 0, x = UPPER(*str); x; x = UPPER(str[++i]))
	{
		if (x >= '0' && x <= '9')
			r |= x - '0';
		else if (x >= 'A' && x <= 'F')
			r |= x - 'A' + 0x0A;
		else
			return r;
		r <<= 4;
	}
	return r;
}

/* checks if c is a certain type of character */
int strislwr(const char c)
{
	return c >= 'a' && c <= 'z';
}
int strisupr(const char c)
{
	return c >= 'A' && c <= 'Z';
}
int strisalpha(const char c)
{
	return strislwr(c) || strisupr(c);
}
int strisnum(const char c)
{
	return c >= '0' && c <= '9';
}
int strisalphanum(const char c)
{
	return strisalpha(c) || strisnum(c);
}
int strisbin(const char c)
{
	return c == '0' || c == '1';
}
int strisoct(const char c)
{
	return c >= '0' && c <= '7';
}
int strishex(const char c)
{
	const char y = UPPER(c);
	return (y >= 'A' && y <= 'F') || strisnum(c);
}
int strisdeftxt(const char c)
{
	return strisalphanum(c) || c == '_';
}
int strislbltxt(const char c)
{
	return strisalpha(c) || c == '_' || c == '.' || c == '?';
}
int striswhite(const char c)
{
	return c == ' ' || c == '\t' || c == '{' || c == '}';
}

/* common string search functions xkas uses */
int strissquote(const char *str)
{
	return *str == '\'' && str[strlen(str) - 1] == '\'';
}
int strisdquote(const char *str)
{
	return *str == '\"' && str[strlen(str) - 1] == '\"';
}
int strisquote(const char *str)
{
	return (*str == '\'' || *str == '\"') && str[strlen(str) - 1] == *str;
}
int strisrep(const char *str, const char c)
{
	int i = 0;
loop:
	if (str[i] ^ c)
		return NOTFOUND;
	if (str[i])
		return i;
	i++;
	goto loop;
}
	
/* checks if str has a full path format */
int strisfullpath(const char *str)
{
	if (!*str)					//zero-length string
		return 0;
	if (strisalpha(*str))		//volume drive
		return str[1] == ':';
	if (*str == '\\')
		return str[1] == '\\';	//network
	return 0;
}