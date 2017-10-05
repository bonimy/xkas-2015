#include "strmath.h"

int getnum()
{
	int num;
	switch (SRCCHAR)
	{
	case '$':
		SRCINDEX++;
		switch (SRCCHAR)
		{
		case HEXCHAR:
			num = gethexnum();
			break;
		default:
			log(LOG_ERROR, TRUE, TRUE, 0, "not a valid hex number");
			return 0;
		}
		break;
	case '%':
		SRCINDEX++;
		switch (SRCCHAR)
		{
		case BINARYCHAR:
			num = getbinnum();
			break;
		default:
			log(LOG_ERROR, TRUE, TRUE, 0, "not a valid binary number");
			return 0;
		}
	case NUMCHAR:
		num = getdecnum();
		break;
	default:
		log(LOG_ERROR, TRUE, TRUE, 0, "not a valid number");
		return 0;
	}
	return num;
}

int gethexnum()
{
	int r = 0;
	for (; SRCCHAR; SRCINDEX++)
	{
		switch (SRCCHAR)
		{
		case NUMCHAR:
			r <<= 4;
			r |= SRCCHAR - '0';
			break;
		case HEXALPHALWRCHAR:
			r <<= 4;
			r |= SRCCHAR - 'a' + 0xa;
			break;
		case HEXALPHAUPRCHAR:
			r <<= 4;
			r |= SRCCHAR - 'A' + 0xA;
			break;
		default:
			return r;
		}
	}
	return r;
}

int getdecnum()
{
	int r = 0;
	for (; SRCCHAR; SRCINDEX++)
	{
		switch (SRCCHAR)
		{
		case NUMCHAR:
			r *= 10;
			r += SRCCHAR - '0';
			break;
		default:
			return r;
		}
	}
	return r;
}

int getbinnum()
{
	int r = 0;
	for (; SRCCHAR; SRCINDEX++)
	{
		switch (SRCCHAR)
		{
		case '1':
			r <<= 1;
			r |= 1;
			break;
		case '0':
			r <<= 1;
			break;
		default:
			return r;
		}
	}
	return r;
	return r;
}