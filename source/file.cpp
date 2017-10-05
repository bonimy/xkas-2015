#include "file.h"

file_item::~file_item()
{
	if (this->data)
		free(this->data);
}

char	asmpath[MAX_PATH];
char	asmdir[MAX_PATH];
int		dirlen;

list<file_item> files;
file_item fi, *pfi;
int filedepth = 0;

/* get the asm path and working asm directory. */
void initasmpath(const char *path, const char *dir)
{
	/* Get asm directory from asm path if no dir is specified */
	if (!dir)
	{
		dirlen = strrpos(path, '\\') + 1;		//This also works with no directory as NOTFOUND returns -1.
		memcpy(asmdir, path, dirlen);
		asmdir[dirlen] = 0;
	}
	else
	{
		dirlen = 0;
		strcpy(asmdir, dir);
	}

	/* load the main asm file */
	strcpy(asmpath, path + dirlen);
}

/* load file for assembling */
void loadasmfile(const char *path)
{
	if (filedepth == FILE_LIMIT)
		return log(LOG_ERROR, TRUE, TRUE, 2080, "maximum file depth limit reached [%d]", FILE_LIMIT);

	// the real path is relative to the asmdir
	char realpath[MAX_PATH];
	getrealpath(path, realpath);

	// asm files (probably) shouldn't be referenced more than once
	int index = getfilenumber(realpath);
	if (index < files.count)
		return log(LOG_WARNING, TRUE, TRUE, 2030, "asm file referenced more than once [%s]", path);

	// open the asm file
	FILE *src = fopen(realpath, "rb");
	if (!src)
		return log(LOG_ERROR, index, index, 2000, "%s could not be opened", realpath);

	// get the size of the file
	if (fseek(src, 0, SEEK_END))
		return log(LOG_ERROR, index, index, 2001, "%s could not be accessed", realpath);
	int size = ftell(src);
	if (size == -1)
		return log(LOG_ERROR, index, index, 2002, "could not get file size (%s)", realpath);

	// get the previous file number
	*pfi = fi;
		
	// initialize the new file item
	fi = *files.get(index);
	free(fi.data);
	fi.data = (char*)malloc(size + 2);

	// copy the asm path
	strcpy(fi.name, realpath);

	// read the file data
	rewind(src);
	if (fread(fi.data, 1, size, src) != size)
		return log(LOG_ERROR, index, index, 2003, "%s could not be read", realpath);

	// close the file
	if (fclose(src))
		return log(LOG_WARNING, index, index, 2004, "%s could not be closed", realpath);

	// appended a string terminator to the end of the data
	fi.data[size] = '\n';
	fi.data[fi.size = size + 1] = 0;

	// start reading at beginning of file
	fi.start =
	fi.length =
	fi.index =
	fi.linenum =
	fi.blocknum = 0;

	// associate this file item with a file number
	fi.pfile = pfi;

	filedepth++;
}

void returnfromfile()
{
	fi = *fi.pfile;
	filedepth--;
}

void getrealpath(const char* path, char *realpath)
{
	const int len = strisfullpath(path) ? 0 : dirlen;
	memcpy(realpath, asmdir, len);
	strcpy(realpath + len, path);
}

int getfilenumber(const char* path)
{
	for (int i = files.count; i; )
		if (!_stricmp(files[--i]->name, path))
			return i;
	return files.count;
}

void resetasemblyfiles()
{
	files.count = 0;
	filedepth = 0;
	loadasmfile(asmpath);
}

void setstart()
{
	strset(arg);
	SRCSTART = SRCINDEX;
	SRCLENGTH = 0;
}