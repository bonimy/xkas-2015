#include "statement.h"

int asmode;
int lastasmode;
int argmode;
int readmode;
int allowblock;
BOOL beginstatement = FALSE;

string	*arg = new string(),
		*tempstr1 = new string();