#include "clargs.h"

// Default command-line args
clargs defargs;

// Initialize Default Args: Sets the fallback assembly options
void initdefargs()
{
	// All messages print by default.
	defargs.printmessages =
	defargs.printwarnings =
	defargs.printerrors = TRUE;

	// Default message formats
	defargs.messageformat = new string(LOG_MESSAGEKEY);
	defargs.warningformat =  new string(
		LOG_FILEPREFIX LOG_FILEKEY " (" LOG_LINEKEY ") : " LOG_FILESUFFIX
		"warning" LOG_CODEPREFIX " " LOG_CODEKEY LOG_CODESUFFIX ": " LOG_MESSAGEKEY
		LOG_CMDPREFIX " [" LOG_COMMANDKEY "]" LOG_CMDSUFFIX);
	defargs.errorformat = new string(
		LOG_FILEPREFIX LOG_FILEKEY " (" LOG_LINEKEY ") : " LOG_FILESUFFIX
		"error" LOG_CODEPREFIX " " LOG_CODEKEY LOG_CODESUFFIX ": " LOG_MESSAGEKEY
		LOG_CMDPREFIX " [" LOG_COMMANDKEY "]" LOG_CMDSUFFIX);

	// Clear assembly paths
	defargs.asmdir[0] =
	defargs.asmpath[0] =
	defargs.srcpath[0] =
	defargs.destpath[0] = 0;

	// Clear EXE path
	defargs.exepath[0] = 0;

	// No current assembler uses string escape codes. Disable codes by default.
	defargs.strescape = FALSE;

	// Print to stdout by default.
	defargs.printstderr = FALSE;
	defargs.printstdout = TRUE;
}

/* If command is true, increase args count and continue. */
#define PROCESSCOMMAND(command) if (command) { count++; continue; }

/* Set default argument switches. 
	Returns: Number of switch arguments parsed. */
int setdefargs(int argc, char **argv)
{
	/* Ignore first argument (application path) */
	int count = 1;

	/* Process all command line arguments */
	for (int i = 1; i < argc; i++)
	{		
		PROCESSCOMMAND(getcommandbool(argv[i], CL_PRINTMESSAGES, defargs.printmessages))
		PROCESSCOMMAND(getcommandbool(argv[i], CL_PRINTWARNINGS, defargs.printwarnings))
		PROCESSCOMMAND(getcommandbool(argv[i], CL_PRINTERRORS, defargs.printerrors))
		PROCESSCOMMAND(getcommandtext(argv[i], CL_MESSAGEFORMAT, defargs.messageformat))
		PROCESSCOMMAND(getcommandtext(argv[i], CL_WARNINGFORMAT, defargs.warningformat))
		PROCESSCOMMAND(getcommandtext(argv[i], CL_ERRORFORMAT, defargs.errorformat))
		/* TREAT WARNINGS AS ERRORS */
		PROCESSCOMMAND(getcommandpath(argv[i], CL_DIRECTORY, defargs.asmdir));
		PROCESSCOMMAND(getcommandpath(argv[i], CL_MAINASMPATH, defargs.asmpath));
		PROCESSCOMMAND(getcommandpath(argv[i], CL_SRCROMPATH, defargs.srcpath));
		PROCESSCOMMAND(getcommandpath(argv[i], CL_DESTROMPATH, defargs.destpath));
		/* USE LUNAR COMPRESS */
		/* DISABLE WARNINGS */
		/* INCLUDE WARNINGS */
		PROCESSCOMMAND(getcommandpath(argv[i], CL_EXEPATH, defargs.exepath));
		/* PRINT TEXT */
		PROCESSCOMMAND(getcommandbool(argv[i], CL_STRESCAPE, defargs.strescape));
		PROCESSCOMMAND(getcommandbool(argv[i], CL_PRINTSTDERR, defargs.printstderr));
		PROCESSCOMMAND(getcommandbool(argv[i], CL_PRINTSTDOUT, defargs.printstdout));
	}

	return count;
}

/* Gets a BOOL from a command arg.
	const char *arg:	The argument to inspect
	const char *key:	The key value
	BOOL &command:		The command value of arg
	Returns:			TRUE if command was set (to any value), otherwise FALSE
	Remarks: If arg and key match, or if arg matches key but with an appended '+'
		or '-' char, then command is set to either TRUE (if arg matches key and/or
		has an appended '+' char) or FALSE (if arg matches key with an appended '-')*/
BOOL getcommandbool(const char *arg, const char *key, BOOL &command)
{
	/* Loop through arg string */
	for (int i = 0; arg[i]; i++)
	{
		/* Check for arg/key mismatch */
		if (arg[i] != key[i])
		{
			// Return FALSE if arg does not end one char above key
			if (key[i] || arg[i + 1])
				return FALSE;

			// Inspect last char of arg
			switch (arg[i])
			{
			case '+':	// Set command to TRUE
				command = TRUE;
				return TRUE;
			case '-':	// Set command to FALSE
				command = FALSE;
				return TRUE;
			default:	// Do not set command
				return FALSE;
			}
		}
	}

	/* Strings match: Set command to TRUE */
	command = TRUE;
	return TRUE;
}

/* Gets a string from a command arg.
	Returns: TRUE if the arg passed a string,
	otherwise FALSE. */
BOOL getcommandtext(const char* arg, const char* key, string* command)
{
	/* Match key and arg. */
	if (stribegin(arg, key))
		return FALSE;

	/* Ensure arg starts with a double quote. */
	int ksl = strlen(key);
	if (arg[ksl] != '\"')
		return FALSE;

	/* Ensure arg ends with a double quote. */
	int len = strlen(arg);
	if (arg[len - 1] != '\"')
		return FALSE;
	
	/* Ensure no extra quote chars exist in path string. */
	if (strcount(arg + ksl, '\"') > 2)
	{
		log(LOG_WARNING, FALSE, FALSE, 0, "command line arg error: %s", arg);
		return FALSE;
	}

	/* Copy string. */
	strcpy(command, arg + ksl + 1, len - ksl - 2);
	return TRUE;
}

/* Gets a path string from a command arg.
	Returns: TRUE if the arg passed a path string,
	otherwise FALSE. */
BOOL getcommandpath(const char* arg, const char* key, char command[MAX_PATH])
{
	if (stribegin(arg, key))
		return FALSE;

	/* ensure arg starts with a double quote */
	int ksl = strlen(key);
	if (arg[ksl] != '\"')
		return FALSE;

	/* ensure arg ends with a double quote */
	int len = strlen(arg);
	if (arg[len - 1] != '\"')
		return FALSE;
	
	/* Ensure no extra quote chars exist in path string. */
	if (strcount(arg + ksl, '\"') > 2)
	{
		log(LOG_MESSAGE, FALSE, FALSE, 0, "command line arg error: %s", arg);
		return FALSE;
	}

	/* Copy string. */
	memcpy(command, arg + ksl + 1, len - ksl - 2);
	return TRUE;
}