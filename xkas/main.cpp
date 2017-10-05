#include "../source/xkas.h"

// File.GetPath: Converts a newline string to an empty string (for console input).
inline void fgetp(char path[MAX_PATH])
{
	fgets(path, MAX_PATH, stdin);
	if (!strcmp(path, "\n"))
		*path = 0;
}

// Main entry point of the application.
int main(int argc, char **argv)
{
    // Set default assembly options
    initdefargs();

    // Get command line assembly options
    int count = argc - setdefargs(argc, argv);

#ifdef LUNAR_DLL
    /* Load Lunar Compress DLL (noticable overhead. Use static library one day...) */
    if (!LunarLoadDLL())
    {
        fputs("Could not load Lunar Compress.dll...\n", stderr);
        return -1;
    }
#endif
    CompressTest("C:\\GFX00.bin");
    return 0;

	// Do assembly depending on number of command args.
	switch (count)
	{
	case 4:	// ASM directory specified
		strlencpy(defargs.asmdir, argv[4]);
	case 3:	// Source ROM path specified
		strlencpy(defargs.srcpath, argv[3]);
	case 2: // Output path specified
		strlencpy(defargs.destpath, argv[2]);
	case 1:	// ASM path specified
		strlencpy(defargs.asmpath, argv[1]);
		break;
	default:	// Nothing specified
		// Check if ASM path already exists
		if (*defargs.asmpath)
			break;

		//Show application title.
		puts("xkas v0.06 ~byuu");
		puts("this is an unofficial build by spel werdz rite");
		puts(NULL);
		
		/* Main ASM path */
		fputs("Enter path of main ASM file: ", stdout);
		fgetp(defargs.asmpath);

		/* Destination ROM path */
		fputs("Enter destination path of assembly (Press \"Enter\" to use ASM path as output): ", stdout);
		fgetp(defargs.destpath);

		/* Source ROM path */
		fputs("Enter source ROM to patch to (Press \"Enter\" for no source ROM): ", stdout);
		fgetp(defargs.srcpath);

		/* ASM Directory */
		fputs("Enter directory for relative include files (Press \"Enter\" to use main ASM directory): ", stdout);
		fgetp(defargs.asmdir);

		break;
	}

	/* Initialize the assembly data */
	initialize();

	/* Assemble the data */
	assemble();

#if _DEBUG
		system("pause");
#endif

#ifdef LUNAR_DLL
	/* Unload DLL after application is finished */
	LunarUnloadDLL();
#endif

	return 0;
}