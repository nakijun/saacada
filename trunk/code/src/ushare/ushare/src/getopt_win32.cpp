#include <stdio.h>
#include <stddef.h>
#include <ctype.h>
#include <string.h>
#include "getopt_win32.h"

/*
 *
 *  FUNCTION: getopt()
 *
 *	  Get next command line option and parameter
 *	  source gathered from MS examples and modified
 *	  to conform with unix like getopt.
 *
 */

/* Global Exportable */
int optind;
char *optarg;

int getopt (int argc, char** argv, char* pszValidOpts) {
	char chOpt;
	char* psz = NULL;
	char* pszParam = NULL;
	static int iArg = 1;

	if (iArg < argc) {
		psz = &(argv[iArg][0]);
		if (*psz == '-' || *psz == '/') {
			/* we have an option specifier */
			chOpt = argv[iArg][1];
			if (isalnum(chOpt) || ispunct(chOpt)) {
				/* we have an option character */
				psz = strchr(pszValidOpts, chOpt);
				if (psz != NULL) {
					/* option is valid, we want to return chOpt */
					if (psz[1] == ':') {
						/* option can have a parameter */
						psz = &(argv[iArg][2]);
						if (*psz == '\0') {
							/* must look at next argv for param */
							if (iArg+1 < argc) {
								psz = &(argv[iArg+1][0]);
								if (*psz == '-' || *psz == '/') {
									/* next argv is a new option, so param
									 * not given for current option
									*/
									fprintf(stderr, "-%c option requires an argument.\n", chOpt);
									chOpt = '?';
									pszParam = NULL;
								} else {
									/* next argv is the param */
									iArg++;
									pszParam = psz;
								}
							} else {
								/* reached end of args looking for param */
							}
						} else {
							/* param is attached to option */
							pszParam = psz;
						}
					} else {
						/* option is alone, has no parameter */
					}
				} else {
					/* option specified is not in list of valid options */
					fprintf(stderr, "Invalid option -- %c\n", chOpt);
					chOpt = '?';
					pszParam = NULL;
				}
			} else {
				/* though option specifier was given, option character
				 * is not alpha or was was not specified
				 */
				chOpt = 0;
				pszParam = &(argv[iArg][0]);
			}
		} else {
			/* standalone arg given with no option specifier */
			chOpt = -1;
			pszParam = &(argv[iArg][0]);
		}
	} else {
		/* end of argument list */
		chOpt = -1;
	}

	optind = iArg++;
	optarg = pszParam;
	return (chOpt);
}

