#include "char_win32_linux.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <atlbase.h>
#include <atlconv.h>

#include "dirent_win32.h"

DIR *
opendir (const char * name)
{
  DIR *dir;
  HANDLE hnd;
  char *file;
#ifdef UNICODE
  PWCHAR file_w;
#else
  PCHAR file_w;
#endif
  WIN32_FIND_DATA find;

  if (!name || !*name) 
    return NULL;
  file = (char *)malloc (strlen (name) + 3);
  strcpy (file, name);
  if (file[strlen (name) - 1] != SLASH_CHAR)
    strcat (file, SLASH_STR"*");
  else
    strcat (file, "*");
#ifdef UNICODE
  USES_CONVERSION; 
  file_w = A2W(file);
#else
  file_w = file;
#endif
  if ((hnd = FindFirstFile (file_w, &find)) == INVALID_HANDLE_VALUE)
    {
	  GetLastError();
      free (file);
      return NULL;
    }

  dir = (DIR *)malloc (sizeof (DIR));
  dir->mask = file;
  dir->fd = (int) hnd;
  dir->data = (char *)malloc (sizeof (WIN32_FIND_DATA));
  dir->allocation = sizeof (WIN32_FIND_DATA);
  dir->size = dir->allocation;
  dir->filepos = 0;
  memcpy (dir->data, &find, sizeof (WIN32_FIND_DATA));
  return dir;
}

struct dirent *
readdir (DIR * dir)
{
  static struct dirent entry;
  WIN32_FIND_DATA *find;

  entry.d_ino = 0;
  entry.d_type = 0;
  find = (WIN32_FIND_DATA *) dir->data;

  if (dir->filepos)
    {
      if (!FindNextFile ((HANDLE) dir->fd, find))
	return NULL;
    }

  entry.d_off = dir->filepos;
 #ifdef UNICODE
  USES_CONVERSION; 
  char *cFileName_w = W2A(find->cFileName);
#else
  char *cFileName_w = find->cFileName;
#endif
  strcpy (entry.d_name, (const char *)cFileName_w);
  entry.d_reclen = strlen ((const char *)cFileName_w);
  dir->filepos++;
  return &entry;
}

int 
closedir (DIR * dir)
{
  HANDLE hnd = (HANDLE) dir->fd;
  free (dir->data);
  free (dir->mask);
  free (dir);
  return FindClose (hnd) ? 0 : -1;
}

void 
rewinddir (DIR * dir)
{
  HANDLE hnd = (HANDLE) dir->fd;
  WIN32_FIND_DATA *find = (WIN32_FIND_DATA *) dir->data;

  FindClose (hnd);
  hnd = FindFirstFile (dir->mask, find);
  dir->fd = (int) hnd;
  dir->filepos = 0;
}

void 
seekdir (DIR * dir, off_t offset)
{
  off_t n;

  rewinddir (dir);
  for (n = 0; n < offset; n++)
    {
      if (FindNextFile ((HANDLE) dir->fd, (WIN32_FIND_DATA *) dir->data))
	dir->filepos++;
    }
}

off_t 
telldir (DIR * dir)
{
  return dir->filepos;
}

int 
dirfd (DIR * dir)
{
  return dir->fd;
}
