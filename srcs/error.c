//
// Created by s18 on 1/21/17.
//

#include "../hdrs/strace.h"

void	fatal(const char* msg)
{
	fprintf(stderr, "%s : %s : %s\n", PROGRAM_NAME, msg, strerror(errno));
	exit(EXIT_FAILURE);
}