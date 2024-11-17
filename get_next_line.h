#ifndef GET_NEXT_LINE
# define GET_NEXT_LINE

# include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct double_str
{
	char *pre;
	char *post;
} t_double_str;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

#endif