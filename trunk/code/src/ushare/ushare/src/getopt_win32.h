#ifndef __GETOPT_H__
#define __GETOPT_H__

#ifdef __cplusplus
extern "C" {
#endif

static int opterr;		/* if error message should be printed */
static int optind;		/* index into parent argv vector */
static int optopt;		/* character checked for validity */
static int optreset;		/* reset getopt */
static char *optarg;		/* argument associated with option */

struct option
{
  const char *name;
  int has_arg;
  int *flag;
  int val;
};

#define no_argument       0
#define required_argument 1
#define optional_argument 2

int getopt(int, char**, char*);
int getopt_long(int, char**, char*, struct option*, int*);

#ifdef __cplusplus
}
#endif

#endif /* __GETOPT_H__ */
