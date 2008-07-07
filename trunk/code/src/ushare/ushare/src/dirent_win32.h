#ifndef _WIN32_DIRENT_H
#define _WIN32_DIRENT_H

#include <sys/types.h>

struct dirstream
{
  int fd;		/* File descriptor.  */
  char *data;		/* Directory block.  */
  size_t allocation;	/* Space allocated for the block.  */
  size_t size;		/* Total valid data in the block.  */
  size_t offset;	/* Current offset into the block.  */
  off_t filepos;	/* Position of next entry to read.  */
  char *mask;           /* Initial file mask. */
};

struct dirent
{
  long d_ino;
  off_t d_off;
  unsigned short int d_reclen;
  unsigned char d_type;
  char d_name[256];
};

#define d_fileno d_ino /* Backwards compatibility. */

/* This is the data type of directory stream objects.
   The actual structure is opaque to users.  */

typedef struct dirstream DIR;

DIR * opendir (const char * name);
struct dirent * readdir (DIR * dir);
int closedir (DIR * dir);
void rewinddir (DIR * dir);
void seekdir (DIR * dir, off_t offset);
off_t telldir (DIR * dir);
int dirfd (DIR * dir);

#endif /* SCM_WIN32_DIRENT_H */
