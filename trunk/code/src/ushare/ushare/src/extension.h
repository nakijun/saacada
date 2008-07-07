#ifndef _EXTENSION_H_
#define _EXTENSION_H_

#if defined(_WIN32) || defined(NO_USHARE_MAIN)
enum FILE_TYPE{
	FILE_LOCAL,
	FILE_MEMORY
};
#endif

#ifdef _WIN32

#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "dirent_win32.h"
#include "getopt_win32.h"
#include <winsock2.h>

#define PACKAGE_NAME "uShare"
#define VERSION "1.1a"
#define SYSCONFDIR "D:\\test"
#define PATH_MAX 1024
#ifndef ssize_t
#define ssize_t size_t
#endif
#define MSG_DONTWAIT 0
#define R_OK 4
#define S_ISDIR(mode) (mode&_S_IFDIR)

typedef unsigned long int uint32_t;
typedef int socklen_t;

ssize_t
getline (char **lineptr, size_t *n, FILE *stream);

//size_t strnlen (const char *string, size_t maxlen);

char * strndup (const char *s, size_t n);

int scandir(const char *dir, struct dirent ***namelist,
			int (*select)(const struct dirent *),
			int (*compar)(const struct dirent **, const struct dirent **));

int alphasort(const struct dirent **a, const struct dirent **b);

int pipe(SOCKET socks[2]);

#endif
#endif 
