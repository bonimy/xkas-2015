#include "log.h"

strlist *errors		= new strlist(),
		*warnings	= new strlist(),
		*messages	= new strlist();

string *messageformat = new string(LOG_MESSAGEKEY);
string *errorformat = new string(LOG_FILEPREFIX LOG_FILEKEY " (" LOG_LINEKEY ") : " LOG_FILESUFFIX
	"error" LOG_CODEPREFIX " " LOG_CODEKEY LOG_CODESUFFIX ": " LOG_MESSAGEKEY LOG_CMDPREFIX " [" LOG_COMMANDKEY " ]" LOG_CMDSUFFIX);
string *warningformat = new string(LOG_FILEPREFIX LOG_FILEKEY " (" LOG_LINEKEY ") : " LOG_FILESUFFIX
	"warning" LOG_CODEPREFIX " " LOG_CODEKEY LOG_CODESUFFIX ": " LOG_MESSAGEKEY LOG_CMDPREFIX " [" LOG_COMMANDKEY " ]" LOG_CMDSUFFIX);

int printerrors,
	printwarnings,
	printmessages;

void log(const int dest, const BOOL show, const BOOL infile, const int code, const char *text, ...)
{
	static string* data;
	static string* format;

	switch (dest)
	{
	case LOG_MESSAGE:
		data = messages->get();
		format = messageformat;
		break;
	case LOG_ERROR:
		data = errors->get();
		format = errorformat;
		break;
	case LOG_WARNING:
		data = warnings->get();
		format = warningformat;
		break;
	default:
		return;
	}

	const char *ftext = format->text;
	BOOL write = TRUE;
	int start = 0, i = 0;
	while (ftext[i])
	{
		if (!stribegin(ftext + i, LOG_FILEPREFIX))
		{
			strcat(data, ftext + start, i - start);
			write = infile;
			start = i += strlen(LOG_FILEPREFIX);
		}
		if (!stribegin(ftext + i, LOG_FILESUFFIX))
		{
			write = TRUE;
			start = i += strlen(LOG_FILESUFFIX);
		}
		if (!stribegin(ftext + i, LOG_CODEPREFIX))
		{
			strcat(data, ftext + start, i - start);
			write = code;
			start = i += strlen(LOG_CODEPREFIX);
		}
		if (!stribegin(ftext + i, LOG_CODESUFFIX))
		{
			write = TRUE;
			start = i += strlen(LOG_CODESUFFIX);
		}
		if (!stribegin(ftext + i, LOG_CMDPREFIX))
		{
			strcat(data, ftext + start, i - start);
			write = code;
			start = i += strlen(LOG_CMDPREFIX);
		}
		if (!stribegin(ftext + i, LOG_CMDSUFFIX))
		{
			write = TRUE;
			start = i += strlen(LOG_CMDSUFFIX);
		}
		if (!stribegin(ftext + i,  LOG_FILEKEY))
		{
			// write the file name
			if (write)
			{
				strcat(data, ftext + start, i - start);

				strcat(data, "FILE");
			}
			start = i += strlen(LOG_FILEKEY);
		}
		else if (!stribegin(ftext + i, LOG_LINEKEY))
		{
			// write the line number
			if (write)
			{
				strcat(data, ftext + start, i - start);
				
				strcat(data, "LINE");
			}
			start = i += strlen(LOG_LINEKEY);
		}
		else if (!stribegin(ftext + i, LOG_CODEKEY))
		{
			// write code number
			if (write)
			{
				strcat(data, ftext + start, i - start);
				
				strcat(data, "CODE");
			}
			start = i += strlen(LOG_CODEKEY);
		}
		else if (!stribegin(ftext + i, LOG_MESSAGEKEY))
		{
			// write code number
			if (write)
			{
				strcat(data, ftext + start, i - start);
				
				strcat(data, "MESSAGE");
			}
			start = i += strlen(LOG_MESSAGEKEY);
		}
		else if (!stribegin(ftext + i, LOG_COMMANDKEY))
		{
			// write code number
			if (write)
			{
				strcat(data, ftext + start, i - start);
				
				strcat(data, "COMMAND");
			}
			start = i += strlen(LOG_COMMANDKEY);
		}
		else
			i++;
	}
	strcat(data, ftext + start, i - start);
}

void resetlogdata()
{
	errors->count =
	warnings->count =
	messages->count = 0;
}