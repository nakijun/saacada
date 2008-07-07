#include "extension.h"

ssize_t
getline (char **lineptr, size_t *n, FILE *stream)
{
  static char line[256];
  char *ptr;
  ssize_t len;

  if (!lineptr || !n)
    return -1;

  if (ferror (stream))
    return -1;

  if (feof (stream))
    return -1;

  fgets (line, 256, stream);
  ptr = strchr (line, '\n');

  if (ptr)
    *ptr = '\0';

  len = strlen (line);
  if ((len + 1) < 256)
  {
    ptr = (char *)realloc (*lineptr, 256);
    if (!ptr)
      return -1;

    *lineptr = ptr;
    *n = 256;
  }
  strcpy (*lineptr, line);

  return len;
}

 //size_t strnlen (const char *string, size_t maxlen) {
 //  const char *end = (const char *)memchr (string, '\0', maxlen);
 //  return end ? (size_t) (end - string) : maxlen;
 //}
 


char * strndup (const char *s, size_t n) {
   size_t len = strnlen (s, n);
   char *_new = (char *)malloc (len + 1);
 
   if (_new == NULL)
     return NULL;
 
   _new[len] = '\0';
   return (char *) memcpy (_new, s, len);
}

 int scandir(const char *dir, struct dirent ***namelist,
             int (*select)(const struct dirent *),
             int (*compar)(const struct dirent **, const struct dirent **)) {
   DIR *d;
   struct dirent *entry;
   register int i=0;
   size_t entrysize;
 
   if ((d=opendir(dir)) == NULL)
      return(-1);
 
   *namelist=NULL;
   while ((entry=readdir(d)) != NULL)
   {
     if (select == NULL || (select != NULL && (*select)(entry)))
     {
       *namelist=(struct dirent **)realloc((void *)(*namelist),
                  (size_t)((i+1)*sizeof(struct dirent *)));
 	if (*namelist == NULL) return(-1);
 	entrysize=sizeof(struct dirent)-sizeof(entry->d_name)+strlen(entry->d_name)+1;
 	(*namelist)[i]=(struct dirent *)malloc(entrysize);
 	if ((*namelist)[i] == NULL) return(-1);
 	memcpy((*namelist)[i], entry, entrysize);
 	i++;
     }
   }
   if (closedir(d)) return(-1);
   if (i == 0) return(-1);
   if (compar != NULL)
     qsort((void *)(*namelist), (size_t)i, sizeof(struct dirent *), (int (*)(const void*, const void*))compar);
     
   return(i);
 }
 
 int alphasort(const struct dirent **a, const struct dirent **b) {
   return(strcmp((*a)->d_name, (*b)->d_name));
 }

 int pipe(SOCKET socks[2])
{
	struct sockaddr_in addr;
	SOCKET listener;
	int e;
	int addrlen = sizeof(addr);
	//DWORD flags = (make_overlapped ? WSA_FLAG_OVERLAPPED : 0);
	DWORD flags = 0;

	if (socks == 0)
	{
		WSASetLastError(WSAEINVAL);
		return SOCKET_ERROR;
	}

	socks[0] = socks[1] = INVALID_SOCKET;
	if ((listener = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
		return SOCKET_ERROR;

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(0x7f000001);
	addr.sin_port = 0;

	e = bind(listener, (const struct sockaddr*) &addr, sizeof(addr));
	if (e == SOCKET_ERROR)
	{
		e = WSAGetLastError();
		closesocket(listener);
		WSASetLastError(e);
		return SOCKET_ERROR;
	}
	e = getsockname(listener, (struct sockaddr*) &addr, &addrlen);
	if (e == SOCKET_ERROR)
	{
		e = WSAGetLastError();
		closesocket(listener);
		WSASetLastError(e);
		return SOCKET_ERROR;
	}

	do
	{
		if (listen(listener, 1) == SOCKET_ERROR)
			break;
		if ((socks[0] = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, flags))
		        == INVALID_SOCKET)
			break;
		if (connect(socks[0], (const struct sockaddr*) &addr,
		            sizeof(addr)) == SOCKET_ERROR)
			break;
		if ((socks[1] = accept(listener, NULL, NULL))
		        == INVALID_SOCKET)
			break;
		closesocket(listener);

		return 0;
	}
	while (0);

	e = WSAGetLastError();
	closesocket(listener);
	closesocket(socks[0]);
	closesocket(socks[1]);
	WSASetLastError(e);

	return SOCKET_ERROR;
}
