#pragma once

#include "preprocessor.h"

class define_item
{
public:
	string *name;
	string *value;

	define_item();
};

extern BOOL lastdefine;
extern define_item *di;
extern list<define_item> defines;
extern list<file_item>	deftext;
extern int indefine;

define_item *getdefine(string *name);
void adddefine(string *name, string *value);
void processdefine();
void adddefine();
void enterdefine();
void exitdefine();