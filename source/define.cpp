#include "define.h"

BOOL lastdefine;
define_item *di;
list<define_item> defines;
list<file_item>	deftext;
int indefine = 0;

define_item::define_item()
{
	this->name = new string();
	this->value = new string();
}

define_item *getdefine(string *name)
{
	define_item *di;
	for (int i = 0; i < defines.count; i++)
	{
		di = defines.get(i);
		if (!strcmp(di->name, name))
			return di;
	}
	di = defines.get();
	strcpy(di->name, name);
	return di;
}

void enterdefine()
{
	file_item *fi = deftext.get(indefine++);

}

void exitdefine()
{

}